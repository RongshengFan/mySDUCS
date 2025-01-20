//#include<iostream>
//#include <sstream>
//using namespace std;
////三元组定义
//struct matrixTerm
//{
//	int row;	//行位置
//	int col;	//列位置
//	int value;	//元素值
//
////	int getValue() const { return value; }
//	matrixTerm& operator=(matrixTerm& x)//重载"="，方便后续使用，代替课本中的insert函数
//	{
//		row = x.row;
//		col = x.col;
//		value = x.value;
//		return *this;
//	}
//};
////稀疏矩阵
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
//	int rows;//行数
//	int cols;//列数
//	int termSize;//三元组存放的非零元素个数
//	int maxSize;//三元组可容纳的最大元素个数
//	matrixTerm* terms;//存放非零元素的三元组表
//};
////构造函数
//sparseMatrix::sparseMatrix(int n, int m)
//{
//	rows = n;
//	cols = m;
//	termSize = 0;
//	maxSize = 250000;
//	terms = new matrixTerm [maxSize];
//}
////重载稀疏矩阵的“=”
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
////1.重置
//void sparseMatrix::initial(int n, int m)
//{
//	rows = n;//记录行数
//	cols = m;//记录列数
//	termSize = 0;//非零项表要先清空
//	int v = 0;     //记录输入元素值
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
////2.乘法
//int sparseMatrix::multiply(sparseMatrix& b)
//{
//	//合法性判定
//	if (cols != b.rows)
//	{
//		*this = b;
//		return -1;
//	}
//	//设置结果矩阵c
//	sparseMatrix c(rows, b.cols);
//	int rowSize[500] = { 0 };		//每行非零元素个数
//	int rowIndex[500] = { 0 };		//每行首个非零元素索引
//	int ans[10000] = { 0 };			//累加器，记录乘积值
//	for (int i = 1; i <= b.rows; i++)//初始化
//	{
//		rowSize[i] = 0;
//	}
//	for (int i = 0; i < b.termSize; i++)//记录b中每行元素个数
//	{
//		if (b.terms[i].value != 0)
//			rowSize[b.terms[i].row]++;
//	}
//	rowIndex[1] = 0;
//	for (int i = 2; i <= b.termSize; i++)//记录每行首个非零元素索引值
//		rowIndex[i] = rowIndex[i - 1] + rowSize[i - 1];
//
//	for (int i = 1, it = 0; i <= rows && it < termSize; i++)//遍历*this矩阵的每一行直到遍历完所有非零元素
//	{
//		for (int j = 1; j <= b.cols; j++)
//		{
//			ans[j] = 0;//累加器初始化
//		}
//		//开始计算乘积,遍历三元组表
//		while (it < termSize && terms[it].row == i)//遍历*this的第i行
//		{
//			int y = terms[it].col;//记录it的列位置，对应ib的行位置
//			for (int ib = rowIndex[y]; ib < rowIndex[y] + rowSize[y]; ib++)
//			{
//				//计算第i行每列的乘积
//				if (y == b.terms[ib].row)
//					ans[b.terms[ib].col] += terms[it].value * b.terms[ib].value;
//			}
//			it++;
//		}
//		//将数组ans记录的答案存到c中
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
////3.加法
//int sparseMatrix::add(sparseMatrix& b)
//{
//	if (b.cols != cols || b.rows != rows) //合法性检验
//	{
//		*this = b;
//		return -1;
//	}
//	else
//	{
//		sparseMatrix C(rows, cols);//设置结果矩阵的特征 
//		int it = 0, ib = 0;//设置游标
//		while (it < termSize && ib < b.termSize)//遍历相加 
//		{   
//			//行主索引加上每一项的列数,设置专属索引值 
//			int tIndex = (terms[it]).row * cols + (terms[it]).col;
//			int bIndex = (b.terms[ib]).row * cols + (b.terms[ib]).col;
//			if (tIndex < bIndex)
//			{//*this元素在前
//				C.terms[C.termSize++] = terms[it];
//				it++;
//			}
//			else if (tIndex == bIndex)
//			{//两项在同一个位置 
//				if ((terms[it]).value + (b.terms[ib]).value != 0)//仅当相加后不为0时加入c 
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
//			{//b元素在前
//				C.terms[C.termSize++] = b.terms[ib];
//				ib++;
//			}
//		}
//		//复制剩余项，把没遍历完的三元组表剩余元素加到结果矩阵三元组表中
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
//	int termNum = 0;//用以记录已经输出的非零元素个数
//	cout << rows << " " << cols << endl;//输出行数、列数
//	for (int i = 1; i <= rows; i++)//遍历输出
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
//	//转置后的矩阵
//	sparseMatrix b(cols,rows);
//	//设置转置矩阵特征
//	b.rows = cols;
//	b.cols = rows;
//	b.termSize = termSize;
//	//初始化以实现转置
//	int* colSize = new int[cols + 1];//输入矩阵*this第i列非零元素个数
//	int* colIndex = new int[cols + 1];//转置矩阵第i列首个非零元素在b中的索引
//	//计算矩阵中每一列的非零元素的数目
//	for (int i = 1; i <= cols; i++)//初始化
//		colSize[i] = 0;
//	for (int i = 0; i < termSize; i++)
//		colSize[terms[i].col]++;
//	//寻找b中每一行的起始点，记录矩阵中每一列的第一个非零元素的索引
//	colIndex[1] = 0;
//	for (int i = 2; i <= cols; i++)
//		colIndex[i] = colIndex[i - 1] + colSize[i - 1];
//	//实施从*this到b的转置复制
//	for (int i = 0; i < termSize; i++)
//	{
//		int j = colIndex[terms[i].col]++;//b中的位置，同时索引加一，避免同列有多个非零元素时复制混乱
//		b.terms[j].row = terms[i].col;
//		b.terms[j].col = terms[i].row;
//		b.terms[j].value = terms[i].value;
//	}
//	*this = b;
//	delete[]colSize;
//	delete[]colIndex;
//}
////单个三元组数据的赋值
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
//		{//重置
//			cin >> n >> m;
//			P.initial(n, m);
//		}
//		if (k == 2)
//		{//乘法
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
//		{//加法
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
//		{//输出
//			P.output();
//		}	
//		if (k == 5)
//		{//装置
//			P.transpose();
//		}
//	}
//	return 0;
//}