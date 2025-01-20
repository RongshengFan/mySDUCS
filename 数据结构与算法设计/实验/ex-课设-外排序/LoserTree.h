#pragma once
#include<bits/stdc++.h>
using namespace std;
template <class T>
class LoserTree {
public:
	LoserTree(T* thePlayer = nullptr, int theSize = 0) {
		this->tree = nullptr;
		this->advance = nullptr;
		Initialize(thePlayer, theSize);
	}
	~LoserTree() { delete[]tree; delete[]advance; };
	//��������Ӯ�ߵ��±�
	int Winner()const { return tree[0]; };//O(1)
	//��������Ӯ��
	T getWinner()const { return player[tree[0]]; };
	//��ʼ��
	void Initialize(T* thePlayer, int theNumberOfPlayer);//O(n)
	//�ع�
	void rePlay(int thePLayer, T newPlaye);//O(logn)
protected:
	//��tree[p]���б�����������и��ڵ㣬�������ϱ���
	void play(int p, int leftChild, int rightChild);
	int judgeWinner (int i, int j) { return player[i] <= player[j] ? i : j; }
	int judgeLoser(int i, int j) { return player[i] <= player[j] ? j : i; }
private:
	int lowExt;             //��ײ��ⲿ�ڵ����
    int offset;             //offset=2*s-1,sΪ��ײ�������ڲ��ڵ㣬s=2^[log(n-1)];
    int* tree;              //��¼�ڲ��ڵ�,��¼����
	int* advance;			//��¼����ѡ�֣���¼������
    int numberOfPlayers;    //����ѡ������
    T* player;              //��¼����ѡ��
};

template<class T>
inline void LoserTree<T>::Initialize(T* thePlayer, int theNumberOfPlayer)
{
	int n = theNumberOfPlayer;
	if (n < 2) {
		cout << "the number of player must be >= 2 " << endl;
		return;
	}
	
	delete[]tree;
	delete[]advance;
	this->numberOfPlayers = n;
	this->player = thePlayer;
	this->tree = new int[n + 1];
	this->advance = new int[n + 1];

	int s;
	for (s = 1; 2 * s <= n - 1; s += s);
	this->lowExt = 2 * (n - s);
	this->offset = 2 * s - 1;
	//Ϊ��ͼ�����ⲿ�ڵ����ƥ��
	for (int i = 2; i <= lowExt; i += 2) {
		play((offset + i) / 2, i - 1, i);
	}
	
	//����ʣ����ⲿ�ڵ�
	int x = 0;
	if (n % 2 == 1) {//�������nΪ�����������ڲ��ڵ���ⲿ�ڵ�
		play(n / 2, advance[n - 1], lowExt + 1);
		x = lowExt + 3;
	}
	else {
		x = lowExt + 2;
	}
	//x�������ʣ����ⲿ�ڵ�
	for (int i=x; i <= n; i += 2) {
		play((i - lowExt + n - 1) / 2, i - 1, i);
	}
	tree[0] = advance[1];//tree[0]Ϊ���������ߣ�������Ӯ��
}

template<class T>
inline void LoserTree<T>::rePlay(int thePlayer,T newPlayer)
{
	int n = numberOfPlayers;
	if (thePlayer <= 0 || thePlayer > n) {
		throw logic_error("player index is illegal");
		//cout << "player index is illegal" << endl;
		return;
	}
	player[thePlayer] = newPlayer;

	int matchNode;	//��Ҫ�����ĳ���
	int leftChild;	//�����ڵ������
	int rightChild;	//�����ڵ���Һ���

	//���ҵ�һ��ƥ��ڵ㼰���ӽڵ�
	if (thePlayer <= lowExt) {//��������Ľڵ������²�
		matchNode = (offset + thePlayer) / 2;
		leftChild = 2 * matchNode - offset;
		rightChild = leftChild + 1;
	}
	else{//Ҫ�����Ľڵ��ڴ��²�
		matchNode = (thePlayer - lowExt + n - 1) / 2;
		if (2 * matchNode == n - 1) {//�������������һ���ǽ��������
			leftChild = advance[2 * matchNode];
			rightChild = thePlayer;
		}
		else {
			leftChild = 2 * matchNode - n + 1 + lowExt;//�����������Ϊ����matchNode������/2ȡ����
			rightChild = leftChild + 1;
		}
	}
	//��ʱ�Ѿ�����˱������������ѡ�ֵ�ȷ�������������б���������������Ҫ�������������
	if (thePlayer == tree[0]) {//�ع��ĵ����ϳ�����Ӯ�ߣ����̱�Ӯ�����ϼ�
		while (matchNode >= 1) {
			int oldNode = tree[matchNode];
			tree[matchNode] = judgeLoser(oldNode, thePlayer);
			advance[matchNode] = judgeWinner(oldNode, thePlayer);
			thePlayer = advance[matchNode];
			matchNode /= 2;//�������ڵ�
		}
	}
	else {
		tree[matchNode] = judgeLoser(leftChild,rightChild);
		advance[matchNode] = judgeWinner(leftChild, rightChild);
		if (matchNode == n - 1 && n % 2 == 1) {//���������������������һ������һ��������������matchNode/2��������ǽ�����ѡ�֣��Ҷ�����һ����û�бȹ�����ѡ��
			matchNode /= 2;
			tree[matchNode] = judgeLoser(advance[n - 1], lowExt + 1);
			advance[matchNode] = judgeWinner(advance[n - 1], lowExt + 1);
		}
		//��ʣ�µı���
		matchNode /= 2;//�������ڵ�
		while (matchNode >= 1) {
			tree[matchNode] = judgeLoser(advance[2 * matchNode], advance[2 * matchNode + 1]);
			advance[matchNode] = judgeWinner(advance[2 * matchNode], advance[2 * matchNode + 1]);
			matchNode /= 2;//�������ڵ�
		}
	}
	tree[0] = advance[1];//����Ӯ��
}

template<class T>
inline void LoserTree<T>::play(int p, int leftChild, int rightChild)
{
	//tree���洢��Խϴ��ֵ��Ҳ�����ⳡ����������
	tree[p] = judgeLoser(leftChild, rightChild);
	//advance���洢��Խ�С��ֵ��Ҳ�����ⳡ�����Ľ�����
	advance[p] = judgeWinner(leftChild, rightChild);
	while (p % 2 == 1 && p > 1) {//pΪ���ӽڵ��һ��и��ڵ㣬�������ϱ���
		//�Ը��ڵ���б���
		tree[p / 2] = judgeLoser(advance[p - 1], advance[p]);
		advance[p / 2] = judgeWinner(advance[p - 1], advance[p]);
		//�����������ڵ�
		p /= 2;
	}
}
