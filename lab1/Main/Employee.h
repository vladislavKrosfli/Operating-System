#pragma once
#include <fstream>
using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

ostream& operator << (ostream& os, const employee& p) {
	return os << p.num << " " << p.name << " " << p.hours << "\n";
}

istream& operator >> (istream& is, employee& p) {
	return is >> p.num >> p.name >> p.hours;
}
