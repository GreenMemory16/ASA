#include <string>
#include <iostream>
#include <list>

using namespace std;

/* IDEIAS
 *  - remover linha da lista sempre que se tornar 0
 *  - algum tipo de memoization ou semelhantes
 *  - trocar list por vector (assim podemos aceder complexidade constante aos elementos)
 */

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

void remove_block(list<int> &staircase, int max_line, int num) {
	list<int>::iterator itr = staircase.begin();
    while (*itr != max_line) itr++;
	for (int i=0;  i<num; i++) {
		*itr -= num;
		itr++;
	}
}

unsigned long long fill_staircase(list<int> &staircase) { 

	if (isEmpty(staircase)) return 1; // TODO maybe check size and if there's only 1 line or row return aswell

    list<int>::iterator max_line_itr = get_max(staircase);
    int max_tile = max_block(staircase), max_line = *max_line_itr;

	unsigned long long options = 0;
	for (int i=0; i < max_tile; i++) {
		list<int> new_stairs (staircase);
		remove_block(new_stairs, max_line, i+1); // FIXME
		options += fill_staircase(new_stairs);
	}

	return options;
}

int main() {
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
    
    int result = !isEmpty(staircase)? fill_staircase(staircase) : 0;
    cout << result << endl;

    return 0;
}

