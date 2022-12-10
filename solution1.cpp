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
	for (vector<int>::iterator itr = staircase.begin(); itr != staircase.end(); itr++) {
		if (*itr != 0) return false;
	}
	return true;
}

void print_stairs(vector<int> &staircase) {
	for (vector<int>::iterator it = staircase.begin(); it != staircase.end(); it++) 
		cout << *it << endl;
}

vector<int>::iterator get_max(vector<int> &staircase) { 
	vector<int>::iterator itr = staircase.begin();
	vector<int>::iterator max_line = itr;

	itr++;

	for (; itr != staircase.end(); itr++) {
		if (*itr > *max_line) {
			max_line = itr;
		}
	}
	return max_line;
}

int max_block(vector<int> &staircase) { // TODO e se só tiver 0?
	vector<int>::iterator max_line = get_max(staircase);
	int max_row = 0;
	int block = 0;

	for (vector<int>::iterator itr = max_line; *itr == *max_line && itr != staircase.end(); itr++) {
		max_row++; 
	}

	// compara blocos na horizontal(max_line) que na vertical(max_row) e devolve o menor entre ambos
	block = *max_line > max_row ? max_row : *max_line; 

	return block;
}

void remove_block(vector<int>::iterator itr, int num) {
	for (int i=0;  i<num; i++) {
		*itr -= num;
		itr++;
	}
}

void add_block(vector<int>::iterator itr, int num) {
	for (int i=0;  i<num; i++) {
		*itr += num;
		itr++;
	}
}

size_t hasher(vector<int> const& lst) {
	size_t seed = lst.size();
	for(auto x : lst) {
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

	vector<int>::iterator max_line_itr = get_max(staircase);
	int max_tile = max_block(staircase);

	unsigned long long options = 0;
	for (int i=0; i < max_tile; i++) {

		remove_block(max_line_itr, i+1); // FIXME
		options += fill_staircase(staircase, memoization);
		add_block(max_line_itr, i+1);
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

