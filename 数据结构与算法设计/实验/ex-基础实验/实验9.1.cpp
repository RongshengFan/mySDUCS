//#include<iostream>
//#include<string>
//#include<queue>
//#include<stack>
//using namespace std;
//template<class T>
//class emptyTree
//{
//public:
//	emptyTree(string message = "Tree Is Empty")
//	{
//		*this = message;
//	}
//	void outputMessage()
//	{
//		cout << message << endl;
//	}
//private:
//	string message;
//};
////�����������ṹ��
//template<class T>
//struct binaryTreeNode
//{
//	T element;
//	binaryTreeNode<T>* leftChild,  //������
//					* rightChild;  //������
//	binaryTreeNode() { leftChild = rightChild = NULL; }
//	binaryTreeNode(const T& theElement)
//	{
//		element=theElement;
//		leftChild = rightChild = NULL;
//	}
//	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
//	{
//		element(theElement);
//		leftChild = theLeftChild;
//		rightChild = theRightChild;
//	}
//};
//
////��ʽ������
//template<class T>
//class linkedBinaryTree
//{
//public:
//	linkedBinaryTree() { root[1]=NULL; treeSize = 0; }
//	~linkedBinaryTree() {}
//	void makeTree(int n);
//	//binaryTreeNode<T>* find(binaryTreeNode<T>*, int x);//���ҵ�x���ڵ�
//	int countNode(binaryTreeNode<T>* t);//������tΪ�������Ľڵ���
//	void visit(binaryTreeNode<T>*x) //���ʽڵ�x�����elementֵ
//	{ cout << x->element << " "; }
//	int height(binaryTreeNode<T>* t);
//	void preOrder(binaryTreeNode<T>* t);
//	void inOrder(binaryTreeNode<T>* t);
//	void postOrder(binaryTreeNode<T>* t);
//	void levelOrder();
//	void preOrderOutput() { preOrder(root[1]); cout << endl; }
//	void inOrderOutput() { inOrder(root[1]); cout << endl; }
//	void postOrderOutput() { postOrder(root[1]); cout << endl; }
//	void levelOrderOutput() { levelOrder(); cout << endl; }
//	void output(int n);
//private:
//	binaryTreeNode<int>* root[100000];//����һ���ڵ�����,����Ѱ�ҵ�i���ڵ�
//	int treeSize;					  //����Ԫ�ظ���
//};
////������
//template<class T>
//void linkedBinaryTree<T>::makeTree(int n)
//{
//	int a = 0, b = 0;
//	for (int i = 1; i <= n; i++)
//	{
//		root[i] = new binaryTreeNode<int>(i);
//	}
//	for (int i = 1; i <= n; i++)
//	{
//		cin >> a >> b;
//		if (a != -1)
//		{
//			root[i]->leftChild = root[a];
//			treeSize++;
//		}
//		else root[i]->leftChild = NULL;
//		if (b != -1)
//		{
//			root[i]->rightChild = root[b];
//			treeSize++;
//		}
//		else root[i]->rightChild = NULL;
//	}
//}
//////Ѱ�ҵ�i���ڵ�
////template<class T>
////binaryTreeNode<T>* linkedBinaryTree<T>::find(binaryTreeNode<T>* t, int x)
////{
////	if (t == NULL)return NULL;
////	queue<binaryTreeNode<T>*>q;
////	while (t != NULL)
////	{
////		if (t->element == x)
////			return t;
////		if (t->leftChild != NULL)
////			q.push(t->leftChild);
////		if (t->rightChild != NULL)
////			q.push(t->rightChild);
////		if (q.empty()) { break; }
////		t = q.front();
////		q.pop();
////	}
////	return NULL;
////}
//
//template<class T>
//void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* t)
//{//ǰ�����������*t
//	if (t != NULL)
//	{
//		visit(t);					//��������
//		preOrder(t->leftChild);		//ǰ�����������
//		preOrder(t->rightChild);	//ǰ�����������
//	}
//}
//
//template<class T>
//void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t)
//{//�������������*t
//	//if (t != NULL)
//	//{
//	//	inOrder(t->leftChild);		  //ǰ�����������
//	//	linkedBinaryTree<T>::visit(t);//��������
//	//	inOrder(t->rightChild);		  //ǰ�����������
//	//}
//	binaryTreeNode<T>* p = nullptr;
//	stack<binaryTreeNode<T>*>stack;
//	while (!stack.empty() || t != NULL)
//	{
//		//һֱ�Ƚ���ڵ����ջ��
//		while (t != NULL)
//		{
//			stack.push(t);
//			t = t->leftChild;
//		}
//		p = stack.top();
//		stack.pop();
//		visit(p);
//		if (p->rightChild != NULL)
//		{
//			t = p->rightChild;
//		}
//	}
//}
//
//template<class T>
//void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* t)
//{//�������������*t
//	//if (t != NULL)
//	//{
//	//	postOrder(t->leftChild);		//�������������
//	//	postOrder(t->rightChild);		//�������������
//	//	linkedBinaryTree<T>::visit(t);	//��������
//	//}
//	binaryTreeNode<T>* p = nullptr; //�����ڵ�
//	stack<binaryTreeNode<T>*>stack1;//����ջ���ȴ�����ڵ�
//	stack<binaryTreeNode<T>*>stack2;//���ջ������������
//	stack1.push(t);
//	while (!stack1.empty())
//	{
//		p = stack1.top();
//		stack1.pop();
//		stack2.push(p);
//		if (p->leftChild != NULL)
//		{
//			stack1.push(p->leftChild);
//		}
//		if (p->rightChild != NULL)
//		{
//			stack1.push(p->rightChild);
//		}
//	}
//	//�������ʽ��ջ
//	while (!stack2.empty())
//	{
//		p = stack2.top();
//		visit(p);
//		stack2.pop();
//	}
//}
//template<class T>
//void linkedBinaryTree<T>::levelOrder()
//{//��α���������*t
//	queue<binaryTreeNode<T>*>q;
//	binaryTreeNode<T>* t = root[1];
//	while (t != NULL)
//	{
//		visit(t);//ÿ���ȷ��ʽڵ�ֵ
//		//��t�ĺ��Ӳ������
//		if (t->leftChild != NULL)
//			q.push(t->leftChild);
//		if (t->rightChild != NULL)
//			q.push(t->rightChild);
//
//		//��ȡ��һ��Ҫ���ʵĽڵ�
//		if (q.empty())break;
//		t = q.front();
//		q.pop();
//	}
//}
//
////���ص�i���ڵ�������Ľڵ������ݹ�
//template<class T>
//int linkedBinaryTree<T>::countNode(binaryTreeNode<T>* t)
//{
//	int x = 0;
//	if (t != NULL) 
//	{
//		x = countNode(t->leftChild) + countNode(t->rightChild) + 1;
//	}
//	return x;
//}
////���ص�i���ڵ�������߶�
//template<class T>
//int linkedBinaryTree<T>::height(binaryTreeNode<T>* t)
//{//���ض������ĸ߶�
//	if (t == NULL)return 0;
//	int hl = height(t->leftChild);
//	int hr = height(t->rightChild);
//	if (hl > hr)return ++hl;
//	else return ++hr;
//}
//
////������
//template<class T>
//void linkedBinaryTree<T>::output(int n)
//{
//	//�������ĵ������
//	preOrderOutput();
//	inOrderOutput();
//	postOrderOutput();
//	levelOrderOutput();
//	for (int i = 1; i <= n; i++)
//	{
//	//	binaryTreeNode<int>* q = find(root, i);
//		cout << countNode(root[i]) << " ";
//	}
//	cout << endl;
//	for (int i = 1; i <= n; i++)
//	{
//	//	binaryTreeNode<int>* q = find(root, i);
//		cout << height(root[i]) << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	int n;
//	cin >> n;
//	linkedBinaryTree<int> r;
//	r.makeTree(n);
//	r.output(n);
//	return 0;
//} 