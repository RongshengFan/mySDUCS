//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <fstream>
//using namespace std;
//const int x = 1, y = 1000;  //�����������[x,y]֮�����
//const int m = 100, n = 30;//mΪ��ʼ��������nΪ��������,��ʮ��������������������
//int op,temp;
//int main()
//{
//	srand((unsigned)time(NULL)*10);
//
//	ofstream fout1, fout2;
//	fout1.open("d:\\codefile\\vs\\ex3���ݽṹ�㷨���ʵ��\\input1.txt", ios::app | ios::out);
//	fout2.open("d:\\codefile\\vs\\ex3���ݽṹ�㷨���ʵ��\\input.txt", ios::app | ios::out);
//	if (!fout1.is_open() || !fout2.is_open()) { cout << "error" << endl; }
//
//	for (int i = 0; i < m; i++)//����m����������ڳ�ʼ������
//	{
//		fout1 << ((rand() % (y - x + 1)) + x) << '\n';//ȡ��[x,y]�����������
//	}
//	for (int i = 0; i < n; i++) 
//	{
//		if (i < (n / 3)) {//���ɲ������2
//			op = 2;
//			temp = (rand() % (y - x + 1)) + x;//���������
//			fout2 << op << " " << temp << '\n';
//		}
//		else if (i >= (n / 3) && i < (2 * n / 3)) {//����ɾ������3,4,5
//			op = (rand() % (5 - 3 + 1)) + 3;
//			if (op == 3) {//����ɾ������3
//				temp = (rand() % (y - x + 1)) + x;//���������
//				fout2 << op << " " << temp << '\n';
//			}
//			else if (op == 4 || op == 5) fout2 << op << '\n';//����ɾ�����ֵ����Сֵ����4,5
//		}
//		else {//���ɲ��Ҳ���1
//			op = 1;
//			temp = (rand() % (y - x + 1)) + x;//���������
//			fout2 << op << " " << temp << '\n';
//		}
//	}
//	cout << "�ɹ�������������������" << endl;
//	fout1.close();
//	fout2.close();
//	return 0;
//}