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
	/// This constructor is called before calling insertEdge() function
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


	/// This is a method inside the *Graph class* for the graph indicating insertion of edges
	///
	/// This method is called after Graph() constructor is called.
	/// ### Function insertEdge
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// void insertEdge(int a,int b){
	/// 	adj[a].push_back(b); //lists are only for those which have outgoing edges
	/// 	vertices.insert(a);
	/// 	vertices.insert(b);  //all vertices  are in set right now
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param a : vertex of Graph having *outgoing edge* to b
	/// @param nE : vertex of Graph having *incoming edge* from a
	/// @returns nothing is returned
	/// @see Graph()  main()
	/// @note This is a function inside Graph class and we are adding all vertices into set - *vertices*
	/// @warning It is required to specify a and b

	void insertEdge(int a,int b){
		adj[a].push_back(b); //lists are only for those which have outgoing edges
		vertices.insert(a);
		vertices.insert(b);  //all vertices  are in set right now
	}

	/// This is a method inside the *Graph class* for reversing the graph
	///
	/// We reverse the graph for comparing original graph to find *SCC*.
	/// ### Function looks like this
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// Graph reverseGraph(){
	/// 	Graph newGraph =  Graph(nV,nE);
	/// 	for(auto i :adj){
	/// 		for(auto j:i.second){
	/// 			newGraph.adj[j].push_back(i.first);
	/// 		}
	/// 	}
	/// 	return newGraph;
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @returns The function returns newGraph which is reversed it's edge directions
	/// @see topological_sort()  main()
	/// @note Reversed Graph contains same no. of vertices and edges just direction of edges changes.

	Graph reverseGraph(){
		Graph newGraph =  Graph(nV,nE);
		for(auto i :adj){
			for(auto j:i.second){
				newGraph.adj[j].push_back(i.first);
			}
		}
		return newGraph;
	}

	/// This is a method inside Graph Class which does sorts vertices inside graph using topological sorting
	/// based on vertices if they are visited or not and push them onto the stack *Top_order*
	/// This is similar to insertEdge()
	/// ### Topological Sort function
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// void topological_sort(int vertex){
	/// 	visited.insert(vertex); // insert element into set of visited vertices
	/// 	list<int>::iterator iter;
	/// 	for(iter = adj[vertex].begin(); iter!= adj[vertex].end();iter++){
	/// 		if(visited.find(*iter)==visited.end()){
	/// 			topological_sort(*iter);
	/// 		}
	/// 	}
	/// 	Top_order.push(vertex);
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param vertex : vertex of Graph which is the next visited vertex
	/// @returns nothing is returned
	/// @see DFS()  main()
	/// @note This function helps in building stack which is used to compare original graph and reversed graph for finding SCC.
	/// @attention This is a linear ordering of vertices and done for Directed Acyclic Graphs

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

	/// This is a method inside Graph Class which does *Depth First Search* on the Graph
	///
	/// We traverse 
	/// ### DFS function
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// void DFS(int vertex){
	/// 	cout<<vertex << " ";
	/// 	DFSvisited.insert(vertex);
	/// 	list<int>::iterator iter;
	/// 	for(iter = adj[vertex].begin(); iter!= adj[vertex].end();iter++){
	/// 		if(DFSvisited.find(*iter)==DFSvisited.end()){
	/// 			DFS(*iter);
	/// 		}
	/// 	}
	/// }	
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param vertex : vertex of Graph on which DFS is performed
	/// @returns nothing is returned
	/// @see topological_sort()  main()
	/// @note DFS is done two times in kosaraju_algorithm and DFS is a recursive function

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

/// This is the main function which initializes object instance of graph class
/// We build the graph by calling Graph class methods and by using **topological sorting** we traverse on vertices
/// We build the reverse of graph and check whether both DFS traversal results in same vertex for entire graph
///
/// @returns nothing is returned. the result is just printed
/// @see reverseGraph()  topological_sort()
/// @note We have used *high_resolution_clock* for finding the time taken for the entire program to run.
/// @attention No loops are allowed for the graph

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