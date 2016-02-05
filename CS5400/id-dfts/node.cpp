//
// Created by brandon on 2/3/16.
//

#include "node.h"

Node::Node(std::vector<int> actions, Node *parent, const int path_cost,
           std::vector<std::vector<int>>& grid)
{
  m_actions = actions;
  m_parent = parent;
  m_path_cost = path_cost;
  m_grid = grid;
}

bool Node::checkGoalState(const std::vector<int>& end_pts) const
{
  bool goal = false;

  if (m_actions == end_pts)
  {
    goal = true;
  }

  return goal;
}
