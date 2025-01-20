//#include<iostream>
//#include<sstream>
//using namespace std;
////定义一个用数组描述的队列
//template<class T>
//class arrayQueue
//{
//public:
//    arrayQueue(int initialCapacity = 10);
//    ~arrayQueue() { delete[] queue; }
//    //返回队列是否为空
//    bool empty() const { return theFront == theBack; }
//    //返回队列长度
//    int size() const
//    {
//        return (theBack - theFront + arrayLength) % arrayLength;
//    }
//    //返回队首元素
//    T& front()
//    {
//        if (theFront == theBack)
//            exit(1);
//        return queue[(theFront + 1) % arrayLength];
//    }
//    //返回队尾元素
//    T& back()
//    {
//        if (theFront == theBack)
//            exit(1);
//        return queue[theBack];
//    }
//    //出队
//    void pop()
//    {
//        if (theFront == theBack)
//            return;
//        theFront = (theFront + 1) % arrayLength;
// 
//        queue[theFront].~T();  // destructor for T
//    }
//    //入队
//    void push(const T& theElement);
//private:
//    int theFront;       
//    int theBack;        
//    int arrayLength;    
//    T* queue;           
//};
////构造函数
//template<class T>
//arrayQueue<T>::arrayQueue(int initialCapacity)
//{
//    if (initialCapacity < 1)
//    {
//        ostringstream s;
//        s << "Initial capacity = " << initialCapacity << " Must be > 0";
//        throw logic_error(s.str());
//    }
//    arrayLength = initialCapacity;
//    queue = new T[arrayLength];
//    theFront = 0;
//    theBack = 0;
//}
////实现push函数
//template<class T>
//void arrayQueue<T>::push(const T& theElement)
//{
//    //先判断是否需要扩容
//    if ((theBack + 1) % arrayLength == theFront)
//    {
//        T* newQueue = new T[2 * arrayLength];
//
//        int start = (theFront + 1) % arrayLength;
//        if (start < 2)//没有形成环
//            copy(queue + start, queue + start + arrayLength - 1, newQueue);
//        else //队列形成环
//        {  
//            copy(queue + start, queue + arrayLength, newQueue);
//            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
//        }
//        //设置新队列的首尾元素位置
//        theFront = 2 * arrayLength - 1;
//        theBack = arrayLength - 2;   
//        arrayLength *= 2;
//        delete queue;
//        queue = newQueue;
//    }
//    //插入新元素
//    theBack = (theBack + 1) % arrayLength;
//    queue[theBack] = theElement;
//}
//int main()
//{
//    int n;
//    cin >> n;
//    arrayQueue<int> list(n);//声明一个队列
//    for (int i = 1; i <= n; i++)
//    {//将数据传入队列
//        list.push(i);
//    }
//    while (n >= 2)
//    {//开始进行运算
//        list.pop();//第一个队头元素出队
//        list.push(list.front());//将新队头元素放到队尾
//        list.pop();//第二个队头元素出队
//        n--;
//    }
//    cout << list.front();//输出
//    return 0;
//}