//#include <sstream>
//#include <string>
//#include<cstring>
//#include<iostream>
//#include<queue>
//using namespace std;
///*ʹ���ڽ�����������ݴ洢*/
//
///******ʵ����С�Ѳ���*******/
////�ı�һά����ĳ���
//template<class t>
//void changelength1d(t*& a, int oldlength, int newlength)
//{
//	if (newlength < 0)
//	{
//		throw logic_error("new length must be >= 0");
//	}
//	t* temp = new t[newlength];
//	int n = min(oldlength, newlength);
//	copy(a, a + n, temp);
//	delete[]a;
//	a = temp;
//}
////�쳣��
//class queueempty
//{
//public:
//	queueempty(string themessage =
//		"invalid operation on empty queue")
//	{
//		message = themessage;
//	}
//	void outputmessage() { cout << message << endl; }
//private:
//	string message;
//};
////��С��
//template<class t>
//class minheap
//{
//public:
//	minheap(int initcapacility=10);
//	//~minheap() { delete[]heap; }//��Ҫ����
//	bool empty()const { return heapsize == 0; }
//	int size()const { return heapsize; }
//	const t& top()
//	{
//		if (heapsize == 0)
//			throw queueempty();
//		return heap[1];
//	}
//	void pop();
//	void push(const t&);
//	void initialize(t*, int);
//private:
//	t* heap;
//	int heapsize;
//	int arraylength;
//};
//template<class t>
//minheap<t>::minheap(int initialcapacity)
//{//���캯��
//	arraylength = initialcapacity + 1;
//	heap = new t[arraylength];
//	heapsize = 0;
//}
////ɾ��
//template<class t>
//void minheap<t>::pop()
//{
//	//ɾ�����Ԫ��
//	heap[1].~t();
//
//	//ɾ�����һ��Ԫ��Ȼ�����½���
//	t lastelement = heap[heapsize--];
//	//ΪԪ��rootelementѰ��λ��
//	int currentnode = 1, child = 2;
//	while (child <= heapsize)
//	{
//		//heap[child]Ӧ���ֵ��н�С��
//		if (child < heapsize && heap[child] > heap[child + 1])
//			child++;
//		//���԰�Ԫ�ط���heap[currentnode]��
//		if (lastelement <= heap[child])
//			break;//����
//		//������
//		heap[currentnode] = heap[child];//�Ѻ���������
//		currentnode = child;            //�Ƶ���һ��
//		child *= 2;
//	}
//	heap[currentnode] = lastelement;//����
//}
//template<class t>
//void minheap<t>::push(const t& theelement)
//{
//	//����
//	if (heapsize == arraylength - 1)
//	{
//		changelength1d(heap, arraylength, 2 * arraylength);
//		arraylength *= 2;
//	}
//	//ΪԪ��Ѱ�Ҳ���λ��
//	//currentnode����Ҷ�������ƶ�
//	int currentnode = ++heapsize;
//	while (currentnode != 1 && heap[currentnode / 2] > theelement)
//	{
//		heap[currentnode] = heap[currentnode / 2];
//		currentnode /= 2;
//	}
//	heap[currentnode] = theelement;
//}
//template<class t>
//void minheap<t>::initialize(t* theheap, int thesize)
//{
//	delete[]heap;
//	heap = theheap;
//	heapsize = thesize;
//
//	//�ѻ�
//	for (int root = heapsize / 2; root >= 1; root--)
//	{
//		t rootelement = heap[root];
//		//ΪԪ��rootelementѰ��λ��
//		int child = 2 * root;//���ӵ�˫����Ԫ��rootelement��λ��
//		while (child <= heapsize)
//		{
//			//heap[child]Ӧ���ֵ��н�С��
//			if (child < heapsize && heap[child] > heap[child + 1])
//				child++;
//			//���԰�Ԫ�ط���heap[child/2]��
//			if (rootelement <= heap[child])
//				break;//����
//			//������
//			heap[child / 2] = heap[child];//�Ѻ���������
//			child *= 2;                   //�Ƶ���һ��
//		}
//		heap[child / 2] = rootelement;//����
//	}
//}
///**********ʵ�ֱ߼��Ľṹ�岿��**********/
//struct wEdge {
//	int v;
//	int w;
//	wEdge() {};
//	wEdge(int thev, int thew) {
//		v = thev;
//		w = thew;
//	}
//	bool operator < (const wEdge& b) const
//	{
//		return w < b.w;
//	}
//	bool operator <= (const wEdge& b) const
//	{
//		return w <= b.w;
//	}
//	bool operator > (const wEdge& b) const
//	{
//		return w > b.w;
//	}
//	bool operator !=(const wEdge& b)const
//	{
//		return v != b.v;
//	}
//};
//bool reach[200002];   //��������������������ڽӶ���
//
///************ʵ���ڽ������ಿ��***************/
////����Ľṹ�ڵ㶨��
//template<class t>
//struct chainnode
//{
//	t element;
//	chainnode<t>* next;
//
//	chainnode() {};
//	chainnode(const t& element)
//	{
//		this->element = element;
//	}
//	chainnode(const t& element, chainnode<t>* next)
//	{
//		this->element = element;
//		this->next = next;
//	}
//};
//template <class t>class digraph;
//
////ʵ����չ���������graphchain
//template <class t>
//class graphchain
//{
//	friend digraph<t>;
//	friend digraph<wEdge>;
//public:
//	chainnode<t>* firstnode;
//	int listsize;
//public:
//	graphchain(int initialcapacity = 10);
//    ~graphchain();
//    void insert(int theindex, const t& theelement);
//};
////���캯��
//template<class t>
//graphchain<t>::graphchain(int initialcapacity)
//{
//	firstnode = null;
//	listsize = 0;
//}
////��������
//template<class t>
//graphchain<t>::~graphchain()
//{
//	while (firstnode != null)
//	{
//		chainnode<t>* nextnode = firstnode->next;
//		delete[] firstnode;
//		firstnode = nextnode;
//	}
//}
////������Ϊtheindex����Ԫ��theelement
//template<class t>
//void graphchain<t>::insert(int theindex, const t& theelement)
//{
//	if (theindex == 0)
//	{
//		firstnode = new chainnode<t>(theelement, firstnode);
//	}
//	else
//	{
//		chainnode<t>* p = firstnode;
//		for (int i = 0; i < theindex - 1; i++)
//		{
//			p = p->next;
//		}
//		p->next = new chainnode<t>(theelement, p->next);
//	}
//	listsize++;
//}
////ʵ����ʽ����ͼ��
//template<class t>
//class digraph
//{
//	friend graphchain<wEdge>;
//	friend graphchain<t>;
//	protected:
//		int vnum;                    //������
//		int enum;                    //����
//		graphchain<wEdge>* alist;    //�ڽӱ�
//	public:
//		digraph(int n,int m) {
//			vnum = n;
//			enum = m;
//			alist = new graphchain<wEdge>[vnum + 1];
//		}
//		~digraph() { delete[] alist; }
//		
//		void insertedge(int v1, int v2, int w) {//�����
//			wEdge t1{ v1,w };
//			wEdge t2{ v2,w };
//			alist[v2].insert(0, t1);
//			alist[v1].insert(0, t2);
//		}
//		void prim() {
//			long long sum = 0;
//			minheap<wEdge>q;
//			reach[1] = false;
//			chainnode<wEdge>* p = alist[1].firstnode;
//			while (p) {
//				wEdge t { p->element.v,p->element.w };
//				q.push(t);
//				p = p->next;
//			}
//			for (int i = 1; i < vnum; i++)
//			{
//				int minweight, thev;
//				while (reach[q.top().v] == false){//���飬�����ǰ��С����СԪ����ָ��Ľ����붥���Ѿ���false�������Ѿ������ˣ� 
//					q.pop();//���������pop�� 
//				}
//				//�ó���СȨֵ������ָ��Ķ��� 
//				minweight = q.top().w;
//				thev = q.top().v;
//				q.pop();
//				//���½��
//				sum += minweight;
//				reach[thev] = false;//���¶���״̬ 
//				chainnode<wEdge>* p = alist[thev].firstnode;
//				while (p) {
//					if (reach[p->element.v]){//����õ�δ������㼯
//						wEdge t{ p->element.v,p->element.w };
//						q.push(t);
//					}
//					p = p->next;
//				}
//			}
//			cout << sum << endl;
//		}
//};
//int main() {
//	int n, m;
//	cin >> n >> m;
//	digraph<int> a(n,m);
//	for (int i = 0; i < m; i++) //������m������
//	{
//		int v1, v2, w;
//		cin >> v1 >> v2 >> w;
//		a.insertedge(v1, v2, w);
//	}
//	for (int i = 0; i <= n; i++) {//��ʼ����������
//		reach[i] = true;
//	}
//	a.prim();
//	return 0;
//}