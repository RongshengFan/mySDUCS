#pragma once
#include<iostream>
using namespace std;

template<class T>
struct PolyNode {
	T coef;            //ϵ��
	int expon;         //ָ��
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
	int Degree() { return degree; }							//������߽���
	int Size() { return size; }								//��������
	void Input(istream& in);								//�������ʽ
	void Output(ostream& out)const;							//�������ʽ
	void insert(T& c, int e);								//�����½ڵ�
	Polynomial<T>& Add(Polynomial<T>& b);					//���
	Polynomial<T>& Subtrac(Polynomial<T>& b);				//���
	Polynomial<T>& Multiply(Polynomial<T>& b);				//���
	Polynomial<T>& Divide(Polynomial<T>& b);				//���
	Polynomial<T>& DivMultiply(const int expon);			//���������
	Polynomial<T>& Derivative();                            //��
	T Value(const T& x);									//��ֵ
	Polynomial<T>& operator +(Polynomial<T>& b);
	Polynomial<T>& operator -(Polynomial<T>& b);
	Polynomial<T>& operator *(Polynomial<T>& b);
	Polynomial<T>& operator /(Polynomial<T>& b);
	Polynomial<T>& operator %(const T &MOD);
	T operator ()(const T& x);
protected:
	PolyNode<T>* firstNode; 
	int degree;             //����ʽ����
	int size;               //����
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
	Polynomial<T> p;//���ڼ�¼���
	for (int i = 0; i < n; i++) {//ѭ���������
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
{	//ϵ����Ч�Լ�⣬ϵ��Ϊ����ֱ�ӷ���
	if (coef == 0)return;
	//�����½ڵ�
	PolyNode<T>* newNode = new PolyNode<T>(coef, expon,NULL);
	//���¶���ʽ����
	if (degree < expon) {
		degree = expon;
	}
	//1.������Ϊ�ջ��½ڵ�Ӧ��Ϊͷ�������
	if (firstNode == NULL || firstNode->expon < expon) {
		newNode->next = firstNode;
		firstNode = newNode;
		size++;
	}
	else {
		//���������ҵ�����λ��
		PolyNode<T>* current = firstNode;
		while (current->next && current->next->expon > expon) {
			current = current->next;
		}
		//2.�����д���ָ����ͬ�Ľڵ㣬ϵ����Ӳ�����Ч���ж�
		if (current->next&&current->next->expon == expon) {//ʹ�ú�̽ڵ��жϣ�������������������
			current->next->coef += coef;
			if (current->next->coef == 0) {//ϵ��Ϊ�㣬ɾȥ�ڵ�
				PolyNode<T>* nextNode = current->next->next;
				delete current->next;
				current->next = nextNode;
				size--;
			}
		}
		//3.�����½ڵ�
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
	//������������ʽ��������ָ����ͬ�Ľڵ������ϵ�����
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->expon > p2->expon) {
			p.insert(p1->coef, p1->expon);
			p1 = p1->next;
		}
		else if (p1->expon < p2->expon) {
			p.insert(p2->coef, p2->expon);
			p2 = p2->next;
		}
		else {//ָ����ͬϵ�����
			int sumCoef = p1->coef + p2->coef;
			p.insert(sumCoef, p1->expon);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	// ����ʣ����  
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
	//������������ʽ��������ָ����ͬ�Ľڵ������ϵ�����
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
		else {//ָ����ͬϵ�����
			int sumCoef = p1->coef - p2->coef;
			p.insert(sumCoef, p1->expon);
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	// ����ʣ����  
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
	Polynomial<T> p;                   //p������¼���ս��
	PolyNode<T>* p1 = this->firstNode; //p1ָ��aʽ
	PolyNode<T>* p2 = b.firstNode;     //p2ָ��bʽ       
	//������������ڵ���г˷�����
	while (p1) {
		p2 = b.firstNode;
		while (p2) {
			//ָ����ӣ�ϵ����ˣ����������в����½ڵ�
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
	Polynomial<T> p;                   //p������¼���ս��
	PolyNode<T>* p1 = this->firstNode; //p1ָ��aʽ
	PolyNode<T>* p2 = b.firstNode;     //p2ָ��bʽ  
	Polynomial<T> quo;                 //��¼����
	Polynomial<T> ram;				   //��¼����
	//��������������
	while (p1) {
		//ָ�������ϵ����������½ڵ��������������
		int divExpon = p1->expon - p2->expon;
		T divCoef = p1->coef / p2->coef;

		quo.insert(divCoef, divExpon);

		//����������������������Ϊ����
		Polynomial temp = *this;
		temp.firstNode = p1->next;             //�����������Ѿ����������ߴ���
		ram = temp - (b.DivMultiply(divCoef)); //��������=������-����*�̵�ϵ��
		*this = ram;						   //����������Ϊ����
		p1 = this->firstNode;				   //p1����ָ�򱻳�����ߴ���
	}
	return quo;  //������
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
