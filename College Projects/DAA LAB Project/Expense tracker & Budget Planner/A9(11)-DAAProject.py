import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from operator import itemgetter


class ExpenseManager:
    def __init__(self):
        self.expenses = []

    def add_expense(self, name, cost, priority):
        try:
            cost = float(cost)
            priority = int(priority)
            if cost <= 0 or priority <= 0:
                return "Cost and Priority must be positive numbers."

            self.expenses.append({
                'name': name,
                'cost': cost,
                'priority': priority,
                'ratio': cost / priority
            })
            return "Success"
        except ValueError:
            return "Invalid input for Cost or Priority."

    def sort_expenses(self):
        self.expenses.sort(key=itemgetter('cost'))

    def binary_search_cost(self, target_cost):
        self.sort_expenses()

        try:
            target = float(target_cost)
        except ValueError:
            return "Invalid input. Cost must be a number."

        low = 0
        high = len(self.expenses) - 1
        found_indices = []

        while low <= high:
            mid = (low + high) // 2
            current_cost = self.expenses[mid]['cost']

            if current_cost == target:
                # Find all occurrences
                i = mid
                while i >= 0 and self.expenses[i]['cost'] == target:
                    found_indices.append(i)
                    i -= 1

                j = mid + 1
                while j < len(self.expenses) and self.expenses[j]['cost'] == target:
                    found_indices.append(j)
                    j += 1

                found_indices = sorted(list(set(found_indices)))
                return found_indices

            elif current_cost < target:
                low = mid + 1
            else:
                high = mid - 1

        return None

    def greedy_budget_planner(self, budget_limit):
        try:
            budget = float(budget_limit)
            if budget <= 0:
                return "Budget must be a positive number."
        except ValueError:
            return "Invalid input for Budget."

        # The DAA: Greedy Choice Property based on maximizing utility (Priority) per cost.
        # Ratio is cost/priority. We want the LOWEST ratio (best value).
        sorted_expenses = sorted(self.expenses, key=itemgetter('ratio'))

        recommended_expenses = []
        current_cost = 0.0

        for expense in sorted_expenses:
            if current_cost + expense['cost'] <= budget:
                current_cost += expense['cost']
                recommended_expenses.append(expense)
            else:
                break

        return recommended_expenses, current_cost


