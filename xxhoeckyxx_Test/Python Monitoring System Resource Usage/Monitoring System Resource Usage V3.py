import tkinter as tk
import tkinter.ttk as ttk
import psutil

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
    root.after(1000, update_process_list)

root = tk.Tk()
root.title('Task Manager')

frame = ttk.Frame(root, padding="10")
frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

columns = ('PID', 'Name', 'User', 'Memory %', 'CPU %')
process_list = ttk.Treeview(frame, columns=columns, show='headings')

for column in columns:
    process_list.heading(column, text=column)
    process_list.column(column, stretch=True, minwidth=75)

process_list.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

scrollbar = ttk.Scrollbar(frame, orient='vertical', command=process_list.yview)
scrollbar.grid(row=0, column=1, sticky=(tk.N, tk.S))
process_list.configure(yscrollcommand=scrollbar.set)

root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)
frame.columnconfigure(0, weight=1)
frame.rowconfigure(0, weight=1)

update_process_list()
root.mainloop()
