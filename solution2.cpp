#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

class edge {
    public:
        int _from; 
        int _dest;
        int _weight;
        edge* _next;
        edge(int from, int dest, int weight) {
            _from = from;
            _dest = dest;
            _weight = weight;
            _next = nullptr;
        }
        edge(int from, int dest, int weight, edge* ptr) {
            _from = from;
            _dest = dest;
            _weight = weight;
            _next = ptr;
        }
};

class edge2 {
    public:
        int _from;
        int _dest;
        int _weight;
};

typedef struct edge2* edge_ptr2;

typedef struct edge* edge_ptr;

class node {
    public:
        int _num;
        int _weight;
        vector<edge_ptr2> edges;
};

typedef struct node* node_ptr;

struct greastest {
    bool operator()(const edge_ptr2 a, const edge_ptr2 b) const {
        return a->_weight < b->_weight;
    }
};

void printHeap(vector<edge_ptr2> heap) {
    for (size_t i = 0; i < heap.size(); i++) {
        cout << "from: " << heap[i]->_from << " dest: " << heap[i]->_dest << " weight: " << heap[i]->_weight << endl;
    }

    cout << "DONE" << endl;
}

int selectNextNode(vector<edge_ptr2> &my_edges, set<int> &selected, vector<node_ptr> &my_nodes, int previous) {
    int max = 0;
    int index = -1;

    while (true) {

        if (my_edges.size() == 0) {
            break;
        }

        edge_ptr2 edge = my_edges.front();

        pop_heap(my_edges.begin(), my_edges.end());
        my_edges.pop_back();
        
        if (selected.find(edge->_dest) != selected.end()) { 
            make_heap(my_edges.begin(), my_edges.end(), greastest());
            continue;
        }
        
        index = edge->_dest;

        my_edges.insert(my_edges.end(), my_nodes[index]->edges.begin(), my_nodes[index]->edges.end());
        make_heap(my_edges.begin(), my_edges.end(), greastest());

        max = edge->_weight;

        break;
    }

    if (index == -1) return index;
    
    my_nodes[index]->_weight = my_nodes[previous]->_weight + max;

    return index;
}



int traverseGraph(vector<node_ptr> &my_nodes, size_t &n_nodes) {
    int previous = 0;
    set<int> selected;
    vector<edge_ptr2> my_edges;

    my_edges.insert(my_edges.end(), my_nodes[0]->edges.begin(), my_nodes[0]->edges.end());
    make_heap(my_edges.begin(), my_edges.end(), greastest());
    selected.insert(0);

    while (selected.size() < n_nodes) {
        int index = selectNextNode(my_edges, selected, my_nodes, previous);

        if (index == -1) {
            for (size_t i = 0; i < n_nodes; i++) {
                if (selected.find(i) == selected.end()) {
                    index = i;
                    my_edges.clear();

                    my_edges.insert(my_edges.end(), my_nodes[index]->edges.begin(), my_nodes[index]->edges.end());
                    make_heap(my_edges.begin(), my_edges.end(), greastest());
                    selected.insert(index);
                    
                    my_nodes[index]->_weight = my_nodes[previous]->_weight;

                    break;
                }
            }
        }

        previous = index;
        selected.insert(index);
    }

    return my_nodes[previous]->_weight;
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

int main() {
    size_t n_nodes;
    int n_edges;
    int n1 = 0;
    int n2 = 0;
    int val = 0;

    cin >> n_nodes;
    cin >> n_edges;
    
    vector<node_ptr> my_nodes (n_nodes, nullptr);

    for (size_t i = 0; i < n_nodes; i++) {
        my_nodes[i] = new node;
        my_nodes[i]->_num = i;
        my_nodes[i]->_weight = 0;
    }

    while (cin >> n1 >> n2 >> val && n_edges) {
        edge_ptr2 new_edge = new edge2;
        new_edge->_from = n1-1;
        new_edge->_dest = n2-1;
        new_edge->_weight = val;
        my_nodes[n1-1]->edges.push_back(new_edge);

        edge_ptr2 new_edge2 = new edge2;
        new_edge2->_from = n2-1;
        new_edge2->_dest = n1-1;
        new_edge2->_weight = val;
        my_nodes[n2-1]->edges.push_back(new_edge2);
    }

    cout << traverseGraph(my_nodes, n_nodes) << endl;

    return 0;
}