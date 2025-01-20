#pragma once
class fastUnionFind {

private:
    int n;//节点数目
    int* node; //每个节点
    int* rank; //树的高度

public:
    //初始化n个节点
    void Init(int n) {
        for (int i = 0; i < n; i++) {
            node[i] = i;
            rank[i] = 0;
        }
    }

    //构造函数
    fastUnionFind(int n) : n(n) {
        node = new int[n];
        rank = new int[n];
        Init(n);
    }

    //析构函数
    ~fastUnionFind() {
        delete[] node;
        delete[] rank;
    }

    //查找当前元素所在树的根节点(代表元素)
    int find(int x) {
        if (x == node[x])
            return x;
        return node[x] = find(node[x]); //在第一次查找时，将节点直连到根节点
    }
    //合并元素x， y所处的集合
    void unite(int x, int y) {
        //查找到x，y的根节点
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        //判断两棵树的高度，然后在决定谁为子树
        if (rank[x] < rank[y]) {
            node[x] = y;
        }
        else {
            node[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    //判断x，y是属于同一个集合
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
