#include<bits/stdc++.h>
#include<sys/resource.h>
#include <chrono> 
using namespace std::chrono;
using namespace std;


int Bipar = 0;
int nVSet1=0;
/// This Program is the implementation the "Ford-Fulkerson" algorithm to find the maximum flow and minimum cut.

/// This function finds if a path exists between source node and sink node using BFS.
///
/// Initialize parent array before calling BFS function
///
/// @param Res : an array of vectors. Each vector is a pair of pair<int, int> and char.
/// @param src : an integer, source node.
/// @param sink : an integer, sink node.
/// @param parent : array of parent nodes.
/// @param nVer : number of vertices.
/// @returns boolean. True if a path is found else False.

bool findPath(vector<pair<pair<int,int>,char>> Res[],int src,int sink,int parent[],int nVer){
    int visited[nVer+1];
    memset(visited,0,sizeof(visited));
    queue<int> BFS;
    BFS.push(src);
    parent[src]=-1;
    visited[src]=1;
    while(BFS.empty()==false){
        int v = BFS.front();
        BFS.pop();
        for (int i=0;i<Res[v].size();i++){
            // Consider only the edges that have greater than 0 value
            if((Res[v][i].first).second!=0&&visited[Res[v][i].first.first]==0){
                BFS.push(Res[v][i].first.first);
                parent[Res[v][i].first.first] = v;
                visited[Res[v][i].first.first]=1;
            }
        }
    }
    if(parent[sink]==0) return false;
    return true;
}

/// This function finds an s-t cut of minimum capacity between the two partitions.
///
/// Flow is always limited by capacity of S-T cut edges 
/// max flow and min cut are same
/// flow in edges from A to B is full capacity and B to A is 0
///
/// @param Res : an array of vectors. Each vector is a pair of pair<int, int> and char.
/// @param Capacity : an array of vectors. Each vector is a pair of integers.
/// @param src : an integer, source node.
/// @param nVer : number of vertices.
/// @returns integer. minimum capacity.

int findMinCut(vector<pair<pair<int,int>,char>> Res[],vector<pair<int,int> > Capacity[],int src,int nVer){
    set<int> A; //set of all reachable vertices
    queue<int> BFS;
    int visited[nVer+1];
    memset(visited,0,sizeof(visited));
    BFS.push(src);
    while(BFS.empty()==false){
        int v = BFS.front();
        BFS.pop();
        A.insert(v);
        for (int i=0;i<Res[v].size();i++){
            if((Res[v][i].first).second!=0&&visited[Res[v][i].first.first]==0){ //still there is an edge of non zero weight
                BFS.push(Res[v][i].first.first);
                visited[Res[v][i].first.first]=1;
            }
        }
    }
    int capacity = 0;
    for(auto iter:A){
        for(int i=0;i<Capacity[iter].size();i++){
            if(A.find(Capacity[iter][i].first)==A.end()){
                capacity+=Capacity[iter][i].second;
                //This is a vertex that is not in Reachable set so this edge contributes to max flow at full capacity
                cout<<iter<<" "<<Capacity[iter][i].first<<"\n";
                //For a Bipartite case if we want to print Vertices Seperately
                // if(Bipar==1){
                //     cout<<iter-1<<" "<<Capacity[iter][i].first-nVSet1-1<<"\n";
                // }
            }
        }
    }
    return capacity;
}

/// This function finds the bottleneck capacity in all paths between source and sink.
///
/// @param Res : an array of vectors. Each vector is a pair of pair<int, int> and char.
/// @param Capacity : an array of vectors. Each vector is a pair of integers.
/// @param src : an integer, source node.
/// @param sink : an integer, sink node.
/// @param parent : array of parent nodes.
/// @param nVer : number of vertices.
/// @returns integer. the bottleneck capactiy.

