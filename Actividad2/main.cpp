#include <iostream>
#include "tstree.h"
#include "record.h"
using namespace std;

int main() {
    insertRecords();
    std::cout << "\nTERNARY" << std::endl;
	TSTrie tsTrie;
	tsTrie.startMeasures();
	tsTrie.addFiles();
	tsTrie.endMeasures();

    std::cout << "\nTERNARY" << std::endl;
	tsTrie.startMeasures();
	tsTrie.findFiles("test.txt", true);
	tsTrie.endMeasures();

}

