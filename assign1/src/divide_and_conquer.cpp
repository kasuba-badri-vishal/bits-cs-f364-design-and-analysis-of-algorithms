#include<bits/stdc++.h>
// #include<sys/resource.h> 
#include <chrono> 
using namespace std::chrono;
using namespace std;
#define N 1000
#define ll long long

/// This Program is the Implementation of **Divide_and_Conquer Algorithm** presented in the research paper.
///
/// We use DCSC, predecesser,descendent methods to find the **Stroingly Connected Components**.

unordered_map<int, list<int> > adj;
unordered_map<int, list<int> > rev_adj;

class Graph{
	public:
	int n_edges;
	set<int> V;

	/// This is a constructor for the Graph class.
	///	It is called by passing the number of edges as argument.
	///
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// Graph(int n_edges){
	/// 	this->n_edges = n_edges;
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param n_edges : number of edges
	/// @returns nothing is returned
	/// @see getPred() getDesc()  main()
	/// @note This is a constructor of Graph class
	/// @attention It is required to specify n_edges
	/// @warning There is another constructor with different type, so argument is crucial to call one constructor.

	Graph(int n_edges){
		this->n_edges = n_edges;
	}

	/// This is a Constructor for the graph class.
	/// This constructor is called by passing a list of vertices as argument.
	/// It creates a subgraph of the Graph specified by adj (adjacency list) using 
	/// a subset of vertices.
	///
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	///	Graph(set<int> V1){
	/// 	V = V1;
	/// 	n_edges = 0;
	/// 	for(auto x: V){
	/// 		for(auto y: adj[x]){
	/// 			if(V.find(y)!=V.end()) n_edges++;
	/// 		}
	/// 	}
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param V1 : set of vertices
	/// @returns nothing is returned
	/// @see main()
	/// @note This is a constructor
	/// @attention This is constructor for the graph
	/// @warning It is required to specify V1

	Graph(set<int> V1){
		V = V1;
		n_edges = 0;
		for(auto x: V){
			for(auto y: adj[x]){
				if(V.find(y)!=V.end()) n_edges++;
			}
		}
	}

	/// This is a function that runs Breadth first search starting 
	/// from the node passed as argument, to find all of its predecessors.
	///	It uses the transpose of the original adjacency matrix.
	///
	/// @param x : node for which predecessors are required
	/// @returns s: set of predecessor nodes
	/// @see getDesc()  main()
	/// @note This is a method
	/// @warning It is required to specify x

	set<int> getPred(int x){
		queue<int> q; 
		set<int> s;
		q.push(x); 
		s.insert(x);
		while (!q.empty()) { 
			int f = q.front(); 
			q.pop(); 
			for (auto i:rev_adj[f]) { 
				if ((V.find(i)!=V.end()) && (s.find(i)==s.end())) { 
					try{
						q.push(i); 
						s.insert(i);
					}catch (std::bad_alloc & ba) {
						cout  << "queue bad alloc caught\n";
					}	
				} 
			} 
   	 	} 
		return s;
	}

	/// This is a function that runs Breadth first search starting 
	/// from the node passed as argument, to find all of its descendents.
	///	It uses the original adjacency matrix in its bfs.
	///
	/// @param x : node for which descendents are required
	/// @returns s: set of descendent nodes
	/// @see getPred()  main()
	/// @note This is a method
	/// @warning It is required to specify x

	set<int> getDesc(int x){
		queue<int> q; 
		set<int> s;
		q.push(x); 
		s.insert(x);
		while (!q.empty()) { 
			int f = q.front(); 
			q.pop(); 
			for (auto i:adj[f]) { 
				if ((V.find(i)!=V.end()) && (s.find(i)==s.end())) { 
					q.push(i); 
					s.insert(i);
				} 
			} 
   	 	} 
		return s;
	}

};


/// This is the core function of the Divide and Conquer Algorithm to find Strongly Connected Components.
///
/// ### Algorithm
/// ~~~~~~~~~~~~~~~~~~~~~~
/// DCSC(G)
/// 	If G has no edges then
/// 		forall v in V Output {v}.
/// 	Else
/// 		Select a random vertex v from V
/// 		SCC <- Pred(G, v) \ Desc(G, v)
/// 		Output SCC
/// 		DCSC(Pred(G, v) \ SCC)
/// 		DCSC(Desc(G, v) \ SCC)
/// 		DCSC(Rem(G, v))
/// ~~~~~~~~~~~~~~~~~~~~~~
/// @param g : Graph on which the algorithm is to be applied
/// @returns nothing is returned
/// @see getPred() getDesc()  main()

void DCSC(Graph g){
	if(g.n_edges == 0){
		for(int i:g.V) cout << i << "\n";
	}else{
		int x = *g.V.begin();
		set<int> pred = g.getPred(x);
		set<int> desc = g.getDesc(x);

		set<int> SCC;
		set_intersection(pred.begin(), pred.end(), desc.begin(), desc.end(), inserter(SCC, SCC.begin()));
		for(auto i: SCC){
			cout << i << " ";
		}
		cout << "\n";

		set<int> a;
		set_difference(pred.begin(), pred.end(), SCC.begin(), SCC.end(), inserter(a, a.begin()));
		Graph g1 = Graph(a);
		DCSC(g1);

		set<int> b;
		set_difference(desc.begin(), desc.end(), SCC.begin(), SCC.end(), inserter(b, b.begin()));
		Graph g2 = Graph(b);
		DCSC(g2);

		set<int> rem;	
		pred.insert(desc.begin(), desc.end());
		set_difference(g.V.begin(), g.V.end(), pred.begin(), pred.end(), inserter(rem, rem.begin()));
		Graph g3 = Graph(rem);
		DCSC(g3);
	}

}

/// This is the main function of this c++ program.
///	A graph object is created using data from input and 
/// the function DCSC is called on this graph.
///
/// 
/// @returns int
/// @see DCSC()
/// @note This is the main function

int main(){
	/* uncomment the lines below and <sys.resource.h> 
	header to increase stack mem in linux.*/

	// rlimit R;
	// getrlimit(RLIMIT_STACK, &R);
	// R.rlim_cur = R.rlim_max;
	// setrlimit(RLIMIT_STACK, &R);

	int v, e; cin >> v >> e;

	Graph g = Graph(e);
	set<int> V;

	for(int i=0; i<e; i++){
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		rev_adj[y].push_back(x);
		g.V.insert(x);
		g.V.insert(y);
	}

	auto start = high_resolution_clock::now(); 
	DCSC(g);
	auto stop = high_resolution_clock::now(); 

	auto duration = duration_cast<microseconds>(stop - start); 

	cout << "\nTime taken: " << (duration.count()/(double)1000000.0) << " s\n";

	return 0;
}