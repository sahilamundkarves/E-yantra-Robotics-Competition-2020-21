#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "lcd.c"
//#include "CFile2.c"
#include "functions.c"
int x=20,y= 20,a=110,b=250;
int n=1;

int main(void)

{
	_delay_ms(5000);
	init_devices();
	lcd_set_4bit();
	sinit_devices();
	
	/***************H4****************/
		while(n==1)
		{
		
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			
			natural_behav();
			
			if(left_sensor> x && centre_sensor> y && right_sensor> x)
			{	
				velocity(150,150);
				forward();
				_delay_ms(350);
			
				velocity(150,150);
				left();
				_delay_ms(850);
				
				n++;
			}
	
		
		}
			

		/***********************************/
		while(n==2)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			
			natural_behav();

			if(left_sensor> x && centre_sensor> y && right_sensor> x)
			{	
				velocity(150,150);
				forward();
				_delay_ms(380);
				
				velocity(150,150);
				right();
				_delay_ms(850);
				n++;
				
			}
			
		}
		

		
		/*****************W5****************/
		while(n==3)
		{
			
			velocity(150,150);
			forward();
			_delay_ms(250);
			
			stop();
			_delay_ms(1000);
			
			place();
			_delay_ms(1000);
			down_pick_up();
			_delay_ms(1000);
			n++;
		
		}
		
		while(n==4)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			
			back_behav();
			
			if(left_sensor> x && centre_sensor> y && right_sensor> x)
			{
				velocity(150,150);
				forward();
				_delay_ms(350);
				
				velocity(150,150);
				left();
				_delay_ms(600);
				
				n++;
			}
			
		}
		
}

void natural_behav(void)
{
	unsigned int left_sensor=ADC_Conversion(1);
	unsigned int right_sensor=ADC_Conversion(3);
	unsigned int centre_sensor=ADC_Conversion(2);
	if(left_sensor<x && centre_sensor>y && right_sensor<x)
	{
		velocity(150,150);
		forward();
	}
	if(left_sensor<x && centre_sensor<y && right_sensor>x)
	{
		velocity(80,80);
		right();
	}
	if(left_sensor>x && centre_sensor<y && right_sensor<x)
	{
		velocity(80,80);
		left();
	}
}

void back_behav(void)
{
	unsigned int left_sensor=ADC_Conversion(1);
	unsigned int right_sensor=ADC_Conversion(3);
	unsigned int centre_sensor=ADC_Conversion(2);
	if(left_sensor<x && centre_sensor>y && right_sensor<x)
	{
		velocity(150,150);
		back();
	}
	if(left_sensor<x && centre_sensor<y && right_sensor>x)
	{
		velocity(80,80);
		right();
	}
	if(left_sensor>x && centre_sensor<y && right_sensor<x)
	{
		velocity(80,80);
		left();
	}

}