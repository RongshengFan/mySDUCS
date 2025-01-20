#pragma once
class fastUnionFind {

private:
    int n;//�ڵ���Ŀ
    int* node; //ÿ���ڵ�
    int* rank; //���ĸ߶�

public:
    //��ʼ��n���ڵ�
    void Init(int n) {
        for (int i = 0; i < n; i++) {
            node[i] = i;
            rank[i] = 0;
        }
    }

    //���캯��
    fastUnionFind(int n) : n(n) {
        node = new int[n];
        rank = new int[n];
        Init(n);
    }

    //��������
    ~fastUnionFind() {
        delete[] node;
        delete[] rank;
    }

    //���ҵ�ǰԪ���������ĸ��ڵ�(����Ԫ��)
    int find(int x) {
        if (x == node[x])
            return x;
        return node[x] = find(node[x]); //�ڵ�һ�β���ʱ�����ڵ�ֱ�������ڵ�
    }
    //�ϲ�Ԫ��x�� y�����ļ���
    void unite(int x, int y) {
        //���ҵ�x��y�ĸ��ڵ�
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        //�ж��������ĸ߶ȣ�Ȼ���ھ���˭Ϊ����
        if (rank[x] < rank[y]) {
            node[x] = y;
        }
        else {
            node[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    //�ж�x��y������ͬһ������
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
