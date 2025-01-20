#pragma once
#include<iostream>
using namespace std;

template<class T>
struct PolyNode {
	T coef;            //系数
	int expon;         //指数
	PolyNode<T>* next;
	PolyNode() {};
	PolyNode(const T &c, const int e) {
		this->coef = c;
		this->expon = e;
	}
	PolyNode(const T &c,const int e, PolyNode<T>* next) {
		this->coef = c;
		this->expon = e;
		this->next = next;
	}
};

template<class T>
class Polynomial {
public:
	Polynomial();
	Polynomial(Polynomial<T>&b);
	int Degree() { return degree; }							//返回最高阶数
	int Size() { return size; }								//返回项数
	void Input(istream& in);								//输入多项式
	void Output(ostream& out)const;							//输出多项式
	void insert(T& c, int e);								//插入新节点
	Polynomial<T>& Add(Polynomial<T>& b);					//相加
	Polynomial<T>& Subtrac(Polynomial<T>& b);				//相减
	Polynomial<T>& Multiply(Polynomial<T>& b);				//相乘
	Polynomial<T>& Divide(Polynomial<T>& b);				//相除
	Polynomial<T>& DivMultiply(const int expon);			//计算除余数
	Polynomial<T>& Derivative();                            //求导
	T Value(const T& x);									//求值
	Polynomial<T>& operator +(Polynomial<T>& b);
	Polynomial<T>& operator -(Polynomial<T>& b);
	Polynomial<T>& operator *(Polynomial<T>& b);
	Polynomial<T>& operator /(Polynomial<T>& b);
	Polynomial<T>& operator %(const T &MOD);
	T operator ()(const T& x);
protected:
	PolyNode<T>* firstNode; 
	int degree;             //多项式阶数
	int size;               //项数
};

template<class T>
inline Polynomial<T>::Polynomial()
{
	degree = 0;
	firstNode = NULL;
	size = 0;
}

template<class T>
inline Polynomial<T>::Polynomial(Polynomial<T>& b)
{
	this->firstNode = b.firstNode;
	this->degree = b.degree;
	this->size = b.size;
}

template<class T>
void Polynomial<T>::Input(istream& in)
{
	int n;
	in >> n;
	Polynomial<T> p;//用于记录结果
	for (int i = 0; i < n; i++) {//循环输入各项
		T coef = 0;
		int expon = 0;
		in >> coef >> expon;
		p.insert(coef, expon);
		*this = p;
	}
}
template<class T>
istream& operator>>(istream& in, Polynomial<T>& p)
{
	p.Input(in);
	return in;
}

template<class T>
inline void Polynomial<T>::Output(ostream& out)const
{
	if (firstNode == NULL) {
		out << "0" << endl;
		return;
	}
	PolyNode<T>* p = firstNode;
	if (p->coef == 1) {
		if (p->expon == 1) {
			out << "x";
		}
		else if (p->expon == 0) {
			out <<"1";
		}		
		else {
			out << "x^" << p->expon;
		}
	}
	else if(p->coef == -1) {
		if (p->expon == 1) {
			out << "-x";
		}
		else if (p->expon == 0) {
			out << "-1";
		}
		else {
			out << "-x^" << p->expon;
		}
	}
	else {
		if (p->expon == 1) {
			out << p->coef << "x";
		}
		else if (p->expon == 0) {
			out << p->coef;
		}
		else {
			out << p->coef << "*x^" << p->expon;
		}
	}
	p = p->next;
	while (p) {
		if (p->coef == 1) {
			if (p->expon == 1) {
				out << "+x";
			}
			else if (p->expon == 0) {
				out << "+1";
			}
			else {
				out << "+x^" << p->expon;
			}
		}
		else if (p->coef == -1) {
			if (p->expon == 1) {
				out << "-x";
			}
			else if (p->expon == 0) {
				out << "-1";
			}
			else {
				out << "-x^" << p->expon;
			}
		}
		else {
			if (p->coef > 0) {
				if (p->expon == 1) {
					out <<"+" << p->coef << "x";
				}
				else if (p->expon == 0) {
					out <<"+" << p->coef;
				}
				else {
					out <<"+" << p->coef << "*x^" << p->expon;
				}
			}
			else if (p->coef < 0) {
				if (p->expon == 1) {
					out << p->coef << "x";
				}
				else if (p->expon == 0) {
					out << p->coef;
				}
				else {
					out << p->coef << "*x^" << p->expon;
				}
			}	
		}
		p = p->next;
	}
	out << endl;
}
template<class T>
ostream& operator <<(ostream& out, const Polynomial<T> p)
{
	p.Output(out);
	return out;
}

template<class T>
inline void Polynomial<T>::insert(T& coef, int expon)
{	//系数有效性检测，系数为零则直接返回
	if (coef == 0)return;
	//构造新节点
	PolyNode<T>* newNode = new PolyNode<T>(coef, expon,NULL);
	//更新多项式阶数
	if (degree < expon) {
		degree = expon;
	}
	//1.若链表为空或新节点应成为头结点的情况
	if (firstNode == NULL || firstNode->expon < expon) {
		newNode->next = firstNode;
		firstNode = newNode;
		size++;
	}
	else {
		//遍历链表找到插入位置
		PolyNode<T>* current = firstNode;
		while (current->next && current->next->expon > expon) {
			current = current->next;
		}
		//2.链表中存在指数相同的节点，系数相加并做有效性判断
		if (current->next&&current->next->expon == expon) {//使用后继节点判断，否则容易跳过该条件
			current->next->coef += coef;
			if (current->next->coef == 0) {//系数为零，删去节点
				PolyNode<T>* nextNode = current->next->next;
				delete current->next;
				current->next = nextNode;
				size--;
			}
		}
		//3.插入新节点
		else {
			newNode->next = current->next;
			current->next = newNode;
			size++;
		}
	}
}

