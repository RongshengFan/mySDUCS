//#include<iostream>
//#include<sstream>
//#include<string>
//#include<stdio.h>
//using namespace std;
////�ı�һά���鳤��
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
//        {//����������������� 
//            changeLength1D(stack, arrayLength, arrayLength * 2);
//            arrayLength *= 2;//��ջ������������� 
//        }
//        stack[++stacktop] = theElement;
//    }
//private:
//    int stacktop;         // current top of stack
//    int arrayLength;      // stack capacity
//    T* stack;             // element array
//};
////����һ�������������е��μӼ��˳�����
//void calculator(arraystack<double>& num, arraystack<char>& str)
//{
//    double a, b;//ȡ������ջ��ǰ��������
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
//    str.pop();//������Ҫ���ַ������ַ�ջ
//}
////����һ�����ܺ����������ֺ��ַ����ֳ��������ҵ������������и�������
//void func(string s, int len)
//{
//    arraystack<double>num;//����ջ
//    arraystack<char>str;//�ַ�ջ
//    bool flag = false;//�����жϱ�ʶ
//    for (int i = 0; i < len; i++)
//    {
//        if (s[i] >= '0' && s[i] <= '9')
//        {
//            int x = s[i] - '0';
//            if (flag)//�����ж�
//            {
//                x = -x;
//                flag = false;
//            }
//            num.push(x);//������ѹ��ջ��
//        }
//        else
//        {
//            //�����ж�
//            if ((i == 0 || s[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '(') && s[i] == '-')
//            {
//                flag = true;
//                continue;
//            }
//            switch (s[i])
//            {
//                //���мӼ�����
//            case '+':
//            case '-':
//                if (str.empty() || str.top() == '(')
//                {
//                    str.push(s[i]);//���ַ�ѹ��ջ��
//                }
//                else
//                {
//                    //������һ�飬��ǰһ�������ַ�����
//                    calculator(num, str);
//
//                    //�粻��ջ��ջ����Ϊ�����ž�������һ��
//                    if(!str.empty()&&str.top()!='(')calculator(num, str);
//
//                    str.push(s[i]);//���ַ�ѹ��ջ�У������´�����
//                }
//                break;
//                //���г˳�����
//            case'*':
//            case'/':
//                if (str.empty() || str.top() == '(')
//                {
//                    str.push(s[i]);//���ַ�ѹ��ջ�У������´�����
//                }
//                else if (str.top() == '+' || str.top() == '-')
//                {
//                    str.push(s[i]);//���ַ�ѹ��ջ�У������´�����
//                }
//                else if (str.top() == '*' || str.top() == '/')
//                {
//                    calculator(num, str);//ջ��Ϊ��*������/������������
//                    str.push(s[i]);//���ַ�ѹ��ջ�У������´�����
//                }
//                break;
//            case'('://����������ѹ��ջ�м���
//                str.push(s[i]);
//                break;
//            case')'://���������ţ����ϸ������ŵ�������֮���ʽ�ӽ�������
//                while (str.top() != '(')
//                {
//                    calculator(num, str);
//                }
//                str.pop();//�������ŵ���ջ
//                break;
//            default:
//                break;
//            }
//        }
//    }
//    //�������㣬ֱ����ʣ���ַ�ȫ������
//    while (!str.empty())
//    {
//        calculator(num, str);
//    }
//    //������
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