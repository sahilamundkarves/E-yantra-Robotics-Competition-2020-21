/*
 * prox.c
 *
 * Created: 2/6/2020 9:57:36 AM
 *  Author: Admin
 */ 


#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "functions.c"
int n=1,k=1,a=80,x=20,y=21;
unsigned char prox_value1=0;
unsigned int prox=0;

int main(void)
{
	
	_delay_ms(5000);
	init_devices();
	lcd_set_4bit();
	sinit_devices();
	
	
	/*while(1)
	{
		prox_value1 = ADC_Conversion(10);
		prox = Sharp_GP2D12_estimation(prox_value1);
		lcd_print(2,14,prox,3);
	}*/
   while(n==1)
    {
		
		unsigned int left_sensor=ADC_Conversion(1);
		unsigned int right_sensor=ADC_Conversion(3);
		unsigned int centre_sensor=ADC_Conversion(2);
		
		
		while(k==1)
		{
			prox_value1 = ADC_Conversion(9);						
			prox = Sharp_GP2D12_estimation(prox_value1);		 		
			lcd_print(2,14,prox,3); 						

			if(prox > a && prox < 285)
			{
				natural_behav();		
			}
			else
			{
				stop();
				_delay_ms(1000);
				down_pick_up();
				_delay_ms(1000);
				place();
				_delay_ms(200);
				k++;
			}	
		}
    }
	
	while(n==2)
	{
		
		unsigned int left_sensor=ADC_Conversion(1);
		unsigned int right_sensor=ADC_Conversion(3);
		unsigned int centre_sensor=ADC_Conversion(2);
		back_behav();
		if(left_sensor> x && centre_sensor> y && right_sensor> x)
		{
			velocity(150,150);
			left();
			_delay_ms(850);
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
		velocity(97,97);
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