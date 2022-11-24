#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

struct to_thread {
	vector<int> arr;
	int minItem = 0;
	int maxItem = 0;
	int averageValue = 0;
};

DWORD WINAPI average(LPVOID lpParam) {
	const auto buf = static_cast<to_thread*>(lpParam);
	const vector<int> arr = buf->arr;
	int sum = 0;

	for (int i = 0; i < arr.size(); i++) {
		sum += arr[i];
		Sleep(30);
	}
	buf->averageValue = sum / arr.size();
	return 0;
}

DWORD WINAPI min_max(LPVOID lpParam) {
	const auto buf = static_cast<to_thread*>(lpParam);
	const vector<int> arr = buf->arr;
	int min = arr[0];
	int max = arr[0];

	for (int i = 1; i < int(arr.size()); i++) {
		if (arr[i] > max) {
			Sleep(30);
			max = arr[i];
		}

		if (arr[i] < min) {
			Sleep(30);
			min = arr[i];
		}
	}

	buf->minItem = min;
	buf->maxItem = max;

	return 0;
}

int main() {

	cout << "Enter size of mass ";

	vector<int> arr;
	int size;
	cin >> size;

	cout << "Enter the array elements";
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}

	const auto to_min_max_thr = new to_thread();
	to_min_max_thr->arr = arr;

	const auto to_average_thr = new to_thread();
	to_average_thr->arr = arr;

	DWORD dw_thread_id, dw_thread_id2;
	HANDLE h_thread1 = CreateThread(NULL, 0, min_max, to_min_max_thr, 0, &dw_thread_id);
	HANDLE h_thread2 = CreateThread(NULL, 0, average, to_average_thr, 0, &dw_thread_id2);

	if (h_thread1 == NULL || h_thread2 == NULL) {
		cerr << GetLastError();
		return -1;
	}

	WaitForSingleObject(h_thread1, INFINITE);	// ждём завершения потока
	WaitForSingleObject(h_thread2, INFINITE);

	CloseHandle(h_thread1);
	CloseHandle(h_thread2);

	cout << endl << "Min item = " << to_min_max_thr->minItem << "\tMax item = " << to_min_max_thr->maxItem << endl;
	cout << "Average value = " << to_average_thr->averageValue << endl << endl << "Mas: ";

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == to_min_max_thr->maxItem || arr[i] == to_min_max_thr->minItem) {
			arr[i] = to_average_thr->averageValue;
		}
		cout << arr[i] << " ";
	}

	cout << endl;

	return 0;
}
