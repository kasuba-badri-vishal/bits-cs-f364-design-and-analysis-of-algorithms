#include<bits/stdc++.h>
#include<sys/resource.h>  
#include <chrono>
using namespace std::chrono;
using namespace std;

//Initialize parent array before calling BFS function
bool findPath(vector<pair<pair<int,int>,char>> Res[],int src,int sink,int parent[],int nVer){
    int visited[nVer+1];
    memset(visited,0,sizeof(visited));
    queue<int> BFS;
    BFS.push(src);
    parent[src]=-1;
    visited[src]=1;
    while(BFS.empty()==false){// in the graph see if edge has greater than 0 weight
        int v = BFS.front();
        BFS.pop();
        // cout<<"v is "<<v<<"\n";
        for (int i=0;i<Res[v].size();i++){
            if((Res[v][i].first).second!=0&&visited[Res[v][i].first.first]==0){
                // cout<<Res[v][i].first.first<<"\n";
                BFS.push(Res[v][i].first.first);
                parent[Res[v][i].first.first] = v;
                visited[Res[v][i].first.first]=1;
            }
        }
    }
    if(parent[sink]==0) return false;
    return true;
}
//Flow is always limited by capacity of S-T cut edges 
//max flow and min cut are same
//flow in edges from A to B is full capacity abd B to A is 0
int findMinCut(vector<pair<pair<int,int>,char>> Res[],vector<pair<int,int> > Capacity[],int src,int nVer){
    set<int> A; //set of all reachable vertices
    queue<int> BFS;
    int visited[nVer+1];
    memset(visited,0,sizeof(visited));
    BFS.push(src);
    while(BFS.empty()==false){// in the graph see if edge has greater than 0 weight
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
            }
        }
    }
    return capacity;
}


int findBottleNeck(vector<pair<pair<int,int>,char>> Res[],int source,int sink,int parent[],int nVer){
    int bottleNeck=INT_MAX;
    int v =sink;
    // cout<<"BottleNeck Finding\n"<<v<<"\n";
    // cout<<"BottleNeck Finding\n";
    while(parent[v]!=-1){
        // cout<<parent[v]<<"\n";
        //Edge is now from parent[v] to v
        for(int i=0;i<Res[parent[v]].size();i++){
            if(Res[parent[v]][i].first.first==v&&Res[parent[v]][i].first.second!=0){
                bottleNeck = min(bottleNeck,Res[parent[v]][i].first.second);
                break; //choose the first path
            }
        }
        v = parent[v];
    }
    return bottleNeck;
}

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
        // }
        
        int bottleNeck = findBottleNeck(Res,src,sink,parent,nVer);
        // cout<<bottleNeck<<"\n";
        maxflow += bottleNeck;
        // cout<<maxflow<<"\n";
        //a,b always decrease and b,a always increase in res graph
        int v=sink;
        while(parent[v]!=-1){
            // cout<<"Edge is "<<parent[v]<<" "<<v<<"\n";
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
        // cout<<"Residual Graph After Updation\n";
        // for(int i=1;i<=nVer;i++){
        //     cout<<i<<"\n";
        //     for(int j=0;j<Res[i].size();j++){
        //         cout<<Res[i][j].first.first<<" ";
        //         cout<<Res[i][j].first.second<<" ";
        //         cout<<Res[i][j].second<<"\n";
        //     }
        // }
        memset(parent,0,sizeof(parent));
    }
    int valueFlow=0;
    for(int i=0;i<Flow[src].size();i++){
        valueFlow+=Flow[src][i].second;
    }
    cout<<"Max Flow is "<<maxflow<<"\n";
    cout<<"Mincut Capacity is  "<<findMinCut(Res,Capacity,src,nVer)<<"\n";
    cout<<"Value of the Flow is "<<valueFlow<<"\n";
}

void BipartiteMatching(){
    // cout<<"Hello\n";
    int nVer,nEdg;
    int v1,v2,a,b;
    cin>>a>>b>>nEdg;
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
    fordFulkerson(Capacity,Flow,Res,src,sink,nVer);
}

int main(){
    rlimit R;
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);
    auto start = high_resolution_clock::now();
    BipartiteMatching();
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start); 
	cout << "Time taken: "<<duration.count() << endl;
    return 0;
    int nVer,nEdg;
    cin>>nVer>>nEdg;
    int v1,v2,edge;
    int src,sink;
    // map< pair<int,int>,int> Capacity;
    vector<pair<int,int> > Capacity[nVer+1];
    vector<pair<int,int> > Flow[nVer+1];
    vector<pair<pair<int,int>,char>> Res[nVer+1];
    int inDegree[nVer+1];
    int outDegree[nVer+1];
    memset(inDegree,0,sizeof(inDegree));
    memset(outDegree,0,sizeof(outDegree));
    for(int i=0;i<nEdg;i++){
        cin>>v1>>v2>>edge;
        // v1++;
        // v2++;
        outDegree[v1]++;
        inDegree[v2]++;
        // Capacity[make_pair(v1,v2)]=edge;
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
    fordFulkerson(Capacity,Flow,Res,src,sink,nVer);
    return 0;
}
