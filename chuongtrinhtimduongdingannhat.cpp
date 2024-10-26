#include <bits/stdc++.h>
using namespace std;

int vertex, edge;
const int maxVertex = 10000;
vector<pair<int, int>> adj[maxVertex];	
const int infinite = 1e9;
int previous[maxVertex]; // Luu dinh truoc do toi dinh hien tai


void choice() {
	cout<<"Chon thuat toan tim duong di ngan nhat: "<<endl;
	cout<<"1. Dijkstra"<<endl;
	cout<<"2. Bellman-Ford"<<endl;
	cout<<"3. Floyd-Warshall"<<endl;
	cout<<"4. Thoat"<<endl;
}

// Thuat toan Dijkstra
void dijkstra(int start, int end) {
	// Tao mot mang luu khoang cach cac duong
	vector<long long> d(vertex + 1, infinite);
	d[start] = 0;
	previous[start] = start;
	// Su dung hang doi uu tien de luu mot dinh nao do va luu khoang cach tu dinh nguon den dinh do
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push(make_pair(0,start));// Them dinh nguon va khoang cach bang 0 vao hang doi uu tien
	while(!Q.empty()){
		pair<int, int> top = Q.top();
		Q.pop();
		int u = top.second;
		int kc = top.first;
		if(kc > d[u]){
			continue;
		}else{
			for(auto child : adj[u]){
				int v = child.first;
				int w = child.second;
				if(d[v] > w + d[u]){
					d[v] = w + d[u];
					Q.push(make_pair(d[v], v)); // Cap nhat lai khoang cach va cap nhat lai dinh
					previous[v] = u; // Gan dinh truoc cua dinh u
				}
			}
		}
	}
	if(d[end] == infinite){
		cout<<"Khong co duong di tu "<<start<<" den "<<end<<endl;
	}
		cout<<"Do dai ngan nhat tu dinh "<<start<<" den dinh "<<end<<" bang: "<<d[end]<<endl;
		vector<int> path;
		while(true){
			path.push_back(end);
			if(end == start) break;
			end = previous[end];
		}
		reverse(path.begin(), path.end());
		for(int i = 0; i < path.size(); i++){
			cout<<path[i];
			if(i != path.size() - 1){
				cout<<" -> ";
			}
		}
	
	
	cout<<endl;
}

void bellmanFord(int start, int end) {
	// Tao mot mang luu khoang cach cac dinh
	vector<int> d(vertex + 1, infinite);
	d[start] = 0; // Dat khoang cach cua dinh nguon bang 0
	previous[start] = start;
	for(int i = 0; i < vertex - 1; i++){
		for(int u = 0; u < vertex; u++){
			for(auto edge : adj[u]){
				int v = edge.first;
				int w = edge.second;
				if(d[u] != infinite && d[v] > d[u] + w){
					d[v] = d[u] + w;
					previous[v] = u;
				}
			}
		}
	}
	
	// Tìm chu trinh am 
	bool negativeCycle = false;
	for(int u = 0; u < vertex; u++){
		for(auto edge : adj[u]){
			int v = edge.first;
			int w = edge.second;
			if(d[u] != infinite && d[v] > d[u] + w){
				negativeCycle = true;
				break;
			}
		}
		if(negativeCycle) break;
	}
	
	if(negativeCycle){
		cout<<"Do thi co chu trinh am!"<<endl;
		return;
	}
	
	if(d[end] == infinite){
		cout<<"Khong co duong di";
	}
	cout<<"Duong di ngan nhat tu "<<start<<" den "<<end<<" bang = "<<d[end]<<endl;
	vector<int> path;
	while(true){
		path.push_back(end);
		if(end == start) break;
		end = previous[end];
	}
	reverse(path.begin(), path.end());
	cout<<"Cac duong di la: ";
	for(int i = 0; i < path.size(); i++){
		cout<<path[i];
		if(i != path.size() - 1){
			cout<<" -> ";
		}
	}
	cout<<endl;
}

// Thuat toan floyd-warshall
void floydWarshall(vector<vector<int>> &dist) {
	for(int i = 0; i < vertex; i++){
		dist[i][i] = 0;
	}
	for(int k = 0; k < vertex; k++){
		for(int i = 0; i < vertex; i++){
			for(int j = 0; j < vertex; j++){
				if(dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}
int main() {
	int start, end;
	choice();
	int choice;
	do {
		cout<<"Nhap lua chon: ";cin>>choice;cout<<endl;
		if(choice == 1 || choice == 2){
			for(int i = 0; i < vertex; i++){
				adj[i].clear();
			}
			cout<<"Nhap so dinh: ";cin>>vertex;cout<<endl;
			cout<<"Nhap so canh: ";cin>>edge;cout<<endl;
			cout<<"Nhap dinh bat dau: ";cin>>start;cout<<endl;
			cout<<"Nhap dinh ket thuc: ";cin>>end;cout<<endl;
			for(int i = 0; i < edge; i++){
				int x, y, weight;
				cout<<"Nhap dinh, canh ke va trong so(vidu: 0 1 5): ";cin>>x>>y>>weight;cout<<endl;
				adj[x].push_back(make_pair(y, weight));
			}
			if(choice == 1){
				dijkstra(start, end);	
			}else if(choice == 2){
				bellmanFord(start, end);
			}
			
		}else if(choice == 3){
			cout<<"Nhap vao so dinh: ";cin>>vertex;cout<<endl;
			vector<vector<int>> dist(vertex, vector<int>(vertex, infinite));
			cout<<"Nhap vao khoang cach giua cac dinh(nhap 999 neu khong có khoang cach)\n";
			for(int i = 0; i < vertex; i++){
				for(int j = 0; j < vertex; j++){
					if(i == j){
						dist[i][j] = 0;
					}else{
						cout<<"Khoang cach tu "<<i<<" den "<<j<<" : ";
						cin>>dist[i][j];
					}
				}
			}	
			cout<<"Ma tran khoang cach ban dau là: \n";
			for(int i = 0; i < vertex; i++){
				for(int j = 0; j < vertex; j++){
					if(dist[i][j] == 999){
						cout<<setw(5)<<"INF";
					}else{
						cout<<setw(5)<<dist[i][j];
					}
				}
				cout<<endl;
			}
			floydWarshall(dist);
			cout<<"Ma tran sau khi ap dung thuat toan Floyd-Warshall: \n";
			for(int i = 0; i < vertex; i++){
				for(int j = 0; j < vertex; j++){
					if(dist[i][j] == 999){
						cout<<setw(5)<<"INF";
					}else{
						cout<<setw(5)<<dist[i][j];
					}
				}
				cout<<endl;
			}
		}else if(choice == 4){
			cout<<"Thoat chuong trinh!";
		}else{
			cout<<"Lua chon khong hop le! Vui long chon lai."<<endl;
		}
	}while(choice != 4);
	
	return 0;
}
