#include "TrieNode.h"

TrieNode::TrieNode() {
    children = std::vector<TrieNode*>(10, nullptr);
    n_children = 0;
    address = -1;
}
