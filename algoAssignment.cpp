#include <iostream>
#include <string.h>
using namespace std;
#define max 20

bool graph[max][max];   //graph array
bool vis[max][max];     //mark edges of size k

//check if minimum vertex cover exists
bool checkMinCover(int V, int k, int E) {
   int set = (1 << k) - 1;    //shift to left position
   int limit = (1 << V);
   while (set < limit) {
      //reset vertex cover for each iteration
      memset(vis, 0, sizeof vis);
      int count = 0;
      //check for a high value 
      for (int j = 1, v = 1 ; j < limit ; j = j << 1, v++) {
         if (set & j) {
            //mark visited edges
            for (int k = 1 ; k <= V ; k++) {
               if (graph[v][k] && !vis[v][k]) {
                  vis[v][k] = 1;
                  vis[k][v] = 1;
                  count++;
               }
            }
         }
      }
      //if all the edges are covered
      if (count == E)
         return true;
      int c = set & -set;
      int r = set + c;
      set = (((r^set) >> 2) / c) | r;     //shift to right position
   }
   return false;
}
//find minimum vertex cover
int findMinCover(int n, int m) {
   //binary search
   int left = 1, right = n;
   while (right > left){
      int mid = (left + right) >> 1;
      if (checkMinCover(n, mid, m) == false)
         left = mid + 1;
      else
         right = mid;
   }
   return left;
}

//add edge into graph
void addEdge(int u, int v) {
   graph[u][v] = 1;
   graph[v][u] = 1;
}

int main() {
   memset(graph, 0, sizeof graph);     
   int V, E, x, y, ch;
   
   cout<<"\nNumber of vertices:";
   cin>>V;
    
   cout<<"\nNumber of Edges:";
	cin>>E;
    
   //loop for edges
   cout<<"\n";
   for(int i=0;i<E;i++){
      cout<<"End-points of edge "<<i+1<<":";
      cin>>x>>y;
      addEdge(x, y);
   }

   cout << "\nSize of Minimum Vertex Cover: " << findMinCover(V, E) << endl << endl;
   return 0;
}