import psutil
import time
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

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

def update_data(interval):
    cpu_percent = psutil.cpu_percent(interval=interval)
    ram_percent = psutil.virtual_memory().percent
    network_percent = get_network_usage_percent()
    return cpu_percent, ram_percent, network_percent

network_lines = {}

def update_plots(cpu_history, ram_history, network_history):
    cpu_line.set_ydata(cpu_history)
    ram_line.set_ydata(ram_history)
    for interface, history in network_history.items():
        if interface not in network_lines:
            line, = network_ax.plot(history, label=interface)
            network_lines[interface] = line
        else:
            network_lines[interface].set_ydata(history)
    network_ax.legend()
    network_ax.relim()
    network_ax.autoscale_view()

def on_slider_change(val):
    global update_interval
    update_interval = val

# Initialize plots
history_length = 60
update_interval = 1

# Initialize histories
cpu_history = [0] * history_length
ram_history = [0] * history_length
network_history = {}

# Initialize the Tkinter window
root = tk.Tk()
root.title("Resource Monitor")

fig = Figure(figsize=(10, 8))
cpu_ax = fig.add_subplot(3, 1, 1)
ram_ax = fig.add_subplot(3, 1, 2)
network_ax = fig.add_subplot(3, 1, 3)

# Set up the canvas and add it to the Tkinter window
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

# Set up the plots
# CPU plot
cpu_ax.set_ylim([0, 100])
cpu_ax.set_title('CPU Usage (%)')
cpu_line, = cpu_ax.plot(cpu_history, color='C0', alpha=0.8)

# RAM plot
ram_ax.set_ylim([0, 100])
ram_ax.set_title('RAM Usage (%)')
ram_line, = ram_ax.plot(ram_history, color='C1', alpha=0.8)

# Network plot
network_ax.set_title('Network Usage (%)')

# Time axis
time_labels = [f'-{history_length - i}s' for i in range(history_length)][::-5]
cpu_ax.set_xticks(range(0, history_length, 5))
cpu_ax.set_xticklabels(time_labels)
ram_ax.set_xticks(range(0, history_length, 5))
ram_ax.set_xticklabels(time_labels)
network_ax.set_xticks(range(0, history_length, 5))
network_ax.set_xticklabels(time_labels)

def update():
    global cpu_history, ram_history, network_history
    cpu_percent, ram_percent, network_percent = update_data(update_interval)
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
    canvas.draw()
    root.after(int(update_interval * 1000), update)

# Start updating the plots
update()

# Run the Tkinter main loop
root.mainloop()