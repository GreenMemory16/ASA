#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class edge {
    public:
        int val1;
        int val2;
        int weight;
        
        edge() {}
        
        void setValues(int v1, int v2, int w) {
            val1 = v1;
            val2 = v2;
            weight = w;
        }

        bool operator < (const edge& ed) const {
            return (weight < ed.weight);
        }
};

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

        int parent1 = getParent(head.val1, parents);
        int parent2 = getParent(head.val2, parents);

        if (parent1 != parent2) {
            result += head.weight;
            updateNodes(parent1, parent2, parents, ranks);
        }
    }

    return result;
}

int main() {
    size_t n_nodes;
    int n_edges;
    int n1, n2, val;

    if (!scanf("%li", &n_nodes)) return EXIT_FAILURE;
    if (!scanf("%i", &n_edges)) return EXIT_FAILURE;

    vector<int> parents(n_nodes);
    vector<int> ranks(n_nodes, 0);
    vector<edge> edges (n_edges);

    for (size_t i = 0; i < n_nodes; i++) {
        parents[i] = i;
    }

    for (int i = 0; n_edges && scanf("%i %i %i", &n1, &n2, &val); n_edges--, i++) {
        edges[i].setValues(n1-1, n2-1, val);
    }

    sort(edges.rbegin(), edges.rend());

    cout << kruskal(parents, ranks, edges) << endl;

    return 0;
}