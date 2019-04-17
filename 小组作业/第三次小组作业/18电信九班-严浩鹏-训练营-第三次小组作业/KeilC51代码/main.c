#include "reg52.h"
#include <math.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar bitsel[]={0xfb,0xf7,0xef,0xdf};		 //数码管位选  
uchar code table[10]=			   //数码管段选
{0xc0,0xf9,0xa4,
0xb0,0x99,0x92,
0x82,0xF8,0x80,
0x90};
uint time=900,t,tt;				//time是初始时间，t记录定时器0的溢出次数，
uchar i=0;						// 达到规定值清零，执行相应步骤
uint css=1,csss=0;				//css处理段选选择产生的变量    csss为段选选择
sbit BUZ = P3^7;				//定义BUZZER
uchar LEDsel =0xff;				//对LED选择赋初值		
void main()
{
	uint x;
	TMOD=0X11;					//选择定时器工作模式
	TH0=(65535-50000)/256;		//分别对T0、T1装入初值
	TL0=(65535-50000)%256;
	TH1=(65535-55000)/256;
	TL1=(65535-55000)%256;		
	EA=1;						//开总中断
	ET0=1;					   //开T0中断允许
	TR0=1;					   //开定时器T0
	TR1=1;
	ET1=1;
	while (1)
	{   
		while(LEDsel!=0x00)			//当LED选择不为0
		{
			LEDsel<<=1;				 //右移一位
			P1=LEDsel;				  //P1赋值为LED选择
			while(i<4)				  //数码管显示数字
			{
				csss=time%(css*10)/css;		//获取时间的个十百千位
				P3=0xff;					//消隐
				P3=bitsel[i];				//赋值位选
				P2=table[csss];				//赋值段选
				css*=10;					//处理css数据以便获得下一位
				i++;
				for(x=1000;x>0;x--)		   //延时，对12MHz晶振来说延时1ms
					_nop_();
			}
			css=1;						  //初始化处理数值的变量
			i=0; 			  			
		}
		LEDsel =0xff;			 		    		   
	}					 
}
void Timer0()  interrupt 1		 
{
	TR0=0;						 //关定时器中断
	TH0=(65535-50000)/256;		 //重新装入初值
	TL0=(65535-50000)%256;	
	t++;
	if(t==20)					 //约1s后进入时间处理，为了程序更好地展示，这里去实际1sed = 程序1min
	{
		t=0;					//处理相应数值
		time++;
		if(time%100==60)
			time+=40;
		if(time==2400)
			time=0;
	}
	TR0=1;						//再次开中断
}	 
void Timer1()  interrupt 3
{
	TR1=0;
	TH1=(65535-60000)/256;
	TL1=(65535-60000)%256;	
	tt++;
	if(tt==10)
	{
		tt=0;
		BUZ=~BUZ;					//BUZ位取反让蜂鸣器发声
	}
	TR1=1;
}	 	