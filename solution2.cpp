#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class edge {
    public:
        int _val1;
        int _val2;
        int _weight;
        
        edge() {}
        
        void setValues(int val1, int val2, int weight) {
            _val1 = val1;
            _val2 = val2;
            _weight = weight;
        }

        bool operator < (const edge& ed) const {
            return (_weight < ed._weight);
        }
};

typedef edge* edge_ptr;

int getParent(int node, vector<int> &parents) {
    if (parents[node] != node) return getParent(parents[node], parents);
    return node;
}

void updateNodes(int parent1, int parent2, vector<int> &parents, vector<int> &ranks) {
    if (ranks[parent1] < ranks[parent2]) parents[parent1] = parent2;
    else if (ranks[parent1] > ranks[parent2]) parents[parent2] = parent1;
    else {
        ranks[parent1]++;
        parents[parent2] = parent1;
    }
}

int kruskal(vector<int> &parents, vector<int> &ranks, vector<edge> &edges) { // n
    int result = 0;

    for (vector<edge>::iterator itr = edges.begin(); itr != edges.end(); itr++) {
        edge head = *(itr);
        int parent1 = getParent(head._val1, parents);
        int parent2 = getParent(head._val2, parents);
        if (parent1 != parent2) {
            result += head._weight;
            updateNodes(parent1, parent2, parents, ranks);
        }
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
    vector<edge> edges (n_edges);

    for (size_t i = 0; i < n_nodes; i++) {
        parents[i] = i;
    }

    int i=0;
    while (cin >> n1 >> n2 >> val && n_edges) {
        edges[i].setValues(n1-1, n2-1, val);
        n_edges--;
        i++;
    }

    sort(edges.rbegin(), edges.rend());

    cout << kruskal(parents, ranks, edges) << endl;

    return 0;
}