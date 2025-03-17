#include <iostream>
using std::cout;
using std::endl;
class Queue
{
public:
     Queue()
     :_front(0)
     ,_rear(0)
     ,_size(0)
     {
          cout << "队列创建成功" << endl;
     }

     bool empty()
     {
          return _size == 0;//队列元素个数为0时队列为空
     }

     bool full()
     {
          return _size == MAXSIZE;//队列元素等于最大容量时，队列满
     }
     
     void push(int value)
     {
          if(full())
          {
               cout << "队列已满，无法入队" << endl;
          }
          else
          {
               _arr[_rear] = value;
               _rear = (_rear + 1) % MAXSIZE;//保证循环
               _size++;//队列元素+1
               cout << value << " 成功入队" << endl;
          }
     }

     void pop()
     {
          if(empty())
          {
               cout << "队列为空，无法出队" << endl;
          }
          else
          {
               cout << "元素：" << _arr[_front] << "成功出队" << endl;
               _size--;
               _front = (_front + 1) % MAXSIZE;//保证循环
          }
     }

     int front()
     {
          if(empty())
          {
               cout << "队列为空，没有队头元素" << endl;
               return -1;
          }
          else
          {
               return _arr[_front];
          }
     }
     
     int back()
     {
          if(empty())
          {
               cout << "队列为空，没有队尾元素" << endl;
               return -1;
          }
          else
          {
               //防止_rear - 1指向负值，且队尾元素是(_rear - 1) % MAXSIZE
               return _arr[(_rear - 1 + MAXSIZE) % MAXSIZE];
          }
     }

private:
     static const int MAXSIZE = 5;//队列最大容量
     int _arr[MAXSIZE];//存储队列元素的数组
     int _front;//队头指针
     int _rear;//队尾指针
     int _size;//队列元素个数
};

int main()
{
     Queue q;
     q.push(1);//尝试入队
     q.push(2);
     q.push(3);
     q.push(4);
     q.push(5);
     q.push(6);//尝试过量入队
     cout << "队头元素为：" << q.front() << endl;
     cout << "队尾元素为：" << q.back() << endl;
     q.pop();//尝试出队
     cout << "队头元素为：" << q.front() << endl;
     q.push(7);//看看能不能循环
     cout << "队头元素为：" << q.front() << endl;
     cout << "队尾元素为：" << q.back() << endl;
     q.pop();
     q.pop();
     q.pop();
     q.pop();
     q.pop();
     q.pop();//尝试过量出队

     return 0;
}
