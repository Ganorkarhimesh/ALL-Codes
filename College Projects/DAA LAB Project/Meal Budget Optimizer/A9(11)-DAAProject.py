import tkinter as tk
from tkinter import messagebox

root = tk.Tk()
root.title("SmartMeal - Meal Budget Optimizer")
root.geometry("640x560")

items = []

def add_item():
    name = name_entry.get().strip()
    cost_text = cost_entry.get().strip()
    value_text = value_entry.get().strip()
    if not name or not cost_text or not value_text:
        messagebox.showinfo("Error", "Please enter name, cost and value")
        return
    try:
        cost = int(cost_text)
        val = int(value_text)
    except:
        messagebox.showinfo("Error", "Cost and value must be integers")
        return
    items.append((name, cost, val))
    listbox.insert(tk.END, f"{name}  |  Cost: {cost}  |  Value: {val}")
    name_entry.delete(0, tk.END)
    cost_entry.delete(0, tk.END)
    value_entry.delete(0, tk.END)

def clear_items():
    items.clear()
    listbox.delete(0, tk.END)
    result_text.delete(1.0, tk.END)
    budget_entry.delete(0, tk.END)

def optimize():
    if not items:
        messagebox.showinfo("Error", "Add items first")
        return
    budget_text = budget_entry.get().strip()
    try:
        budget = int(budget_text)
        if budget < 0:
            raise ValueError
    except:
        messagebox.showinfo("Error", "Enter a valid non-negative integer budget")
        return
    n = len(items)
    dp = [[0] * (budget + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        name, cost, val = items[i - 1]
        for w in range(budget + 1):
            if cost <= w:
                take = val + dp[i - 1][w - cost]
                notake = dp[i - 1][w]
                dp[i][w] = take if take > notake else notake
            else:
                dp[i][w] = dp[i - 1][w]
    w = budget
    chosen = []
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i - 1][w]:
            name, cost, val = items[i - 1]
            chosen.append((name, cost, val))
            w -= cost
            if w <= 0:
                break
    chosen.reverse()
    result_text.delete(1.0, tk.END)
    if not chosen:
        result_text.insert(tk.END, "No items can be selected within the given budget.\n")
        return
    total_cost = sum(x[1] for x in chosen)
    total_value = sum(x[2] for x in chosen)
    result_text.insert(tk.END, "Selected Items:\n\n")
    for it in chosen:
        result_text.insert(tk.END, f"{it[0]}    Cost: {it[1]}    Value: {it[2]}\n")
    result_text.insert(tk.END, f"\nTotal Cost: {total_cost}\n")
    result_text.insert(tk.END, f"Total Value: {total_value}\n")

title_label = tk.Label(root, text="SmartMeal - Meal Budget Optimizer", font=("Helvetica", 16))
title_label.pack(pady=10)

input_frame = tk.Frame(root)
input_frame.pack(pady=6)

tk.Label(input_frame, text="Item Name").grid(row=0, column=0, padx=6)
tk.Label(input_frame, text="Cost").grid(row=0, column=1, padx=6)
tk.Label(input_frame, text="Value").grid(row=0, column=2, padx=6)

name_entry = tk.Entry(input_frame, width=28)
cost_entry = tk.Entry(input_frame, width=10)
value_entry = tk.Entry(input_frame, width=10)

name_entry.grid(row=1, column=0, padx=6, pady=4)
cost_entry.grid(row=1, column=1, padx=6, pady=4)
value_entry.grid(row=1, column=2, padx=6, pady=4)

add_btn = tk.Button(input_frame, text="Add Item", width=12, command=add_item)
add_btn.grid(row=1, column=3, padx=8)

listbox_frame = tk.Frame(root)
listbox_frame.pack(pady=8)

listbox = tk.Listbox(listbox_frame, width=80, height=8)
listbox.pack(side=tk.LEFT, padx=(6,0))

scrollbar = tk.Scrollbar(listbox_frame, orient=tk.VERTICAL)
scrollbar.config(command=listbox.yview)
listbox.config(yscrollcommand=scrollbar.set)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y, padx=(0,6))

budget_frame = tk.Frame(root)
budget_frame.pack(pady=8)

tk.Label(budget_frame, text="Enter Budget").grid(row=0, column=0, padx=6)
budget_entry = tk.Entry(budget_frame, width=15)
budget_entry.grid(row=0, column=1, padx=6)

opt_btn = tk.Button(budget_frame, text="Optimize", width=12, command=optimize)
opt_btn.grid(row=0, column=2, padx=8)

clear_btn = tk.Button(budget_frame, text="Clear All", width=12, command=clear_items)
clear_btn.grid(row=0, column=3, padx=8)

result_text = tk.Text(root, width=80, height=12)
result_text.pack(pady=10)

root.mainloop()
