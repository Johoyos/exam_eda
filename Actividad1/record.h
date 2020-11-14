#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

struct Record{
    char key[4];
	char value[3000];
};

void insertRecords(){
	std::ifstream infile("dataSet.txt");
	system("rm data.db");
	std::ofstream outfile("data.db", std::ios::binary | std::ios::app);
	std::string line;
	while (std::getline(infile, line)){
		Record r;
        std::string key(line.begin(), line.begin()+4);
        std::string value(line.begin()+4, line.end());
		strcpy(r.key, key.c_str());
        strcpy(r.value, value.c_str());
	    outfile.write((char*)&r, sizeof(Record));
	}
	infile.close();
	outfile.close();
	//system("rm files.txt");
};