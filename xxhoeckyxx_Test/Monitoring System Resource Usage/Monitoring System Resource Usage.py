import psutil
import time
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

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

def update_plots(cpu_history, ram_history, network_history):
    cpu_line.set_ydata(cpu_history)
    ram_line.set_ydata(ram_history)
    for interface, line in network_ax.lines.items():
        line.set_ydata(network_history[interface])
    network_ax.set_ylim(
        [0, max(max(network_history.values()), default=0) * 1.1])

def on_slider_change(val):
    global update_interval
    update_interval = val

# Initialisiere Diagramme
history_length = 60
update_interval = 1

fig, (cpu_ax, ram_ax, network_ax) = plt.subplots(
    3, 1, figsize=(10, 8), sharex=True)
fig.subplots_adjust(hspace=0.5, bottom=0.25)

slider_ax = plt.axes([0.25, 0.1, 0.5, 0.03])
slider = Slider(slider_ax, "Update Interval (s)", 0.1, 5, valinit=1, valstep=0.1)
slider.on_changed(on_slider_change)

# Rest of the code remains the same

while plt.fignum_exists(fig.number):
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
    plt.draw()
    plt.pause(0.1)
