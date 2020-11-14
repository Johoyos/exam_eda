#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "record.h"
using namespace std;
class TSTrie
{
    struct Node
    {
        char value;
        Node* left = nullptr; 
        Node* right = nullptr;
        Node* middle = nullptr;
        bool isTerminal = true;
        vector<unsigned long> paths_pos;
        void show(int pos) {
            if (isTerminal && !middle) {
                cout << " @" << paths_pos.size() << endl;
            } else {
                if (isTerminal) cout << "@" << paths_pos.size();
                if (right) {
                    right->show(pos + 1);
                }
                   
                for (int i = 0; i < pos; i++)
                    cout << " ";
      
                cout << value;

                if (middle) {
                    middle->show(1);
                }
                if (left) {
                    left->show(pos + 1);
                }
            }
        }
    };
    
    Node* root; //main node
    // Exection time and disk access
    clock_t tStart, tEnd;
    double timeTaken;
    long totalSize;

    void insert(string name, Node* node, unsigned long position) {
        int size = (int) name.size();
        totalSize += sizeof(size);
        for (int i = 0; i < size; i++) {
            if (node->isTerminal && !node->middle) {
                    node->value = name[i];
                    if (node->paths_pos.empty())
                        node->isTerminal = false;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    node->middle = terminal;
                    node = node->middle;
            } else if (node->value < name[i]) {
                if (!node->right) {
                    Node* newNode = new Node();
                    totalSize += sizeof(newNode);
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->right = newNode;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    newNode->middle = terminal;
                    node = newNode->middle;
                } else {
                    node = node->right;
                    i--;
                }
                
            } else if (node->value > name[i]) {
                if (!node->left) {
                    Node* newNode = new Node();
                    totalSize += sizeof(newNode);
                    newNode->value = name[i];
                    newNode->isTerminal = false;
                    node->left = newNode;
                    Node* terminal = new Node();
                    totalSize += sizeof(terminal);
                    newNode->middle = terminal;
                    node = newNode->middle;
                } else {
                    node = node->left;
                    i--;
                }
            } else node = node->middle;
        }
        if (!node->isTerminal) {
            node->isTerminal = true;
           
        } 
         node->paths_pos.push_back(position);
         totalSize += sizeof(position);
        
    }

	void find(string name, Node* node, ofstream & fileout){
		int size = (int) name.size();
		for(int i = 0; i < size; i++) {
            if (!node) {
                fileout << "File not  found\n";
                return;
            }
            if (node->value == name[i]) {
                node = node->middle;
            } else if (node->value < name[i]) {
                node = node->right;
                i--;

            } else if (node->value > name[i]) {
                node = node->left;
                i--;
            }
		}
        vector<string> paths;
        if (!node->isTerminal) fileout << "File not found\n";
		else {
            fstream infile("data.db");
            int idx = 0;
            for (auto path:node->paths_pos) {
                Record r;
                infile.seekg(path);
                infile.read((char*)&r, sizeof(Record));
                paths.push_back(r.value);
                fileout << idx << ") " << r.value << '\n';   
                idx++;
            }        
        }
	}

    

    void findPartially(string name, Node* node, ofstream & fileout){
		int size = (int) name.size();
		for(int i = 0; i < size; i++) {
            if (node->value == name[i]) {
                node = node->middle;
            } else if (node->value < name[i]) {
                node = node->right;
                i--;

            } else if (node->value > name[i]) {
                node = node->left;
                i--;
            }
		}
        vector<string> paths;
        int idx = 0;
        dfs(node, idx, paths, fileout);
	}

    void dfs(Node* node, int &idx, vector<string> &paths, ofstream& fileout) {
        if (node->isTerminal) {
            fstream infile("data.db");
            
            for (auto path:node->paths_pos) {
                Record r;
                infile.seekg(path);
                infile.read((char*)&r, sizeof(Record));
                paths.push_back(r.value);
                fileout << idx << ") " << r.value << '\n';   
                idx++;
            }
        } 
        if (node->left) dfs(node->left, idx, paths, fileout);
        if (node->middle) dfs(node->middle, idx, paths, fileout);
        if (node->right) dfs(node->right, idx, paths, fileout);  
        
    }

    void remove() {
        
    }

public:
    TSTrie() {
        root = new Node();
    };

    void insert(string name, unsigned position = -1) {
        insert(name, root, position);
    }

    void addFiles(){
		ifstream infile("data.db");
		Record r;
		int pos = 0;
		while (infile.read((char*)&r, sizeof(Record))){
			string name = r.value;
		    insert(name, pos);
			pos = infile.tellg();
		}
	};

    void find(string name, bool partial = false) {
        ofstream fileout("tstrie_result.txt", ios::app);
        if (partial) findPartially(name, root, fileout);
        else find(name, root, fileout);
    }

    void remove(string name) {
        remove(name, root, fileout);

    }

    void findFiles(string filename, bool partial = false){
        system("rm tstrie_result.txt");
        ifstream infile(filename);
        string query;
        while(getline(infile, query)) {
            find(query, partial);
        }
        infile.close();
    }

    void startMeasures() {
        tStart = clock();
        totalSize = sizeof(Node);
    }

    pair<double, long> endMeasures() {
        tEnd = clock();
        timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC; 
        cout << "Time taken: " << timeTaken << " s , Total size: " << totalSize << " B" << endl;
        return {timeTaken, totalSize};
    }

    void show() {
        root->show(0);
    }

    ~TSTrie() {

    };
};
