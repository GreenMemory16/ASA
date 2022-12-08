#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main() {
    string line;
    ifstream infile("input.txt");

    list<int> staircase;

    int size_x = 0; 
    int size_y = 0;

    getline(infile, line);
    size_x = stoi(line);
    getline(infile, line);
    size_y = stoi(line);
    
    while (getline(infile, line)) {
        staircase.push_back(stoi(line));
    }

    return 0;
}