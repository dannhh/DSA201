#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    int V, E;
    vector < pair<int, pair<int, int>> > edges;

    Graph(int V, int E){
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w){
        edges.push_back({ w, {u, v} });
    }
    
    int findSet(vector<int>& store, int i){
        if(store[i] == i) return i;
        else
            return store[i] = findSet(store, store[i]);
    }

    void unionSet(vector<int>& store, vector<int>& rank, int i, int j){
        int x = findSet(store, i);
        int y = findSet(store, j);
        if(rank[x] > rank[y]) swap(x,y);
        store[x] = y;
        if(rank[x] == rank[y]) rank[y]++;
    }

    int kruskalMST() {
		sort(edges.begin(), edges.end());
        vector<int> store;
        store.assign(V, 0);
        for(int i = 0; i < V; i++)
            store[i] = i;
        vector<int> rank;
        rank.assign(V, 0);
		int mst_cost = 0, num_taken = 0;
        for(int i = 0; i < E; i++){
            if(findSet(store, edges[i].second.first) == findSet(store, edges[i].second.second));
            else{
                mst_cost += edges[i].first;
                unionSet(store, rank, edges[i].second.first, edges[i].second.second);
                ++num_taken;
                if(num_taken == V-1) break;
            }
        }
		return mst_cost;
	}
};

int main(){
    if(1){
        int V = 3, E = 3;
        Graph g(V, E);

        g.addEdge(0, 1, 2);
        g.addEdge(1, 2, 2);
        g.addEdge(0, 2, 3);


        cout << g.kruskalMST();
    }
}