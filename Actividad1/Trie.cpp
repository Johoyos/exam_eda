#include "Trie.h"
#include "record.h"
#include <fstream>
#include <algorithm>
using namespace std;


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

Trie::Trie() {
    root = new TrieNode;
    std::ifstream infile("data.db");
		Record r;
		int pos = 0;
		while (infile.read((char*)&r, sizeof(Record))){
			std::string key = r.key;
		    insert(key, pos);
			pos = infile.tellg();
		}

}


