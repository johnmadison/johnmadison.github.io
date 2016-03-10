//
//  main.cpp
//  kruskals
//
//  Created by John Madison on 12/3/15.
//  Copyright (c) 2015 cmu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class kruskal
{
private:
    int nodes; //number of nodes
    int edges; //number edges in the graph
    int graphEdges[300][4];
    int tree[10][10];
    int sets[300][10];
    int top[300];
public:
    int graphInput();
    void initialize_span_t();
    void sortTheEdges();
    void kruskals();
    int find_node(int );
};

int kruskal::graphInput()
{
    
    cout<<"Enter the number of nodes in the graph"<< endl;
    cin>>nodes;
    edges=0;
    
    cout<<endl<<"Enter the weights for the following edges "<< endl;
    
    for(int i=1;i<=nodes;i++)
    {
        for(int j=i+1;j<=nodes;j++)
        {
            cout<<i<<" , "<<j<<endl;
            int w;
            cin>>w;
            if(w!=0)
            {
                edges++;
                
                graphEdges[edges][1]=i;
                graphEdges[edges][2]=j;
                graphEdges[edges][3]=w;
            }
        }
    }
    
    // print the graph edges
    
    cout<<endl<<endl<<"The graph contains edges: "<< endl;
    for(int i=1;i<=edges;i++)
    {
        cout<<graphEdges[i][1] // starting edge
       <<" "<<graphEdges[i][2] // ending edge
<<" "<<graphEdges[i][3]<<endl; // weight of the edge
        
    }
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
    // ->make a set for each node
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
            
            // Mix the two sets
            
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

int main()
{
    kruskal obj;
    obj.graphInput(); //get the adjacency matrix from the console
    obj.sortTheEdges(); //sort edges in acending order
    obj.kruskals(); // use kruskals to get the MST
    return 0;
}