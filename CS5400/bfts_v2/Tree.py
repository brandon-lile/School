from Node import Node
from sys import getsizeof
from queue import Queue
import time
from copy import copy, deepcopy


class Tree:
    def __init__(self, colors, dim, grid, start, end):
        self.colors = colors
        self.dim = dim
        self.grid = grid
        self.start = start
        self.end = end
        self.root = Node(None, start)
        self.frontier = Queue()
        self.frontier.put(self.root)

    def bfts(self):
        complete = False
        start = time.clock()
        while complete is False and self.frontier.empty() is not True:
            # Pull of queue
            cur_node = self.frontier.get()
            # self.print_grid(cur_node)

            # Check for goal state
            if cur_node.check_goal_state(self.end) is True:
                # Goal
                end = time.clock()
                print(end - start)
            else:
                # Generate new nodes
                self.generate_nodes(cur_node)

    def generate_nodes(self, node):
        # Get the history for all colors
        occupied = []
        parent = node
        while parent is not None:
            occupied += parent.actions
            parent = parent.parent

        self.print_grid(node)
        print(occupied)
        new_moves = {}
        for i in range(self.colors):
            new_moves[i] = []
            # Check that we aren't at goal
            if node.actions[i] != self.end[i]:
                # Let's try to make some moves
                x = node.actions[i][0]
                y = node.actions[i][1]

                if ((x - 1, y) not in occupied and 0 <= x - 1 < self.dim) or not (self.grid[x - 1][y] != i):
                    new_moves[i].append((x - 1, y))
                if ((x + 1, y) not in occupied and 0 <= x + 1 < self.dim) or not (self.grid[x + 1][y] != i):
                    new_moves[i].append((x + 1, y))
                if ((x, y - 1) not in occupied and 0 <= y - 1 < self.dim) or not (self.grid[x][y - 1] != i):
                    new_moves[i].append((x, y - 1))
                if ((x, y + 1) not in occupied and 0 <= y + 1 < self.dim) or not (self.grid[x][y + 1] != i):
                    new_moves[i].append((x, y + 1))

        for x in new_moves:
            if len(new_moves[x]) > 0:
                for n in new_moves[x]:
                    # Generate new action
                    new_actions = copy(node.actions)
                    new_actions[x] = n
                    self.frontier.put(Node(node, new_actions))

    def print_grid(self, node):
        grid = deepcopy(self.grid)
        parent = node
        while parent is not None:
            for i in range(self.colors):
                x_loc = parent.actions[i][0]
                y_loc = parent.actions[i][1]
                grid[x_loc][y_loc] = i
            parent = parent.parent

        print(grid)
