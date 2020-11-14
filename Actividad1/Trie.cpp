#include "Trie.h"
#include "record.h"
#include <fstream>
#include <algorithm>


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
                if (child->address >= 0) addr.push_back(child->address);
                findChildren(child, addr);
            }
        }
    }
}

std::vector<int> Trie::find(const std::string& word) {
    auto node = root;
    for (char c : word) {
        c = c - '0';
        if (node->children[c] == nullptr) {
            return std::vector<int>();
        }
        node = node->children[c];
    }
    std::vector<int> addr;
    if (node->address >= 0) addr.push_back(node->address);
    findChildren(node, addr);
    std::sort(addr.begin(), addr.end());
    std::ifstream infile("data.db");
    for (auto pos : addr) {
        Record r;
        infile.seekg(pos, std::ios::beg);
        infile.read((char*)&r, sizeof(Record));
        std::cout <<  r.key << std::endl;
        std::cout <<  r.value << std::endl;
    }
    return addr;
}

Trie::Trie() {
    insertRecords();
    root = new TrieNode;
    std::ifstream infile("data.db", std::ios::binary);
		Record r;
		int pos = 0;
		while (infile.read((char*)&r, sizeof(Record))){
			std::string key = r.key;
			key.resize(4);
		    insert(key, pos);
			pos = infile.tellg();
		}

}


