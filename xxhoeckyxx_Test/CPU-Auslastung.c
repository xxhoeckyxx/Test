#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <ncurses.h>

int main()
{
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();

    // Define colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);

    while (1)
    {
        // Clear screen
        clear();

        // Get total memory
        long mem;
        size_t len = sizeof(mem);
        sysctlbyname("hw.memsize", &mem, &len, NULL, 0);

        // Get CPU usage
        processor_info_array_t cpuinfo;
        mach_msg_type_number_t count;
        natural_t numCPUs;
        kern_return_t err = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &numCPUs, (processor_info_array_t *)&cpuinfo, &count);
        if (err != KERN_SUCCESS)
        {
            fprintf(stderr, "Failed to get CPU usage info.\n");
            exit(EXIT_FAILURE);
        }
        double cpu = ((cpuinfo[CPU_STATE_USER] + cpuinfo[CPU_STATE_SYSTEM] + cpuinfo[CPU_STATE_NICE]) / (double)(cpuinfo[CPU_STATE_USER] + cpuinfo[CPU_STATE_SYSTEM] + cpuinfo[CPU_STATE_NICE] + cpuinfo[CPU_STATE_IDLE])) * 100.0;
        vm_deallocate(mach_task_self(), (vm_offset_t)cpuinfo, count * sizeof(int));

        // Get memory usage
        vm_size_t page_size;
        mach_port_t mach_port;
        mach_msg_type_number_t count1;
        vm_statistics64_data_t vm_stats;

        mach_port = mach_host_self();
        count1 = sizeof(vm_stats) / sizeof(natural_t);
        if (KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO64, (host_info64_t)&vm_stats, &count1))
        {
            page_size = vm_page_size;
            long used_memory = (long)(vm_stats.active_count + vm_stats.inactive_count + vm_stats.wire_count) * page_size / (1024 * 1024);
            long free_memory = (long)vm_stats.free_count * page_size / (1024 * 1024);
            mvprintw(0, 0, "Memory Usage: %ld/%ld MB", used_memory, (used_memory + free_memory));
        }
        else
        {
            mvprintw(0, 0, "Failed to get memory usage info.");
        }

        // Get disk activity
        long reads, writes;
        FILE *fp = popen("iostat -d disk0", "r");
        fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %ld %*s %*s %*s %*s %ld", &reads, &writes);
        pclose(fp);

        // Get window size
        int maxx, maxy;
        getmaxyx(stdscr, maxy, maxx);

        // Print CPU usage bar
        attron(COLOR_PAIR(1));
        int cpu_bar_length = (int)((double)maxx * 0.75);
        mvhline(maxy / 2, maxx / 2 - cpu_bar_length / 2, ' ', cpu_bar_length);
        mvhline(maxy / 2, maxx / 2 - cpu_bar_length / 2, ACS_CKBOARD, (int)(cpu * ((double)cpu_bar_length / 100.0)));
        attroff(COLOR_PAIR(1));
        mvprintw(maxy / 2 + 1, maxx / 2 - 8, "CPU Usage: %.2f%%", cpu);

        // Print memory usage bar
        int memory_bar_length = (int)((double)maxx * 0.75);
        long used_memory = (long)(vm_stats.active_count + vm_stats.inactive_count + vm_stats.wire_count) * page_size / (1024 * 1024);
        long free_memory = (long)vm_stats.free_count * page_size / (1024 * 1024);
        long total_memory = used_memory + free_memory;
        attron(COLOR_PAIR(2));
        mvvline(maxy / 2 - 10, maxx / 2 + memory_bar_length / 2 + 1, ' ', 20);
        mvvline(maxy / 2 - 10 + (int)(((double)used_memory / (double)total_memory) * 20), maxx / 2 + memory_bar_length / 2 + 1, ACS_CKBOARD, 20 - (int)(((double)used_memory / (double)total_memory) * 20));
        attroff(COLOR_PAIR(2));
        mvprintw(maxy / 2 - 9, maxx / 2 - 13, "Memory Usage: %ld/%ld MB", used_memory, total_memory);

        // Print disk activity
        mvprintw(maxy / 2 + 3, maxx / 2 - 23, "Disk Activity: %ld reads/s, %ld writes/s", reads, writes);

        // Refresh screen
        refresh();

        // Sleep for 1 second
        sleep(1);
    }

    // Clean up ncurses
    endwin();

    return 0;
}
