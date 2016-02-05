//
// Created by brandon on 2/3/16.
//

#ifndef ID_DFTS_NODE_H
#define ID_DFTS_NODE_H
#include <vector>
#include <iostream>

class Node
{
  public:
    Node(std::vector<int> actions, Node *parent, const int path_cost, std::vector<std::vector<int>>& grid);
    ~Node();
    bool checkGoalState(const std::vector<int>& end_pts) const;
    int& getPathCost() { return m_path_cost; }
    std::vector<int>& getActions() { return m_actions; }
    Node* getParent() const { return m_parent; }
    std::vector<std::vector<int>>& getGrid() { return m_grid; }
  private:
    std::vector<int> m_actions;
    Node* m_parent;
    int m_path_cost;
    std::vector<std::vector<int>> m_grid;
};

#endif //ID_DFTS_NODE_H
