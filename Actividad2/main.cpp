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
	tsTrie.remove("abandoned");
	tsTrie.find("abandoned");
	tsTrie.endMeasures();

    std::cout << "\nTERNARY" << std::endl;
	tsTrie.startMeasures();
	tsTrie.findFiles("test.txt", true);
	tsTrie.endMeasures();

}

