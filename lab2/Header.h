#pragma once
#include <vector>
using namespace std;

class lab2 {

public:
	void average(vector<int> arr, int& average) {

		int sum = 0;

		for (int i = 0; i < arr.size(); i++) {
			sum += arr[i];
		}

		average = sum / arr.size();
	}

	void min_max(vector<int> arr, int& min, int& max) {

		min = arr[0];
		max = arr[0];

		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] > max) {
				max = arr[i];
			}

			if (arr[i] < min) {
				min = arr[i];
			}
		}
	}

	void change_arr(vector<int>& arr, int average, int min, int max) {
	
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i] == min || arr[i] == max) {
				arr[i] = average;
			}
		}
	}
};