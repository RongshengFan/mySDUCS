//#include <iostream>
//using namespace std;
//const int N = 10000;
////�����������ṹ��
//template<class T>
//struct binaryTreeNode
//{
//    T element;
//    binaryTreeNode<T>* leftChild,  //������
//        * rightChild;  //������
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
////�ݹ鹹����,�������ǰ�����У�ǰ����������������㣻�������У�������������������㣻
//binaryTreeNode<int>* makeTree(int pre[], int l1, int r1, int in[], int l2, int r2) 
//{
//    //l1>r2��˵���ⲿ�ڵ��Ѿ�������ɣ������Ѿ��޽ڵ㣬����NULL;
//    if (l1 > r1)return NULL;
//    //ǰ�����еĵ�һ�����Ǹ��ڵ㣬ÿ�����ҵ����ڵ�
//    binaryTreeNode<int>* root = new binaryTreeNode<int>(pre[l1]);
//    //�ݳ���������������
//    if (l1 == r1) { return root; }
//    //�ҳ��������������ĸ��ڵ�����λ�ã�Ȼ�����ȷ�����������ڵ���
//    int k = l2;
//    while (in[k] != pre[l1])k++;
//    //�������и��ڵ�ǰ������Ϊ�������ڵ㣬���ڵ���Ϊ�������ڵ㣬�ɴ�ȷ���ݹ�߽�
//    root->leftChild = makeTree(pre, l1 + 1, l1 + k - l2, in, l2, k - 1);//�������ӣ����¹���������
//    root->rightChild = makeTree(pre, l1 + k - l2 + 1, r1, in, k + 1, r2);//�����Һ��ӣ����¹���������
//
//    return root;
//}
//
////����������
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
//    for (int i = 0; i < n; i++)//����ǰ�����������
//        cin >> pre[i];
//    for (int i = 0; i < n; i++)//�����������������
//        cin >> in[i];
//    binaryTreeNode<int>* root = makeTree(pre, 0, n - 1, in, 0, n - 1);//�ҵ����ڵ㣬��������
//    postOrder(root);//������������
//    return 0;
//}
