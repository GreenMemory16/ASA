#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <queue>

using namespace std;

class edge {
    public:
        int _val1;
        int _val2;
        int _weight;
        
        edge(int val1, int val2, int weight) {
            _val1 = val1;
            _val2 = val2;
            _weight = weight;
        }
};

typedef struct edge* edge_ptr;

class node {
    public:
        int _weight;
        vector<int> _edges; //stores index of in edge vector

        node() {
            _weight = -1;
        }

        void addEdge(int &num) {
            _edges.push_back(num);
        }
};

class edge_comparison {
    public:
        edge_comparison() {};
        bool operator() (const edge_ptr &n1, const edge_ptr &n2) const {
            return n1->_weight < n2->_weight;
        }
};

typedef priority_queue<edge_ptr, vector<edge_ptr>, edge_comparison> edge_queue;

void initialize_nodes(vector<node> &nodes) {
    for (size_t i=0; i < nodes.size(); i++) {
        nodes[i]._weight = -1;
    }
}

void delete_all(vector<edge_ptr> &edges, edge_queue &edge_q) {
    for (edge_ptr e : edges) {
        delete e;
    }
    while (!edge_q.empty()) {
        edge_q.pop();
    }
}

void queueEdges(node &node_o, edge_queue &edge_q, vector<edge_ptr> &edges) {
    for (int edge_in : node_o._edges) {
        if (edges[edge_in] != nullptr) {
            edge_q.push(edges[edge_in]);
            edges[edge_in] = nullptr;
        }
    }
}

int selectNextNode(set<int> &selected, edge_queue &edge_q, vector<node> &nodes) {
    edge_ptr max = edge_q.top();
    int next = -1;
    edge_q.pop();

    if (max == nullptr) {cout << "HERE"; return -1;}

    if (selected.find(max->_val1) == selected.end()) next = max->_val1;
    else if (selected.find(max->_val2) == selected.end()) next = max->_val2;
    else if (next == -1) {
        if (edge_q.empty()) return next;
        return selectNextNode(selected, edge_q, nodes);
    }

    nodes[next]._weight = max->_weight;

    return next;
}

int traverseGraph(vector<node> &nodes, vector<edge_ptr> &edges, size_t &n_nodes) {
    int result = 0;
    edge_queue edge_q;
    set<int> selected;
    
    nodes[0]._weight = 0;
    selected.insert(0);
    queueEdges(nodes[0], edge_q, edges);

    while (selected.size() < n_nodes) {
        int index = selectNextNode(selected, edge_q, nodes);
        
        if (index == -1) {
            for (size_t i = 0; i < n_nodes; i++) {
                if (nodes[i]._weight == -1) {
                    nodes[i]._weight = 0;
                    index = i;
                    
                    break;
                }
            }
        }

        selected.insert(index);
        queueEdges(nodes[index], edge_q, edges);
    }

    for (size_t i=0; i < n_nodes; i++) {
        result += nodes[i]._weight;
    }

    delete_all(edges, edge_q);

    return result;
}

int main() {
    size_t n_nodes;
    int n_edges;
    int n1 = 0;
    int n2 = 0;
    int val = 0;
    int i = 0;

    cin >> n_nodes;
    cin >> n_edges;

    vector<node> nodes (n_nodes);
    vector<edge_ptr> edges (n_edges);

    initialize_nodes(nodes);

    while (cin >> n1 >> n2 >> val && n_edges) {
        edge_ptr new_edge = new edge(n1-1, n2-1, val);
        edges[i] = new_edge;
        nodes[n1-1].addEdge(i);
        nodes[n2-1].addEdge(i);
        n_edges--;
        i++;
    }

    cout << traverseGraph(nodes, edges, n_nodes) << endl;

    return 0;
}