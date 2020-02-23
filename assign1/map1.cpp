#include<bits/stdc++.h>
#include <chrono> 
using namespace std::chrono;
using namespace std;

/// This Program is the Implementation of **Kosaraju Algorithm**.
///
/// We use two *DFS* algorithmic searches to find the **Connected Components**.

class Graph{
public:
	int nV,nE;
	map<int,list<int> > adj; 
	unordered_set<int> visited;
	unordered_set<int> DFSvisited;
	set<int,greater<int> >vertices;
	stack<int> Top_order;

	/// This is Constructor for the graph indicating nodes and edges
	///
	/// nodes are vertices and edges are connections. This is similar to insertEdge()
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// Graph(int nV,int nE) { // constructor
	/// 	this->nV = nV;
	///		this->nE = nE;
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param nV : Number of Vertices
	/// @param nE : Number of Edges
	/// @returns nothing is returned
	/// @see insertEdge()  main()
	/// @note This is a constructor
	/// @attention This is constructor for the graph
	/// @warning It is required to specify nV and nE

	Graph(int nV,int nE){
		this->nV = nV;
		this->nE = nE;
	}

	void insertEdge(int a,int b){
		adj[a].push_back(b); //lists are only for those which have outgoing edges
		vertices.insert(a);
		vertices.insert(b);  //all vertices  are in set right now
	}

	Graph reverseGraph(){
		Graph newGraph =  Graph(nV,nE);
		for(auto i :adj){
			for(auto j:i.second){
				newGraph.adj[j].push_back(i.first);
			}
		}
		return newGraph;
	}

	void topological_sort(int vertex){
		visited.insert(vertex); // insert element into set of visited vertices
		list<int>::iterator iter;
		for(iter = adj[vertex].begin(); iter!= adj[vertex].end();iter++){
			if(visited.find(*iter)==visited.end()){
				topological_sort(*iter);
			}
		}
		Top_order.push(vertex);
	}

	void DFS(int vertex){
		cout<<vertex << " ";
		DFSvisited.insert(vertex);
		list<int>::iterator iter;
		for(iter = adj[vertex].begin(); iter!= adj[vertex].end();iter++){
			if(DFSvisited.find(*iter)==DFSvisited.end()){
				DFS(*iter);
			}
		}
	}	
};
int main(){

	auto start = high_resolution_clock::now();

	int nV,nE,v1,v2;
	cin>>nV>>nE;
	Graph g =  Graph(nV,nE);

	for(int i=0;i<nE;i++){
		cin>>v1>>v2;
		g.insertEdge(v1,v2);
	}

	for(auto i:g.vertices){
		// i is vertex in set of all vertices
		if(g.visited.find(i)==g.visited.end()){
			g.topological_sort(i);
		}
	} 

	Graph newGraph = g.reverseGraph();

	cout<<"\nConnnected Components are :\n";
	while(g.Top_order.empty()==false){
		int vertex = g.Top_order.top();
		if(newGraph.DFSvisited.find(vertex)==newGraph.DFSvisited.end()){
			newGraph.DFS(vertex);
			cout<<"\n";
		}
		g.Top_order.pop();
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start); 
	cout << "Time taken: "<<duration.count() << endl;

	return 0;
}