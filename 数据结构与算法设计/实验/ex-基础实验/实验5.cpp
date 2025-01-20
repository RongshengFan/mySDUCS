//#include<iostream>
//#include <sstream>
//using namespace std;
////��Ԫ�鶨��
//struct matrixTerm
//{
//	int row;	//��λ��
//	int col;	//��λ��
//	int value;	//Ԫ��ֵ
//
////	int getValue() const { return value; }
//	matrixTerm& operator=(matrixTerm& x)//����"="���������ʹ�ã�����α��е�insert����
//	{
//		row = x.row;
//		col = x.col;
//		value = x.value;
//		return *this;
//	}
//};
////ϡ�����
//class sparseMatrix
//{
//	
//public:
//	sparseMatrix(int n,int m);
//	~sparseMatrix() { delete[]terms; }
//
//	sparseMatrix& operator=(sparseMatrix& b);
//	void initial(int n, int m);
//	int multiply(sparseMatrix& b);
//	int add(sparseMatrix& b);
//	void output();
//	void transpose();
//	void intputTerm(int x, int y, int v);
//
//private:
//	int rows;//����
//	int cols;//����
//	int termSize;//��Ԫ���ŵķ���Ԫ�ظ���
//	int maxSize;//��Ԫ������ɵ����Ԫ�ظ���
//	matrixTerm* terms;//��ŷ���Ԫ�ص���Ԫ���
//};
////���캯��
//sparseMatrix::sparseMatrix(int n, int m)
//{
//	rows = n;
//	cols = m;
//	termSize = 0;
//	maxSize = 250000;
//	terms = new matrixTerm [maxSize];
//}
////����ϡ�����ġ�=��
//sparseMatrix& sparseMatrix::operator=(sparseMatrix& b)
//{
//	rows = b.rows;
//	cols = b.cols;
//	termSize = b.termSize;
//	maxSize = b.maxSize;
//	for (int i = 0; i < termSize; i++)
//	{
//		terms[i] = b.terms[i];
//	}
//	return *this;
//}
////1.����
//void sparseMatrix::initial(int n, int m)
//{
//	rows = n;//��¼����
//	cols = m;//��¼����
//	termSize = 0;//�������Ҫ�����
//	int v = 0;     //��¼����Ԫ��ֵ
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= m; j++)
//		{
//			cin >> v;
//			if (v != 0)
//			{
//				matrixTerm mTerm;
//				mTerm.row = i;
//				mTerm.col = j;
//				mTerm.value = v;
//				terms[termSize++] = mTerm;
//			}
//		}
//	}
//}
////2.�˷�
//int sparseMatrix::multiply(sparseMatrix& b)
//{
//	//�Ϸ����ж�
//	if (cols != b.rows)
//	{
//		*this = b;
//		return -1;
//	}
//	//���ý������c
//	sparseMatrix c(rows, b.cols);
//	int rowSize[500] = { 0 };		//ÿ�з���Ԫ�ظ���
//	int rowIndex[500] = { 0 };		//ÿ���׸�����Ԫ������
//	int ans[10000] = { 0 };			//�ۼ�������¼�˻�ֵ
//	for (int i = 1; i <= b.rows; i++)//��ʼ��
//	{
//		rowSize[i] = 0;
//	}
//	for (int i = 0; i < b.termSize; i++)//��¼b��ÿ��Ԫ�ظ���
//	{
//		if (b.terms[i].value != 0)
//			rowSize[b.terms[i].row]++;
//	}
//	rowIndex[1] = 0;
//	for (int i = 2; i <= b.termSize; i++)//��¼ÿ���׸�����Ԫ������ֵ
//		rowIndex[i] = rowIndex[i - 1] + rowSize[i - 1];
//
//	for (int i = 1, it = 0; i <= rows && it < termSize; i++)//����*this�����ÿһ��ֱ�����������з���Ԫ��
//	{
//		for (int j = 1; j <= b.cols; j++)
//		{
//			ans[j] = 0;//�ۼ�����ʼ��
//		}
//		//��ʼ����˻�,������Ԫ���
//		while (it < termSize && terms[it].row == i)//����*this�ĵ�i��
//		{
//			int y = terms[it].col;//��¼it����λ�ã���Ӧib����λ��
//			for (int ib = rowIndex[y]; ib < rowIndex[y] + rowSize[y]; ib++)
//			{
//				//�����i��ÿ�еĳ˻�
//				if (y == b.terms[ib].row)
//					ans[b.terms[ib].col] += terms[it].value * b.terms[ib].value;
//			}
//			it++;
//		}
//		//������ans��¼�Ĵ𰸴浽c��
//		for (int k = 1; k <= b.cols; k++)
//		{
//			if (ans[k] != 0)
//			{
//				matrixTerm mTerm;
//				mTerm.row = i;
//				mTerm.col = k;
//				mTerm.value = ans[k];
//				c.terms[c.termSize++] = mTerm;
//			}
//		}
//	}
//	*this = c;
//	return 0;
//}
////3.�ӷ�
//int sparseMatrix::add(sparseMatrix& b)
//{
//	if (b.cols != cols || b.rows != rows) //�Ϸ��Լ���
//	{
//		*this = b;
//		return -1;
//	}
//	else
//	{
//		sparseMatrix C(rows, cols);//���ý����������� 
//		int it = 0, ib = 0;//�����α�
//		while (it < termSize && ib < b.termSize)//������� 
//		{   
//			//������������ÿһ�������,����ר������ֵ 
//			int tIndex = (terms[it]).row * cols + (terms[it]).col;
//			int bIndex = (b.terms[ib]).row * cols + (b.terms[ib]).col;
//			if (tIndex < bIndex)
//			{//*thisԪ����ǰ
//				C.terms[C.termSize++] = terms[it];
//				it++;
//			}
//			else if (tIndex == bIndex)
//			{//������ͬһ��λ�� 
//				if ((terms[it]).value + (b.terms[ib]).value != 0)//������Ӻ�Ϊ0ʱ����c 
//				{
//					matrixTerm mTerm;
//					mTerm.row = terms[it].row;
//					mTerm.col = terms[it].col;
//					mTerm.value = terms[it].value + b.terms[ib].value;
//					C.terms[C.termSize++] = mTerm;
//				}
//				it++; ib++;
//			}
//			else
//			{//bԪ����ǰ
//				C.terms[C.termSize++] = b.terms[ib];
//				ib++;
//			}
//		}
//		//����ʣ�����û���������Ԫ���ʣ��Ԫ�ؼӵ����������Ԫ�����
//		for (; it != termSize; it++)
//		{
//			C.terms[C.termSize++] = terms[it];
//		}
//		for (; ib != b.termSize; ib++)
//		{
//			C.terms[C.termSize++] = b.terms[ib];
//		}
//		*this = C;
//		return 0;
//	}
//}
//
//void sparseMatrix::output()
//{
//	int termNum = 0;//���Լ�¼�Ѿ�����ķ���Ԫ�ظ���
//	cout << rows << " " << cols << endl;//�������������
//	for (int i = 1; i <= rows; i++)//�������
//	{
//		for (int j = 1; j <= cols; j++)
//		{
//			if (termNum < termSize && terms[termNum].row == i && terms[termNum].col == j)
//			{
//				cout << terms[termNum++].value << " ";
//			}
//			else cout << 0 << " ";
//		}
//		cout << endl;
//	}
//}
//void sparseMatrix::transpose()
//{	
//	//ת�ú�ľ���
//	sparseMatrix b(cols,rows);
//	//����ת�þ�������
//	b.rows = cols;
//	b.cols = rows;
//	b.termSize = termSize;
//	//��ʼ����ʵ��ת��
//	int* colSize = new int[cols + 1];//�������*this��i�з���Ԫ�ظ���
//	int* colIndex = new int[cols + 1];//ת�þ����i���׸�����Ԫ����b�е�����
//	//���������ÿһ�еķ���Ԫ�ص���Ŀ
//	for (int i = 1; i <= cols; i++)//��ʼ��
//		colSize[i] = 0;
//	for (int i = 0; i < termSize; i++)
//		colSize[terms[i].col]++;
//	//Ѱ��b��ÿһ�е���ʼ�㣬��¼������ÿһ�еĵ�һ������Ԫ�ص�����
//	colIndex[1] = 0;
//	for (int i = 2; i <= cols; i++)
//		colIndex[i] = colIndex[i - 1] + colSize[i - 1];
//	//ʵʩ��*this��b��ת�ø���
//	for (int i = 0; i < termSize; i++)
//	{
//		int j = colIndex[terms[i].col]++;//b�е�λ�ã�ͬʱ������һ������ͬ���ж������Ԫ��ʱ���ƻ���
//		b.terms[j].row = terms[i].col;
//		b.terms[j].col = terms[i].row;
//		b.terms[j].value = terms[i].value;
//	}
//	*this = b;
//	delete[]colSize;
//	delete[]colIndex;
//}
////������Ԫ�����ݵĸ�ֵ
//void sparseMatrix::intputTerm(int x, int y, int v)
//{
//	terms[termSize].row = x;
//	terms[termSize].col = y;
//	terms[termSize].value = v;
//	termSize++;
//}
//
//int main()
//{
//	sparseMatrix P(0, 0);
//	int w, k, n, m, t;
//	cin >> w;
//	for (int i = 0; i < w; i++)
//	{
//		cin >> k;
//		if (k == 1)
//		{//����
//			cin >> n >> m;
//			P.initial(n, m);
//		}
//		if (k == 2)
//		{//�˷�
//			cin >> n >> m >> t;
//			sparseMatrix Q(n, m);
//			for (int i = 0; i < t; i++)
//			{
//				int x, y, v;
//				cin >> x >> y >> v;
//				Q.intputTerm(x, y, v);
//			}
//			int ans = P.multiply(Q);
//			if (ans == -1) cout << "-1" << endl;
//		}
//		if (k == 3)
//		{//�ӷ�
//			cin >> n >> m >> t;
//			sparseMatrix Q1(n, m);
//			for (int i = 0; i < t; i++)
//			{
//				int x, y, v;
//				cin >> x >> y >> v;
//				Q1.intputTerm(x, y, v);
//			}
//			int ans = P.add(Q1);
//			if (ans == -1) cout << "-1" << endl;
//		}
//		if (k == 4)
//		{//���
//			P.output();
//		}	
//		if (k == 5)
//		{//װ��
//			P.transpose();
//		}
//	}
//	return 0;
//}