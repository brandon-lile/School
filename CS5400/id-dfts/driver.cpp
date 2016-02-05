#include "driver.h"
using namespace std;

int main()
{
  int dim;
  int colors;
  std::vector<std::vector<int>> grid;
  std::vector<int> start_pts;
  std::vector<int> end_pts;

  std::string filename;
  std::cout << "Enter the filename of the puzzle to solve: ";
  std::cin >> filename;

  std::ifstream puz_file(filename, ifstream::in);
  if (!puz_file.eof())
  {
    // Get dim and colors
    puz_file >> dim;
    puz_file >> colors;

    // Initialize the start/end pts and grid
    grid.resize(dim, std::vector<int>(dim, -1));
    start_pts.resize(dim, -1);
    end_pts.resize(dim, -1);

    // Get the grid
    int i = 0;
    while (i < dim)
    {
      int j = 0;
      while (j < dim)
      {
        char tmp;
        puz_file >> tmp;
        if (tmp != 'e')
        {
          tmp = tmp - '0';
          grid[j][i] = tmp;

          // Check if in start pts
          if (start_pts[tmp*2] != -1)
          {
            // Put in end_pts
            end_pts[tmp*2] = j;
            end_pts[tmp*2 + 1] = i;
          }
          else
          {
            start_pts[tmp*2] = j;
            start_pts[tmp*2 + 1] = i;
          }
        }
        j++;
      }
      i++;
    }
  }
  puz_file.close();


  Tree tree(colors, dim, grid, start_pts, end_pts);
  tree.bfts();

  return 0;
}