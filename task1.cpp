// #include<iostream>
// #include<fstream>
// #include<limits.h>
// #include<string.h>
// #include<queue>
#include<bits/stdc++.h>
#define MAX_NODES 1000000000


using namespace std;

int augment(vector<vector<int>> &Gf, int V, int f, vector<int> &P, int s, int t) {
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

bool isThereAPath(int s, int t, vector<int> &P, vector<vector<int>> &Gf, int V) {
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

int fordFulkerson(vector<vector<int>> &G, int V, int s, int t) {
	
	///initially f(e) = 0 for all e in G
    int f=0;
    ///making the residual graph Gf
    vector<vector<int>> Gf(V, vector<int>(V));
    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
            Gf[i][j]=G[i][j];
            
    /// Let P be a simple s-t path in Gf
    vector<int> P(V);
            
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
	int s,t;
	
    ///cin input part. To enter input manually. comment the file stream part and uncomment the cin input part
// 	cin >> V >> n;
// 	cin>>s>>t;
//     vector<vector<int>> G(V,vector<int> (V));
	
//     for(int i=0; i<n; i++) {
//         int a,b,c;
//         cin>>a>>b>>c;
//         G[a][b] = c;
//     }
    
    ///file stream part. To enter input through file. uncomment the file stream part and comment the cin input part
    
    fstream myfile;
    myfile.open ("input.txt");
    string word;
    int wNo = 1;
    int a,b,c;
    while(myfile >> word) {
        if(wNo==1) {
            V=stoi(word);
            wNo++;
        }
        else if(wNo==2) {
            n=stoi(word);
            wNo++;
        }
        else if(wNo==3) {
            s=stoi(word);
            wNo++;
        }
        else if(wNo==4) {
            t=stoi(word);
            wNo++;
            break;
        }
    }
    vector<vector<int>> G(V,vector<int> (V));
    while(myfile>>word) {
        if(wNo%3==2) a=stoi(word);
        else if(wNo%3==0) b=stoi(word);
        else {
            c=stoi(word);
            G[a][b] = c;
        }
        wNo++;
    }
    myfile.close();
	
	int ans = fordFulkerson(G, V, s, t);
	cout << ans;
	return 0;
}
