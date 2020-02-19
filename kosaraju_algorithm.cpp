// C++ implementation of Kosaraju algorithm to print all Strongly Conneceted Components of a Graph
#include<bits/stdc++.h>

using namespace std;

class Graph {
    int V;              // Number of Vertices
    list<int> *adj;     // array of adjacency lists

    // Following function fills stack with vertices,the top element of stack has maximum finishing time
    void fill_Order_of_finishing_time(int v, bool visited[], stack<int> &Stack);

    // A Recursive function to print DFS starting from v
    void DFS_Utilities(int v, bool visited[]);

    public:
        Graph(int V);
        void add_Edge(int v, int w);
        void print_SCCs();              // Function finds and prints all connected components
        Graph get_Transpose();          // Function that returns transpose of Graph
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::add_Edge(int v, int w) { 
    adj[v].push_back(w);                // Add w to v’s list. 
} 

// void PrintStack(stack<int> s) { 
//     // If stack is empty then return 
//     if (s.empty())  
//         return; 
//     int x = s.top(); 
//     // Pop the top element of the stack 
//     s.pop(); 
//     // Recursively call the function PrintStack 
//     PrintStack(s); 
//     // Print the stack element starting 
//     // from the bottom 
//     cout << x << " "; 
//     // Push the same element onto the stack 
//     // to preserve the order 
//     s.push(x); 
// } 

void Graph::fill_Order_of_finishing_time(int v, bool visited[], stack<int> &Stack) { 
    
    visited[v] = true;                   // Mark the current node as visited and print it
  
    list<int>::iterator i;               // Recur for all the vertices adjacent to this vertex 
    for(i = adj[v].begin(); i != adj[v].end(); i++) 
        if(visited[*i]==false) 
            fill_Order_of_finishing_time(*i, visited, Stack); 
  
    Stack.push(v);                       // All vertices reachable from v are processed by now, push v 
    // PrintStack(Stack);
    // cout << "\n";
    // cout << v << " ";
} 

void Graph::DFS_Utilities(int v, bool visited[]) {

    visited[v] = true;                  // Mark the current node as visited and print it 
    cout << v << " ";

    list<int>::iterator i;              // Recur for all the vertices adjacent to this vertex 
    for(i=adj[v].begin();i!=adj[v].end();i++) {
        if(visited[*i]==false)
            DFS_Utilities(*i,visited);
    }
}



Graph Graph::get_Transpose() { 
    Graph g(V); 
    for (int v=0;v<V;v++) {     
        list<int>::iterator i;          // Recur for all the vertices adjacent to this vertex 
        for(i=adj[v].begin();i!=adj[v].end();i++) { 
            g.adj[*i].push_back(v); 
        } 
    } 
    return g; 
} 




// The main function that finds and prints all strongly connected components 
void Graph::print_SCCs() { 
    stack<int> Stack; 
   
    bool *visited = new bool[V];        // Mark all the vertices as not visited (For first DFS) 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
   
    for(int i = 0; i < V; i++)          // Fill vertices in stack according to their finishing times
        if(visited[i] == false) 
            fill_Order_of_finishing_time(i, visited, Stack); 
  
    Graph gr = get_Transpose();         // Create a reversed graph 
   
    for(int i = 0; i < V; i++)          // Mark all the vertices as not visited (For second DFS) 
        visited[i] = false; 
    
    while (Stack.empty() == false) {    // Now process all vertices in order defined by Stack                                     
        int v = Stack.top();            // Pop a vertex from stack
        Stack.pop();                                   
        if (visited[v] == false) {      // Print Strongly connected component of the popped vertex
            gr.DFS_Utilities(v, visited); 
            cout << endl; 
        } 
    } 
} 

int main() {
    int v,e;
    cout << "Enter the number of vertices and edges in the Directed Graph\n";
    cin >> v >> e;
    Graph graph(v);
    cout << "Enter the Edges of the Directed Graph\n";
    int x,y;
    for(int i=0;i<e;i++) {
        cin >> x >> y;
        graph.add_Edge(x,y);
    }
    cout << "The Connected Components of the Given Graph are : \n";
    graph.print_SCCs();
    return 0;
}
