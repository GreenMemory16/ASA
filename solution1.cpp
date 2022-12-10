#include <string>
#include <iostream>
#include <list>
#include <map>

using namespace std;


/* IDEIAS
 *  - remover linha da lista sempre que se tornar 0
 *  - trocar list por vector (assim podemos aceder complexidade constante aos elementos)
 */

string printList(list<int> lst) {
    string s;
    for (list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++) {
        s.append(to_string(*itr));
        s.append(" ");
    }
    return s;
}

int printMemoization(map<list<int>, unsigned long long>memoization) {
    int i = 0;
    for (auto const &pair: memoization) {
        i++;
        cout << "{" << printList(pair.first) << " : " << pair.second << "}" << endl;
    }
    return i;
}

bool isEmpty(list<int> &staircase) {
	for (list<int>::iterator itr = staircase.begin(); itr != staircase.end(); itr++) {
		if (*itr != 0) return false;
	}
	return true;
}

void print_stairs(list<int> &staircase) {
    for (list<int>::iterator it = staircase.begin(); it != staircase.end(); it++) 
        cout << *it << endl;
}

list<int>::iterator get_max(list<int> &staircase) { 
    list<int>::iterator itr = staircase.begin();
    list<int>::iterator max_line = itr;

    itr++;

    for (; itr != staircase.end(); itr++) {
		if (*itr > *max_line) {
            max_line = itr;
        }
	}
    return max_line;
}

int max_block(list<int> &staircase) { // TODO e se só tiver 0?
    list<int>::iterator max_line = get_max(staircase);
    int max_row = 0;
    int block = 0;

    for (list<int>::iterator itr = max_line; *itr == *max_line && itr != staircase.end(); itr++) {
        max_row++; 
	}

    // compara blocos na horizontal(max_line) que na vertical(max_row) e devolve o menor entre ambos
    block = *max_line > max_row ? max_row : *max_line; 

    return block;
}

void remove_block(list<int> &staircase, list<int>::iterator itr, int num) {
	for (int i=0;  i<num; i++) {
		*itr -= num;
		itr++;
	}
}

void add_block(list<int> &staircase, list<int>::iterator itr, int num) {
	for (int i=0;  i<num; i++) {
		*itr += num;
		itr++;
	}
}

unsigned long long fill_staircase(list<int> &staircase, map<list<int>, unsigned long long> &memoization) { 

	if (isEmpty(staircase)) return 1; // TODO maybe check size and if there's only 1 line or row return aswell

    if (memoization.count(staircase)) {
        return memoization[staircase];
    }

    list<int>::iterator max_line_itr = get_max(staircase);
    int max_tile = max_block(staircase);

	unsigned long long options = 0;
	for (int i=0; i < max_tile; i++) {

		remove_block(staircase, max_line_itr, i+1); // FIXME
		options += fill_staircase(staircase, memoization);
        add_block(staircase, max_line_itr, i+1);
	}

    memoization.insert({staircase, options});

	return options;
}

int main() {
    map<list<int>, unsigned long long> memoization;
    list<int> staircase;

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

    //cout << "ITEMS: " << printMemoization(memoization);

    return 0;
}

