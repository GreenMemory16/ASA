#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

class edge {
    public:
        int _dest;
        int _weight;
        edge* _next;
        edge(int dest, int weight) {
            _dest = dest;
            _weight = weight;
            _next = nullptr;
        }
        edge(int dest, int weight, edge* ptr) {
            _dest = dest;
            _weight = weight;
            _next = ptr;
        }
};

typedef struct edge* edge_ptr;

void addEdge(vector<edge_ptr> &adjacency, int val1, int val2, int weight) {
    edge_ptr first_edge = new edge(val2, weight, adjacency[val1]);
    edge_ptr second_edge = new edge(val1, weight, adjacency[val2]);
    
    adjacency[val1] = first_edge;
    adjacency[val2] = second_edge;
}

void initialize_nodes(vector<int> &nodes) {
    for (size_t i=0; i < nodes.size(); i++) {
        nodes[i] = -1;
    }
}

int selectNextNode(vector<int> &nodes, set<int> &selected, vector<edge_ptr> &adjacent) {
    int max = 0;
    int index = -1;

    for (auto node_in : selected) {
        edge_ptr head = adjacent[node_in];
        while (head != nullptr) {
            if (head->_weight > max && selected.find(head->_dest) == selected.end()) {
                max = head->_weight;
                index = head->_dest;
            }
            head = head->_next;
        }
    }

    if (index == -1) return index;

    nodes[index] = max;

    return index;
}

int traverseGraph(vector<edge_ptr> &adjacent, size_t &n_nodes) {
    int result = 0;
    vector<int> nodes (n_nodes);
    set<int> selected;

    initialize_nodes(nodes);
    
    nodes[0] = 0;
    selected.insert(0);

    while (selected.size() < n_nodes) {
        int index = selectNextNode(nodes, selected, adjacent);
        
        if (index == -1) {
            for (size_t i = 0; i < n_nodes; i++) {
                if (nodes[i] == -1) {
                    nodes[i] = 0;
                    index = i;
                    
                    break;
                }
            }
        }

        selected.insert(index);

    }

    for (size_t i=1; i < n_nodes; i++) {
        result += nodes[i];
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

void listPrinter(vector<edge_ptr> adjacent) {
    for (size_t i = 0; i < adjacent.size(); i++) {
        edge_ptr head = adjacent[i];
        while (head != nullptr) {
            cout << "(" << i << ", " << head->_dest << ") ->" << head->_weight << endl;
            head = head->_next;
        }
    }
}

void deleteAdjacent(vector<edge_ptr> &to_delete) {
    edge_ptr head, next;
    for (size_t i = 0; i < to_delete.size(); i++) {
        head = to_delete[i];
        while (head != nullptr) {
            next = head->_next;
            delete head;
            head = next;
        }
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

    vector<edge_ptr> adjacent (n_nodes, nullptr);

    while (cin >> n1 >> n2 >> val && n_edges) {
        addEdge(adjacent, n1-1, n2-1 ,val);
        n_edges--;
    }

    cout << traverseGraph(adjacent, n_nodes) << endl;

    deleteAdjacent(adjacent);

    return 0;
}