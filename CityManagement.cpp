#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

class CityManager {
    unordered_map<string, int> cityToId;
    vector<string> idToCity;
    vector<vector<pair<int, int>>> adj;
    int cityCount = 0;

public:
    void addCity(string name) {
        if (cityToId.count(name)) {
            cout << "City already exists!\n";
            return;
        }
        cityToId[name] = cityCount++;
        idToCity.push_back(name);
        adj.push_back({});
        cout << "City added: " << name << "\n";
    }

    void addRoad(string a, string b, int dist) {
        if (!cityToId.count(a) || !cityToId.count(b)) {
            cout << "One or both cities not found.\n";
            return;
        }
        int u = cityToId[a], v = cityToId[b];
        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist});
        cout << "Road added between " << a << " and " << b << " with distance " << dist << "\n";
    }

    void showMap() {
        cout << "\nCity Map:\n";
        for (int u = 0; u < cityCount; ++u) {
            cout << idToCity[u] << " -> ";
            for (int i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int dist = adj[u][i].second;
                cout << "(" << idToCity[v] << ", " << dist << ") ";
            }
            cout << "\n";
        }
    }

    void shortestPath(string src, string dest) {
        if (!cityToId.count(src) || !cityToId.count(dest)) {
            cout << "City not found.\n";
            return;
        }

        int n = cityCount;
        //using dijkstra's algorithm to find shortest path between two cities
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);//for printing the cities in order
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int start = cityToId[src];
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) { 
            int d = pq.top().first;
            int node = pq.top().second;
             pq.pop();

            for (int i = 0; i < adj[node].size(); i++) {
                int adjnode = adj[node][i].first;
                int edgewt = adj[node][i].second;
                if (d + edgewt < dist[adjnode]) {
                    dist[adjnode] = d + edgewt;
                    prev[adjnode] = node;
                    pq.push({dist[adjnode], adjnode});
                }
            }
        }

        int end = cityToId[dest];
        if (dist[end] == INT_MAX) {
            cout << "No path found.\n";
            return;
        }

        vector<string> path;//for printing the path traverse through previous array and reverse it
        for (int i = end; i != -1; i = prev[i]) {
            path.push_back(idToCity[i]);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path from " << src << " to " << dest << " (Distance: " << dist[end] << "): ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << " ";
        }
        cout << "\n";
    }

    void minimumSpanningTree() {
        int n = cityCount;
        if (n == 0) return;


        //using prim's algorithm for minimum spannig tree
        vector<bool> visited(n, 0);
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        
  
        pq.push({0,{0,-1}});

        int totalcost=0;
        cout << "\nSuggested MST Roads:\n";

        while(!pq.empty()){
            int node=pq.top().second.first;
            int parent=pq.top().second.second;
            int wt=pq.top().first;
            pq.pop();

            if(visited[node])continue;

            visited[node]=1;
            if(node!=0){
            totalcost+=wt;
            cout << idToCity[parent] << " --(" << wt << ")--> " << idToCity[node] << "\n";
            }

            for(int i=0;i<adj[node].size();i++){
                int adjnode=adj[node][i].first;
                int edgewt=adj[node][i].second;
                
                if(!visited[adjnode]){
                    pq.push({edgewt,{adjnode,node}});
                }

            }
        }

        cout << "Total cost of connecting all cities: " << totalcost << "\n";

    }
};

int main() {
    CityManager cm;
    int choice;

    cout << "\n==== City Management Menu ====\n";
    cout << "1. Add City\n2. Add Road\n3. View Map\n4. Shortest Route\n5. Suggest MST\n6. Exit\n";

    while (true) {
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string city;
            cout << "Enter city name: ";
            cin >> city;
            cm.addCity(city);
        } else if (choice == 2) {
            string a, b;
            int dist;
            cout << "Enter city A: ";
            cin >> a;
            cout << "Enter city B: ";
            cin >> b;
            cout << "Enter distance: ";
            cin >> dist;
            cm.addRoad(a, b, dist);
        } else if (choice == 3) {
            cm.showMap();
        } else if (choice == 4) {
            string src, dest;
            cout << "Enter source city: ";
            cin >> src;
            cout << "Enter destination city: ";
            cin >> dest;
            cm.shortestPath(src, dest);
        } else if (choice == 5) {
            cm.minimumSpanningTree();
        } else if (choice == 6) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice.\n";
            break;
        }
    }
    return 0;
}
