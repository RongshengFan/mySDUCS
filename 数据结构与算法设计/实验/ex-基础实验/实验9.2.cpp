//#include <iostream>
//using namespace std;
//const int N = 10000;
////二叉树树结点结构体
//template<class T>
//struct binaryTreeNode
//{
//    T element;
//    binaryTreeNode<T>* leftChild,  //左子树
//        * rightChild;  //右子树
//    binaryTreeNode() { leftChild = rightChild = NULL; }
//    binaryTreeNode(const T& theElement)
//    {
//        element = theElement;
//        leftChild = rightChild = NULL;
//    }
//    binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild)
//    {
//        element(theElement);
//        leftChild = theLeftChild;
//        rightChild = theRightChild;
//    }
//};
//
////递归构造树,传入参数前序序列，前序序列左起点和右起点；中序序列，中序序列左起点和右起点；
//binaryTreeNode<int>* makeTree(int pre[], int l1, int r1, int in[], int l2, int r2) 
//{
//    //l1>r2，说明外部节点已经构造完成，往下已经无节点，返回NULL;
//    if (l1 > r1)return NULL;
//    //前序序列的第一个数是根节点，每次先找到根节点
//    binaryTreeNode<int>* root = new binaryTreeNode<int>(pre[l1]);
//    //递出条件，遍历结束
//    if (l1 == r1) { return root; }
//    //找出中序序列中树的根节点索引位置，然后可以确定左右子树节点数
//    int k = l2;
//    while (in[k] != pre[l1])k++;
//    //中序序列根节点前的数皆为左子树节点，根节点后皆为右子树节点，由此确定递归边界
//    root->leftChild = makeTree(pre, l1 + 1, l1 + k - l2, in, l2, k - 1);//构建左孩子，往下构造左子树
//    root->rightChild = makeTree(pre, l1 + k - l2 + 1, r1, in, k + 1, r2);//构建右孩子，往下构造右子树
//
//    return root;
//}
//
////后序遍历输出
//template<class T>
//void postOrder(binaryTreeNode<T>* t) {
//    if (t != NULL) {
//        postOrder(t->leftChild);
//        postOrder(t->rightChild);
//        cout << t->element << " ";
//    }
//}
//int main() {
//    int n;
//    cin >> n;
//    int pre[N]{}, in[N]{};
//    for (int i = 0; i < n; i++)//传入前序遍历的序列
//        cin >> pre[i];
//    for (int i = 0; i < n; i++)//传入中序遍历的序列
//        cin >> in[i];
//    binaryTreeNode<int>* root = makeTree(pre, 0, n - 1, in, 0, n - 1);//找到根节点，并构造树
//    postOrder(root);//后序遍历并输出
//    return 0;
//}
