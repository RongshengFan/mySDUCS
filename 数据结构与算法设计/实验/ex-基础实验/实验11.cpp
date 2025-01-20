//#include <iostream>
//using namespace std;
////�����������ڵ�
//template <class T>
//struct IndexBSTNode
//{   
//	T leftSize;//����ֵ
//	T key;     //�ؼ���=Ԫ��ֵ���Ͳ���������Ԫ��ֵ�ĳ�Ա������
//	//T value;   //Ԫ��ֵ
//	IndexBSTNode<T>* leftChild,  //������
//		          * rightChild;  //������
//
//	IndexBSTNode() { leftChild = rightChild = NULL; }
//
//	IndexBSTNode(const T& theKey)
//	{
//		leftSize = 0;
//		key = theKey;
//		leftChild = rightChild = NULL;
//	}
//	IndexBSTNode(const T& theKey,const T& theLeftSize, IndexBSTNode* theLeftChild, IndexBSTNode* theRightChild)
//	{
//		leftSize = theLeftSize;
//		key = theKey;
//	//	value = theValue;
//		leftChild = theLeftChild;
//		rightChild = theRightChild;
//	}
//};
////������������
//template<class T>
//class IndexedBSTree
//{
//public:
//	IndexedBSTree(){
//		root = NULL;
//		treeSize = 0;
//	}
//	int find(const T& theKey) const;
//	int get(int Index);
//	int insert(const T& theKey);
//	int erase(const T& theKey);
//	int eraseOfIndex(int theKey);
//	void acend();
//
//private:
//	IndexBSTNode<T>* root;
//	int treeSize;
//};
////ͨ���ؼ�������
//template<class T>
//int IndexedBSTree<T>::find(const T& theKey)const
//{
//	int sum = 0;//��¼���ֵ
//	IndexBSTNode<T>* p = root;//��¼���ڵ�
//	//����ƥ��ؼ��ֵĽڵ�
//	while (p != NULL && p->key != theKey) {
//		sum ^= p->key;//�������
//		if (theKey < p->key) {
//			p = p->leftChild;
//		}
//		else if (theKey > p->key) {
//			p = p->rightChild;
//		}
//	}
//	//�Ҳ���ֱ�ӷ���0���ҵ�����������ѯԪ��
//	if (p == NULL)
//		return 0;
//	else 
//		sum ^= p->key;
//	return sum;
//}
////ͨ����������
//template<class T>
//int IndexedBSTree<T>::get(int theIndex)
//{
//	int sum = 0;//��¼���ֵ
//	IndexBSTNode<T>* p = root;//��¼���ڵ�
//	//����ƥ�����εĽڵ�
//	while (p != NULL && p->leftSize != theIndex) {
//		sum ^= p->key;
//		if (theIndex < p->leftSize) {
//			p = p->leftChild;
//		}
//		else if (theIndex > p->leftSize) {
//			theIndex = theIndex - p->leftSize - 1;
//			p = p->rightChild;
//		}
//	}
//	//�Ҳ���ֱ�ӷ���0���ҵ�����������ѯԪ��
//	if (p == NULL)return 0;
//	else {
//		sum ^= p->key;
//		return sum;
//	}
//}
////����
//template<class T>
//int IndexedBSTree<T>::insert(const T& theKey)
//{
//	int sum = 0;//��¼���ֵ
//	IndexBSTNode<T>* p = root,   //��¼���ڵ�
//		          * pp = NULL;   //��¼ǰ���ڵ�(��ǰ�����)
//	//���Һ��ʵĲ���λ��
//	while (p != NULL) {
//		pp = p;
//		sum ^= p->key;
//		if (theKey < p->key) {
//			p = p->leftChild;
//		}
//		else if (theKey > p->key) {
//			p = p->rightChild;
//		}
//		else if (theKey == p->key){
//			return 0;//�Ѵ���ֱ�ӷ���0
//		}
//	}
//	//�����½ڵ�
//	IndexBSTNode<T>* newNode = new IndexBSTNode<T>(theKey);
//	if (root != NULL) {
//		if (theKey < pp->key)
//			pp->leftChild = newNode;
//		else
//			pp->rightChild = newNode;
//	}
//	else root = newNode;
//	treeSize++;
//	//���¼���leftSize��ֵ
//	p = root;
//	while (p->key != theKey) {
//		if (p->key < theKey) {
//			p = p->rightChild;
//		}
//		else if (p->key > theKey) {
//			p->leftSize++;
//			p = p->leftChild;
//		}
//    }
//	return sum;
//}
////ɾ��
//template<class T>
//int IndexedBSTree<T>::erase(const T& theKey)
//{
//	int sum = 0;//��¼���ֵ
//	IndexBSTNode<T>* p = root,   //��¼���ڵ�
//		          * pp = NULL;   //��¼ǰ���ڵ�(��ǰ�����)
//	//����ƥ��ؼ��ֵĽڵ�
//	while (p != NULL && p->key != theKey) {
//		pp = p;
//		sum ^= p->key;
//		if (theKey < p->key) {
//			p = p->leftChild;
//		}
//		else if (theKey > p->key) {
//			p = p->rightChild;
//		}
//	}
//	if (p == NULL)return 0;
//	sum ^= p->key;
//	//�Ӹ��ڵ㿪ʼ���¼���leftSize��ֵ
//	p = root;
//	while (p != NULL && p->key != theKey) {
//		if (p->key < theKey) {
//			p = p->rightChild;
//		}
//		else if (p->key > theKey) {
//			//˵��Ҫɾ���Ľڵ���p��������
//			p->leftSize--;
//			p = p->leftChild;
//		}
//	}
//
//	//������֯���ṹ
//	//��P����������ʱ�Ĵ���
//	if (p->leftChild != NULL && p->rightChild != NULL) {
//		//ת��Ϊ�ջ�ֻ��һ������
//		//��P����������Ѱ����С�ؼ��ֽڵ�
//		IndexBSTNode<T>* s = p->rightChild, * ps = p;
//		while (s->leftChild != NULL) {
//			s->leftSize--;
//			ps = s;
//			s = s->leftChild;
//		}
//		//����������С�ؼ��ֹ����µĽڵ����p�ڵ㣬ʵ��ɾ��
//		IndexBSTNode<T>* q = new IndexBSTNode<T>(s->key,p->leftSize, p->leftChild, p->rightChild);
//		//p�޸��ڵ�
//		if (pp == NULL) {
//			root = q;
//		}
//		//p�и��ڵ�
//		else {
//			if (p == pp->leftChild)
//				pp->leftChild = q;
//			else pp->rightChild = q;
//		}
//		if (ps == p)pp = q;//p�Һ��Ӽ�����С�ؼ��ֽڵ�
//		else pp = ps;
//		delete p;
//		p = s;
//	}
//	//P�����һ������
//	IndexBSTNode<T>* c;
//	if (p->leftChild != NULL)
//		c = p->leftChild;
//	else
//		c = p->rightChild;
//	//p�޸��ڵ�
//	if (p == root)
//		root = c;
//	//p�и��ڵ�
//	else {
//		if (p == pp->leftChild)
//			pp->leftChild = c;
//		else 
//			pp->rightChild = c;
//	}
//	treeSize--;
//	delete p;
//	return sum;
//}
////������ɾ��
//template<class T>
//int IndexedBSTree<T>::eraseOfIndex(int theIndex)
//{
//	int sum = 0;//��¼���ֵ
//	IndexBSTNode<T>* p = root,   //��¼���ڵ�
//		          * pp = NULL;   //��¼ǰ���ڵ�(��ǰ�����)
//	//����ƥ������ֵ�Ľڵ�
//	while (p != NULL && p->leftSize != theIndex) {
//		pp = p;
//		sum ^= p->key;
//		if (theIndex < p->leftSize) {
//			p = p->leftChild;
//		}
//		else if (theIndex > p->leftSize) {
//			//ת�������������¼���theIndex
//			theIndex = theIndex - p->leftSize - 1;
//			p = p->rightChild;
//		}
//	}
//	if (p == NULL)return 0;
//	sum ^= p->key;
//
//	//�Ӹ��ڵ㿪ʼ���¼���leftSize��ֵ
//	int theKey = p->key;//��¼Ҫɾ���ڵ�Ĺؼ���
//	p = root;
//	while (p != NULL && p->key != theKey) {
//		if (p->key < theKey) {
//			p = p->rightChild;
//		}
//		else if (p->key > theKey) {
//			//˵��Ҫɾ���Ľڵ���p��������
//			p->leftSize--;
//			p = p->leftChild;
//		}
//	}
//	//������֯���ṹ
//	//��P����������ʱ�Ĵ���
//	if (p->leftChild != NULL && p->rightChild != NULL) {
//		//ת��Ϊ�ջ�ֻ��һ������
//		//��P����������Ѱ����СԪ��
//		IndexBSTNode<T>* s = p->rightChild, * ps = p;
//		while (s->leftChild != NULL) {
//			s->leftSize--;
//			ps = s;
//			s = s->leftChild;
//		}
//		//����������С�ؼ��ֹ����µĽڵ����p�ڵ㣬ʵ��ɾ��
//		IndexBSTNode<T>* q = new IndexBSTNode<T>(s->key, p->leftSize, p->leftChild, p->rightChild);
//		//p�޸��ڵ�
//		if (pp == NULL) {
//			root = q;
//		}
//		//p�и��ڵ�
//		else {
//			if (p == pp->leftChild)
//				pp->leftChild = q;
//			else pp->rightChild = q;
//		}
//		if (ps == p)pp = q;
//		else pp = ps;
//		delete p;
//		p = s;
//	}
//	//P�����һ������
//	IndexBSTNode<T>* c;
//	if (p->leftChild != NULL)
//		c = p->leftChild;
//	else
//		c = p->rightChild;
//	//p�޸��ڵ�
//	if (p == root)
//		root = c;
//	//p�и��ڵ�
//	else {
//		if (p == pp->leftChild)
//			pp->leftChild = c;
//		else pp->rightChild = c;
//	}
//    treeSize--;
//	delete p;
//	return sum;
//}
//
//template<class T>
//void IndexedBSTree<T>::acend()
//{
//	IndexBSTNode<T>* P = root;
//	acend(P->leftChild);
//	cout << P->key << " ";
//	acend(P->rightChild);
//}
//int main() {
//	int m, a, b;
//	cin >> m;
//	IndexedBSTree<int>BST;
//	for (int i = 0; i < m; i++)
//	{
//		cin >> a >> b;
//		switch (a)
//		{
//		case 0:
//			cout << BST.insert(b) << endl;
//			break;
//		case 1:
//			cout << BST.find(b) << endl;
//			break;
//		case 2:
//			cout << BST.erase(b) << endl;
//			break;
//		case 3:
//			b--;
//			cout << BST.get(b) << endl;
//			break;
//		case 4:
//			b--;
//			cout << BST.eraseOfIndex(b) << endl;
//			break;
//		}
//	}
//	return 0;
//}