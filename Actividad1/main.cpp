#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;
int main() {
    Trie trie;
std:string num;
    cout << "Escriba una clave k para retornar su informacion ó sus digitos iniciales: ";

    cin>>num;
    auto paths = trie.find(num);


    return 0;
}
