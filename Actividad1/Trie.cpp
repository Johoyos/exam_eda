#include "Trie.h"

#include <fstream>
#include <algorithm>

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word, int address) {
    auto node = root;
    for (char c : word) {
        c = c - '0';
        if (node->children[c] == nullptr) {
            node->n_children++;
            auto tmp = new TrieNode();
            //tmp->data = c;
            node->children[c] = tmp;
        }
        node = node->children[c];
    }
    node->address = address;
}

void findChildren(TrieNode* node, std::vector<int>& addr) {
    if (node->n_children > 0) {
        for (auto &child : node->children) {
            if (child) {
                addr.emplace_back(node->address);
                findChildren(child, addr);
            }
        }
    }
}

std::vector<int> Trie::find(const std::string& word) {
    auto node = root;
    for (char c : word) {
        if (node->children[c] == nullptr) {
            return std::vector<int>();
        }
        node = node->children[c];
    }
    std::vector<int> addr;
    addr.emplace_back(node->address);
    findChildren(node, addr);
    std::sort(addr.begin(), addr.end());
    return addr;
}

Trie::Trie(const std::string& filename) {
    root = new TrieNode;
    std::ifstream file(filename, std::ios::in);
    int path = 0;
    while (!file.eof()) {
        std::string word;
        file >> word;
        size_t size = word.length()+1;
        int pos;
        while ((pos = word.find('/')) != std::string::npos) {
            word.erase(0, pos + 1);
        }
        insert(word, path);
        path += size;
    }

}


