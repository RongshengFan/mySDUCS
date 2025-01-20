#include <sstream>
#include <string>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;

//链表的结构节点定义
template<class T>
struct chainnode
{
	T element;
	chainnode<T>* next;

	chainnode() {};
	chainnode(const T& element)
	{
		this->element = element;
	}
	chainnode(const T& element, chainnode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
template <class T>class linkeddigraph;

//实现扩展后的链表类graphchain
template <class T>
class graphchain
{
	friend linkeddigraph<T>;
protected:
	void checkindex(int theindex) const
	{
		if (theindex<0 || theindex>listsize)
		{
			ostringstream s;
			s << "index = " << theindex << " size = " << listsize;
			throw logic_error(s.str());
		}
	}
	chainnode<T>* firstnode;
	int listsize;
public:
	graphchain(int initialcapacity = 10);
	graphchain(const graphchain<T>& thelist);
    ~graphchain();

    bool empty()const { return listsize == 0; }
    int size()const { return listsize; }
    T& get(int theindex)const;
    int indexof(const T& theelement)const;
    void erase(int theindex);
    void insert(int theindex, const T& theelement);
	  int indexofinsert(const T& theelement);
    T* eraseelement(int thevertex)
    { //删除顶点为thevertex的元素，返回该元素指针；否则返回空
        chainnode<T>* current = firstnode,//当前节点
                    * pre = nullptr;         //前驱节点 

        //搜索元素==thevertex的节点
        while (current != nullptr && current->element != thevertex)
        {
            pre = current;
            current = current->next;
        }

        if (current == nullptr) //不存在该节点
            return nullptr;

        //存在该节点
        T* theelement = &current->element; //记录该节点元素

        //移动当前节点实现删除
        if (pre != nullptr)
            pre->next = current->next;
        else
            firstnode = current->next; //点前节点为表头

        delete current;
        listsize--;
        return theelement;
    }
};
//构造函数
template<class T>
graphchain<T>::graphchain(int initialcapacity)
{
	if (initialcapacity < 1)
	{
		ostringstream s;
		s << "initial capacity = " << initialcapacity << " must be > 0";
		throw logic_error(s.str());
	}
	firstnode = nullptr;
	listsize = 0;
}
//复制构造函数
template<class T>
graphchain<T>::graphchain(const graphchain<T>& thelist)
{
	listsize = thelist.listsize;

	if (listsize = 0)
	{
		firstnode = nullptr;
		return;
	}
	chainnode<T>* sourcenode = thelist.firstnode;
	firstnode = new chainnode<T>(sourcenode->element);
	sourcenode = sourcenode->next;
	chainnode<T>* targetnode = firstnode;

	while (sourcenode != nullptr)
	{
		targetnode->next = new chainnode<T>(sourcenode->element);
		targetnode = targetnode->next;
		sourcenode = sourcenode->next;
	}
	targetnode->next = nullptr;
}
//析构函数
template<class T>
graphchain<T>::~graphchain()
{
	while (firstnode != nullptr)
	{
		chainnode<T>* nextnode = firstnode->next;
		delete firstnode;
		firstnode = nextnode;
	}
}
//返回索引值是theindex的元素
template<class T>
T& graphchain<T>::get(int theindex) const
{
	checkindex(theindex);

	chainnode<T>* currentnode = firstnode;
	for (int i = 0; i < theindex; i++)
	{
		currentnode = currentnode->next;
	}
	return currentnode->element;
}
//返回元素是theelement首次出现的索引值
template<class T>
int graphchain<T>::indexof(const T& theelement) const
{
	chainnode<T>* currentnode = firstnode;
	int index = 0;
	while (currentnode != nullptr && currentnode->element != theelement)
	{
		currentnode = currentnode->next;
		index++;
	}
	if (currentnode == nullptr)
		return -1;
	else
		return index;
}
//删除索引为theindex的元素
template<class T>
void graphchain<T>::erase(int theindex)
{
	checkindex(theindex);
	chainnode<T>* deletenode;
	if (theindex == 0)
	{
		deletenode = firstnode;
		firstnode = firstnode->next;
	}
	else
	{
		chainnode<T>* p = firstnode;			//指向要删节点的前驱结点
		for (int i = 0; i < theindex - 1; i++)
		{
			p = p->next;
		}
		deletenode = p->next;
		p->next = p->next->next;
	}
	listsize--;
	delete deletenode;
}
//在索引为theindex插入元素theelement
template<class T>
void graphchain<T>::insert(int theindex, const T& theelement)
{
	checkindex(theindex);
	if (theindex == 0)
	{
		firstnode = new chainnode<T>(theelement, firstnode);
	}
	else
	{
		chainnode<T>* p = firstnode;
		for (int i = 0; i < theindex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainnode<T>(theelement, p->next);
	}
	listsize++;
}
//返回合适的插入索引值（升序）
template<class T>
int graphchain<T>::indexofinsert(const T& theelement)
{
	if(firstnode== nullptr)return 0;
	else {
		chainnode<T>* currentnode = firstnode;
		int index = 0;
		while (currentnode != nullptr && currentnode->element < theelement)
		{
			currentnode = currentnode->next;
			index++;
		}
		return index;
	}
}

int reach[1000000];//用来标记所有邻接顶点
int lable = 1;   //标记值
int num = 0;     //记录长度

//实现链式无向图类
template<class T>
class linkeddigraph
{
	protected:
		int V;                  //顶点数
		int E;                  //边数
		graphchain<int>* alist;    //邻接表
	public:
		linkeddigraph(int numberofvertexces = 0) {
			V = numberofvertexces;
			E = 0;
			alist = new graphchain<int>[V + 1];
		}
		~linkeddigraph() { delete[] alist; }
		
		void insertedge(int v1, int v2) {//插入一条边
			if (v1 < 1 || v2 < 1 || v1 > V || v2 > V || v1 == v2)
			{
				ostringstream s;
				s << "(" << v1 << "," << v2 << ") is not a permissible edge";
				throw logic_error(s.str());
			}
			if (alist[v1].indexof(v2) == -1&&alist[v2].indexof(v1)==-1) {
				alist[v2].insert(alist[v2].indexofinsert(v1), v1);
				alist[v1].insert(alist[v1].indexofinsert(v2), v2);
				E++;
			}
		}
		void eraseedge(int v1, int v2) {//删除一条边
			if (v1 >= 1 && v2 >= 1 && v1 <= V && v2 <= V) {
				int* i = alist[v1].eraseelement(v2);
				int* j = alist[v2].eraseelement(v1);
				if (i != nullptr && j != nullptr) {//边(v1,v2)存在
					E--;
				}
			}
		}
		void components(int n) {//输出连通分量个数
			int flag = 0;//用于记录连通分量个数
			for (int i = 1; i <= n; i++) {
				if (reach[i] == 0) {
					fdfs(i);
					flag++;
				}
			}
			cout << flag << endl;
		}
		void eachcomponents(int n) {//升序输出所有连通子图中最小点的编号
			for (int i = 1; i <= n; i++) {
				if (reach[i] == 0) {
					cout << i << " ";
				    fdfs(i);
				}
			}
			cout << endl;
		}
		void fdfs(int v) {//用于辅助的dfs函数
			reach[v] = lable;
			chainnode<int>* p = alist[v].firstnode;
			while (p) {
				if (reach[p->element] == 0) {
					fdfs(p->element);
				}
				p = p->next;
			}
		}
		void dfscounter(int s) {//输出从 s 点开始的 dfs 序列长度
			num++;
			reach[s] = lable;
		    chainnode<int>* p = alist[s].firstnode;
			while (p) {
				if (reach[p->element] == 0) {
				    dfscounter(p->element);
				}
				p = p->next;
			}
		}
		void dfs(int s) {//输出从 s 点开始的字典序最小的 dfs 序列
			reach[s] = lable;
			cout << s << " ";
			chainnode<int>* p = alist[s].firstnode;
			while (p) {
				if (reach[p->element] == 0) {
					dfs(p->element);
				}
				p = p->next;
			}
		}
		void bfscounter(int T) {//输出从 t 点开始的 bfs 序列的长度
			num++;
			queue<int> q;
			q.push(T);
			reach[T] = lable;
			while (!q.empty()) {
				int w = q.front();
				//标记所有邻接顶点w的还没有到达的顶点
				for (chainnode<int>* u = alist[w].firstnode; u != nullptr; u = u->next) {
					//访问顶点w的一个关联的顶点
					if (reach[u->element] == 0) {//u是一个没到达的顶点
						num++;
						q.push(u->element);
						reach[u->element] = lable;//做到达标记
					}
				}
				q.pop();
			}
		}
		void bfs(int T) {//输出从 t 点开始的字典序最小的 bfs 序列
			queue<int> q;
			q.push(T);
			reach[T] = lable;
			while (!q.empty()) {
				int w = q.front();
				cout << w << " ";			
				//标记所有邻接顶点w的还没有到达的顶点
				for (chainnode<int>* p = alist[w].firstnode; p != nullptr; p = p->next) {
					//访问顶点w的一个关联的顶点
					if (reach[p->element] == 0) {//u是一个没到达的顶点
						q.push(p->element);       //压入队列
						reach[p->element] = lable;//做到达标记
					}
				}
				q.pop();
			}
			cout << endl;
		}
		void path(int s, int t) {//输出从 s 点到 t 点的最短路径，若是不存在路径则输出-1
			queue<int> q; 
			int n = V + 1; 
			q.push(s);               // 压入起点
			reach[s] = lable;        // 标记
			int* road=new int[n];    // 定义一个数组(用于记录路径长度)
			for (int i = 0; i < n; i++)
				road[i] = 0;   // 数组初始化
			while (!q.empty()) // 在链表中查找时（查询直到链表末尾）
			{
				int w = q.front(); //记录队首
				q.pop(); 
				chainnode<T>* p =alist[w].firstnode;
				while (p != nullptr)
				{
					if (reach[p->element] == 0){ // 如果没有被标记
						// 一个节点的所有下一个节点路径长度都相同，所以可以实现最短路径的实现
						road[p->element] = road[w] + 1;  // 下一个节点都在这个节点的基础上进行加一操作
						q.push(p->element);              // 压入下一个节点
						reach[p->element] = lable;       // 标记
						if (p->element == t) // 判断是否为终点
						{
							cout << road[t] << endl; // 输出长度
							delete[] road;
							return;
						}
						
					}
					p = p->next;
				}
			}
			cout << "-1" << endl;
			delete[] road;
		}
};
int main() {
	int n, m, s, T;
	cin >> n >> m >> s >> T;
	linkeddigraph<int> a(n);
	for (int i = 0; i < m; i++) //接下来m行输入
	{
		int op;
		cin >> op;
		if (op == 0)
		{
			int v1, v2;
			cin >> v1 >> v2;
			a.insertedge(v1, v2);
		}
		else if (op == 1)
		{
			int v1, v2;
			cin >> v1 >> v2;
			a.eraseedge(v1, v2);
		}
	}
	//输出连通分量个数
	memset(reach, 0, sizeof(reach));
	a.components(n);
	//升序输出所有连通子图中最小点的编号
	memset(reach, 0, sizeof(reach));
	a.eachcomponents(n);
	//输出从 s 点开始的 dfs 序列长度
	memset(reach, 0, sizeof(reach));
	a.dfscounter(s);
	cout << num << endl;
	num = 0;
	//输出从 s 点开始的字典序最小的 dfs 序列
	memset(reach, 0, sizeof(reach));
	a.dfs(s);
	cout << endl;
	//输出从 t 点开始的 bfs 序列的长度
	memset(reach, 0, sizeof(reach));
	a.bfscounter(T);
	cout << num << endl;
	num = 0;
	//输出从 t 点开始的字典序最小的 bfs 序列
	memset(reach, 0, sizeof(reach));
	a.bfs(T);
	//输出从 s 点到 t 点的最短路径，若是不存在路径则输出-1
	memset(reach, 0, sizeof(reach));
	a.path(s, T);
	return 0;
}