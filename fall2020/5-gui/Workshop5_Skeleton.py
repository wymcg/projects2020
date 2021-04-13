# PSU IEEE - 2020
# Workshop 5 Code

import tkinter as tk

class Todo(tk.Tk):
    def __init__(self, tasks=None):
        super().__init__()
# set up code to show 'tasks'
        if not tasks:
            
        else:
            
# Setting title and size of window
        
        
# First label at top - static
        todo1 = tk.Label(self,...)
# Add the other labels
        

        for task in self.tasks:
            task.pack(side=tk.TOP, fill=tk.X)
# create textbox for inputting task text
        self.task_create = tk.Text(self, height=3, bg="white", fg="black")
        #calling it this to denote the creation text used
        #put this at the bottom of the window
        
         #focus will be set on this element upon launch
# bind the enter key to execute the 'add_task' function
        
# make alternating color schemes for the to-do list entries
        self.colour_schemes = [{"bg": "lightgrey", "fg": "black"}, {"bg": "grey", "fg": "white"}]
# adding tasks!
    def add_task(self, event=None):
        # get the data from the textbox and clear using '.strip'
        

# we only want a task to be created if there is text in the field
        if len(task_text) > 0:
            

            # alternate the color schemes of the tasks
            _, task_style_choice = divmod(len(self.tasks), 2) 

            my_scheme_choice = self.colour_schemes[task_style_choice]

            new_task.configure(bg=my_scheme_choice["bg"])
            new_task.configure(fg=my_scheme_choice["fg"])

            # pack the new task after config
            

            #append new task onto the list!
            
            
        #clear the data of the created task so we can make another
        

# run the main program
if __name__ == "__main__":
    todo = Todo()
    todo.mainloop()
