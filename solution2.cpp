#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

typedef struct node{
    int weight;
    int predecessor;
} node;

/*  */
void initialize_nodes(vector<struct node> &nodes) {
    for (size_t i=0; i < nodes.size(); i++) {
        nodes[i].weight = 0;
        nodes[i].predecessor = -1;
    }
}

/* putWeightAdjacentNodes --> getar os nodes adjacentes e mudar o seu peso
 */

void putWeightAdjacentNodes(vector<vector<int>> &matrix, int index, vector<struct node> &nodes) {
    size_t n_nodes = nodes.size();
    for (size_t i=0; i < n_nodes; i++) {
        if (matrix[index][i] != 0 && nodes[i].weight < matrix[index][i]) { //dar double check à comparação
            nodes[i].weight = matrix[index][i];
            nodes[i].predecessor = index;
        }
    }
}

/* getNonSelectedButWithWeight --> 
 * retornar o próximo node a analisar (n tá nos selected mas tem weight e o seu weight é máximo)
 */

int getNonSelectedButWithWeight(vector<struct node> &nodes, set<int> &selected) {
    int max = 0;
    int index = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].weight >= max && selected.find(i) == selected.end()) {
            max = nodes[i].weight;
            index = i;
        }
    }
    return index;
}

int traverseGraph(vector<vector<int>> matrix, size_t n_nodes) {
    int result = 0;
    vector<struct node> nodes (n_nodes);
    set<int> selected;

    initialize_nodes(nodes);
    
    nodes[0].weight = INT8_MAX; //maybe outro numero??
    nodes[0].predecessor = -1;

    //does prims algorithm
    while (selected.size() < n_nodes) {
        int index = getNonSelectedButWithWeight(nodes, selected);
        selected.insert(index);
        putWeightAdjacentNodes(matrix, index, nodes);
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

    cout << traverseGraph(matrix, n_nodes);

}