class ExpenseApp:
    def __init__(self, master):
        self.manager = ExpenseManager()
        self.master = master
        master.title("DAA Expense Planner")
        master.geometry("850x600")
        master.configure(bg="#f4f4f9")

        style = ttk.Style()
        style.theme_create("HumanTheme", parent="alt", settings={
            "TLabel": {"configure": {"font": ('Inter', 10), "background": "#f4f4f9"}},
            "TButton": {"configure": {"font": ('Inter', 10, 'bold'), "background": "#6c63ff", "foreground": "white",
                                      "padding": 8},
                        "map": {"background": [("active", "#5a50e8")]}},
            "TFrame": {"configure": {"background": "#f4f4f9"}},
            "TNotebook": {"configure": {"background": "#f4f4f9"}},
            "TNotebook.Tab": {"configure": {"font": ('Inter', 10, 'bold'), "padding": [10, 5], "background": "#ddd"}},
            "Treeview": {"configure": {"font": ('Inter', 10), "rowheight": 25}},
            "TEntry": {"configure": {"fieldbackground": "white"}}
        })
        style.theme_use("HumanTheme")

        self.notebook = ttk.Notebook(master)
        self.notebook.pack(pady=10, padx=10, fill="both", expand=True)

        self.input_frame = ttk.Frame(self.notebook, padding="15 15 15 15")
        self.output_frame = ttk.Frame(self.notebook, padding="15 15 15 15")

        self.notebook.add(self.input_frame, text="Add & Analyze")
        self.notebook.add(self.output_frame, text="Expense List")

        self.setup_input_ui()
        self.setup_output_ui()

    def setup_input_ui(self):
        input_title = ttk.Label(self.input_frame, text="Add New Expense (Cost & Priority are DAA Inputs)",
                                font=('Inter', 12, 'bold'), background="#f4f4f9")
        input_title.grid(row=0, column=0, columnspan=2, pady=(0, 15), sticky="w")

        ttk.Label(self.input_frame, text="Name:").grid(row=1, column=0, padx=5, pady=5, sticky="w")
        self.name_entry = ttk.Entry(self.input_frame, width=30)
        self.name_entry.grid(row=1, column=1, padx=5, pady=5, sticky="ew")

        ttk.Label(self.input_frame, text="Cost ($):").grid(row=2, column=0, padx=5, pady=5, sticky="w")
        self.cost_entry = ttk.Entry(self.input_frame, width=30)
        self.cost_entry.grid(row=2, column=1, padx=5, pady=5, sticky="ew")

        ttk.Label(self.input_frame, text="Priority (1-10):").grid(row=3, column=0, padx=5, pady=5, sticky="w")
        self.priority_entry = ttk.Entry(self.input_frame, width=30)
        self.priority_entry.grid(row=3, column=1, padx=5, pady=5, sticky="ew")

        add_button = ttk.Button(self.input_frame, text="Add Expense", command=self.add_expense_ui)
        add_button.grid(row=4, column=0, columnspan=2, pady=10, sticky="ew")

        # DAA/Algorithm Section
        alg_frame = ttk.Frame(self.input_frame, padding="10", relief="groove", borderwidth=1)
        alg_frame.grid(row=5, column=0, columnspan=2, pady=20, sticky="ew")

        ttk.Label(alg_frame, text="Search (Binary Search)", font=('Inter', 10, 'bold')).grid(row=0, column=0, padx=5,
                                                                                             pady=5, sticky="w")
        self.search_entry = ttk.Entry(alg_frame, width=15)
        self.search_entry.grid(row=0, column=1, padx=5, pady=5, sticky="ew")
        search_button = ttk.Button(alg_frame, text="Run Search", command=self.run_search_ui)
        search_button.grid(row=0, column=2, padx=5, pady=5)
        self.search_result_label = ttk.Label(alg_frame, text="", wraplength=300)
        self.search_result_label.grid(row=1, column=0, columnspan=3, padx=5, pady=5, sticky="w")

        ttk.Separator(alg_frame, orient="horizontal").grid(row=2, column=0, columnspan=3, sticky="ew", pady=10)

        ttk.Label(alg_frame, text="Budget (Greedy Knapsack)", font=('Inter', 10, 'bold')).grid(row=3, column=0, padx=5,
                                                                                               pady=5, sticky="w")
        self.budget_entry = ttk.Entry(alg_frame, width=15)
        self.budget_entry.grid(row=3, column=1, padx=5, pady=5, sticky="ew")
        budget_button = ttk.Button(alg_frame, text="Plan Budget", command=self.run_budget_ui)
        budget_button.grid(row=3, column=2, padx=5, pady=5)

        self.input_frame.columnconfigure(1, weight=1)

    def setup_output_ui(self):
        columns = ("Name", "Cost", "Priority", "Ratio (C/P)")
        self.tree = ttk.Treeview(self.output_frame, columns=columns, show="headings")
        self.tree.pack(side="left", fill="both", expand=True)

        for col in columns:
            self.tree.heading(col, text=col, anchor="w")
            self.tree.column(col, anchor="w", width=100 if col != "Name" else 200)

        self.scrollbar = ttk.Scrollbar(self.output_frame, orient="vertical", command=self.tree.yview)
        self.scrollbar.pack(side="right", fill="y")
        self.tree.configure(yscrollcommand=self.scrollbar.set)

        self.update_display()

    def update_display(self):
        for item in self.tree.get_children():
            self.tree.delete(item)

        for expense in self.manager.expenses:
            values = (
                expense['name'],
                f"${expense['cost']:.2f}",
                expense['priority'],
                f"{expense['ratio']:.2f}"
            )
            self.tree.insert("", tk.END, values=values)

    def add_expense_ui(self):
        name = self.name_entry.get()
        cost = self.cost_entry.get()
        priority = self.priority_entry.get()

        if not name or not cost or not priority:
            messagebox.showerror("Input Error", "All fields must be filled.")
            return

        result = self.manager.add_expense(name, cost, priority)

        if result == "Success":
            self.name_entry.delete(0, tk.END)
            self.cost_entry.delete(0, tk.END)
            self.priority_entry.delete(0, tk.END)
            self.update_display()
            self.notebook.select(self.output_frame)
        else:
            messagebox.showerror("Data Error", result)

    def run_search_ui(self):
        target_cost = self.search_entry.get()
        if not target_cost:
            self.search_result_label.config(text="Please enter a cost to search.")
            return

        search_result = self.manager.binary_search_cost(target_cost)

        if search_result is None or search_result == []:
            self.search_result_label.config(
                text=f"Cost ${target_cost} not found. List must be sorted first for Binary Search to be efficient.")
        elif isinstance(search_result, str):
            self.search_result_label.config(text=search_result, foreground="red")
        else:
            found_names = [self.manager.expenses[i]['name'] for i in search_result]
            self.search_result_label.config(
                text=f"Binary Search Found {len(search_result)} item(s) with cost ${target_cost}: {', '.join(found_names)}.",
                foreground="#0077b6")
            self.search_result_label.config(foreground="#0077b6")

    def run_budget_ui(self):
        budget_limit = self.budget_entry.get()

        if not budget_limit:
            messagebox.showerror("Input Error", "Please enter a budget amount.")
            return

        recommendations, total_cost = self.manager.greedy_budget_planner(budget_limit)

        if isinstance(recommendations, str):
            messagebox.showerror("Budget Error", recommendations)
            return

        budget_window = tk.Toplevel(self.master)
        budget_window.title(f"Greedy Budget Plan (${budget_limit})")
        budget_window.geometry("500x400")
        budget_window.configure(bg="#e9ecef")

        if not recommendations:
            ttk.Label(budget_window, text="No expenses fit within the budget limit or the list is empty.",
                      font=('Inter', 12), background="#e9ecef").pack(padx=20, pady=20)
            return

        ttk.Label(budget_window, text="Recommended Expenses (Greedy Choice: Maximize Priority/Cost)",
                  font=('Inter', 11, 'bold'), background="#e9ecef").pack(padx=20, pady=(10, 5), anchor="w")

        columns = ("Name", "Cost", "Priority")
        reco_tree = ttk.Treeview(budget_window, columns=columns, show="headings")
        reco_tree.pack(fill="both", expand=True, padx=20, pady=5)

        for col in columns:
            reco_tree.heading(col, text=col, anchor="w")
            reco_tree.column(col, anchor="w", width=120 if col != "Name" else 150)

        for expense in recommendations:
            values = (
                expense['name'],
                f"${expense['cost']:.2f}",
                expense['priority']
            )
            reco_tree.insert("", tk.END, values=values)

        ttk.Label(budget_window, text=f"Total Cost of Recommendations: ${total_cost:.2f} (Budget Used)",
                  font=('Inter', 11, 'bold'), foreground="#2a9d8f", background="#e9ecef").pack(padx=20, pady=(10, 20),
                                                                                               anchor="w")


if __name__ == "__main__":
    root = tk.Tk()
    app = ExpenseApp(root)
    root.mainloop()