#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Employee.h"
using namespace std;

void write_bin_file(string& fileName, vector<employee> vec) {
	ofstream out;
	out.open(fileName, ios::binary);
	for (auto& i : vec) {
		out.write(reinterpret_cast<char*>(&i.num), sizeof(int));
		out.write(reinterpret_cast<char*>(&i.name), sizeof i.name);
		out.write(reinterpret_cast<char*>(&i.hours), sizeof(double));
	}
	out.close();
}

int main(int argc, char* argv[]) {

	int numberCreator = atoi(argv[1]);
	string file_nameCreator = argv[0];

	ofstream out(file_nameCreator);
	employee empl;
	out.open(file_nameCreator, ios::binary);
	vector<employee> v;

	for (int i = 0; i < numberCreator; i++) {
		cout << "Enter " << i + 1  <<" employee elements(number, name, hours)\n";
		cin >> empl;
		v.push_back(empl);
		write_bin_file(file_nameCreator, v);
	}

	out.close();

	return 0;
}