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
void initialize_nodes(vector<node> &nodes) {
    for (size_t i=0; i < nodes.size(); i++) {
        nodes[i].num = i;
        nodes[i].weight = -1;
        nodes[i].predecessor = -1;
    }
}

int selectNextNode(vector<node> &nodes, set<int> &selected, vector<vector<int>> &matrix) {
    int max = 0;
    int index = -1;
    int predec = -1;

    for (auto node_in : selected) {
        for (size_t i = 0; i < nodes.size(); i++) {
            if (matrix[node_in][i] > max && selected.find(i) == selected.end()) {
                max = matrix[node_in][i];
                index = i;
                predec = node_in;
            }
        }
    }


    if (index == -1) return index;

    nodes[index].predecessor = predec;
    nodes[index].weight = max;

    return index;
}

int traverseGraph(vector<vector<int>> &matrix, size_t &n_nodes) {
    int result = 0;
    vector<node> nodes (n_nodes);
    set<int> selected;

    initialize_nodes(nodes);
    
    nodes[0].weight = 0;
    selected.insert(0);

    while (selected.size() < n_nodes) {
        int index = selectNextNode(nodes, selected, matrix);
        
        if (index == -1) {
            for (auto node : nodes) {
                if (node.weight == -1) {
                    index = node.num;
                    nodes[index].weight = 0;
                    
                    break;
                }
            }
        }

        selected.insert(index);

    }

    for (size_t i=1; i < n_nodes; i++) {
        result += nodes[i].weight;
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

int main() {
    size_t n_nodes;
    int n_edges;
    int n1 = 0;
    int n2 = 0;
    int val = 0;

    cin >> n_nodes;
    cin >> n_edges;

    vector<vector<int>> matrix(n_nodes);

    for (size_t i = 0; i < n_nodes; i++) {
        matrix[i].resize(n_nodes);
    }

    while (cin >> n1 >> n2 >> val && n_edges) {
        matrix[n1-1][n2-1] = val;
        matrix[n2-1][n1-1] = val;
        n_edges--;
    }

    graphPrinter(matrix);

    cout << traverseGraph(matrix, n_nodes) << endl;

    return 0;
}