#include "reg52.h"
#include <math.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar bitsel[]={0xfb,0xf7,0xef,0xdf};		 //�����λѡ  
uchar code table[10]=			   //����ܶ�ѡ
{0xc0,0xf9,0xa4,
0xb0,0x99,0x92,
0x82,0xF8,0x80,
0x90};
uint time=900,t,tt;				//time�ǳ�ʼʱ�䣬t��¼��ʱ��0�����������
uchar i=0;						// �ﵽ�涨ֵ���㣬ִ����Ӧ����
uint css=1,csss=0;				//css�����ѡѡ������ı���    csssΪ��ѡѡ��
sbit BUZ = P3^7;				//����BUZZER
uchar LEDsel =0xff;				//��LEDѡ�񸳳�ֵ		
void main()
{
	uint x;
	TMOD=0X11;					//ѡ��ʱ������ģʽ
	TH0=(65535-50000)/256;		//�ֱ��T0��T1װ���ֵ
	TL0=(65535-50000)%256;
	TH1=(65535-55000)/256;
	TL1=(65535-55000)%256;		
	EA=1;						//�����ж�
	ET0=1;					   //��T0�ж�����
	TR0=1;					   //����ʱ��T0
	TR1=1;
	ET1=1;
	while (1)
	{   
		while(LEDsel!=0x00)			//��LEDѡ��Ϊ0
		{
			LEDsel<<=1;				 //����һλ
			P1=LEDsel;				  //P1��ֵΪLEDѡ��
			while(i<4)				  //�������ʾ����
			{
				csss=time%(css*10)/css;		//��ȡʱ��ĸ�ʮ��ǧλ
				P3=0xff;					//����
				P3=bitsel[i];				//��ֵλѡ
				P2=table[csss];				//��ֵ��ѡ
				css*=10;					//����css�����Ա�����һλ
				i++;
				for(x=1000;x>0;x--)		   //��ʱ����12MHz������˵��ʱ1ms
					_nop_();
			}
			css=1;						  //��ʼ��������ֵ�ı���
			i=0; 			  			
		}
		LEDsel =0xff;			 		    		   
	}					 
}
void Timer0()  interrupt 1		 
{
	TR0=0;						 //�ض�ʱ���ж�
	TH0=(65535-50000)/256;		 //����װ���ֵ
	TL0=(65535-50000)%256;	
	t++;
	if(t==20)					 //Լ1s�����ʱ�䴦��Ϊ�˳�����õ�չʾ������ȥʵ��1sed = ����1min
	{
		t=0;					//������Ӧ��ֵ
		time++;
		if(time%100==60)
			time+=40;
		if(time==2400)
			time=0;
	}
	TR0=1;						//�ٴο��ж�
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
		BUZ=~BUZ;					//BUZλȡ���÷���������
	}
	TR1=1;
}	 	