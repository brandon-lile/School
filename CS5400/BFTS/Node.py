from sys import getsizeof

class Node:

    def __init__(self, grid, actions, path_cost, parent):
        self.grid = grid
        self.path_cost = path_cost
        self.parent = parent
        self.actions = actions

    def __sizeof__(self):
        total = getsizeof(self.grid) + getsizeof(self.path_cost) + getsizeof(self.actions)
        return total

    def check_goal_state(self, end_pts, num_colors):
        complete_colors = 0
        for i in self.actions:
            if self.actions[i] == end_pts[i]:
                complete_colors += 1
        if complete_colors == num_colors:
            return True
        else:
            return False
