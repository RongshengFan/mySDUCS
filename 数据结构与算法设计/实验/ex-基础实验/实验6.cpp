//#include<iostream>
//#include<sstream>
//#include<string>
//#include<stdio.h>
//using namespace std;
////改变一维数组长度
//template<class T>
//void changeLength1D(T*& a, int oldLength, int newLength)
//{
//    if (newLength < 0)
//    {
//        throw logic_error("new length must be >= 0");
//    }
//    T* temp = new T[newLength];
//    int n = min(oldLength, newLength);
//    copy(a, a + n, temp);
//    delete[]a;
//    a = temp;
//}
//template<class T>
//class arraystack 
//{
//public:
//    arraystack(int initialcapacity = 10)
//    {
//        if (initialcapacity < 1)
//            exit(1);
//        arrayLength = initialcapacity;
//        stack = new T[arrayLength];
//        stacktop = -1;
//    }
//    ~arraystack() { delete[] stack; }
//    bool empty() const { return stacktop == -1; }
//    int size() const { return stacktop + 1; }
//    T& top()
//    {
//        if (stacktop == -1)
//            exit(1);
//        return stack[stacktop];
//    }
//    void pop()
//    {
//        if (stacktop == -1)
//            exit(1);
//        stack[stacktop--].~T();  // destructor for t
//    }
//    void push(const T& theElement)
//    {// add theelement to stack.
//        if (stacktop == arrayLength - 1)
//        {//容量满后的容量扩充 
//            changeLength1D(stack, arrayLength, arrayLength * 2);
//            arrayLength *= 2;//将栈的容量扩充二倍 
//        }
//        stack[++stacktop] = theElement;
//    }
//private:
//    int stacktop;         // current top of stack
//    int arrayLength;      // stack capacity
//    T* stack;             // element array
//};
////定义一个运算器，进行单次加减乘除运算
//void calculator(arraystack<double>& num, arraystack<char>& str)
//{
//    double a, b;//取出数字栈的前两个数字
//    a = num.top();
//    num.pop();
//    b = num.top();
//    num.pop();
//    if (str.top() == '+')
//    {
//        num.push(a + b);
//    }
//    if (str.top() == '-')
//    {
//        num.push(b - a);
//    }
//    if (str.top() == '*')
//    {
//        num.push(a * b);
//    }
//    if (str.top() == '/')
//    {
//        num.push(b / a);
//    }
//    str.pop();//运算完要把字符弹出字符栈
//}
////定义一个功能函数，将数字和字符区分出来，并且调用运算器进行各种运算
//void func(string s, int len)
//{
//    arraystack<double>num;//数字栈
//    arraystack<char>str;//字符栈
//    bool flag = false;//负数判断标识
//    for (int i = 0; i < len; i++)
//    {
//        if (s[i] >= '0' && s[i] <= '9')
//        {
//            int x = s[i] - '0';
//            if (flag)//负数判断
//            {
//                x = -x;
//                flag = false;
//            }
//            num.push(x);//将数字压入栈中
//        }
//        else
//        {
//            //负数判断
//            if ((i == 0 || s[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '(') && s[i] == '-')
//            {
//                flag = true;
//                continue;
//            }
//            switch (s[i])
//            {
//                //进行加减运算
//            case '+':
//            case '-':
//                if (str.empty() || str.top() == '(')
//                {
//                    str.push(s[i]);//将字符压入栈中
//                }
//                else
//                {
//                    //先运算一遍，把前一个运算字符弹出
//                    calculator(num, str);
//
//                    //如不空栈且栈顶不为左括号就再运算一遍
//                    if(!str.empty()&&str.top()!='(')calculator(num, str);
//
//                    str.push(s[i]);//将字符压入栈中，留到下次运算
//                }
//                break;
//                //进行乘除运算
//            case'*':
//            case'/':
//                if (str.empty() || str.top() == '(')
//                {
//                    str.push(s[i]);//将字符压入栈中，留到下次运算
//                }
//                else if (str.top() == '+' || str.top() == '-')
//                {
//                    str.push(s[i]);//将字符压入栈中，留到下次运算
//                }
//                else if (str.top() == '*' || str.top() == '/')
//                {
//                    calculator(num, str);//栈顶为‘*’、‘/’，进行运算
//                    str.push(s[i]);//将字符压入栈中，留到下次运算
//                }
//                break;
//            case'('://遇到左括号压入栈中即可
//                str.push(s[i]);
//                break;
//            case')'://遇到右括号，将上个左括号到右括号之间的式子进行运算
//                while (str.top() != '(')
//                {
//                    calculator(num, str);
//                }
//                str.pop();//将左括号弹出栈
//                break;
//            default:
//                break;
//            }
//        }
//    }
//    //继续运算，直至把剩余字符全部弹出
//    while (!str.empty())
//    {
//        calculator(num, str);
//    }
//    //输出结果
//    printf("%.2f\n", num.top());
//}
//
//int main()
//{
//    int n;
//    cin >> n;
//    for (int i = 0; i < n; i++)
//    {
//        string s;
//        cin >> s;
//        func(s, s.length());
//    }
//	return 0;
//}