#include <string>
#include <iostream>
#include <list>

using namespace std;

/* IDEIAS
 *  - remover linha da lista sempre que se tornar 0
 *  - algum tipo de memoization ou semelhantes
 */

bool isStaircase(list<int> staircase) {
    list<int>::iterator it;
    int previous = -1; // FIXME me thinks q isto pode ser 0

    for (it = staircase.begin(); it != staircase.end(); it++) {
        if (*it < previous) {
            return false;
        }
        previous = *it;
    }
    return true; // FIXME talvez pôr previous e assim se for uma stair só de zeros não conta como escada??
}

bool isEmpty(list<int> staircase) {
	for (list<int>::iterator itr = staircase.begin(); itr != staircase.end(); itr++) {
		if(*itr != 0) return false;
	}
	return true;
}

int max_block(list<int> staircase) {
    int size = staircase.size();
    list<int>::iterator itr = staircase.begin();
    while (!*itr) { // coloca o pointer na 1a linha com algum bloco
        if (itr == staircase.end()) return 0; // se não houver nenhuma linha com blocos, retorna 0
        itr++;
        size--;
    } 

    // compara blocos na horizontal(*itr) que na vertical(size) e devolve o menor entre ambos
    return *itr > size ? size : *itr; 
}

void remove_block(list<int> &staircase, int num) {
	list<int>::iterator itr = staircase.begin();
    while (!*itr && itr != staircase.end()) itr++;
	for (int i=0; i < num && itr != staircase.end(); i++) {
		*itr -= num;
		itr++;
	}
}

int fill_staircase(list<int> staircase) {
    int max = max_block(staircase);
	if (!max) return 1;

	int options = 0;
	for (int i=0; i < max; i++) {
		list<int> new_stairs (staircase);
		remove_block(new_stairs, i+1);
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

    cout << "INPUT:" << endl;

    cout << size_x << endl;
    cout << size_y << endl;

    for (list<int>::iterator it = staircase.begin(); it != staircase.end(); it++) 
        cout << *it << endl;
    
    int result = isStaircase(staircase) && max_block(staircase)? fill_staircase(staircase) : 0;
    cout << "RESULT: " << result << endl;

    return 0;
}

