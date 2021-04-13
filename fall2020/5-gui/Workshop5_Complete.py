# PSU IEEE - 2020
# Workshop 5 Code

import tkinter as tk

class Todo(tk.Tk):
    def __init__(self, tasks=None):
        super().__init__()
# set up code to show 'tasks'
        if not tasks:
            self.tasks = []
        else:
            self.tasks = tasks
# Setting title and size of window
        self.title("To-Do App v1")
        self.geometry("300x400")
# First label at top - static
        todo1 = tk.Label(self, text="--- Add Items Here ---", bg="lightgrey", fg="black", pady=10)
# Add the other labels
        self.tasks.append(todo1)

        for task in self.tasks:
            task.pack(side=tk.TOP, fill=tk.X)
# create textbox for inputting task text
        self.task_create = tk.Text(self, height=3, bg="white", fg="black")
        #calling it this to denote the creation text used
        #put this at the bottom of the window
        self.task_create.pack(side=tk.BOTTOM, fill=tk.X)
        self.task_create.focus_set() #focus will be set on this element so you can type as soon as it opens
# bind the enter key to execute the 'add_task' function
        self.bind("<Return>", self.add_task)
# make alternating color schemes for the to-do list entries
        self.colour_schemes = [{"bg": "lightgrey", "fg": "black"}, {"bg": "grey", "fg": "white"}]
# adding tasks!
    def add_task(self, event=None):
        # get the data from the textbox and clear using '.strip'
        task_text = self.task_create.get(1.0,tk.END).strip()

# we only want a task to be created if there is text in the field
        if len(task_text) > 0:
            new_task = tk.Label(self, text=task_text, pady=10)

            # alternate the color schemes of the tasks
            _, task_style_choice = divmod(len(self.tasks), 2) 

            my_scheme_choice = self.colour_schemes[task_style_choice]

            new_task.configure(bg=my_scheme_choice["bg"])
            new_task.configure(fg=my_scheme_choice["fg"])

            # pack the new task after config
            new_task.pack(side=tk.TOP, fill=tk.X)

            #append new task onto the list!
            self.tasks.append(new_task)
            
        #clear the data of the created task so we can make another
        self.task_create.delete(1.0, tk.END)

# run the main program
if __name__ == "__main__":
    todo = Todo()
    todo.mainloop()
