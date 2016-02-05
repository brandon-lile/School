from Node import Node
from queue import Queue
from copy import deepcopy
from sys import getsizeof
import time


class Tree:
    def output_goal_state(self, node, time):
        # Print time and path cost
        print(str(time * 1000000) + " microseconds")
        print(node.path_cost)

        # Output the moves
        previous_moves = {}
        output_node = node
        while output_node.parent is not None:
            for i in output_node.actions:
                if i in previous_moves and \
                        previous_moves[i] != output_node.actions[i]:
                    print(str(i) + " ", end="")
                    print(str(output_node.actions[i][1]) + " " +
                          str(output_node.actions[i][0]) + ",", end="")
                    previous_moves[i] = output_node.actions[i]
                else:
                    previous_moves[i] = output_node.actions[i]
            output_node = output_node.parent
        else:
            for i in output_node.actions:
                if i in previous_moves and \
                        previous_moves[i] != output_node.actions[i]:
                    print(str(i) + " ", end="")
                    print(str(output_node.actions[i][1]) + " " +
                          str(output_node.actions[i][0]))

        # Print grid
        for i in node.grid:
            for x in i:
                if x == -1:
                    x = 'e'
                print(str(x) + " ", end="")
            print()

    def generate_nodes(self, node):
        # Loop through the number of movements we need
        moves = {}
        for i, location in node.actions.items():
            x_loc = int(location[0])
            y_loc = int(location[1])
            if self.end_pts[i] != (x_loc, y_loc):
                moves[i] = []

                # Add 1 to x
                if 0 <= x_loc + 1 < self.height and \
                        (node.grid[x_loc + 1][y_loc] == -1 or
                            (x_loc + 1, y_loc) == self.end_pts[i]):
                    moves[i].append((x_loc + 1, y_loc))
                if 0 <= x_loc - 1 < self.height and \
                        (node.grid[x_loc - 1][y_loc] == -1 or
                            (x_loc - 1, y_loc) == self.end_pts[i]):
                    moves[i].append((x_loc - 1, y_loc))
                if 0 <= y_loc + 1 < self.height and \
                        (node.grid[x_loc][y_loc + 1] == -1 or
                            (x_loc, y_loc + 1) == self.end_pts[i]):
                    moves[i].append((x_loc, y_loc + 1))
                if 0 <= y_loc - 1 < self.height and \
                        (node.grid[x_loc][y_loc - 1] == -1 or
                            (x_loc, y_loc - 1) == self.end_pts[i]):
                    moves[i].append((x_loc, y_loc - 1))

        # Go through the moves we have and generate new nodes
        for i in moves:
            if len(moves[i]) > 0:
                for x_loc, y_loc in moves[i]:
                    temp_grid = deepcopy(node.grid)
                    temp_grid[x_loc][y_loc] = str(i)
                    temp_actions = deepcopy(node.actions)
                    temp_actions[i] = (x_loc, y_loc)
                    temp_node = Node(temp_grid, temp_actions, node.path_cost + 1, node)
                    self.frontier.put(temp_node)

    def bfts(self):
        """
        Performs a BFTS on the grid tree was initialized with
        :return:
        """
        complete = False
        start = time.clock()
        while self.frontier.empty() is not True and complete is False:
            # Pull top off frontier
            cur_node = self.frontier.get()

            # Check for goal states
            if cur_node.check_goal_state(self.end_pts, self.num_colors):
                end = time.clock()
                self.output_goal_state(cur_node, end - start)
                complete = True
            else:
                # Generate new nodes
                self.generate_nodes(cur_node)

    def __call__(self):
        return Tree(self)

    def __init__(self, num_colors, height, grid, start_pts, end_pts):
        """
        Tree structure:
        create Nodes, set parent var to Node (can be shared amongst nodes)
        goes backwards up tree
        :param num_colors:
        :param height:
        :param grid:
        :param points:
        :return:
        """
        self.num_colors = num_colors
        self.height = height
        self.root = Node(grid, start_pts, 0, None)

        # Create frontier and add root
        self.frontier = Queue()
        self.frontier.put(self.root)

        # Store the points
        self.start_pts = start_pts
        self.end_pts = end_pts
