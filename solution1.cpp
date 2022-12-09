#include <string>
#include <iostream>
#include <list>
#include <map>

using namespace std;

/* IDEIAS
 *  - remover linha da lista sempre que se tornar 0
 *  - algum tipo de memoization ou semelhantes
 */

// FIXME this is a scuffed way to do memoization ofc
map<list<int>, int> memoization;

void printStaircase(list<int> staircase) {
    for (list<int>::iterator itr = staircase.begin(); itr != staircase.end(); itr++) {
        for (int i=0; i < *itr; i++) {
            cout << "X";
        }
        cout << "\n";
    }
    cout << "\n";
}

string printList(list<int> lst) {
    string s;
    for (list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++) {
        s.append(to_string(*itr));
        s.append(" ");
    }
    return s;
}

void printMemoization() {
    for (auto const &pair: memoization) {
        cout << "{" << printList(pair.first) << " : " << pair.second << "}" << endl;
    }
}

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

int lineToOperate(list<int> staircase) {
    int biggest = 0;
    int index_biggest = 0;
    int i = 0;
    for (list<int>::iterator itr = staircase.begin(); itr != staircase.end(); itr++) {
        i++;
        if (*itr > biggest) {
            biggest = *itr;
            index_biggest = i;
        }
    }

    return index_biggest;
}

int biggestSizePossible(list<int> staircase) {
    int line = lineToOperate(staircase);
    int biggestSize = 1;
    int value = 0;

    list<int>::iterator itr = staircase.begin();
    for (int j=1; j < line; j++) {
        itr++;
    }

    value = *itr;
    itr++;

    while (itr != staircase.end() && value > biggestSize) {
        if (*itr >= value) {
            biggestSize++;
        } 
        itr++;
    }

    return biggestSize;
}


int max_block(list<int> staircase) {
    int size = staircase.size();
    /*list<int>::iterator itr = staircase.begin();
    while (!*itr) { // coloca o pointer na 1a linha com algum bloco
        if (itr == staircase.end()) return 0; // se não houver nenhuma linha com blocos, retorna 0
        itr++;
        size--;
    } */

    int steps = lineToOperate(staircase);
    list<int>::iterator itr;
    
    for (itr = staircase.begin(); steps != 0; itr++) {
        steps--;
        size--;
    }

    // compara blocos na horizontal(*itr) que na vertical(size) e devolve o menor entre ambos
    return steps;
}

void remove_block(list<int> &staircase, int num, int line) {
	list<int>::iterator itr = staircase.begin();

    for (int i=1; i < line; i++) { itr++; }

	for (int i=0; i < num && itr != staircase.end(); i++) {
		*itr -= num;
		itr++;
	}
}

int fill_staircase(list<int> staircase) {
    int max = lineToOperate(staircase);
    int biggestTile = biggestSizePossible(staircase);

	if (!max) return 1;

	int options = 0;
    list<int> new_stairs2 (staircase);
	for (int i=0; i < biggestTile; i++) {
        list<int> new_stairs (staircase);

        if (memoization.count(new_stairs)) {
            return memoization[new_stairs];
        }

		remove_block(new_stairs, i+1, max);
		options += fill_staircase(new_stairs);
	}
    memoization.insert({new_stairs2, options});

	return options;
}

int main() {
    list<int> staircase;

    int n_rows; 
    int n_cols;
    int counter;
    int stair;

    cin >> n_rows;
    cin >> n_cols;
    
    counter = n_rows;
    while (counter) {
        cin >> stair;
        staircase.push_back(stair);
        counter--;
    }

    cout << "INPUT:" << endl;

    cout << n_rows << endl;
    cout << n_cols << endl;

    for (list<int>::iterator it = staircase.begin(); it != staircase.end(); it++) 
        cout << *it << endl;
    
    int result = lineToOperate(staircase)? fill_staircase(staircase) : 0;
    cout << "RESULT: " << result << endl;    

    //printMemoization();

    return 0;
}
