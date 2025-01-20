#pragma once
template<class K,class T>
class dictionary
{
public:
	//析构函数
	virtual ~dictionary() {};
	//返回ture，当且仅当字典为空
	virtual bool empty()const = 0;
	//返回字典中数对的数目
	virtual int size()const = 0;
	//返回匹配数对的指针
	virtual pair<const K, T>* find(const K&)const = 0;
	//删除匹配的数对
	virtual void erase(const K&) = 0;
	//往字典中插入一个数对
	virtual void insert(const pair<const K, T>&) = 0;
};