#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "./matplotlibcpp.h"

namespace plt = matplotlibcpp;

double getCPUPercent()
{
    // TODO: Implement the CPU usage calculation here
    return 0;
}

double getRAMPercent()
{
    // TODO: Implement the RAM usage calculation here
    return 0;
}

std::map<std::string, std::pair<double, double>> getNetPercent(const std::string &iface)
{
    // TODO: Implement the network usage calculation here
    std::map<std::string, std::pair<double, double>> net_percent;
    return net_percent;
}

int main()
{
    // Initialize the plot with three subplots
    plt::figure();
    plt::title("Real-time Resource Monitor");
    plt::xlabel("Time (s)");
    plt::ylabel("Usage (%)");

    plt::subplot(3, 1, 1);
    plt::title("CPU Usage (%)");

    plt::subplot(3, 1, 2);
    plt::title("RAM Usage (%)");

    plt::subplot(3, 1, 3);
    plt::title("Network Usage (%)");

    // Initialize the history lists
    std::vector<double> cpu_y_vals;
    std::vector<double> ram_y_vals;
    std::map<std::string, std::vector<double>> net_y_vals;

    // Set up the lines in the subplots
    auto cpu_line = plt::plot(std::vector<double>{}, std::vector<double>{}, "b-")[0];
    auto ram_line = plt::plot(std::vector<double>{}, std::vector<double>{}, "g-")[0];

    std::vector<plt::Line2D> net_lines;
    std::vector<std::string> net_colors = {"r-", "c-", "m-", "y-", "k-", "w-"};
    std::vector<std::string> net_ifaces = {"eth0", "lo"};
    for (size_t i = 0; i < net_ifaces.size() && i < net_colors.size(); i++)
    {
        auto iface = net_ifaces[i];
        net_y_vals[iface] = std::vector<double>{};
        auto line = plt::plot(std::vector<double>{}, std::vector<double>{}, net_colors[i])[0];
        net_lines.push_back(line);
    }

    // Start monitoring the system resources
    int duration = 60; // duration to monitor in seconds
    int interval = 1;  // update interval in seconds
    auto start_time = std::chrono::system_clock::now();
    while (true)
    {
        // Check if we have exceeded the specified monitoring duration
        auto end_time = std::chrono::system_clock::now();
        int elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        if (elapsed_time >= duration)
        {
            break;
        }

        // Get the current CPU usage, RAM usage, and network usage percentages
        double cpu_percent = getCPUPercent();
        double ram_percent = getRAMPercent();
        std::map<std::string, std::pair<double, double>> net_percent;
        for (auto iface : net_ifaces)
        {
            net_percent[iface] = getNetPercent(iface);
        }

    // Update the history lists by removing the oldest values and appending the