int findBottleNeck(vector<pair<pair<int,int>,char>> Res[],int source,int sink,int parent[],int nVer){
    int bottleNeck=INT_MAX;
    int v =sink;
    while(parent[v]!=-1){
        //Edge is now from parent[v] to v
        for(int i=0;i<Res[parent[v]].size();i++){
            if(Res[parent[v]][i].first.first==v&&Res[parent[v]][i].first.second!=0){
                bottleNeck = min(bottleNeck,Res[parent[v]][i].first.second);
                break; //Always chooses the first path if there are multiple one's
            }
        }
        v = parent[v];
    }
    return bottleNeck;
}

/// This function implements the ford-fulkerson's algorithms to find maxflow-mincut of a graph.
///
/// @param Capacity : an array of vectors. Each vector is a pair of integers (edge). Represents capacity of edges.
/// @param Flow : an array of vectors. Each vector is a pair of integers (edge). Represents flow of edges.
/// @param Res : an array of vectors. Each vector is a pair of pair<int, int> and char.
/// @param src : an integer, source node.
/// @param sink : an integer, sink node.
/// @param nVer : number of vertices.
/// @returns none

void fordFulkerson(vector<pair<int,int> > Capacity[],vector<pair<int,int> > Flow[],vector<pair<pair<int,int>,char>> Res[],int src,int sink,int nVer){
    int maxflow = 0;
    int parent[nVer+1];
    memset(parent,0,sizeof(parent));
    while(findPath(Res,src,sink,parent,nVer)==true){
        // cout<<"Path is -\n";
        // int v=sink;
        // while(parent[v]!=-1){
        //     cout<<parent[v]<<" "<<v<<"\n";
        //     v = parent[v];
        // } //Path from Source to Sink
        
        int bottleNeck = findBottleNeck(Res,src,sink,parent,nVer);
        maxflow += bottleNeck;
        cout<<maxflow<<"\n";
        //a,b always decrease and b,a always increase in res graph irrespective of chosen edge is forward or backward
        int v=sink;
        while(parent[v]!=-1){
            int forw=0;
            for(int i=0;i<Res[parent[v]].size();i++){
                if(Res[parent[v]][i].first.first==v&&Res[parent[v]][i].first.second!=0){
                    if(Res[parent[v]][i].second=='f') forw=1;
                    Res[parent[v]][i].first.second-=bottleNeck;
                    break;
                }
            }
            for(int i=0;i<Res[v].size();i++){
                if(Res[v][i].first.first==parent[v]){
                    Res[v][i].first.second+=bottleNeck;
                    break;
                }
            }
            if(forw==1){
                for(int i=0;i<Flow[parent[v]].size();i++){
                    if(Flow[parent[v]][i].first==v){
                        Flow[parent[v]][i].second+=bottleNeck;
                        break;
                    }
                }
            }
            else{
                 for(int i=0;i<Flow[v].size();i++){
                    if(Flow[v][i].first==parent[v]){
                        Flow[v][i].second+=bottleNeck;
                        break;
                    }
                }
            }
            v=parent[v];
        }
        memset(parent,0,sizeof(parent));
    }
    int valueFlow=0;
    for(int i=0;i<Flow[src].size();i++){
        valueFlow+=Flow[src][i].second;
    }
    cout<<"Max Flow is "<<maxflow<<"\n";
    cout<<"Mincut Edges are \n"<<findMinCut(Res,Capacity,src,nVer)<<"\n";
    // cout<<"Value of the Flow is "<<valueFlow<<"\n";
}


/// This function implements bipartite matching using ford-fulkerson algorithm.
///
/// The input is used to construct the residual graph (Res) and then fordfulkerson() function 
/// is run on it.
///
/// @returns none.
/// @see fordFulkerson() 

