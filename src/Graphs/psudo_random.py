from tkinter import *
import math

class Graph:
    def __init__(self, master, width, height):
        self.width = width
        self.height = height

        self.frame = 40
        self.dot_size = 2

        self.name = ""
        self.x_name = ""
        self.y_name = ""

        self.canvas = Canvas(master, bg="#333333", width=width, height=height)
        self.canvas.place(x=20, y=20)

    def plot(self, xs, ys):
        self.canvas.delete("all")
        self.canvas.create_text(10, 15, anchor=W, font="Purisa", text=self.name, fill="#cccccc")
        self.canvas.create_text(self.frame + 10, self.frame, anchor=N, font="Purisa", text=self.y_name, fill="#cccccc")
        self.canvas.create_text(self.width - self.frame, self.height - self.frame, anchor=S, font="Purisa", text=self.x_name, fill="#cccccc")

        self.canvas.create_line(self.frame, self.frame * 2, self.frame, self.height - self.frame, fill="#cccccc")
        self.canvas.create_line(self.frame, self.height - self.frame, self.width - self.frame * 2, self.height - self.frame, fill="#cccccc")
        self.canvas.create_line(self.frame, self.frame * 2, self.width - self.frame * 2, self.frame * 2, fill="#cccccc")
        self.canvas.create_line(self.width - self.frame * 2, self.height - self.frame, self.width - self.frame * 2, self.frame * 2, fill="#cccccc")

        scale_x = (self.width - self.frame * 3) / max(xs)
        scale_y = (self.height - self.frame * 3) / max(ys)

        for i in range(len(xs)):
            x = xs[i] * scale_x + self.frame
            y = self.height - (ys[i] * scale_y + self.frame)

            self.canvas.create_oval(x - self.dot_size, y - self.dot_size, x + self.dot_size, y + self.dot_size, width=0, fill="#cccccc")


master = Tk()
master.title("Points")
master.geometry("1000x600")

graph = Graph(master, 500, 500)

graph_len = 10
graph_seed = 1
graph_slope = 5

def update_graph():
    graph.name = "Graph y(x) "
    graph.x_name = "x"
    graph.y_name = "y"

    tanble_len = int(math.pow(2, graph_len))

    grph_xs = [x for x in range(0, tanble_len)]
    grph_ys = []

    idx = 0
    for i in grph_xs:
        grph_ys.append(idx)
        idx = (idx * graph_slope + graph_seed) % tanble_len

    graph.plot(grph_xs, grph_ys)

    grph_ys.sort()
    rep = False
    for i in range(len(grph_ys) - 1):
        if grph_ys[i + 1] - grph_ys[i] != 1:
            rep = True
    if rep:
        x = Label(master, text="repeating")
        x.place(x=100, y=500)
    else:
        x = Label(master, text="not repeating")
        x.place(x=100, y=500)

def set_graph_len(val):
    global graph_len
    graph_len = int(val)
    update_graph()


def set_graph_seed(val):
    global graph_seed
    graph_seed = int(val)
    update_graph()


def set_graph_slope(val):
    global graph_slope
    graph_slope = int(val)
    update_graph()


seed = Scale(master, from_=0, to=10, orient=HORIZONTAL, command=set_graph_seed, label="seed")
seed.place(x=600, y=100)

slope = Scale(master, from_=0, to=50, orient=HORIZONTAL, command=set_graph_slope, label="slope")
slope.place(x=600, y=170)

w = Scale(master, from_=0, to=65, orient=HORIZONTAL, command=set_graph_len, label="len")
w.place(x=600, y=30)




mainloop()