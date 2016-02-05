from Tree import Tree


def main():
    """
    Gets all the input from the file and then passes it on to the bfts search
    :return:
    """
    start_pts = {}
    end_pts = {}
    puz_file = input("Name of the puzzle file: ")
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
                    if str(x) in start_pts:
                        end_pts[x] = (int(x_loc), int(y))
                    else:
                        start_pts[x] = (int(x_loc), int(y))
                    row.append(x)
                else:
                    row.append(-1)
                y += 1
            grid.append(row)
            x_loc += 1

    tree = Tree(num_colors, height, grid, start_pts, end_pts)
    tree.bfts()


if __name__ == '__main__':
    main()