template<class T>
Polynomial<T>& Polynomial<T>::Add(Polynomial<T>& b)
{
	Polynomial<T> p;
	PolyNode<T>* p1 = firstNode;
	PolyNode<T>* p2 = b.firstNode;
	//遍历两个多项式链表，遇到指数相同的节点则进行系数相加
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->expon > p2->expon) {
			p.insert(p1->coef, p1->expon);
			p1 = p1->next;
		}
		else if (p1->expon < p2->expon) {
			p.insert(p2->coef, p2->expon);
			p2 = p2->next;
		}
		else {//指数相同系数相加
			int sumCoef = p1->coef + p2->coef;
			p.insert(sumCoef, p1->expon);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	// 处理剩余项  
	while (p1 != nullptr) {
		p.insert(p1->coef, p1->expon);
		p1 = p1->next;
	}
	while (p2 != nullptr) {
		p.insert(p2->coef, p2->expon);
		p2 = p2->next;
	}
	return p;
}

template<class T>
Polynomial<T>& Polynomial<T>::Subtrac(Polynomial<T>& b)
{
	Polynomial<T> p;
	PolyNode<T>* p1 = firstNode;
	PolyNode<T>* p2 = b.firstNode;
	//遍历两个多项式链表，遇到指数相同的节点则进行系数相加
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->expon > p2->expon) {
			p.insert(p1->coef, p1->expon);
			p1 = p1->next;
		}
		else if (p1->expon < p2->expon) {
			T coef = -p2->coef;
			p.insert(coef, p2->expon);
			p2 = p2->next;
		}
		else {//指数相同系数相加
			int sumCoef = p1->coef - p2->coef;
			p.insert(sumCoef, p1->expon);
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	// 处理剩余项  
	while (p1 != nullptr) {
		p.insert(p1->coef, p1->expon);
		p1 = p1->next;
	}
	while (p2 != nullptr) {
		T coef = -p2->coef;
		p.insert(coef, p2->expon);
		p2 = p2->next;
	}

	return p;
}

template<class T>
Polynomial<T>& Polynomial<T>::Multiply(Polynomial<T>& b)
{
	Polynomial<T> p;                   //p用来记录最终结果
	PolyNode<T>* p1 = this->firstNode; //p1指向a式
	PolyNode<T>* p2 = b.firstNode;     //p2指向b式       
	//遍历访问链表节点进行乘法运算
	while (p1) {
		p2 = b.firstNode;
		while (p2) {
			//指数相加，系数相乘，向结果链表中插入新节点
			int mulExpon = p1->expon + p2->expon;
			T muLCoef = p1->coef * p2->coef;
			p.insert(muLCoef, mulExpon);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return p;
}

template<class T>
Polynomial<T>& Polynomial<T>::Divide(Polynomial<T>& b)
{
	Polynomial<T> p;                   //p用来记录最终结果
	PolyNode<T>* p1 = this->firstNode; //p1指向a式
	PolyNode<T>* p2 = b.firstNode;     //p2指向b式  
	Polynomial<T> quo;                 //记录商数
	Polynomial<T> ram;				   //记录余数
	//遍历被除数链表
	while (p1) {
		//指数相减，系数相除，将新节点插入商数链表中
		int divExpon = p1->expon - p2->expon;
		T divCoef = p1->coef / p2->coef;

		quo.insert(divCoef, divExpon);

		//计算余数，将被除数更新为余数
		Polynomial temp = *this;
		temp.firstNode = p1->next;             //过掉被除数已经处理掉的最高次项
		ram = temp - (b.DivMultiply(divCoef)); //更新余数=被除数-除数*商的系数
		*this = ram;						   //被除数更新为余数
		p1 = this->firstNode;				   //p1继续指向被除数最高次项
	}
	return quo;  //返回商
}

template<class T>
inline Polynomial<T>& Polynomial<T>::DivMultiply(const int divCoef)
{
	PolyNode<T>* p = firstNode;
	while (p) {
		p->coef = p->coef * divCoef;
		p = p->next;
	}
	firstNode = p;
	return *this;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::Derivative()
{
	Polynomial<T>p;
	PolyNode<T>* current = this->firstNode;
	while (current) {
		T derCoef = current->coef * current->expon;
		int derExpon = current->expon - 1;
		p.insert(derCoef, derExpon);
		current = current->next;
	}
	return p;
}

template<class T>
inline T Polynomial<T>::Value(const T& x)
{
	T sum{};
	PolyNode<T>* p = firstNode;
	while (p ) {
		sum += p->coef * pow(x, p->expon);
		p = p->next;
	}
	return sum;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::operator+(Polynomial<T>& b)
{
	Polynomial<T> p = Add(b);
	return p;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::operator-(Polynomial<T>& b)
{
	Polynomial<T> p = Subtrac(b);
	return p;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::operator*(Polynomial<T>& b)
{
	Polynomial<T> p = Multiply(b);
	return p;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::operator/(Polynomial<T>& b)
{
	Polynomial<T> p = Divide(b);
	return p;
}

template<class T>
inline Polynomial<T>& Polynomial<T>::operator%(const T& MOD)
{
	Polynomial<T>p;
	PolyNode<T>* current = this->firstNode;
	while (current) {
		T derCoef = current->coef % MOD;
		int derExpon = current->expon;
		p.insert(derCoef, derExpon);
		current = current->next;
	}
	return p;

}

template<class T>
inline T Polynomial<T>::operator()(const T& x)
{
	return Value(x);
}
