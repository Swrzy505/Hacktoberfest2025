#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> iPair;

void primMST(int V, const vector<vector<iPair>>& adj) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    int src = 0;
    pq.push(make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    cout << "Edge \tWeight" << endl;
    int totalWeight = 0;
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " \t" << key[i] << endl;
            totalWeight += key[i];
        }
    }
    cout << "Total MST Weight: " << totalWeight << endl;
}

int main() {
    int V = 5;
    vector<vector<iPair>> adj(V);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    };

    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);
    
    primMST(V, adj);

    return 0;
}
