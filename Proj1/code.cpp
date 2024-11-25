#include "code.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator>

using namespace std;
vector<alloc> alloc_list;
vector<range> free_list;

void mergeMemory(void);
extern long int clock_tick;

void initializeMemory() {
	free_list.push_back(range(0, MEMORY_SIZE)); // Initialize with a single large free block
}

int number_requests;
int number_sat;
int number_unsat;

int smallest = 1000;
int largest;
int total_request;

int shortest = 1000;
int longest;
int total_time;

int nums_merges;

void printFree(vector<range>& free_list) {
	cout << "free List :";
	int n = free_list.size();
	if (n == 0) {
		cout << "--empty--" << endl;
		return;
	}
	for (int i = 0; i < n; ++i) {
		int first = free_list[i].first;
		int second = free_list[i].second;
		if (i % 5 == 0 && i != 0)
			cout << endl;
		cout << "{" << first << ", " << second << "}";
		if (i != n - 1)
			cout << ", ";
	}
	cout << endl;
}

void printAlloc(vector <alloc>& alloc_list) {
	cout << "Allocated List: ";
	int n = alloc_list.size();
	if (n == 0) {
		cout << "--empty--" << endl;
		return;
	}
	for (int i = 0; i < n; ++i) {
		int first = alloc_list[i].first.first;
		int second = alloc_list[i].first.second;
		int third = alloc_list[i].second;
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << "[{" << first << ", " << second << "}, " << third << "]";
		if (i != n - 1)
			cout << ", ";
	}
	cout << endl;
	return;
}

alloc makeAlloc(int start, int memSize, int expiration) {
	return { {start, memSize}, expiration };
}

int findBest(int sizeMem) {
	int size = free_list.size();
	if (alloc_list.size() == 0) {
	    
		free_list[0].first += sizeMem;
		free_list[0].second = MEMORY_SIZE- free_list[0].first;
		return 0;
	}
	mergeMemory();
	for (int i = 0; i < size; i++) {
		
		if (free_list[i].second >= sizeMem) {
			free_list[i].first += sizeMem;
			if(i == free_list.size()-1){
			    free_list[i].second = MEMORY_SIZE- free_list[i].first;
			} else{
			    free_list[i].second = free_list[i].second - sizeMem;
			}
			return free_list[i].first- sizeMem;
		}
	}
	return -1;
}

void getMemory(int sizeMem, int expiration) {
	if (sizeMem > largest) largest = sizeMem;
	if (sizeMem < smallest) smallest = sizeMem;
	total_request += sizeMem;


	if (expiration > longest) longest = expiration;
	if (expiration < shortest) shortest = expiration;
	total_time += expiration;
	int start = findBest(sizeMem);

	number_requests++;

	if (start == -1) {
		number_unsat++;
	    return;
	}
	alloc ticket = makeAlloc(start, sizeMem, expiration + clock_tick);
	alloc_list.push_back(ticket);
	number_sat++;
}


void mergeMemory() {
	std::sort(free_list.begin(), free_list.end(), [](range a1, range a2) {
		return a1.first < a2.first;
	});
	int size = free_list.size();
	for (int i = 0; i < size - 1; i++) {
		if(free_list[i].first + free_list[i].second == free_list[i+1].first){
		    free_list[i].second += free_list[i+1].second;
		    free_list.erase(free_list.begin()+i+1);
		    nums_merges++;
		}
	}
}
void cleanMemory(int clock) {
	int size = alloc_list.size();
	for (int i = 0; i < size; i++) {
		int exp = alloc_list[i].second;
		if (exp == clock) {
			free_list.push_back(alloc_list[i].first);
			alloc_list.erase(alloc_list.begin() + i);
			i--;
		}
	}
	mergeMemory();
}

void print() {
	printFree(free_list);
	printAlloc(alloc_list);
	cout<<endl;
}

void printStats() {
	cout << "Total requests " << number_requests << " Satisfied requests " << number_sat << " Unsatified requests " << number_unsat << endl;
	cout << "Smallest request " << smallest << " Largest request " << largest << " Average block size " << total_request / number_requests<< endl;
	cout << "Shortest request " << shortest << " Longest request " << longest << " Average request time " << total_time/ number_requests<< endl;
	cout << "Number of merges " << nums_merges << endl;
	print();
}
