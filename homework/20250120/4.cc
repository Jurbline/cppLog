#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename T = int,size_t kSize = 10>
class Queue
{
public:
    Queue();
    ~Queue();

    bool empty() const;
    bool full() const;
    void push(const T &value);
    void pop();
    T top() const;
    void printQueue() const;

private:
    int _front;
    int _rear;
    int _size;
    T *_pdata;

};
template <typename T,size_t kSize>
Queue<T,kSize>::Queue()
:_front(0)
,_rear(0)
,_size(0)
,_pdata(new T[kSize]())
{
    cout << "Queue()" << endl;
}
template <typename T,size_t kSize>
Queue<T,kSize>::~Queue()
{
    cout << "~Queue()" << endl;
    if(_pdata)
    {
        delete [] _pdata;
        _pdata = nullptr;
    }
}
template <typename T,size_t kSize>
bool Queue<T,kSize>::empty() const
{
    return _size == 0;
}

template <typename T,size_t kSize>
bool Queue<T,kSize>::full() const
{
    return _size == kSize;
}

template <typename T,size_t kSize>
void Queue<T,kSize>::push(const T &value)
{
    if(!full())
    {
        _pdata[_rear] = value;
        _rear = (_rear + 1) % kSize;
        ++_size;
    }
    else
    {
        cout << "The Queue is full" << endl;
    }
}

template <typename T,size_t kSize>
void Queue<T,kSize>::pop()
{
    if(!empty())
    {
        _front = (_front + 1) %kSize;
        --_size;
    }
    else
    {
        cout << "The Queue is empty" << endl;
    }
}

template <typename T,size_t kSize>
T Queue<T,kSize>::top() const
{
    if(!empty())
    {
        return _pdata[_front];
    }
    else
    {
        cout << "The Queue is empty" << endl;
    }
}

template <typename T,size_t kSize>
void Queue<T,kSize>::printQueue() const
{
    if(empty())
    {
        cout << "The Queue is empty" << endl;
    }
    else
    {
        int idx = _front;
        int count = 0;
        while(count < _size)
        {
            cout << _pdata[idx] << " ";
            idx = (idx + 1) % kSize;
            ++count;
        }
        cout << endl;
    }
}

void test()
{
    Queue q;
    cout << "Queue empty? " << q.empty() << endl;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout << "Queue elements: ";
    q.printQueue();
    cout << "Front element: " << q.top() << endl;
    cout << "Queue empty? " << q.empty() << endl;
}
void test2()
{
    Queue<string,20> q;
    cout << "Queue empty? " << q.empty() << endl;
    q.push("hkc");
    q.push("hello");
    q.push("world");
    q.push("Fujian Xiamen");
    cout << "Queue elements: ";
    q.printQueue();
    cout << "Front element: " << q.top() << endl;
    q.pop();
    cout << endl;
    cout << "Pop a element" << endl;
    cout << "Queue elements: ";
    q.printQueue();
    cout << "Front element: " << q.top() << endl;
}
int main()
{
    test();
    test2();
    return 0;
}

