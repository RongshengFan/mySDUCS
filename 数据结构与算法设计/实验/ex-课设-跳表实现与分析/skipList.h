#pragma once
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
using namespace std;
//�ṹskipNode
template <class K, class E>
struct skipNode {
    typedef pair<const K, E>pairType;

    pairType element;
    skipNode<K, E>** next;//ָ������

    skipNode(const pairType& thePair, int size) :element(thePair) {
        next = new skipNode<K, E>*[size];
    }
};
//��skipList
template <class K, class E>
class skipList
{

public:
    skipList(K largeKey = 100000, int maxPairs = 10000, float prob = 0.5);
    ~skipList();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, E>* find(const K&) const;
    void initialize(int n);
    void erase(const K&);
    pair<const K, E> eraseMin();
    pair<const K, E> eraseMax();
    void insert(const pair<const K, E>&);
    void output() const;
    void inputArry(int a[]);

protected:
    float cutOff;          // ����ȷ��������
    int level() const;     // ���ķ��䷽��������һ����ʾ�������������������maxLevel
    int levels;            // ��ǰ���ķǿ�����
    int dSize;             // �ֵ�����Ը���
    int maxLevel;          // ���������������
    K tailKey;             // ���ؼ���
    skipNode<K, E>* search(const K&) const; // ���������濴�������һ���ڵ㵽����last��
    skipNode<K, E>* headerNode;  // ͷ�ڵ�ָ��
    skipNode<K, E>* tailNode;    // β�ڵ�ָ��
    skipNode<K, E>** last;       // last[i]��ʾi������ڵ�

};

template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{//���캯��
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
    levels = 0;
    dSize = 0;
    tailKey = largeKey;

    //����ͷ�ڵ㡢β�ڵ������last
    pair<K, E>tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K, E>(tailPair, 0);
    last = new skipNode<K, E> *[maxLevel + 1];

    //����Ϊ��ʱ�����⼶�����е�ͷ�ڵ㶼ָ��β�ڵ�
    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K, E>::~skipList()
{// ��������
    skipNode<K, E>* nextNode;

    // ɾ��0�����������нڵ�
    while (headerNode != tailNode)
    {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;

    delete[] last;

}

template<class K, class E>
pair<const K, E>* skipList<K, E>::find(const K& theKey) const //ʱ�临�Ӷ�ƽ��O(logn)���O(n)
{// ����ƥ������Ե�ָ��
 // ���û��ƥ������ԣ�����NULL;
    if (theKey >= tailKey)
        return NULL;  // û�п��ܵ�ƥ�������

    // λ�� beforeNode�ǹؼ���ΪtheKey�ýڵ�֮ǰ�����ұߵ�λ��
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)          // ���ϼ������¼�����
        // ����i������ָ��
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];

    // �����һ���ڵ�Ĺؼ����Ƿ���theKey
    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;

    return NULL;  //��ƥ�������
}
template<class K, class E>
void skipList<K, E>::initialize(int n)
{//��ʼ����keyֵ��valueֵ��ͬ
    pair<K, E> thePair(make_pair(n,n));
    insert(thePair);
}
template<class K, class E>
void skipList<K, E>::erase(const K& theKey)//ʱ�临�Ӷ�ƽ��O(logn)���O(n)
{//ɾ���ؼ��ֵ���theKey������
    if (theKey >= tailKey) // �ؼ���̫��
        return;

    // �鿴�Ƿ���ƥ�������
    skipNode<K, E>* theNode = search(theKey);
    if (theNode->element.first != theKey) // ������
        return;

    // ��������ɾ���ڵ�
    for (int i = 0; i <= levels &&
        last[i]->next[i] == theNode; i++)
        last[i]->next[i] = theNode->next[i];

    // ��������
    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
    
}
template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMin()//O(1)���Ӷ�
{//ɾ���ؼ�����С������

    //����Ϊ�գ��˳�
    if (headerNode->next[0] == tailNode)
    {
        pair<const K, E> thePair(make_pair(-1, -1));
        return thePair;
    }
        

    //ɾ���ڵ�
    skipNode<K, E>* theNode = headerNode->next[0];
    pair<const K, E> thePair = theNode->element;
    //cout << "(" << theNode->element.first << " " << theNode->element.second << ")" < endl;
    for (int i = 0; i <= levels &&
        headerNode->next[i] == theNode; i++)
        headerNode->next[i] = theNode->next[i];

    // ��������
    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
    return thePair;
}
template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMax() //ʱ�临�Ӷ�ƽ��O(logn)���O(n)
{//ɾ���ؼ�����������
    //����Ϊ�գ��˳�
    if (headerNode->next[0] == tailNode) {
        pair<const K, E> thePair(make_pair(-1, -1));
        return thePair;
    }

    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        if (beforeNode->next[i] == tailNode)
            continue;
        while (beforeNode->next[i]->next[i] != tailNode)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;  // ���һ������i�Ľڵ�
    }
    //ɾ���ڵ�
    skipNode<K, E>* theNode = beforeNode->next[0];
    pair<const K, E> thePair = theNode->element;
    //cout << "(" << theNode->element.first << " " << theNode->element.second << ")" < endl;
    for (int i = 0; i <= levels &&
        last[i]->next[i] == theNode; i++)
        last[i]->next[i] = theNode->next[i];

    // ��������
    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
    return thePair;
}
template<class K, class E>
int skipList<K, E>::level() const
{// ����һ����ʾ��������������Ҳ�����maxLevel
    int lev = 0;
    while (rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel;
}
template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{// �����ؼ���theKey����ÿһ��������Ҫ�鿴�����һ���ڵ�洢������last��
 //���ذ����ؼ���theKey�Ľڵ�
   // λ�� beforeNode�ǹؼ���ΪtheKey�ýڵ�֮ǰ���ұߵ�λ��
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;  // ���һ������i�Ľڵ�
    }
    return beforeNode->next[0];
}

template<class K, class E>
void skipList<K, E>::insert(const pair<const K, E>& thePair) //ʱ�临�Ӷ�ƽ��O(logn)���O(n)
{// ������thePair�����ֵ䣬�����Ѵ��ڵ���ͬ����
    if (thePair.first >= tailKey) // �ؼ���̫��
    {
        ostringstream s;
        s << "Key = " << thePair.first << " Must be < " << tailKey;
        throw logic_error(s.str());
    }

    // �鿴�ؼ���ΪtheKey�������Ƿ��Ѿ�����
    skipNode<K, E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first)
    {// ����������¸����Ե�ֵ
        theNode->element.second = thePair.second;
        return;
    }

    // �������ڣ���ȷ���½ڵ����ڵļ�����
    int theLevel = level(); // �½ڵ�ļ�
    // ʹ�� theLevel Ϊ <= levels + 1
    if (theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    // �ڽڵ�theNode������½ڵ�
    skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; i++)
    {// ����i������
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
    return;
}
template<class K, class E>
void skipList<K, E>::output() const
{//���0������ڵ�
    for (skipNode<K, E>* currentNode = headerNode->next[0];
        currentNode != tailNode;
        currentNode = currentNode->next[0])
        cout<<"(" << currentNode->element.first << ","<< currentNode->element.first << ")->";
}

template<class K, class E>
inline void skipList<K, E>::inputArry(int a[])
{//���ڽ������е�Ԫ�عؼ�������һά������
    int i = 0;
    for (skipNode<K, E>* currentNode = headerNode->next[0];
        currentNode != tailNode;
        currentNode = currentNode->next[0])
        a[i++] = currentNode->element.first;
}

