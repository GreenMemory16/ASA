#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;


/* IDEIAS
 *  - remover linha da lista sempre que se tornar 0
 *  - trocar list por vector (assim podemos aceder complexidade constante aos elementos)
 */

bool isEmpty(vector<int> &staircase) {
	for (auto & num: staircase) {
		if (num != 0) return false;
	}
	return true;
}

void print_stairs(vector<int> &staircase) {
	for (auto & num: staircase)
		cout << num << endl;
}

int get_max(vector<int> &staircase) { 
	int max_line = 0;
	for (int i=1; i < staircase.size(); i++) {
		if (staircase[i] > staircase[max_line]) {
			max_line = i;
		}
	}
	return max_line;
}

int max_block(vector<int> &staircase, int index) { // TODO e se só tiver 0?
	int max_line = staircase[index];
	int max_row = 0;

	for (int i = index; staircase[i] == max_line && i > staircase.size(); i++) {
		max_row++; 
	}

	// compara blocos na horizontal(max_line) que na vertical(max_row) e devolve o menor entre ambos
	return max_line > max_row ? max_row : max_line;
}

void remove_block(vector<int> &staircase, int index, int num) { //FIXME iterator or index + staircase
	for (int i=0;  i<num; i++) {
		staircase[index] -= num;
		index++;
	}
}

void add_block(vector<int> &staircase, int index, int num) { //FIXME iterator or index + staircase
	for (int i=0;  i<num; i++) {
		staircase[index] += num;
		index++;
	}
}

size_t hasher(vector<int> const& vec) {
	size_t seed = vec.size();
	for(auto x : vec) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

unsigned long long fill_staircase(vector<int> &staircase, map<int, unsigned long long> &memoization) { 

	if (isEmpty(staircase)) return 1; // TODO maybe check size and if there's only 1 line or row return aswell

	if (memoization.count(hasher(staircase))) {
		return memoization[hasher(staircase)];
	}

	int max_line_in = get_max(staircase);
	int max_tile = max_block(staircase, max_line_in);

	unsigned long long options = 0;
	for (int i=1; i <= max_tile; i++) {
		remove_block(staircase, max_line_in, i); // FIXME
		options += fill_staircase(staircase, memoization);
		add_block(staircase, max_line_in, i);
	}

	memoization.insert({hasher(staircase), options});

	return options;
}

int main() {
	map<int, unsigned long long> memoization;
	vector<int> staircase;

	int size_x; 
	int size_y;
	int counter;
	int stair;

	cin >> size_y;
	cin >> size_x;
	
	counter = size_y;
	while (cin >> stair && counter) {
		staircase.push_back(stair);
		counter--;
	}
	
	unsigned long long result = !isEmpty(staircase)? fill_staircase(staircase, memoization) : 0;
	cout << result << endl;

	return 0;
}

