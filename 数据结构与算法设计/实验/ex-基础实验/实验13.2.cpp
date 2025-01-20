//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int a[200002];   //用作并查集数组
//int find(int i) {//并查集的find函数,路径压缩
//	if (a[i] != i)a[i] = find(a[i]);
//	return a[i];
//}
//
///**********实现边集的结构体部分**********/
//struct wEdge {//存边的结构体
//	int v1, v2, w;
//	wEdge(int i = 0, int j = 0, int weight = 0) {
//		v1 = i;
//		v2 = j;
//		w = weight;
//	}
//	bool operator<(wEdge& b) {//用于权值升序排列比较
//	return w < b.w;
//}
//};
////实现无向有权图
//template<class t>
//class Digraph
//{
//protected:
//	int Vnum;
//	int Enum;
//	wEdge* edge;
//public:
//	Digraph(int n, int e) {
//		Vnum = n;
//		Enum = e;
//		edge = new wEdge[Enum];
//	}
//	~Digraph() { delete[] edge; }
//	void insert(int v1, int v2, int w, int i) {
//		edge[i] = wEdge(v1, v2, w);
//	}
//	
//	void kruskal() {//kruskal算法生成一颗最小树
//	    long long sum = 0;//记录权重值之和
//
//		sort(edge, edge + Enum);//按权值升序排列
//
//		for (int i = 1; i <= Vnum; i++) {//初始化并查集
//			a[i] = i;
//		}
//		int v1, v2, w;
//		for (int i = 0; i < Enum; i++) {//使用并查集生成最小树，计算权值和
//			v1 = edge[i].v1;
//			v2 = edge[i].v2;
//			w = edge[i].w;
//			v1 = find(v1); //查询v1对应的根节点
//			v2 = find(v2); //查询v2对应的根节点
//			if (v1 != v2) {//不属于同一个集合，将该边加入最小树里
//				a[v1] = v2; 
//				sum += w;
//			}
//		}
//		cout << sum << endl;
//	}
//	
//};
//int main() {
//	int n, e;
//	cin >> n >> e;
//	Digraph<int> g(n,e);
//	for (int i = 0; i < e; i++){
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		g.insert(v1, v2, w,i);
//	}
//	g.kruskal();
//	return 0;
//}