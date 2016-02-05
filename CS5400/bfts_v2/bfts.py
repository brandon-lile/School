from Tree import Tree


def main():
    """
    Gets all the input from the file and then passes it on to the bfts search
    :return:
    """
    start_pts = {}
    end_pts = {}
    puz_file = "puzzle1.txt"
    with open(puz_file) as f:
        height, num_colors = [int(x) for x in f.readline().split()]
        grid = []
        x_loc = 0
        for line in f:
            row = []
            y = 0
            for x in line.split():
                if x != "e":
                    # It's  number so we should analyze it
                    if int(x) in start_pts:
                        end_pts[int(x)] = (int(y), int(x_loc))
                    else:
                        start_pts[int(x)] = (int(y), int(x_loc))
                    row.append(int(x))
                else:
                    row.append(-1)
                y += 1
            grid.append(row)
            x_loc += 1

    # Fix the pts
    start = []
    end = []
    for i in range(num_colors):
        start.append(start_pts[i])
        end.append(end_pts[i])

    tree = Tree(num_colors, height, grid, start, end)
    tree.bfts()


if __name__ == '__main__':
    main()
