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
	//返回最终赢者的下标
	int Winner()const { return tree[0]; };//O(1)
	//返回最终赢者
	T getWinner()const { return player[tree[0]]; };
	//初始化
	void Initialize(T* thePlayer, int theNumberOfPlayer);//O(n)
	//重构
	void rePlay(int thePLayer, T newPlaye);//O(logn)
protected:
	//对tree[p]进行比赛，如果还有父节点，继续向上比赛
	void play(int p, int leftChild, int rightChild);
	int judgeWinner (int i, int j) { return player[i] <= player[j] ? i : j; }
	int judgeLoser(int i, int j) { return player[i] <= player[j] ? j : i; }
private:
	int lowExt;             //最底层外部节点个数
    int offset;             //offset=2*s-1,s为最底层最左端内部节点，s=2^[log(n-1)];
    int* tree;              //记录内部节点,记录输者
	int* advance;			//记录晋级选手，记录晋级者
    int numberOfPlayers;    //竞赛选手数量
    T* player;              //记录竞赛选手
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
	//为最低级别的外部节点进行匹配
	for (int i = 2; i <= lowExt; i += 2) {
		play((offset + i) / 2, i - 1, i);
	}
	
	//处理剩余的外部节点
	int x = 0;
	if (n % 2 == 1) {//特殊情况n为奇数，发挥内部节点和外部节点
		play(n / 2, advance[n - 1], lowExt + 1);
		x = lowExt + 3;
	}
	else {
		x = lowExt + 2;
	}
	//x是最左边剩余的外部节点
	for (int i=x; i <= n; i += 2) {
		play((i - lowExt + n - 1) / 2, i - 1, i);
	}
	tree[0] = advance[1];//tree[0]为决赛晋级者，即最终赢者
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

	int matchNode;	//将要比赛的场次
	int leftChild;	//比赛节点的左孩子
	int rightChild;	//比赛节点的右孩子

	//查找第一个匹配节点及其子节点
	if (thePlayer <= lowExt) {//如果比赛的节点在最下层
		matchNode = (offset + thePlayer) / 2;
		leftChild = 2 * matchNode - offset;
		rightChild = leftChild + 1;
	}
	else{//要比赛的节点在次下层
		matchNode = (thePlayer - lowExt + n - 1) / 2;
		if (2 * matchNode == n - 1) {//特殊情况，其中一方是晋级后的人
			leftChild = advance[2 * matchNode];
			rightChild = thePlayer;
		}
		else {
			leftChild = 2 * matchNode - n + 1 + lowExt;//这个操作是因为上面matchNode计算中/2取整了
			rightChild = leftChild + 1;
		}
	}
	//此时已经完成了比赛场次与比赛选手的确定，接下来进行比赛重赛，这里需要分两种情况分析
	if (thePlayer == tree[0]) {//重构的点事上场比赛赢者，过程比赢者树较简化
		while (matchNode >= 1) {
			int oldNode = tree[matchNode];
			tree[matchNode] = judgeLoser(oldNode, thePlayer);
			advance[matchNode] = judgeWinner(oldNode, thePlayer);
			thePlayer = advance[matchNode];
			matchNode /= 2;//移至父节点
		}
	}
	else {
		tree[matchNode] = judgeLoser(leftChild,rightChild);
		advance[matchNode] = judgeWinner(leftChild, rightChild);
		if (matchNode == n - 1 && n % 2 == 1) {//特殊情况，比赛结点是最后一层的最后一场比赛，特殊在matchNode/2后，左儿子是晋级的选手，右儿子是一场都没有比过赛的选手
			matchNode /= 2;
			tree[matchNode] = judgeLoser(advance[n - 1], lowExt + 1);
			advance[matchNode] = judgeWinner(advance[n - 1], lowExt + 1);
		}
		//玩剩下的比赛
		matchNode /= 2;//移至父节点
		while (matchNode >= 1) {
			tree[matchNode] = judgeLoser(advance[2 * matchNode], advance[2 * matchNode + 1]);
			advance[matchNode] = judgeWinner(advance[2 * matchNode], advance[2 * matchNode + 1]);
			matchNode /= 2;//移至父节点
		}
	}
	tree[0] = advance[1];//最终赢者
}

template<class T>
inline void LoserTree<T>::play(int p, int leftChild, int rightChild)
{
	//tree结点存储相对较大的值，也就是这场比赛的输者
	tree[p] = judgeLoser(leftChild, rightChild);
	//advance结点存储相对较小的值，也就是这场比赛的晋级者
	advance[p] = judgeWinner(leftChild, rightChild);
	while (p % 2 == 1 && p > 1) {//p为右子节点且还有父节点，继续向上比赛
		//对父节点进行比赛
		tree[p / 2] = judgeLoser(advance[p - 1], advance[p]);
		advance[p / 2] = judgeWinner(advance[p - 1], advance[p]);
		//向上移至父节点
		p /= 2;
	}
}
