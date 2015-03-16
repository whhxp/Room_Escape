#ifndef LED_H  //根据条件进行编译
#define LED_H

//我们在这中间添加程序主体的代码部分，首先来添加程序的头文件，需要引用什么都可以加进来

//之后我们可以预定义一些需要的常量，这样维护起来比较方便，如果常量值改变只要统一修改这里就好

//接下来我们来定义变量和声明程序的方法，需要外部调用和访问的就声明成public,不需要外部访问的就声明为private

class led_wall
{
public: 
  void DataSend(int LedData); 
  void DataLock(void) ;
  void send2wall(short* l, short* m,short* r,int d_time);
  void Init(int clk, int le, int oe,int sdi);
private:
  int _lePin; 

  int _clkPin; 

  int _oePin; 

  int _sdiPin;

};
#endif



