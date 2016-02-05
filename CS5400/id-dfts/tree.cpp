//
// Created by brandon on 2/3/16.
//

#include "tree.h"

int Tree::m_num_colors = 0;
int Tree::m_dim = 0;

Tree::Tree(const int colors, const int dim, std::vector<std::vector<int>> grid,
           std::vector<int> start, std::vector<int> end)
{
  m_num_colors = colors;
  m_dim = dim;

  // Initialize start pts and end pts
  m_start_pts = start;
  m_end_pts = end;

  // Create the root node
  m_root = new Node(m_start_pts, nullptr, 0, grid);

  // Create the queue
  m_frontier.push(m_root);

  // Initialize at 0 depth
  m_depth = 0;
}

Tree::~Tree()
{
  // Delete all the nodes

}

void Tree::bfts()
{
  // Run while we don't have a goal
  bool goal = false;
  std::clock_t start = std::clock();
  while (!goal)
  {
    // While the goal isn't empty
    while (!m_frontier.empty() && !goal)
    {
      // Pop element and check for goal state
      Node *cur_node = m_frontier.top();
      m_frontier.pop();
      goal = cur_node->checkGoalState(m_end_pts);

      if (!goal)
      {
        generateNodes(cur_node);
      }
      else
      {
        // Get the time taken
        double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

        // Output solution
        printSolution(cur_node, duration);
        printGrid(cur_node);
        goal = true;
      }
    }

    // Increase depth and throw the root back on
    increaseDepth();
    m_frontier.push(m_root);
  }

  return;
}

void Tree::increaseDepth()
{
  m_depth++;
  std::cout << "Increasing depth: " << m_depth << std::endl;
}

void Tree::generateNodes(Node *cur_node)
{
  // Check to see if we can even generate nodes
  int cur_path_cost = cur_node->getPathCost();
  if (cur_path_cost < m_depth)
  {
    // Generate new nodes
    std::vector<int> cur_actions = cur_node->getActions();
    std::vector<int> new_actions;

    // Get the grid
    std::vector<std::vector<int>> cur_grid = cur_node->getGrid();
    int i = 0;
    while (i < m_num_colors)
    {
      int x_loc = cur_actions[i*2];
      int y_loc = cur_actions[i*2 + 1];

      // Check if already in goal state
      if (!(x_loc == m_end_pts[i*2] && y_loc == m_end_pts[i*2 + 1]))
      {
        if ((x_loc - 1 >= 0 && x_loc - 1 < m_dim) &&
            (cur_grid[x_loc - 1][y_loc] == -1 ||
             (x_loc - 1 == m_end_pts[i*2] && y_loc == m_end_pts[i*2 + 1])))
        {
          new_actions.push_back(x_loc - 1);
          new_actions.push_back(y_loc);
        }
        if ((x_loc + 1 >= 0 && x_loc + 1 < m_dim) &&
            (cur_grid[x_loc + 1][y_loc] == -1 ||
             (x_loc + 1 == m_end_pts[i*2] && y_loc == m_end_pts[i*2 + 1])))
        {
          new_actions.push_back(x_loc + 1);
          new_actions.push_back(y_loc);
        }
        if ((y_loc - 1 >= 0 && y_loc - 1 < m_dim) &&
            (cur_grid[x_loc][y_loc - 1] == -1 ||
             (x_loc == m_end_pts[i*2] && y_loc - 1 == m_end_pts[i*2 + 1])))
        {
          new_actions.push_back(x_loc);
          new_actions.push_back(y_loc - 1);
        }
        if ((y_loc + 1 >= 0 && y_loc + 1 < m_dim) &&
            (cur_grid[x_loc][y_loc + 1] == -1 ||
             (x_loc == m_end_pts[i*2] && y_loc + 1 == m_end_pts[i*2 + 1])))
        {
          new_actions.push_back(x_loc);
          new_actions.push_back(y_loc + 1);
        }

        // Generate nodes for all the new colors
        while (new_actions.size() > 0)
        {
          // Generate new actions
          std::vector<int> node_actions = cur_actions;
          int new_x = new_actions[new_actions.size() - 2];
          int new_y = new_actions[new_actions.size() - 1];
          node_actions[i*2] = new_x;
          node_actions[i*2 + 1] = new_y;

          // Change the grid
          std::vector<std::vector<int>> new_grid = cur_grid;
          new_grid[new_x][new_y] = i;

          // Create node and put on stack
          m_frontier.push(new Node(node_actions, cur_node, cur_path_cost + 1, new_grid));

          // Delete the coords we just used
          new_actions.pop_back();
          new_actions.pop_back();
        }
        new_actions.clear();
      }
      i++;
    }
  }

  return;
}

void Tree::printGrid(Node* node) const
{
  std::vector<std::vector<int>> copy_grid = node->getGrid();

  // Output the grid
  std::cout << std::endl;
  for (int i = 0; i < m_dim; i++)
  {
    for (int j = 0; j < m_dim; j++)
    {
      if (copy_grid[j][i] == -1)
        std::cout << "e ";
      else
        std::cout << copy_grid[j][i] << " ";
    }
    std::cout << std::endl;
  }
}

void Tree::printSolution(Node* node, const double duration) const
{
  std::cout << duration * 1000 << " milliseconds" << std::endl;
  std::cout << node->getPathCost() << std::endl;

  // Create a stack so we can print solution in right order
  std::stack<Node*> solution;

  Node* cur_node = node;
  while (cur_node != nullptr)
  {
    solution.push(cur_node);
    cur_node = cur_node->getParent();
  }

  std::vector<int> previous_actions(m_num_colors*2, -1);
  while (solution.size() > 0)
  {
    cur_node = solution.top();
    solution.pop();

    std::vector<int> cur_actions = cur_node->getActions();
    for (int i = 0; i < m_num_colors; i++)
    {
      if ((cur_actions[i*2] != previous_actions[i*2] ||
          cur_actions[i*2 + 1] != previous_actions[i*2 + 1]) &&
          cur_actions != m_start_pts)
      {
        std::cout << i << " " << cur_actions[i*2] << " " << cur_actions[i*2 + 1];
        if (cur_actions != m_end_pts)
          std::cout << ",";
      }
    }
    previous_actions = cur_actions;
  }
}