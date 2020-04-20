#include<bits/stdc++.h>

using namespace std;
int V;
int augment(vector<vector<int>> &Gf, int V, int f, int P[], int s, int t) {
    ///let b = bottleneck(P,f)
    int b = V;//*******
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
vector<vector<int>> Gf;
bool isThereAPath(int s, int t, int P[], vector<vector<int>> &Gf, int V) {
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

    Gf.assign(G.begin(),G.end());
                
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
void dfs(vector<bool> &visit,int curr){
   ///performing "depth first search" on the residual graph  - Gf

    visit[curr]=true;///marks if a node is visited while dfs

    for(int i=0;i<V;i++){

        if(Gf[curr][i]!=0 && !visit[i]){

            dfs(visit,i);

        }
    }
    return ;

}
int main() {
    
    int n,s,t;
    ///cin input part. To enter input manually. comment the file stream part and uncomment the cin input part
    ///presuming the given input network has 1 as the first node
    ///input format : <number of nodes> <number of edges> <source node> <sink node>
	cin >> V >> n;
	cin>>s>>t;

    vector<int> toass(V,0);
    vector<vector<int>> G(V,toass);

    ///for n times input the edges as : <node1> <node2>
    for(int i=0; i<n; i++) {
        int a,b,c;
        cin>>a>>b>>c;
        G[a-1][b-1] = c;
    }
    --s,--t;
	
	int MaxFlow = fordFulkerson(G, V, s, t);
	cout <<"\nMaximum flow through the network is: "<< MaxFlow <<"\n";

/*Calculating MIN CUT */
    vector<bool> visit(V,false);

    ///dfs on residual function to update visited vaector
    dfs(visit,s);

    cout<<"\nMIN CUT edges are as follows:\n";

    int sumMINst = 0;// sum of min cut edges;
    for(int i=0;i<V;i++){

        for(int j=0;j<V;j++){

            ///if given edge has one node visited another unvisited prints it
            if(visit[i] && !visit[j] && G[i][j]!=0){

                sumMINst+=G[i][j];cout<<i<<" - "<<j<<"\n";

                }
            }
        }
    cout<<"\nSum of min cut edges: "<<sumMINst<<"\n";
	return 0;
}