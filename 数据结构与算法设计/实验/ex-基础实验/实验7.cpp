//#include<iostream>
//#include<sstream>
//using namespace std;
////����һ�������������Ķ���
//template<class T>
//class arrayQueue
//{
//public:
//    arrayQueue(int initialCapacity = 10);
//    ~arrayQueue() { delete[] queue; }
//    //���ض����Ƿ�Ϊ��
//    bool empty() const { return theFront == theBack; }
//    //���ض��г���
//    int size() const
//    {
//        return (theBack - theFront + arrayLength) % arrayLength;
//    }
//    //���ض���Ԫ��
//    T& front()
//    {
//        if (theFront == theBack)
//            exit(1);
//        return queue[(theFront + 1) % arrayLength];
//    }
//    //���ض�βԪ��
//    T& back()
//    {
//        if (theFront == theBack)
//            exit(1);
//        return queue[theBack];
//    }
//    //����
//    void pop()
//    {
//        if (theFront == theBack)
//            return;
//        theFront = (theFront + 1) % arrayLength;
// 
//        queue[theFront].~T();  // destructor for T
//    }
//    //���
//    void push(const T& theElement);
//private:
//    int theFront;       
//    int theBack;        
//    int arrayLength;    
//    T* queue;           
//};
////���캯��
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
////ʵ��push����
//template<class T>
//void arrayQueue<T>::push(const T& theElement)
//{
//    //���ж��Ƿ���Ҫ����
//    if ((theBack + 1) % arrayLength == theFront)
//    {
//        T* newQueue = new T[2 * arrayLength];
//
//        int start = (theFront + 1) % arrayLength;
//        if (start < 2)//û���γɻ�
//            copy(queue + start, queue + start + arrayLength - 1, newQueue);
//        else //�����γɻ�
//        {  
//            copy(queue + start, queue + arrayLength, newQueue);
//            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
//        }
//        //�����¶��е���βԪ��λ��
//        theFront = 2 * arrayLength - 1;
//        theBack = arrayLength - 2;   
//        arrayLength *= 2;
//        delete queue;
//        queue = newQueue;
//    }
//    //������Ԫ��
//    theBack = (theBack + 1) % arrayLength;
//    queue[theBack] = theElement;
//}
//int main()
//{
//    int n;
//    cin >> n;
//    arrayQueue<int> list(n);//����һ������
//    for (int i = 1; i <= n; i++)
//    {//�����ݴ������
//        list.push(i);
//    }
//    while (n >= 2)
//    {//��ʼ��������
//        list.pop();//��һ����ͷԪ�س���
//        list.push(list.front());//���¶�ͷԪ�طŵ���β
//        list.pop();//�ڶ�����ͷԪ�س���
//        n--;
//    }
//    cout << list.front();//���
//    return 0;
//}