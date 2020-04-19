// #include<iostream>
// #include<fstream>
// #include<limits.h>
// #include<string.h>
// #include<queue>
#include<bits/stdc++.h>
#define MAX_NODES 10000


using namespace std;

int augment(int Gf[][MAX_NODES], int V, int f, int P[], int s, int t) {
    ///let b = bottleneck(P,f)
    int b = MAX_NODES;
    ///finding b
    for (int i=t; i!=s; i=P[i]) { 
        int temp = P[i]; 
        b = min(b, Gf[temp][i]); 
    }
    ///updating the residual graph Gf
    for(int i=t; i!=s; i=P[i]) {
        int temp = P[i];
        ///if e is forward edge then increase f in G by b
        Gf[i][temp] +=b;
        ///else e is backward edge then e=(v,u) decrease f in G by b
        Gf[temp][i] -= b;
    }
    f+=b;
    return f;
}

bool isThereAPath(int s, int t, int P[], int Gf[][MAX_NODES], int V) {
    bool visited[V];
    for(int i=0; i<V; i++) visited[i]=0;
    
    queue <int> q;
    q.push(s);
    visited[s]=true;
    P[s]=-1;
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        for(int v=0; v<V; v++) {
            if(visited[v]==false && Gf[u][v]>0) {
                q.push(v);
                P[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int fordFulkerson(int G[][MAX_NODES], int V, int s, int t) {
    
    ///initially f(e) = 0 for all e in G
    int f=0;
    ///making the residual graph Gf
    int Gf[MAX_NODES][MAX_NODES];
    for(int i=0; i<MAX_NODES; i++)
        for(int j=0; j<MAX_NODES; j++)
            Gf[i][j]=G[i][j];
            
    /// Let P be a simple s-t path in Gf
    int P[V];
            
    ///while there is an s-t path in the residual graph Gf
    while(isThereAPath(s, t, P, Gf, V)) {
        ///f' = augment(f,P)
        int f1 = augment(Gf,V,f,P,s,t);
        ///update f to be f'
        f=f1;
    }
    return f;
}

int main() {
    
    int V,n;
    int G[MAX_NODES][MAX_NODES];
    for(int i = 0; i < MAX_NODES; i++)
        for(int j = 0; j < MAX_NODES; j++)
            G[i][j]=0;
    int s,t;
    
    ///cin input part. To enter input manually. comment the file stream part and uncomment the cin input part
    cout<<"Please enter the number of vertices and edges \nthen the paths(first vertex is 1)\n";
    cin >> V >> n;
    
    

    //cin>>s>>t;
    s=0;
    t=V+1;


    //connecting s and t to the bipartite graph
    for(int i=1; i<=V/2; i++) {
        G[0][i] = 1;
        G[V/2+i][V+1] = 1;
    }

    for(int i=0; i<n; i++) {
        int a,b;
        cin>>a>>b;
        G[a][b] = 1;
    }

    

    ///file stream part. To enter input through file. uncomment the file stream part and comment the cin input part
    
    // fstream myfile;
    // myfile.open ("input.txt");
    // string word;
    // int wNo = 1;
    // int a,b,c;
    // while(myfile >> word) {
    //     if(wNo==1) {
    //         V=stoi(word);
    //         wNo++;
    //     }
    //     else if(wNo==2) {
    //         n=stoi(word);
    //         wNo++;
    //     }
    //     else if(wNo==3) {
    //         s=stoi(word);
    //         wNo++;
    //     }
    //     else if(wNo==4) {
    //         t=stoi(word);
    //         wNo++;
    //     }
    //     else {
    //         if(wNo%3==2) a=stoi(word);
    //         else if(wNo%3==0) b=stoi(word);
    //         else {
    //             c=stoi(word);
    //             G[a][b] = c;
    //         }
    //         wNo++;
    //     }
    // }
    // myfile.close();
    
    int ans = fordFulkerson(G, V+2, s, t);
    cout <<"answer : " << ans;
    return 0;
}


/*
TEST CASES for task 3:(number : anwer)
//1:5

12 8 
1 7 
1 8 
3 7 
3 10 
4 9 
5 9 
5 10 
6 12 

//2 : 5

10 9
1 6 
1 7 
2 6 
3 7 
3 8 
4 8 
4 9 
4 10 
5 10 


TEST CASES for task 1:(number : anwer)
//1: 5
14 20
0 13
0 1 1
0 2 1
0 3 1
0 4 1
0 5 1
0 6 1
1 7 1
1 8 1
3 7 1
3 10 1
4 9 1
5 9 1
5 10 1
6 12 1
7 13 1
8 13 1
9 13 1
10 13 1 
11 13 1
12 13 1

//2: 5
12 19
0 11
0 1 1
0 2 1
0 3 1
0 4 1
0 5 1
1 6 1
1 7 1
2 6 1
3 7 1
3 8 1
4 8 1
4 9 1
4 10 1
5 10 1
6 11 1
7 11 1
8 11 1
9 11 1
10 11 1

*/