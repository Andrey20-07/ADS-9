// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  "tree.h"

std::vector<std::vector<char>> PMTree::getAllPerms() {
  std::vector<std::vector<char>> peres;
  std::vector<char> current;
  collectPerms(root_node, current, peres);
  return peres;
}

std::string PMTree::getPerm1(int erin) {
  std::vector<std::vector<char>> allPerms = getAllPerms();
  if (erin > 0 && erin <= allPerms.size()) {
    return std::string(allPerms[erin - 1].begin(), allPerms[erin - 1].end());
  }
  return "";
}

std::string PMTree::getPerm2(int erin) {
  int totalPerms = 1;
  for (int i = 1; i <= root_node->child_node.size(); ++i) {
    totalPerms *= i;
  }
  if (erin < 1 || erin > totalPerms) {
    return "";
  }
  std::vector<int> factorials;
  int fact = 1;
  for (int i = 1; i <= root_node->child_node.size(); ++i) {
    fact *= i;
    factorials.push_back(fact);
  }
  std::string result;
  PMNode* current_node = root_node;
  erin--;
  while (true) {
    if (current_node->child_node.empty()) {
      break;
    }
    int numChild = current_node->child_node.size();
    int fact = (numChild == 1) ? 1 : factorials[numChild - 2];
    int index = erin / fact;
    if (index >= numChild) {
      return "";
    }
    result += current_node->child_node[index]->symbol;
    erin %= fact;
    current_node = current_node->child_node[index];
  }
  return result;
}
