#include<bits/stdc++.h>
#include"Polinomial.h"
using namespace std;
void printMenu() {
    std::cout << "请选择操作：\n";
    std::cout << "1. 加法\n";
    std::cout << "2. 减法\n";
    std::cout << "3. 乘法\n";
    std::cout << "4. 除法\n";
    std::cout << "5. 求值\n";
    std::cout << "6. 求导\n";
    std::cout << "7. 取模\n";
    std::cout << "0. 退出\n";
}
int main() {	
        int op;
        do {
            printMenu();
            Polynomial<int>a,b,c;
            std::cin >> op;
            switch (op) {
            case 1: { // 加法  
                cout << "输入第一个多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入第二个多项式（长度 系数 指数）：\n";
                cin >> b;
                cout << b;
                c = a + b;
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 2: { // 减法  
                cout << "输入第一个多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入第二个多项式（长度 系数 指数）：\n";
                cin >> b;
                cout << b;
                c = a - b;
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 3: { // 乘法  
                cout << "输入第一个多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入第二个多项式（长度 系数 指数）：\n";
                cin >> b;
                cout << b;
                c = a * b;
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 4: { // 除法  
                cout << "输入第一个多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入第二个多项式（长度 系数 指数）：\n";
                cin >> b;
                cout << b;
                c = a / b;
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 5: { // 求值  
                cout << "输入多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入x的值：\n";
                int x,y;
                cin >> x;
                y = a(x);
                cout << "结果：";
                cout << y<< endl;
                break;
            }
            case 6: { // 求导  
                cout << "输入多项式（长度 系数 指数）：\n";
                cin >> a;              
                cout << a;
                c = a.Derivative();
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 7: { // 取模  
                cout << "输入多项式（长度 系数 指数）：\n";
                cin >> a;
                cout << a;
                cout << "输入模数x的值：\n";
                int x = 0;
                cin >> x;
                c = a%x;
                cout << "结果：";
                cout << c << endl;
                break;
            }
            case 0:
                std::cout << "退出程序。\n";
                break;
            default:
                std::cout << "无效的选择，请重新选择。\n";
            }
        } while (op != 0);
	return 0;
}