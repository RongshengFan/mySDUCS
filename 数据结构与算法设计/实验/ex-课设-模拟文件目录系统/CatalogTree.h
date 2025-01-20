#pragma once
#include<bits/stdc++.h>
using namespace std;
struct CatalogNode {
	string name;					//��ǰĿ¼����
	bool isFile;					//��ʶλ�����Ҷ�ڵ�
	CatalogNode* father;			//��¼���ڵ�
	vector<CatalogNode*>next;		//��ǰĿ¼�µ���Ŀ¼
	CatalogNode(const string& Name, CatalogNode* father = nullptr, bool isFile = false) :name(Name), father(father), isFile(isFile) {}
	bool operator<(const CatalogNode& b)const {
		return name < b.name;
	}
};
class CatalogTree {
public:
	//���캯��
	CatalogTree();
	//�г���ǰĿ¼�µ�����Ŀ¼�ļ���
	void Dir();
	//�����ǰĿ¼�ľ���·��
	void Cd();
	//��ǰĿ¼��Ϊ��ǰĿ¼�ĸ�Ŀ¼
	void CdUp();
	//��ǰĿ¼��Ϊstr��ʾ·����Ŀ¼
	void CdTo(const string& str);
	//�ڵ�ǰĿ¼�´���һ����Ŀ¼str
	void Mkdir(const string& str);
	//�ڵ�ǰĿ¼�´���һ���ļ�str
	void Mkfile(const string& str);
	//�ڵ�ǰĿ¼��ɾȥ��Ϊstr����Ŀ¼���ļ�
	void Delete(const string& str);
	//���浱ǰĿ¼���ṹ���ļ���
	void Save(const string& fileName);
	//���ص�ǰĿ¼���ṹ���ļ���
	void Load(const string& fileName);
	//����Ŀ¼���ļ�,Ѱ��ĳһ���ڵ�
	void Search(const string& str);
	//���ļ���s1���Ƶ��ļ���s2��
	void Cpr(const string& s1, const string& s2);
	//�����ļ�����ӦĿ¼��
	void Cp(const string& s1, const string& s2);
	//��ȡ��ǰĿ¼�ľ���·��
	string getRoute()const { return route; }
protected:
	//���µ�ǰ�ڵ㵽���ڵ��·��
	void setRoute();
	//�ж�����Ӧ��Ŀ¼�ڵ����Ƿ����Ҫ�ҵ���Ŀ¼�����ļ�
	bool Judge(CatalogNode* p, const string& name);
	//ͨ����������·��������·��������Ŀ¼���ҵ���Ӧ�Ľڵ�
	CatalogNode* FindNode(const string& path);
private:
	CatalogNode* current;	//Ŀ¼����ǰ�ڵ�
	CatalogNode* root;		//Ŀ¼�����ڵ�
	string route;			//��ǰ�ڵ㵽���ڵ��·��
};
