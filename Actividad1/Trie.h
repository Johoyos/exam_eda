#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <string>
#include "TrieNode.h"

class Trie {
private:
    TrieNode* root;

public:
    Trie();

    void insert(const std::string& word, int address);
    std::vector<int> find(const std::string& word);
};


#endif //TRIE_TRIE_H
