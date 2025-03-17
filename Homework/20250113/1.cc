  #include <iostream>
  #include <string.h>
  #include <stdlib.h>
  using namespace std;
  class Computer
  {
  public:
      Computer(int price,const char *brand)
      :_price(price)
      ,_brand(new char[strlen(brand) + 1]())
      {
          strcpy(_brand,brand);
      }
      ~Computer()
      {
          cout << "~Computer()" << endl;
          if(_brand)
          {
              delete [] _brand;
              _brand = nullptr;
          }
      }
  
      void print() const
      {
          cout << "_price = " << _price << ","
          << "_brand = " << _brand << endl;
      }
  private:
      int _price;
      char *_brand;
      static void *operator new(size_t sz)//私有化
      {
          cout << "void *operator new(size_t sz)" << endl;       
          void *pret = malloc(sz);
          return pret;
      }
      static void operator delete(void *pst)//私有化
      {
          cout << "void *operator delete(void *pst)" << endl;
          free(pst);
      }
  };
  
  void test()
  {
      /* Computer *pstu = new Computer(88888888,"wangdao");//error */
      /* pstu->print(); */
      /* delete pstu; */
      /* pstu = nullptr; */
  }
  int main()
  {
      test();
      Computer test1(88888888,"wangdao");
      test1.print();
     return 0;
  }
