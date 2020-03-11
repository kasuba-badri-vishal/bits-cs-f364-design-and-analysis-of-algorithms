#include<bits/stdc++.h>
// #include<sys/resource.h> 
#include <chrono> 
using namespace std::chrono;
using namespace std;
#define N 1000
#define ll long long

/// This Program is the Implementation of **Divide_and_Conquer Algorithm** defined in the research paper.
///
/// We use DCSC, predecesser,descendent methods to find the **Connected Components**.

unordered_map<int, list<int> > adj;
unordered_map<int, list<int> > rev_adj;

class Graph{
	public:
	int n_edges;
	set<int> V;

	/// This is Constructor for the graph indicating number of edges
	///
	/// nodes are vertices and edges are connections. This constructor is called for instanciating Graph
	/// ### Example
	/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
	/// Graph(int n_edges){
	/// 	this->n_edges = n_edges;
	/// }
	/// ~~~~~~~~~~~~~~~~~~~~~~
	/// @param n_edges : number of edges
	/// @returns nothing is returned
	/// @see get_pred()  main()
	/// @note This is a constructor of Graph class
	/// @attention It is required to specify n_edges
	/// @warning There is another constructor with different type, so argument is crucial to call one constructor.

	Graph(int n_edges){
		this->n_edges = n_edges;
	}

	/// This is Constructor for the graph 
	///
	/// nodes are vertices and edges are connections. This constructor is called first of insertEdge()
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
	/// @param nV : Number of Vertices
	/// @param nE : Number of Edges
	/// @returns nothing is returned
	/// @see insertEdge()  main()
	/// @note This is a constructor
	/// @attention This is constructor for the graph
	/// @warning It is required to specify nV and nE

	Graph(set<int> V1){
		V = V1;
		n_edges = 0;
		for(auto x: V){
			for(auto y: adj[x]){
				if(V.find(y)!=V.end()) n_edges++;
			}
		}
	}

	/// This is Constructor for the graph indicating nodes and edges
	///
	/// nodes are vertices and edges are connections. This constructor is called first of insertEdge()
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

	/// This is Constructor for the graph indicating nodes and edges
	///
	/// nodes are vertices and edges are connections. This constructor is called first of insertEdge()
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


/// This is Constructor for the graph indicating nodes and edges
///
/// nodes are vertices and edges are connections. This constructor is called first of insertEdge()
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

/// This is Constructor for the graph indicating nodes and edges
///
/// nodes are vertices and edges are connections. This constructor is called first of insertEdge()
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