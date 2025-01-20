#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include"skiplist.h"
using namespace std;

const int X = 1, Y = 100000;  //�����������[x,y]֮�����
int M = 1000, N = 100;        //MΪ��ʼ��������NΪ��������
int op,temp,testNum;          //opΪ����ѡ������tempΪ��Ӧ������,testNumΪ����������
int a[1000000];
bool flag = false;
pair<int, int>thePair;

bool Search(int a[], int length, int key) {//��ͨһά�������Բ���                        
    for(int i=0;i<length;i++) {
        if (a[i] == key)return true;
    }
    return false;
}
bool BinSearch(int a[], int length, int key) {//��ͨһά�����۰����                        
    int left = 0, right = length - 1;
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (a[mid] == key) {
            return true;
        }
        else if (a[mid] < key) {
            left = mid + 1;
        }
        else if (a[mid] > key) {
            right = mid - 1;
        }
    }
    return false;
}
void func1() {//ʹ���������������
        
        cout << "�������ʼ��������M: ";
        cin >> M;
        cout << "�����������������N: ";
        cin >> N;
        skipList<int, int>list;
        for (int i = 0; i < M; i++) {//��ʼ������
            temp = (rand() % (Y - X + 1)) + X;//���������
            list.initialize(temp);
        }
        for (int i = 0; i < N; i++) {//N�β���
            op = (rand() % (5 - 1 + 1)) + 1;//�����������
            cout << op << " ";
            switch (op) {
            case 1://����1������
                temp = (rand() % (Y - X + 1)) + X;
                thePair = (make_pair(temp, temp));
                list.insert(thePair);
                cout << temp << endl;
                break;
            case 2://����2������
                temp = (rand() % (Y - X + 1)) + X;
                cout << temp << " ";
                flag = list.find(temp);
                if (flag) {
                    cout << "Is found" << endl;
                }
                else {
                    cout << "Not found" << endl;
                }
                break;
            case 3://����3��ɾ��
                temp = (rand() % (Y - X + 1)) + X;
                list.erase(temp);
                cout << temp << endl;
                break;
            case 4:
                thePair = list.eraseMin();             
                cout << "(" << thePair.first << "," << thePair.second << ")" << endl;
                break;
            case 5:
                thePair = list.eraseMax();                  
                cout << "(" << thePair.first << "," << thePair.second << ")" << endl;

                break;           
            }
        }
        //list.output();//����������нڵ�
}
void func2() {//������������ܵ�ʱ����Ч��

    cout << "������Ҫ���Ե���������";
    cin >> testNum;

    skipList<int, int>list;
    clock_t start1 = clock();//�����������̬
    for (int i = 0; i < testNum; i++) {//�������2��ͬʱҲ�ǳ�ʼ������
        temp = (rand() % (Y - X + 1)) + X;//���������
        list.initialize(temp);
    }
    clock_t end1 = clock();//���������ĩ̬
    double time1 = (double)(1000 * (end1 - start1)) / CLOCKS_PER_SEC;//��¼�������ʱ��

   //Ϊ�����������
   list.inputArry(a);//�������е�Ԫ�ط���һά������,��֤����һ����
   //for (int i = 0; i < list.size(); i++)cout << a[i] << " ";
   clock_t start6 = clock();//����˳����Ҳ�������̬
   for (int i = 0; i < testNum; i++) {
       temp = (rand() % (Y - X + 1)) + X;//���������;
       Search(a, testNum, temp);
   }
   clock_t end6 = clock();//����˳����Ҳ�����ĩ̬
   double time6 = (double)(1000 * (end6 - start6)) / CLOCKS_PER_SEC;//��¼����˳����Ҳ���ʱ��

   clock_t start7 = clock();//�����۰���Ҳ�������̬
   for (int i = 0; i < testNum; i++) {
       temp = (rand() % (Y - X + 1)) + X;//���������;
       BinSearch(a, testNum, temp);
   }
   clock_t end7 = clock();//�����۰���Ҳ�����ĩ̬
   double time7 = (double)(1000 * (end7 - start7))/ CLOCKS_PER_SEC;//��¼�����۰���Ҳ���ʱ��


    clock_t start2 = clock();//���Ҳ�������̬
    for (int i = 0; i < testNum; i++) {//���Ҳ���1
        temp = (rand() % (Y - X + 1)) + X;//���������
        list.find(temp);
    }
    clock_t end2 = clock();//���Ҳ�����ĩ̬
    double time2 = (double)(1000 * (end2 - start2)) / CLOCKS_PER_SEC;//��¼���Ҳ���ʱ��

    clock_t start3 = clock();//ɾ����������̬
    for (int i = 0; i < testNum; i++) {//ɾ������3
        temp = (rand() % (Y - X + 1)) + X;//���������
        list.erase(temp);
    }
    clock_t end3 = clock();//ɾ��������ĩ̬
    double time3 = (double)(1000 * (end3 - start3)) / CLOCKS_PER_SEC;//��¼ɾ������ʱ��

    for (int i = 0; i < testNum; i++) {//��������
        temp = (rand() % (Y - X + 1)) + X;//���������;
        list.initialize(temp);
    }
    clock_t start4 = clock();//ɾ����Сֵ��������̬
    for (int i = 0; i < testNum; i++) {//ɾ������4
        list.eraseMin();
    }
    clock_t end4 = clock();//ɾ����Сֵ������ĩ̬
    double time4 = (double)(1000 * (end4 - start4)) / CLOCKS_PER_SEC;//��¼ɾ����Сֵ����ʱ��

    for (int i = 0; i < testNum; i++) {//��������
        temp = (rand() % (Y - X + 1)) + X;//���������;
        list.initialize(temp);
    }
    clock_t start5 = clock();//ɾ�����ֵ��������̬
    for (int i = 0; i < testNum; i++) {//ɾ������5
        list.eraseMax();
    }
    clock_t end5 = clock();//ɾ�����ֵ������ĩ̬
    double time5 = (double)(1000 * (end5 - start5)) / CLOCKS_PER_SEC;//��¼ɾ�����ֵ����ʱ��

    cout << testNum << "�β��������ƽ��ʱ��Ϊ��" << time1 << "ms" << endl;
    cout << testNum << "�β��Ҳ�����ƽ��ʱ��Ϊ��" << time2 << "ms" << endl;
    cout << testNum << "��ɾ��ĳ�ڵ������ƽ��ʱ��Ϊ��" << time3 << "ms" << endl;
    cout << testNum << "��ɾ����Сֵ������ƽ��ʱ��Ϊ��" << time4 << "ms" << endl;
    cout << testNum << "��ɾ�����ֵ������ƽ��ʱ��Ϊ��" << time5 << "ms" << endl;
    cout << testNum << "��һά����˳����ҵ�ƽ��ʱ��Ϊ��" << time6 << "ms" << endl;
    cout << testNum << "��һά�����۰���ҵ�ƽ��ʱ��Ϊ��" << time7 << "ms" << endl << endl;

}
int main() { 
  
    srand((unsigned)time(NULL)*10);
    cout << "���Բ����밴1��" << endl;
    cout << "������ʱ�밴2��" << endl;
    int n;
    cin >> n;
    if(n==1)func1();
    if(n==2)func2();
    return 0;
}
