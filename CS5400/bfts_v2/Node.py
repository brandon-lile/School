from sys import getsizeof


class Node:
    def __init__(self, parent, actions):
        self.parent = parent
        self.actions = actions

    def __sizeof__(self):
        total = getsizeof(self.parent) + getsizeof(self.actions)
        return total

    def check_goal_state(self, end):
        total = 0
        complete = 0
        for i in self.actions:
            #print(i, end="")
            #print(" ", end="")
            #print(end[total], end="")
            #print(" : ")
            if i == end[total]:
                complete += 1
            total += 1

        #print(str(complete) + " ", end="")
        #print(total)
        #print()
        if complete == total:
            return True
        else:
            return False
