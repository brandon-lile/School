//
// Created by brandon on 2/3/16.
//

#ifndef ID_DFTS_TREE_H
#define ID_DFTS_TREE_H

#include <vector>
#include <stack>
#include <iostream>
#include <ctime>
#include "node.h"

class Tree
{
  public:
    Tree(const int colors, const int dim, std::vector<std::vector<int>> grid,
         std::vector<int> start, std::vector<int> end);
    ~Tree();
    void bfts();
  private:
    void increaseDepth();
    void generateNodes(Node* cur_node);
    void printGrid(Node* node) const;
    void printSolution(Node* node, const double duration) const;
    static int m_num_colors;
    static int m_dim;
    Node *m_root;
    std::stack<Node*> m_frontier;
    int m_depth;

    // Single dimension array using x(color num)*2 for x val and
    // x(color num)*2 + 1 for y val
    std::vector<int> m_start_pts;
    std::vector<int> m_end_pts;
};

#endif //ID_DFTS_TREE_H
