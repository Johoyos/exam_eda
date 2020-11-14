#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

struct Record{
	char value[3000];
};

void insertRecords(){
	std::ifstream infile("dataSet.txt");
	system("rm data.db");
	std::ofstream outfile("data.db", std::ios::binary | std::ios::app);
	std::string line;
	while (infile >> line){
		Record r;
        strcpy(r.value, line.c_str());
	    outfile.write((char*)&r, sizeof(Record));
	}
	infile.close();
	outfile.close();
	//system("rm files.txt");
};