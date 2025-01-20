//#include <iostream>
//using namespace std;
////索引二叉树节点
//template <class T>
//struct IndexBSTNode
//{   
//	T leftSize;//索引值
//	T key;     //关键字=元素值，就不额外增加元素值的成员数据了
//	//T value;   //元素值
//	IndexBSTNode<T>* leftChild,  //左子树
//		          * rightChild;  //右子树
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
////索引二叉树类
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
////通过关键字搜索
//template<class T>
//int IndexedBSTree<T>::find(const T& theKey)const
//{
//	int sum = 0;//记录异或值
//	IndexBSTNode<T>* p = root;//记录根节点
//	//查找匹配关键字的节点
//	while (p != NULL && p->key != theKey) {
//		sum ^= p->key;//异或运算
//		if (theKey < p->key) {
//			p = p->leftChild;
//		}
//		else if (theKey > p->key) {
//			p = p->rightChild;
//		}
//	}
//	//找不到直接返回0；找到了再异或待查询元素
//	if (p == NULL)
//		return 0;
//	else 
//		sum ^= p->key;
//	return sum;
//}
////通过名次搜索
//template<class T>
//int IndexedBSTree<T>::get(int theIndex)
//{
//	int sum = 0;//记录异或值
//	IndexBSTNode<T>* p = root;//记录根节点
//	//查找匹配名次的节点
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
//	//找不到直接返回0；找到了再异或待查询元素
//	if (p == NULL)return 0;
//	else {
//		sum ^= p->key;
//		return sum;
//	}
//}
////插入
//template<class T>
//int IndexedBSTree<T>::insert(const T& theKey)
//{
//	int sum = 0;//记录异或值
//	IndexBSTNode<T>* p = root,   //记录根节点
//		          * pp = NULL;   //记录前驱节点(当前父结点)
//	//查找合适的插入位置
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
//			return 0;//已存在直接返回0
//		}
//	}
//	//插入新节点
//	IndexBSTNode<T>* newNode = new IndexBSTNode<T>(theKey);
//	if (root != NULL) {
//		if (theKey < pp->key)
//			pp->leftChild = newNode;
//		else
//			pp->rightChild = newNode;
//	}
//	else root = newNode;
//	treeSize++;
//	//重新计算leftSize的值
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
////删除
//template<class T>
//int IndexedBSTree<T>::erase(const T& theKey)
//{
//	int sum = 0;//记录异或值
//	IndexBSTNode<T>* p = root,   //记录根节点
//		          * pp = NULL;   //记录前驱节点(当前父结点)
//	//查找匹配关键字的节点
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
//	//从根节点开始重新计算leftSize的值
//	p = root;
//	while (p != NULL && p->key != theKey) {
//		if (p->key < theKey) {
//			p = p->rightChild;
//		}
//		else if (p->key > theKey) {
//			//说明要删除的节点在p左子树里
//			p->leftSize--;
//			p = p->leftChild;
//		}
//	}
//
//	//重新组织树结构
//	//当P有两个孩子时的处理
//	if (p->leftChild != NULL && p->rightChild != NULL) {
//		//转换为空或只有一个孩子
//		//在P的右子树中寻找最小关键字节点
//		IndexBSTNode<T>* s = p->rightChild, * ps = p;
//		while (s->leftChild != NULL) {
//			s->leftSize--;
//			ps = s;
//			s = s->leftChild;
//		}
//		//以右子树最小关键字构建新的节点替代p节点，实现删除
//		IndexBSTNode<T>* q = new IndexBSTNode<T>(s->key,p->leftSize, p->leftChild, p->rightChild);
//		//p无父节点
//		if (pp == NULL) {
//			root = q;
//		}
//		//p有父节点
//		else {
//			if (p == pp->leftChild)
//				pp->leftChild = q;
//			else pp->rightChild = q;
//		}
//		if (ps == p)pp = q;//p右孩子即是最小关键字节点
//		else pp = ps;
//		delete p;
//		p = s;
//	}
//	//P最多有一个孩子
//	IndexBSTNode<T>* c;
//	if (p->leftChild != NULL)
//		c = p->leftChild;
//	else
//		c = p->rightChild;
//	//p无父节点
//	if (p == root)
//		root = c;
//	//p有父节点
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
////按名次删除
//template<class T>
//int IndexedBSTree<T>::eraseOfIndex(int theIndex)
//{
//	int sum = 0;//记录异或值
//	IndexBSTNode<T>* p = root,   //记录根节点
//		          * pp = NULL;   //记录前驱节点(当前父结点)
//	//查找匹配索引值的节点
//	while (p != NULL && p->leftSize != theIndex) {
//		pp = p;
//		sum ^= p->key;
//		if (theIndex < p->leftSize) {
//			p = p->leftChild;
//		}
//		else if (theIndex > p->leftSize) {
//			//转到右子树，重新计算theIndex
//			theIndex = theIndex - p->leftSize - 1;
//			p = p->rightChild;
//		}
//	}
//	if (p == NULL)return 0;
//	sum ^= p->key;
//
//	//从根节点开始重新计算leftSize的值
//	int theKey = p->key;//记录要删除节点的关键字
//	p = root;
//	while (p != NULL && p->key != theKey) {
//		if (p->key < theKey) {
//			p = p->rightChild;
//		}
//		else if (p->key > theKey) {
//			//说明要删除的节点在p左子树里
//			p->leftSize--;
//			p = p->leftChild;
//		}
//	}
//	//重新组织树结构
//	//当P有两个孩子时的处理
//	if (p->leftChild != NULL && p->rightChild != NULL) {
//		//转换为空或只有一个孩子
//		//在P的右子树中寻找最小元素
//		IndexBSTNode<T>* s = p->rightChild, * ps = p;
//		while (s->leftChild != NULL) {
//			s->leftSize--;
//			ps = s;
//			s = s->leftChild;
//		}
//		//以右子树最小关键字构建新的节点替代p节点，实现删除
//		IndexBSTNode<T>* q = new IndexBSTNode<T>(s->key, p->leftSize, p->leftChild, p->rightChild);
//		//p无父节点
//		if (pp == NULL) {
//			root = q;
//		}
//		//p有父节点
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
//	//P最多有一个孩子
//	IndexBSTNode<T>* c;
//	if (p->leftChild != NULL)
//		c = p->leftChild;
//	else
//		c = p->rightChild;
//	//p无父节点
//	if (p == root)
//		root = c;
//	//p有父节点
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