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
////二叉树树结点结构体
//template<class T>
//struct binaryTreeNode
//{
//	T element;
//	binaryTreeNode<T>* leftChild,  //左子树
//					* rightChild;  //右子树
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
////链式二叉树
//template<class T>
//class linkedBinaryTree
//{
//public:
//	linkedBinaryTree() { root[1]=NULL; treeSize = 0; }
//	~linkedBinaryTree() {}
//	void makeTree(int n);
//	//binaryTreeNode<T>* find(binaryTreeNode<T>*, int x);//查找第x个节点
//	int countNode(binaryTreeNode<T>* t);//计算以t为根的树的节点数
//	void visit(binaryTreeNode<T>*x) //访问节点x，输出element值
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
//	binaryTreeNode<int>* root[100000];//声明一个节点数组,用以寻找第i个节点
//	int treeSize;					  //树的元素个数
//};
////建立树
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
//////寻找第i个节点
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
//{//前序遍历二叉树*t
//	if (t != NULL)
//	{
//		visit(t);					//访问树根
//		preOrder(t->leftChild);		//前序遍历左子树
//		preOrder(t->rightChild);	//前序遍历右子树
//	}
//}
//
//template<class T>
//void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t)
//{//中序遍历二叉树*t
//	//if (t != NULL)
//	//{
//	//	inOrder(t->leftChild);		  //前序遍历左子树
//	//	linkedBinaryTree<T>::visit(t);//访问树根
//	//	inOrder(t->rightChild);		  //前序遍历右子树
//	//}
//	binaryTreeNode<T>* p = nullptr;
//	stack<binaryTreeNode<T>*>stack;
//	while (!stack.empty() || t != NULL)
//	{
//		//一直先将左节点放入栈中
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
//{//后序遍历二叉树*t
//	//if (t != NULL)
//	//{
//	//	postOrder(t->leftChild);		//后序遍历左子树
//	//	postOrder(t->rightChild);		//后序遍历右子树
//	//	linkedBinaryTree<T>::visit(t);	//访问树根
//	//}
//	binaryTreeNode<T>* p = nullptr; //辅助节点
//	stack<binaryTreeNode<T>*>stack1;//辅助栈，先存入根节点
//	stack<binaryTreeNode<T>*>stack2;//结果栈，存入遍历结果
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
//	//遍历访问结果栈
//	while (!stack2.empty())
//	{
//		p = stack2.top();
//		visit(p);
//		stack2.pop();
//	}
//}
//template<class T>
//void linkedBinaryTree<T>::levelOrder()
//{//层次遍历二叉树*t
//	queue<binaryTreeNode<T>*>q;
//	binaryTreeNode<T>* t = root[1];
//	while (t != NULL)
//	{
//		visit(t);//每次先访问节点值
//		//将t的孩子插入队列
//		if (t->leftChild != NULL)
//			q.push(t->leftChild);
//		if (t->rightChild != NULL)
//			q.push(t->rightChild);
//
//		//提取下一个要访问的节点
//		if (q.empty())break;
//		t = q.front();
//		q.pop();
//	}
//}
//
////返回第i个节点的子树的节点数，递归
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
////返回第i个节点的子树高度
//template<class T>
//int linkedBinaryTree<T>::height(binaryTreeNode<T>* t)
//{//返回二叉树的高度
//	if (t == NULL)return 0;
//	int hl = height(t->leftChild);
//	int hr = height(t->rightChild);
//	if (hl > hr)return ++hl;
//	else return ++hr;
//}
//
////输出结果
//template<class T>
//void linkedBinaryTree<T>::output(int n)
//{
//	//各遍历的调用输出
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