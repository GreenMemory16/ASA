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
    ifstream infile("input.txt");

    list<int> staircase;

    int size_x; 
    int size_y;
    int stair;

    infile >> size_x;
    infile >> size_y;
    
    while (infile >> stair) {
        staircase.push_back(stair);
    }

    return 0;
}

