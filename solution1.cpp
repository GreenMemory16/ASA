#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

bool isEmpty(vector<int> &staircase) {
	for (int num: staircase) {
		if (num != 0) return false;
	}
	return true;
}

void print_stairs(vector<int> &staircase) {
	for (auto & num: staircase)
		cout << num << endl;
}

size_t get_max(vector<int> &staircase) { 
	size_t max_line = 0;
	for (size_t i=1; i < staircase.size(); i++) {
		if (staircase[i] > staircase[max_line]) {
			max_line = i;
		}
		if (staircase[i] < staircase[max_line]) return max_line;
	}
	return max_line;
}

int max_block(vector<int> &staircase, size_t index) { 
	int max_line = staircase[index];
	int max_row = 0;

	for (size_t i = index; staircase[i] == max_line && i < staircase.size(); i++) {
		max_row++; 
	}

	// compara blocos na horizontal(max_line) que na vertical(max_row) e devolve o menor entre ambos
	return max_line > max_row ? max_row : max_line;
}

void remove_block(vector<int> &staircase, size_t index, int num) { 
	for (int i=0;  i<num; i++) {
		staircase[index] -= num;
		index++;
	}
}

void add_block(vector<int> &staircase, size_t index, int num) { 
	for (int i=0;  i<num; i++) {
		staircase[index] += num;
		index++;
	}
}

unsigned long long hasher(vector<int> const& vec) {
	unsigned long long hash = 0;
	for(int x : vec) {
		hash = hash*10 + x;
	}
	return hash;
}

unsigned long long fill_staircase(vector<int> &staircase, map<unsigned long long, unsigned long long> &memoization) { 

	if (isEmpty(staircase)) return 1; 

	if (memoization.count(hasher(staircase))) {
		return memoization[hasher(staircase)];
	}

	size_t max_line_in = get_max(staircase);
	int max_tile = max_block(staircase, max_line_in);

	unsigned long long options = 0;
	for (int i=1; i <= max_tile; i++) {
		remove_block(staircase, max_line_in, i); 
		options += fill_staircase(staircase, memoization);
		add_block(staircase, max_line_in, i);
	}

	memoization.insert({hasher(staircase), options});

	return options;
}

int main() {
	map<unsigned long long, unsigned long long> memoization;
	vector<int> staircase;

	int size_x; 
	int size_y;
	int stair;

	cin >> size_y;
	cin >> size_x;
	
	while (cin >> stair && size_y) {
		staircase.push_back(stair);
		size_y--;
	}

	unsigned long long result = !isEmpty(staircase)? fill_staircase(staircase, memoization) : 0;
	cout << result << endl;

	return 0;	
}