void BipartiteMatching(){
    cout<<"Bipartite Matching started...\n";
    Bipar=1;
    int nVer,nEdg;
    int v1,v2,a,b;
    cin>>a>>b>>nEdg;
    nVSet1=a;
    nVer=a+b+2;
    int src=1,sink=nVer;
    vector<pair<int,int> > Capacity[nVer+1];
    vector<pair<int,int> > Flow[nVer+1];
    vector<pair<pair<int,int>,char>> Res[nVer+1];
    for(int i=1;i<=nEdg;i++){
        cin>>v1>>v2;
        //vertex in first set are 2 3 a+1..... 16501 
        //a+1+v2 
        v1++;
        v2 = a+1+v2;
        Capacity[v1].push_back(make_pair(v2,1));
        Flow[v1].push_back(make_pair(v2,0));
        Res[v1].push_back(make_pair(make_pair(v2,1),'f'));
        Res[v2].push_back(make_pair(make_pair(v1,0),'b'));
    }
    for(int i=2;i<=a+1;i++){
        Capacity[1].push_back(make_pair(i,1));
        Flow[1].push_back(make_pair(i,0));
        Res[1].push_back(make_pair(make_pair(i,1),'f'));
        Res[i].push_back(make_pair(make_pair(1,0),'b'));
    }
    for(int i=a+2;i<nVer;i++){
        Capacity[i].push_back(make_pair(sink,1));
        Flow[i].push_back(make_pair(sink,0));
        Res[i].push_back(make_pair(make_pair(sink,1),'f'));
        Res[sink].push_back(make_pair(make_pair(i,0),'b'));
    }
	
    //Finding time taken for Bipartite matching
    auto start = high_resolution_clock::now();

    fordFulkerson(Capacity,Flow,Res,src,sink,nVer);

    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start); 

	cout << "Time taken: "<<duration.count() << endl;
}


/// This is the main function.
/// A residual graph is constructed using the data from input.
///
/// @returns integer, 0.
/// @see fordFulkerson()  BipartiteMatching()
/// @note We have used *high_resolution_clock* for finding the time taken for the entire program to run.
int main(){
    //Increase Limits of stack to work on Larger Graphs
    rlimit R;
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);

    // //// uncomment below two lines to find bipartite matching
    BipartiteMatching();
    return 0;

    int nVer,nEdg;
    cin>>nVer>>nEdg;
    int v1,v2,edge;
    int src,sink;
    vector<pair<int,int> > Capacity[nVer+1];
    vector<pair<int,int> > Flow[nVer+1];
    vector<pair<pair<int,int>,char>> Res[nVer+1];
    int inDegree[nVer+1];
    int outDegree[nVer+1];
    memset(inDegree,0,sizeof(inDegree));
    memset(outDegree,0,sizeof(outDegree));
    for(int i=0;i<nEdg;i++){
        cin>>v1>>v2>>edge;
        v1++;
        v2++; //Depends on whether indexing starts from 1 or 0
        outDegree[v1]++;
        inDegree[v2]++;
        Capacity[v1].push_back(make_pair(v2,edge));
        Flow[v1].push_back(make_pair(v2,0));
        Res[v1].push_back(make_pair(make_pair(v2,edge),'f'));
        Res[v2].push_back(make_pair(make_pair(v1,0),'b'));
    }
    for(int i=1;i<=nVer;i++){
        if(inDegree[i]==0){
            src = i;
        }
    }
    for(int i=1;i<=nVer;i++){
        if(outDegree[i]==0){
            sink = i;
        }
    }
    cout<<"Source "<<src<<"\n";
    cout<<"Sink "<<sink<<"\n";
    // cout<<"Flow Graph\n";
    // for(int i=1;i<=nVer;i++){
    //     cout<<i<<"\n";
    //     for(int j=0;j<Flow[i].size();j++){
    //         cout<<Flow[i][j].first<<" ";
    //         cout<<Flow[i][j].second<<"\n";
    //     }
    // }
    // cout<<"Residual Graph\n";
    // for(int i=1;i<=nVer;i++){
    //     cout<<i<<"\n";
    //     for(int j=0;j<Res[i].size();j++){
    //         cout<<Res[i][j].first.first<<" ";
    //         cout<<Res[i][j].first.second<<" ";
    //         cout<<Res[i][j].second<<"\n";
    //     }
    // }

    //Finding time taken to find maximum Network flow
	auto start = high_resolution_clock::now();

    fordFulkerson(Capacity,Flow,Res,src,sink,nVer);

    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start); 
	cout << "Time taken: "<<duration.count() << endl;

    return 0;
}