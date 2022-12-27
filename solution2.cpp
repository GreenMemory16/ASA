#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

typedef struct node{
    int num;
    int weight;
    int predecessor;
} node;

/*  */
void initialize_nodes(vector<struct node> &nodes) {
    for (size_t i=0; i < nodes.size(); i++) {
        nodes[i].num = i;
        nodes[i].weight = -1;
        nodes[i].predecessor = -1;
    }
}

int selectNextNode(vector<struct node> &nodes, set<int> &selected, vector<vector<int>> &matrix, int predec, int &result) {
    int max = 0;
    int index = -1;

    for (auto node : selected) {
        for (size_t i = 0; i < nodes.size(); i++) {
            if (matrix[node][i] != 0 && selected.find(i) == selected.end()) {
                if (matrix[node][i] > max) {
                    max = matrix[node][i];
                    index = i;
                }
            }
        }
    }


    if (index == -1) return index;

    nodes[index].predecessor = predec;
    nodes[index].weight = nodes[predec].weight + max;
    nodes[index].num = index;

    result += max;

    return index;
}

int traverseGraph(vector<vector<int>> &matrix, size_t &n_nodes) {
    int result = 0;
    vector<struct node> nodes (n_nodes);
    set<int> selected;
    int predec = 0;

    initialize_nodes(nodes);
    
    nodes[0].weight = 0; //maybe outro numero??
    nodes[0].predecessor = -1;
    selected.insert(0);

    while (selected.size() < n_nodes) {
        int index = selectNextNode(nodes, selected, matrix, predec, result);
        predec = index;
        
        if (index == -1) {
            for (auto node : nodes) {
                if (node.weight == -1) {
                    predec = node.num;
                    index = node.num;
                    nodes[predec].weight = result;
                    selected.insert(index);

                    index = node.num;
                    break;
                }
            }
        }

        selected.insert(index);

    }

    return result;
}

void graphPrinter(vector<vector<int>> graph) {
    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

void removeDupWord(string str, int &n1, int &n2, int &val) {
    string word = "";
    int counter = 0;
    for (size_t x = 0; x < str.length(); x++) {
        if (x == str.length() - 1) {
            val = stoi(str.substr(x));
        }

        if (str[x] == ' ') {
            if (counter == 0) {
                n1 = stoi(word);
                counter++;
            }
            else if (counter == 1) {
                n2 = stoi(word);
                counter++;
            }
            word = "";
        }
        else {
            word = word + str[x];
        }
    }
}

int main() {
    size_t n_nodes;
    int n_edges;
    int n1 = 0;
    int n2 = 0;
    int val = 0;
    string input;
    string line;

    cin >> n_nodes;
    cin >> n_edges;

    vector<vector<int>> matrix(n_nodes);

    for (size_t i = 0; i < n_nodes; i++) {
        matrix[i].resize(n_nodes);
    }

    // to skip a weird line that i dont know why it's appearing
    getline(cin, line);

    while (getline(cin, line) && n_edges + 1) {
        removeDupWord(line, n1, n2, val);
        matrix[n1-1][n2-1] = val;
        matrix[n2-1][n1-1] = val;
        n_edges--;
    }

    graphPrinter(matrix);

    cout << traverseGraph(matrix, n_nodes) << endl;

    return 0;
}