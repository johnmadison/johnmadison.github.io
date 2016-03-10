//
//  main.cpp
//  dijkstra and kruskal CS Graphs Final Project
//
//  Created by John Madison on 12/2/15.

#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <fstream>
#include <iomanip>
#define INF INT_MAX //Infinity

using namespace std;

class kruskal
{
private:
    int nodes; //number of nodes
    int edges; //number edges in the graph
    int graphEdges[300][4];
    int tree[300][300];
    int sets[300][10];
    int top[300];
public:
    int graphInput();
    void initialize_span_t();
    void sortTheEdges();
    void kruskals();
    int find_node(int );
};

const int size=10001; //Maximum possible number of nodes
vector< pair<int,int> > a[size]; //Adjacency list as a vector of pairs. Fancy shmancy.
int dist[size]; //Stores shortest distance in an array
bool visited[size]={0}; //I feel like I've been here before. Better check.

void Dijkstra(int source, int n)
{
    for(int i=0;i<size;i++) //Set all distances initially to Infinity
        dist[i]=INF;
    //now lets determine priority for priority queue (the shortest edge goes first)
    class priority{
        public: bool operator ()(pair<int, int>&p1 ,pair<int, int>&p2){return p1.second>p2.second;}};
    priority_queue<pair<int,int> ,vector<pair<int,int> >, priority> pq; // jeez I love <queue> and <vector>
    pq.push(make_pair(source,dist[source]=0)); // push 0... push 0... push 0 real good.
    while(!pq.empty())
    {
        pair<int, int> curr=pq.top(); //Current vertex. we've already found its shortest distance.
        pq.pop();
        int cv=curr.first,cw=curr.second; //'cw' the final shortest distance for this vertex
        if(visited[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
            continue;
        visited[cv]=true;
        for(int i=0;i<a[cv].size();i++) //Iterating through all adjacent vertices
            if(!visited[a[cv][i].first] && a[cv][i].second+cw<dist[a[cv][i].first])
                //if we found a new shortest distance, update that sucka!
                pq.push(make_pair(a[cv][i].first,(dist[a[cv][i].first]=a[cv][i].second+cw)));
                //Set the new distance and add to priority queue
    }
}

int kruskal::graphInput()
{
    cout<<"Enter the number of nodes in the graph for Kruskal"<< endl;
    cin>>nodes;
    edges=0;
    cout<<endl<<"Enter the weights for the following edges for Kruskals"<< endl;
    
    for(int i=1;i<=nodes;i++)
    {
        for(int j=i+1;j<=nodes;j++)
        {
            cout<<i<<" , "<<j<<endl;
            int weight;
            cin>>weight;
            if(weight!=0)
            {
                edges++;
                graphEdges[edges][1]=i;
                graphEdges[edges][2]=j;
                graphEdges[edges][3]=weight;
            }
        }
    }
    
//    // print the graph edges
//    
//    cout<<endl<<endl<<"The graph contains edges: "<< endl;
//    for(int i=1;i<=edges;i++)
//    {
//        cout<<graphEdges[i][1] // starting edge
//        <<" "<<graphEdges[i][2] // ending edge
//        <<" "<<graphEdges[i][3]<<endl; // weight of the edge
//        
//    }
    return 0;
}

void kruskal::sortTheEdges() // our best buddy bubble sort :)
{
    for(int i=1;i<=edges-1;i++)
    {
        for(int j=1;j<=edges-i;j++)
        {
            if(graphEdges[j][3]>graphEdges[j+1][3])
            {
                int t=graphEdges[j][1];
                graphEdges[j][1]=graphEdges[j+1][1];
                graphEdges[j+1][1]=t;
                
                t=graphEdges[j][2];
                graphEdges[j][2]=graphEdges[j+1][2];
                graphEdges[j+1][2]=t;
                
                t=graphEdges[j][3];
                graphEdges[j][3]=graphEdges[j+1][3];
                graphEdges[j+1][3]=t;
            }
        }
    }
    
    // print the graph edges
    //  cout<<endl<<endl<<"After sorting the edges in the given graph are: "<<endl;
    //    for(int i=1;i<=edges;i++)
    //        cout<<""<< graph_edge[i][1]
    //        <<" , "<<graph_edge[i][2]
    //        <<" > weight: "<<graph_edge[i][3]<<endl;
}

void kruskal::kruskals()
{
    int totalweight = 0;
    // each node gets it's very own set!
    for(int i=1;i<=nodes;i++)
    {
        sets[i][1]=i;
        top[i]=1;
    }
    
    cout<<endl<<"Minimal Spanning Tree: "<<endl<<endl;
    
    for(int i=1;i<=edges;i++)
    {
        int p1=find_node(graphEdges[i][1]);
        int p2=find_node(graphEdges[i][2]);
        if(p1!=p2)
        {
            cout
            <<" < "<<graphEdges[i][1]<<" , "
            <<graphEdges[i][2]<<" > "<<endl;
            totalweight += graphEdges[i][3];
            
            tree[graphEdges[i][1]][graphEdges[i][2]]=graphEdges[i][3];
            tree[graphEdges[i][2]][graphEdges[i][1]]=graphEdges[i][3];
            
            // Put the lime in the coconut and Mix em sets up...
            
            for(int j=1;j<=top[p2];j++)
            {
                top[p1]++;
                sets[p1][top[p1]]=sets[p2][j];
            }
            
            top[p2]=0;
        }
        else
        {
            //            cout<<"the edge < "
            //            <<graph_edge[i][1]<<" , "
            //            <<graph_edge[i][2]<<" > "<<"forms a cycle so we trash it"<<endl
        }
    }
    cout << "total weight = " << totalweight << endl;
}

int kruskal::find_node(int n)
{
    for(int i=1;i<=edges;i++)
    {
        for(int j=1;j<=top[i];j++)
        {
            if(n==sets[i][j])
                return i;
        }
    }
    
    return -1;
}

int KruskalMain()
{
    kruskal obj;
    obj.graphInput(); //get the adjacency matrix from the console
    obj.sortTheEdges(); //sort edges in acending order
    obj.kruskals(); // use kruskals to get the MST
    return 0;
}

int DijkstraMain()
{
    int nodes,edges,vertex1,vertex2,weight;
    int totalweights = 0;
    cout<<"Enter number of nodes and edges in the graph for Dijkstra"<<endl;
    cin>>nodes>>edges;
    for(int i=0;i<edges;i++) //and now its time to play BUILD... THE... GRAPH...
    {
        cin>>vertex1>>vertex2>>weight; // get some data from da console!
        totalweights += weight;
        a[vertex1].push_back(make_pair(vertex2,weight));
        a[vertex2].push_back(make_pair(vertex1,weight));
    }
    cout<<"Enter source for Dijkstra's SSSP algorithm"<<endl;
    int source;
    cin>>source;
    Dijkstra(source,nodes);//path from source (passing number of nodes)
    cout<<"Source is: "<<source<<". The shortest distance to every other vertex from here is: \n";
    for(int i=1;i<=nodes;i++)//Printing final shortest distances from source
    {
        cout<<"Vertex: "<<i<<" , Distance: ";
        dist[i]!=INF? cout<<dist[i]<<"\n" : cout<<"-1\n";
    }
    cout << "Total Weight of All Edges: " << totalweights << endl;
    return 0;
}

int main(){
    DijkstraMain();
    KruskalMain();
}