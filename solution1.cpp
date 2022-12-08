#include <fstream>
#include <string>
#include <iostream>
#include <list>
using namespace std;

bool isStaircase(list<int> staircase) {
    list<int>::iterator it;
    int previous = -1;

    for (it = staircase.begin(); it != staircase.end(); it++) {
        if (*it < previous) {
            return false;
        }
        previous = *it;
    }
    return true;
}

int main() {
    list<int> staircase;

    int size_x; 
    int size_y;
    int stair;

    cin >> size_x;
    cin >> size_y;
    
    while (cin >> stair) {
        staircase.push_back(stair);
    }
    cout << size_x << endl;
    cout << size_y << endl;

    for (list<int>::iterator it = staircase.begin(); it != staircase.end(); it++) 
        cout << *it << endl;
    return 0;
}

