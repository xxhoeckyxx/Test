import tkinter as tk
import tkinter.ttk as ttk
import psutil
import time
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Funktionen für das erste Programm (Ressourcenüberwachung)
def get_network_usage_percent():
    old_net_io = psutil.net_io_counters(pernic=True)
    time.sleep(1)
    new_net_io = psutil.net_io_counters(pernic=True)
    network_percent = {}
    for interface, stats in new_net_io.items():
        sent = stats.bytes_sent - old_net_io[interface].bytes_sent
        received = stats.bytes_recv - old_net_io[interface].bytes_recv
        total = sent + received
        network_percent[interface] = total * 8 / 1000000000 * 100
    return network_percent

def update_plots(cpu_history, ram_history, network_history):
    cpu_line.set_ydata(cpu_history)
    ram_line.set_ydata(ram_history)
    network_ax.clear()
    for interface, history in network_history.items():
        network_ax.plot(history, label=interface)
    network_ax.legend(loc='upper left')

    fig.canvas.draw()

def update_resource_monitor():
    cpu_percent = psutil.cpu_percent(interval=1)
    ram_percent = psutil.virtual_memory().percent
    network_percent = get_network_usage_percent()

    cpu_history.pop(0)
    cpu_history.append(cpu_percent)
    ram_history.pop(0)
    ram_history.append(ram_percent)
    for interface, percent in network_percent.items():
        if interface not in network_history:
            network_history[interface] = [0] * history_length
        network_history[interface].pop(0)
        network_history[interface].append(percent)

    update_plots(cpu_history, ram_history, network_history)

    resource_tab.after(1000, update_resource_monitor)

# Funktionen für das zweite Programm (Prozessliste)
def update_process_list():
    process_list.delete(*process_list.get_children())
    for process in psutil.process_iter(['pid', 'name', 'username', 'memory_percent', 'cpu_percent']):
        memory_percent = process.info['memory_percent']
        cpu_percent = process.info['cpu_percent']
        if memory_percent is None:
            memory_percent = 0.0
        if cpu_percent is None:
            cpu_percent = 0.0
        process_list.insert('', 'end', values=(process.info['pid'],
                                               process.info['name'],
                                               process.info['username'],
                                               f"{memory_percent:.1f}",
                                               f"{cpu_percent:.1f}"))
    process_tab.after(1000, update_process_list)

# Hauptfenster und Notebook-Widget
root = tk.Tk()
root.title('System Monitor')
notebook = ttk.Notebook(root)
notebook.pack(expand=True, fill=tk.BOTH)

# Erster Tab: Ressourcenüberwachung
resource_tab = ttk.Frame(notebook)
notebook.add(resource_tab, text='Resource Monitor')

history_length = 60
fig, (cpu_ax, ram_ax, network_ax) = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
fig.subplots_adjust(hspace=0.5)

cpu_history = [0] * history_length
cpu_ax.set_ylim([0, 100])
cpu_ax.set_title('CPU Usage (%)')
cpu_line, = cpu_ax.plot(cpu_history, color='C0', alpha=0.8)

ram_history = [0] * history_length
ram_ax.set_ylim([0, 100])
ram_ax.set_title('RAM Usage (%)')
ram_line, = ram_ax.plot(ram_history, color='C1', alpha=0.8)

network_history = {}
network_ax.set_title('Network Usage (%)')

canvas = FigureCanvasTkAgg(fig, master=resource_tab)
canvas.draw()
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

# Zweiter Tab: Prozessliste
process_tab = ttk.Frame(notebook)
notebook.add(process_tab, text='Process List')

columns = ('PID', 'Name', 'User', 'Memory (%)', 'CPU (%)')
process_list = ttk.Treeview(process_tab, columns=columns, show='headings')
process_list.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

for col in columns:
    process_list.heading(col, text=col)
    process_list.column(col, anchor='w')

scrollbar = ttk.Scrollbar(process_tab, orient='vertical', command=process_list.yview)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
process_list.configure(yscrollcommand=scrollbar.set)

# Starten der Update-Funktionen und Haupt-Event-Loop
update_resource_monitor()
update_process_list()
root.mainloop()
