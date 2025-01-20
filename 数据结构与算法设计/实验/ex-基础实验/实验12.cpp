#include <sstream>
#include <string>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;

//����Ľṹ�ڵ㶨��
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

//ʵ����չ���������graphchain
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
    { //ɾ������Ϊthevertex��Ԫ�أ����ظ�Ԫ��ָ�룻���򷵻ؿ�
        chainnode<T>* current = firstnode,//��ǰ�ڵ�
                    * pre = nullptr;         //ǰ���ڵ� 

        //����Ԫ��==thevertex�Ľڵ�
        while (current != nullptr && current->element != thevertex)
        {
            pre = current;
            current = current->next;
        }

        if (current == nullptr) //�����ڸýڵ�
            return nullptr;

        //���ڸýڵ�
        T* theelement = &current->element; //��¼�ýڵ�Ԫ��

        //�ƶ���ǰ�ڵ�ʵ��ɾ��
        if (pre != nullptr)
            pre->next = current->next;
        else
            firstnode = current->next; //��ǰ�ڵ�Ϊ��ͷ

        delete current;
        listsize--;
        return theelement;
    }
};
//���캯��
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
//���ƹ��캯��
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
//��������
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
//��������ֵ��theindex��Ԫ��
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
//����Ԫ����theelement�״γ��ֵ�����ֵ
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
//ɾ������Ϊtheindex��Ԫ��
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
		chainnode<T>* p = firstnode;			//ָ��Ҫɾ�ڵ��ǰ�����
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
//������Ϊtheindex����Ԫ��theelement
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
//���غ��ʵĲ�������ֵ������
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

int reach[1000000];//������������ڽӶ���
int lable = 1;   //���ֵ
int num = 0;     //��¼����

//ʵ����ʽ����ͼ��
template<class T>
class linkeddigraph
{
	protected:
		int V;                  //������
		int E;                  //����
		graphchain<int>* alist;    //�ڽӱ�
	public:
		linkeddigraph(int numberofvertexces = 0) {
			V = numberofvertexces;
			E = 0;
			alist = new graphchain<int>[V + 1];
		}
		~linkeddigraph() { delete[] alist; }
		
		void insertedge(int v1, int v2) {//����һ����
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
		void eraseedge(int v1, int v2) {//ɾ��һ����
			if (v1 >= 1 && v2 >= 1 && v1 <= V && v2 <= V) {
				int* i = alist[v1].eraseelement(v2);
				int* j = alist[v2].eraseelement(v1);
				if (i != nullptr && j != nullptr) {//��(v1,v2)����
					E--;
				}
			}
		}
		void components(int n) {//�����ͨ��������
			int flag = 0;//���ڼ�¼��ͨ��������
			for (int i = 1; i <= n; i++) {
				if (reach[i] == 0) {
					fdfs(i);
					flag++;
				}
			}
			cout << flag << endl;
		}
		void eachcomponents(int n) {//�������������ͨ��ͼ����С��ı��
			for (int i = 1; i <= n; i++) {
				if (reach[i] == 0) {
					cout << i << " ";
				    fdfs(i);
				}
			}
			cout << endl;
		}
		void fdfs(int v) {//���ڸ�����dfs����
			reach[v] = lable;
			chainnode<int>* p = alist[v].firstnode;
			while (p) {
				if (reach[p->element] == 0) {
					fdfs(p->element);
				}
				p = p->next;
			}
		}
		void dfscounter(int s) {//����� s �㿪ʼ�� dfs ���г���
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
		void dfs(int s) {//����� s �㿪ʼ���ֵ�����С�� dfs ����
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
		void bfscounter(int T) {//����� t �㿪ʼ�� bfs ���еĳ���
			num++;
			queue<int> q;
			q.push(T);
			reach[T] = lable;
			while (!q.empty()) {
				int w = q.front();
				//��������ڽӶ���w�Ļ�û�е���Ķ���
				for (chainnode<int>* u = alist[w].firstnode; u != nullptr; u = u->next) {
					//���ʶ���w��һ�������Ķ���
					if (reach[u->element] == 0) {//u��һ��û����Ķ���
						num++;
						q.push(u->element);
						reach[u->element] = lable;//��������
					}
				}
				q.pop();
			}
		}
		void bfs(int T) {//����� t �㿪ʼ���ֵ�����С�� bfs ����
			queue<int> q;
			q.push(T);
			reach[T] = lable;
			while (!q.empty()) {
				int w = q.front();
				cout << w << " ";			
				//��������ڽӶ���w�Ļ�û�е���Ķ���
				for (chainnode<int>* p = alist[w].firstnode; p != nullptr; p = p->next) {
					//���ʶ���w��һ�������Ķ���
					if (reach[p->element] == 0) {//u��һ��û����Ķ���
						q.push(p->element);       //ѹ�����
						reach[p->element] = lable;//��������
					}
				}
				q.pop();
			}
			cout << endl;
		}
		void path(int s, int t) {//����� s �㵽 t ������·�������ǲ�����·�������-1
			queue<int> q; 
			int n = V + 1; 
			q.push(s);               // ѹ�����
			reach[s] = lable;        // ���
			int* road=new int[n];    // ����һ������(���ڼ�¼·������)
			for (int i = 0; i < n; i++)
				road[i] = 0;   // �����ʼ��
			while (!q.empty()) // �������в���ʱ����ѯֱ������ĩβ��
			{
				int w = q.front(); //��¼����
				q.pop(); 
				chainnode<T>* p =alist[w].firstnode;
				while (p != nullptr)
				{
					if (reach[p->element] == 0){ // ���û�б����
						// һ���ڵ��������һ���ڵ�·�����ȶ���ͬ�����Կ���ʵ�����·����ʵ��
						road[p->element] = road[w] + 1;  // ��һ���ڵ㶼������ڵ�Ļ����Ͻ��м�һ����
						q.push(p->element);              // ѹ����һ���ڵ�
						reach[p->element] = lable;       // ���
						if (p->element == t) // �ж��Ƿ�Ϊ�յ�
						{
							cout << road[t] << endl; // �������
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
	for (int i = 0; i < m; i++) //������m������
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
	//�����ͨ��������
	memset(reach, 0, sizeof(reach));
	a.components(n);
	//�������������ͨ��ͼ����С��ı��
	memset(reach, 0, sizeof(reach));
	a.eachcomponents(n);
	//����� s �㿪ʼ�� dfs ���г���
	memset(reach, 0, sizeof(reach));
	a.dfscounter(s);
	cout << num << endl;
	num = 0;
	//����� s �㿪ʼ���ֵ�����С�� dfs ����
	memset(reach, 0, sizeof(reach));
	a.dfs(s);
	cout << endl;
	//����� t �㿪ʼ�� bfs ���еĳ���
	memset(reach, 0, sizeof(reach));
	a.bfscounter(T);
	cout << num << endl;
	num = 0;
	//����� t �㿪ʼ���ֵ�����С�� bfs ����
	memset(reach, 0, sizeof(reach));
	a.bfs(T);
	//����� s �㵽 t ������·�������ǲ�����·�������-1
	memset(reach, 0, sizeof(reach));
	a.path(s, T);
	return 0;
}