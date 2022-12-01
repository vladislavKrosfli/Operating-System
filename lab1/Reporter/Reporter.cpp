#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Employee.h"
using namespace std;

bool compare(employee a, employee b) {
	return a.num < b.num;
}

int main(int argc, char* argv[]) {

	string file_nameCreator = argv[0], file_nameReporter = argv[1];
	int salaryPerHour = atoi(argv[2]);
	file_nameReporter += ".txt";

	ofstream out(file_nameReporter);
	ifstream in(file_nameCreator, ios_base::binary);

	vector<employee> arr;
	employee empl;

	while (in.read(reinterpret_cast<char*>(&empl.num), sizeof empl.num)) {
		in.read(reinterpret_cast<char*>(&empl.name), sizeof empl.name);
		in.read(reinterpret_cast<char*>(&empl.hours), sizeof empl.hours);
		arr.push_back(empl);
	}

	employee a, b;
	sort(arr.begin(), arr.end(), compare);

	for (int i = 0; i < arr.size(); i++) {
	out << to_string(arr[i].num) + " " 
		+ arr[i].name + " " 
		+ to_string(arr[i].hours) + " " 
		+ to_string(arr[i].hours * salaryPerHour) + "\n";

	}

	out.close();

	return 0;
}