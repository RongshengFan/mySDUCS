#include<bits/stdc++.h>
#include"Polinomial.h"
using namespace std;
void printMenu() {
    std::cout << "��ѡ�������\n";
    std::cout << "1. �ӷ�\n";
    std::cout << "2. ����\n";
    std::cout << "3. �˷�\n";
    std::cout << "4. ����\n";
    std::cout << "5. ��ֵ\n";
    std::cout << "6. ��\n";
    std::cout << "7. ȡģ\n";
    std::cout << "0. �˳�\n";
}
int main() {	
        int op;
        do {
            printMenu();
            Polynomial<int>a,b,c;
            std::cin >> op;
            switch (op) {
            case 1: { // �ӷ�  
                cout << "�����һ������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����ڶ�������ʽ������ ϵ�� ָ������\n";
                cin >> b;
                cout << b;
                c = a + b;
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 2: { // ����  
                cout << "�����һ������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����ڶ�������ʽ������ ϵ�� ָ������\n";
                cin >> b;
                cout << b;
                c = a - b;
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 3: { // �˷�  
                cout << "�����һ������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����ڶ�������ʽ������ ϵ�� ָ������\n";
                cin >> b;
                cout << b;
                c = a * b;
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 4: { // ����  
                cout << "�����һ������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����ڶ�������ʽ������ ϵ�� ָ������\n";
                cin >> b;
                cout << b;
                c = a / b;
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 5: { // ��ֵ  
                cout << "�������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����x��ֵ��\n";
                int x,y;
                cin >> x;
                y = a(x);
                cout << "�����";
                cout << y<< endl;
                break;
            }
            case 6: { // ��  
                cout << "�������ʽ������ ϵ�� ָ������\n";
                cin >> a;              
                cout << a;
                c = a.Derivative();
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 7: { // ȡģ  
                cout << "�������ʽ������ ϵ�� ָ������\n";
                cin >> a;
                cout << a;
                cout << "����ģ��x��ֵ��\n";
                int x = 0;
                cin >> x;
                c = a%x;
                cout << "�����";
                cout << c << endl;
                break;
            }
            case 0:
                std::cout << "�˳�����\n";
                break;
            default:
                std::cout << "��Ч��ѡ��������ѡ��\n";
            }
        } while (op != 0);
	return 0;
}