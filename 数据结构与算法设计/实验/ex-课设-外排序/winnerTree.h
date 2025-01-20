#pragma once
#include<iostream>
using namespace std;
template<class T>
class winnerTree
{
public:
    winnerTree(T* thePlayer, int theNumberOfPlayers) {//���캯��
        this->tree = NULL;
        initialize(thePlayer, theNumberOfPlayers);
    }
    ~winnerTree() {//��������
        delete[] tree;
        tree = NULL;
    } 
    // Ϊ�����ʼ��������
    void initialize(T* thePlayer, int theNumberOfPlayers);
    //��������Ӯ�ߵĽڵ�����
    int Winner() const;
    //���ؾ�����ĳ���ڵ������
    int Winner(int i)const;
    //�ڲ�����thePLlayer�仯�����������ع�
    void rePlay(int thePLayer);
protected:
    //��tree[p]���б�����������и��ڵ㣬�������ϱ���
    void play(int p, int leftChild, int rightChild);
private:
    int lowExt;            //��ײ��ⲿ�ڵ����
    int offset;            //offset=2*s-1,sΪ��ײ�������ڲ��ڵ㣬s=2^[log(n-1)];
    int* tree;             //��СӮ����
    int numberOfPlayers;   //����ѡ������
    T* player;             //���澺��ѡ��
};

template<class T>
inline void winnerTree<T>::initialize(T* thePlayer, int theNumberOfPlayers)
{
    int n = theNumberOfPlayers;
    if (n < 2) {
        throw logic_error("the number of players must be at least 2");
    }
    //��ʼ���������ݳ�Ա
    this->numberOfPlayers = n;   //��ǰ��������Ŀ
    this->player = thePlayer;    //������
    delete[]tree;                //ɾ���ɾ�����
    this->tree = new int[n];     //�����¾���������
    //����s��s=2^[log(n-1)];
    int i, s;
    for (s = 1; 2 * s < n - 1; s += s);

    this->lowExt = 2 * (n - s);
    this->offset = 2 * s - 1;

    //Ϊ��ͼ�����ⲿ�ڵ����ƥ��
    for (i = 2; i <= this->lowExt; i += 2) {
        play((this->offset + i) / 2, i - 1, i);
    }
    //����ʣ����ⲿ�ڵ�
    if (n % 2 == 1) {//�������nΪ�����������ڲ��ڵ���ⲿ�ڵ�
        play(n / 2, this->tree[n - 1], this->lowExt + 1);
        i = this->lowExt + 3;
    }
    else {
        i = this->lowExt + 2;
    }
    //i�������ʣ����ⲿ�ڵ�
    for (; i <= n; i += 2) {
        play((i - this->lowExt + n - 1) / 2, i - 1,i);
    }

}

template<class T>
inline int winnerTree<T>::Winner() const
{
    return this->tree[1];
}

template<class T>
inline int winnerTree<T>::Winner(int i) const
{
    return (i < numberOfPlayers) ? this->tree[i] : 0;
}

template<class T>
inline void winnerTree<T>::rePlay(int thePLayer)
{
    int n = numberOfPlayers;
    if (thePLayer <= 0 || thePLayer > n) {
        throw logic_error("player index is illegal");
    }
    int matchNode;
    int leftChild;
    int rightChild;
    //���ҵ�һ��ƥ��ڵ㼰���ӽڵ�
    if (thePLayer <= lowExt) {
        matchNode = (offset + thePLayer) / 2;
        leftChild = 2 * matchNode - offset;
        rightChild = leftChild + 1;
    }
    else
    {
        matchNode = (thePLayer - lowExt + n - 1) / 2;
        if (2 * matchNode == n - 1) {
            leftChild = tree[2 * matchNode];
            rightChild = thePLayer;
        }
        else {
            leftChild = 2 * matchNode - n + 1 + lowExt;
            rightChild = leftChild + 1;
        }
    }
    tree[matchNode] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;
    if (matchNode == n - 1 && n % 2 == 1) {
        matchNode /= 2;
        tree[matchNode]= (this->player[tree[n - 1]] <= this->player[lowExt + 1]) ? tree[n - 1] : lowExt+1;
    }
    //��ʣ�µı���
    matchNode /= 2;//�������ڵ�
    while (matchNode >= 1) {
        tree[matchNode] =( (player[tree[2 * matchNode]] <= player[tree[2 * matchNode + 1]]) ? tree[2 * matchNode] : tree[2 * matchNode + 1]);
        matchNode /= 2;//�������ڵ�
    }
}

template<class T>
inline void winnerTree<T>::play(int p, int leftChild, int rightChild)
{
    //��СӮ������������СӮ��
    this->tree[p] = (this->player[leftChild] <= this->player[rightChild]) ? leftChild : rightChild;
    while (p % 2 == 1 && p > 1) {//pΪ���ӽڵ��һ��и��ڵ㣬�������ϱ���
        //�Ը��ڵ���б���
        this->tree[p / 2] = (this->player[tree[p - 1]] <= this->player[tree[p]]) ? tree[p - 1] : tree[p];
        //�����������ڵ�
        p /= 2;
    }
}
