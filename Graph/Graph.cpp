#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	~Adjacency(){
		size = 0;
		if(adjList.size()) adjList.pop_front();
	}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};
class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *BFS(int v)
    {
       bool visited[V] = {0};
        for (int i = 0; i < V; i++){
            visited[i] = false;
        }
        list<int> queue;
        queue.push_back(v);
        visited[v] = true;

        Adjacency* a = new Adjacency(V);
        while(queue.size()!=0){
            v = queue.front();
            queue.pop_front();
            a->push(v);

            for(int i = 0; i < adj[v].getSize(); i++){
                int s = adj[v].getElement(i);
                if(visited[s] != true){
                    visited[s] = true;
                    queue.push_back(s);
                }
            }
        }
        return a;
	}
	
	void _DFS(int v, bool* visited, Adjacency*& _adj){
		visited[v] = 1;
		_adj->push(v);
		for(int i = 0; i < adj[v].getSize(); i++){
			int s = adj[v].getElement(i);
			if(visited[s] == 0)
				_DFS(s, visited, _adj);
		}
		return;
	}
	Adjacency *DFS(int v)
    {
		bool visited[V] = {0};
		Adjacency* traverse = new Adjacency(V);
		_DFS(v, visited, traverse);
		return traverse;
	}
	void topo_sub(int v, bool* visited, list<int> &a){
		visited[v] = 1;
		for(int i = 0; i < adj[v].getSize(); i++){
			int s = adj[v].getElement(i);
			if(visited[s] == false)
				topo_sub(s, visited, a);
		}
		a.push_back(v);
	}
	// Add một chiều
	void topologicalSort(){
        bool visited[V] = {0};
		list<int>a;
		for(int i = 0; i < V; i++){
			if(visited[i] == 0){
				topo_sub(i, visited, a);
			}
		}
		while(a.size()){
			cout << a.back() << " ";
			a.pop_back();
		}
    }
};
class DirectedGraph 
{ 
	int V;
	list<int> *adj;
	bool isCyclicUtil(int v, bool visited[], bool *rs);
public: 
	DirectedGraph(){
        V = 0;
        adj = NULL;
    }
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = new list<int>[V];
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}

	bool _isCyclic(int v, int* visited, int* parent){
		visited[v] = 1;
		list<int>::iterator i; 
        for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        { 
			int s = *i;
			if(visited[s] == 0){
				parent[s] = v;
				if(_isCyclic(s, visited, parent)) return true;
			}
			else if(visited[s] == 1){
				if(s == parent[v]) return true;
				else return true;
			}
			else if(visited[s] == 2);
		}
		visited[v] = 2;
		return false;
	}
	bool isCyclic(){
		int visited[V] = {0};
		int parent[V] = {0};
		for(int i = 0; i < V; i++){
			parent[i] = -1;
		}
		for(int i = 0; i < V; i++){
			if(visited[i] == 0)
				if(_isCyclic(i, visited, parent)) return true;
		}
		return false;
	}
}; 
int minDist(int *path, bool* set){
	int min = 1000000000, min_dist;
	for(int i = 0; i < 6; i++){
		if(set[i] == false && path[i] <= min){
			min = path[i];
			min_dist = i;
		}
	}
	return min_dist;
}
int Dijkstra(int** graph, int src, int dst) {
	int path[6];
	bool set[6] = {0};
	for(int i = 0; i < 6; i++)
		path[i] = 1000000000;
	path[src] = 0;
	for(int i = 0; i < 5; i++){
		int min = minDist(path, set);
		set[min] = true;
		for(int j = 0; j < 6; j++){
			if(!set[j] && graph[min][j] != 0 && path[min]!=1000000000
				&& graph[min][j] + path[min] < path[j])
				path[j] = path[min] + graph[min][j];
		}
	}
	return path[dst];
}
#include <algorithm>
struct Graph_2
{
    int V, E;
    vector< pair<int, pair<int, int>> > edges;
    // Constructor 
    Graph_2(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({ w, {u, v} });
    }
    
	void Union(int N){
		
	}
    int kruskalMST() {
		sort(edges.begin(), edges.end());
		
		return weight;
	}

};

int main(){
    if(0){
        int V = 6;
        int visited = 0;

        Graph g(V);
        Adjacency* arr = new Adjacency(V);
        int edge[][2] = {{0,1},{0,2},{1,3},{1,4},{2,4},{3,4},{3,5},{4,5}};
            
        for(int i = 0; i < 8; i++)
        {
            g.addEdge(edge[i][0], edge[i][1]);
        }
            
        arr = g.BFS(visited);
        arr->printArray();
        delete arr;
    }
	if(0){
		int V = 8, visited = 0;

		Graph g(V);
		Adjacency *arr;
		int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
		for(int i = 0; i < 9; i++)
		{
			g.addEdge(edge[i][0], edge[i][1]);
		}
		arr = g.DFS(visited);
		arr->printArray();
		delete arr;
	}
	if(0){
		Graph g(6);
		g.addEdge(5, 2);
		g.addEdge(5, 0);
		g.addEdge(4, 0);
		g.addEdge(4, 1);
		g.addEdge(2, 3);
		g.addEdge(3, 1);

		g.topologicalSort();
	}
	if(0){
		DirectedGraph g(4); 
		int edege[][2] = {{0,1}, {0,2}, {1,2}, {2,0}, {2,3}, {3,3}};

		for(int i = 0; i < 6; i++)
			g.addEdge(edege[i][0], edege[i][1]);

		if(g.isCyclic()) 
			cout << "Graph contains cycle"; 
		else
			cout << "Graph doesn't contain cycle"; 
	}
	if(0){
		DirectedGraph g(4); 
		int edege[][2] = {{0,1}, {0,2}, {1,2}, {1,3}, {3,2}, {3,4}};

		for(int i = 0; i < 6; i++)
			g.addEdge(edege[i][0], edege[i][1]);

		if(g.isCyclic()) 
			cout << "Graph contains cycle"; 
		else
			cout << "Graph doesn't contain cycle";
	}
	if(0){
		int n = 6;
		int init[6][6] = {
			{0, 10, 20, 0, 0, 0},
			{10, 0, 0, 50, 10, 0},
			{20, 0, 0, 20, 33, 0},
			{0, 50, 20, 0, 20, 2},
			{0, 10, 33, 20, 0, 1},
			{0, 0, 0, 2, 1, 0} };

		int** graph = new int*[n];
		for (int i = 0; i < n; ++i) {
			graph[i] = init[i];
		}

		cout << Dijkstra(graph, 0, 1);
	}
	if(1){
		int V = 2, E = 1;
		Graph_2 g(V, E);

		g.addEdge(0, 1, 2);


		cout << g.kruskalMST();
	}
}