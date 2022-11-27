#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

vector<int> mas;
vector<bool> mas_of_states;
int arr_size;
int count_of_threads;
int co_t;
condition_variable cv;
mutex mt;
int numb_to_end = -1;

bool consist_metk(const vector<int>& vec, const int a) {
	return any_of(vec.cbegin(), vec.cend(), [&](const int i)->int {return i == a; });
}

bool check_all_threads_stop() {
	for (int i = 0; i < co_t; i++) {
		if (mas_of_states[i])
			return false;
	}
	return true;
}

void print_states() {
	for (int i = 0; i < mas_of_states.size(); i++)
		cout << "thread #" + to_string(i) + to_string(mas_of_states[i]) + " ";
	cout << endl;
}

void f_thread(int x) {
	srand(x);
	vector<int> metki;

	while (true) {
		unique_lock<mutex> ul(mt);
		if (numb_to_end == x) {
			mas_of_states[x] = false;
			for (const int i : metki)
				mas[i] = 0;
			count_of_threads--;
			cv.notify_all();
			ul.unlock();
			return;
		}

		int ch = rand();
		ch %= arr_size;

		if (mas[ch] == 0) {
			Sleep(5);
			mas[ch] = x + 1;
			if (!consist_metk(metki, ch)) {
				metki.push_back(ch);
			}
			Sleep(5);
		}

		else {
			mas_of_states[x] = false;
			cout << "Thread #" << x << endl;
			for (const int i : metki){
				cout << i << " ";
			}
			cout << endl;
			cv.notify_all();
			cv.wait(ul, [=] {return mas_of_states[x] == true; });
		}
		ul.unlock();
	}
}

bool all_threads_ended(const bool* mas, const int size) {
	for (int i = 0; i < size; i++){
		if (mas[i]){
			return false;
		}
	}
	return true;
}

int main() {

	setlocale(LC_ALL, "rus");

	cout << "Enter the size of the array" << endl;
	cin >> arr_size;
	mas.resize(arr_size);

	for (int i = 0; i < arr_size; i++) {
		mas[i] = 0;
	}
	
	cout << "Enter the count of threads maker" << endl;
	cin >> count_of_threads;
	co_t = count_of_threads;

	vector<thread> th;
	
	for (int i = 0; i < count_of_threads; i++) {
		th.emplace_back(&f_thread, i);
		mas_of_states.push_back(true);
	}
	
	for (int i = 0; i < count_of_threads; i++) {
		th[i].detach();
	}

	vector<int> ended_threads;
	
	while (count_of_threads > 0) {
		unique_lock<mutex> ul(mt);
		cv.wait(ul, [=] {return check_all_threads_stop(); });

		cout << "Array: ";
		
		for (int i = 0; i < arr_size; i++) {
			cout << mas[i] << " ";
		}

		cout << endl << "Enter the number of the Marker thread that you want to finish " << endl;

		int numb;
		cin >> numb;
		if (numb >= th.size()){
			numb = 0;
		}

		ended_threads.push_back(numb);
		mas_of_states[numb] = true;
		numb_to_end = numb;
		cv.notify_all();
		cv.wait(ul, [=] {return check_all_threads_stop(); });
		
		for (int i = 0; i < co_t; i++) {
			if (!consist_metk(ended_threads, i)){
				mas_of_states[i] = true;
			}
		}
		cv.notify_all();
		ul.unlock();
	}
	return 0;
}
