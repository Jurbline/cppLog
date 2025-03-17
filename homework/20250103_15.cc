#include <iostream>
using std::cout;
using std::endl;
class Stack
{
public:
     Stack()
     :_stackTop(-1)
     {
     }

     bool empty()//判栈空
     {
          return _stackTop == -1;
     }

     bool full()//判栈满
     {
          return _stackTop == MAXSIZE -1;
     }

     void push(int value)
     {
          if(full())
          {
               cout << "栈满，不能入栈" << endl;
          }
          else
          {
               _arr[++_stackTop] = value;
               cout << "元素 " << value << " 成功入栈" << endl;
          }
     }

     void pop()
     {
          if(empty())
          {
               cout << "出栈失败，栈空，没有元素" << endl;
          }
          else
          {
               cout << "栈顶元素 " << _arr[_stackTop] << "已经出栈" << endl;
               --_stackTop;
          }
     }

     int top()
     {
          if(empty())
          {
               cout << "获取栈顶失败，栈空，没有元素" << endl;
               return -1;
          }
               return _arr[_stackTop];//返回栈顶元素
     }
private:
     static const int MAXSIZE = 5;//最大容量
     int _stackTop;//栈顶指针
     int _arr[MAXSIZE];
};

int main()
{
     Stack s;
     s.push(1);//入栈
     s.push(2);
     s.push(3);
     s.push(4);
     s.push(5);
     s.push(6);//看看能不能过量入栈
     cout << "栈顶元素为：" << s.top() << endl;
     s.pop();
     cout << "栈顶元素为：" << s.top() << endl;
     s.pop();
     s.pop();
     s.pop();
     s.pop();
     s.pop();//尝试过量出栈
     s.top();//再次获取栈顶元素
     return 0;
} 
