#include <iostream>
#include <fstream>
#include "Trie.h"
#include "record.h"
using namespace std;
int main() {
    insertRecords();
    Trie trie;
    auto paths = trie.find("12");
    std::ifstream infile("data.db");
    for (auto pos : paths) {
         Record r;
        infile.seekg(pos);
        infile.read((char*)&r, sizeof(Record));
        cout <<  r.key << '\n';   
        cout <<  r.value << '\n'; 
    }
    
    return 0;
}
