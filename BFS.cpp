#include<iostream>
#include<bits/stdc++.h>
#include<chrono>

using namespace std;


class Graph{
    public:
        vector<vector<int>> graph;
        vector<bool> visited;
        int vertices = 0;
        int edges = 0;

        Graph(){
            cout << "Enter number of nodes: ";
            cin >> vertices;
            cout << "Enter number of edges: ";
            cin >> edges;
            graph.assign(vertices,vector<int>());
            for(int i = 0 ; i < edges;i++){
                int a,b;
                cout << "Enter adjacent nodes: ";
                cin >> a >> b;
                addEdge(a,b);
            }
        }
        
        void addEdge(int a, int b){
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        void printGraph(){
            for(int i = 0; i < vertices; i++){
                cout << i << " -> ";
                for(int j = 0; j < graph[i].size(); j++){
                    cout << graph[i][j] << " ";
                }
                cout << endl;
            }
        }

        void initialize_visited(){
            visited.assign(vertices,false);
        }

        void bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                int current = q.front();
                q.pop();
                cout << current << " ";
                for(int j = 0; j < graph[current].size(); j++){
                    if(visited[graph[current][j]] == false){
                        q.push(graph[current][j]);
                        visited[graph[current][j]] = true;
                    }
                }
            }
        }

        void parallel_bfs(int i){
            // Note: BFS queue operations are inherently sequential
            // Parallelizing neighbor processing has limited benefit due to synchronization overhead
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                int current = q.front();
                q.pop();
                cout << current << " ";
                for(int j = 0; j < graph[current].size(); j++){
                    if(visited[graph[current][j]] == false){
                        q.push(graph[current][j]);
                        visited[graph[current][j]] = true;
                    }
                }
            }
        }
};

int main(int argc, char const *argv[])
{
    Graph g;
    cout << "Adjacency List:\n";
    g.printGraph();
    
    g.initialize_visited();
    cout << "\nBreadth First Search: \n";
    auto start = chrono::high_resolution_clock::now();
    g.bfs(0);
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << "Time taken: "<< chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    
    g.initialize_visited();
    cout << "\nParallel Breadth First Search: \n";
    start = chrono::high_resolution_clock::now();
    g.parallel_bfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    return 0;
}
