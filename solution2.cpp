#include <iostream>
#include <vector>
#include <algorithm>

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

int getParent(int node, vector<int> &parents) {
    if (parents[node] != node) return getParent(parents[node], parents);
    return node;
}

void addEdge(edge_ptr &head, vector<int> &parents, vector<int> &ranks) {
    int val1 = getParent(head->_val1, parents);
    int val2 = getParent(head->_val2, parents);

    if (ranks[val1] < ranks[val2]) parents[val1] = val2;
    else if (ranks[val1] > ranks[val2]) parents[val2] = val1;
    else {
        ranks[val1]++;
        parents[val2] = val1;
    }
}

int kruskal(vector<int> &parents, vector<int> &ranks, vector<edge_ptr> &edges) {
    int result = 0;
    edge_ptr head;

    while (!edges.empty()) {
        head = edges.back();
        if (getParent(head->_val1, parents) != getParent(head->_val2, parents)) {
            result += head->_weight;
            addEdge(head, parents, ranks);
        }
        edges.pop_back();
    }

    return result;
}

int main() {
    size_t n_nodes;
    int n_edges;
    int n1 = 0;
    int n2 = 0;
    int val = 0;

    cin >> n_nodes;
    cin >> n_edges;

    vector<int> parents(n_nodes);
    vector<int> ranks(n_nodes, 0);
    vector<edge_ptr> edges (n_edges);

    for (size_t i = 0; i < n_nodes; i++) {
        parents[i] = i;
    }

    int i = 0;
    while (cin >> n1 >> n2 >> val && n_edges) {
        edge_ptr new_edge = new edge(n1-1, n2-1, val);
        edges[i] = new_edge;
        n_edges--;
        i++;
    }

    sort(edges.begin(), edges.end(), [](edge_ptr &e1, edge_ptr &e2) {
        return (e1->_weight < e2->_weight);
    });

    cout << kruskal(parents, ranks, edges) << endl;

    return 0;
}