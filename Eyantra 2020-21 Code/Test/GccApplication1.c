

/*
 * task5.c
 *
 * Created: 12-02-2020 21:57:44
 *  Author: Sahil Amundkar, Samruddha Kalke, Abhijeet Kale, Raj Talashilkar
 */ 


#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "functions.c"
unsigned char prox_value1=0,prox_value2=0;
unsigned int prox=500,prox2=0;
//initial
int x=01,y=04;
int r=1;
//final
int xf=0,yf=02;

int p=20,q=20;
int n=1;
int a=1;
int k=1.3;

	int setpoint=50;
	unsigned int kp=1.41;
	unsigned int kd=1.45;
	unsigned int ki=0;
	int integral=0;
	unsigned int basespeed=135;    //210
	unsigned int maxspeed=190;
	float lasterror=0;
	int motorspeed;

void pidmotion(float check_line)
{
	int error=check_line-setpoint;
	integral=integral+error;
	motorspeed=kp*error+kd*(error-lasterror)+ki*integral;
	//motorspeed=k*error;
	lasterror=error;
	int rightmotorspeed=basespeed+motorspeed;
	int leftmotorspeed=basespeed-motorspeed;
	if(rightmotorspeed>maxspeed)
	{
		rightmotorspeed=maxspeed;
	}
	if(leftmotorspeed>maxspeed)
	{
		leftmotorspeed=maxspeed;
	}
	if(rightmotorspeed<0)
	{
		rightmotorspeed=0;
	}
	if(leftmotorspeed<0)
	{
		leftmotorspeed=0;
	}

	forward();
	velocity(leftmotorspeed,rightmotorspeed);
}


int main(void)	//this loop will be called 12 times for picking 12 blocks
{
	init_devices();
	binit_devices();
	lcd_set_4bit();
	sinit_devices();
	
	lcd_cursor(1,3);
	lcd_string("E-yantra");	

	_delay_ms(3000);

	/*while(r==1)
	{
		unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
		unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
		unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sens
		pidmotion(centre_sensor);
		if(centre_sensor > q && right_sensor > p && left_sensor > p)
		{
			stop();
			_delay_ms(100);
			velocity(140,140);
			forward_mm(30);
			turn_right();
			r++;
		}
	}
	left();
	_delay_ms(30);
	while(r==2)
	{
		unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
		unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
		unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
		pidmotion(centre_sensor);
		//natural_behav();
		if(centre_sensor > q && right_sensor > p && left_sensor <p)
		{
			stop();
			_delay_ms(30);
			velocity(140,140);
			forward_mm(30);
			turn_right();
			r++;
		}
	}
	
	left();
	_delay_ms(30);
	while(r==3)
	{
		unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
		unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
		unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
		pidmotion(centre_sensor);

		if(centre_sensor > q  && right_sensor > p && left_sensor >p)
		{
			forward_mm(35);
			r++;
		}
	}*/
	

	
	block_pick();
	//LHLR(1,2,2,5);
	
/*
	place_block_HL(2,5);
	
	HLRL(2,5,1,1);
	stop();
	_delay_ms(10000);*/
	
}


void LHLR(int x , int y , int xf, int yf)
{
	while(x!=xf && y!=yf)
	{
		//	case 1:		//check if y,yf co-ordinates are same or not
		if(y!=yf)		//if not
		{
			unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
			unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
			unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
			
			pidmotion(centre_sensor);
			if(left_sensor > p && centre_sensor > q && right_sensor > p)		//node condition
			{
					// same if condition will work until x==i
				velocity(140,140);
				forward_mm(30);
				y++;
			}
		}
		if(y==yf)
		{
			unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
			unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
			unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor

			stop();
			_delay_ms(100);
			turn_right();
			left();
			_delay_ms(30);
			while(x!=xf)
			{
				unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
				unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
				unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
				natural_behav();
				if(left_sensor>p && centre_sensor>q && right_sensor> p)
				{
					x=xf;
				}
			}
		}
	}
}


void HLRL(int x,int y,int xf,int yf)
{
	
	while(x!=xf && y!=yf)
	{
		if(y!=yf)
		{
			unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
			unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
			unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
			
			pidmotion(centre_sensor);
			if(centre_sensor > q  && left_sensor > p && right_sensor > p)
			{
				velocity(140,140);
				forward_mm(30);
				y--;
			}
		}
		if(y==yf && x!=xf)
		{
			stop();
			_delay_ms(100);
			turn_right();
			left();
			_delay_ms(30);
			
			while(x!=xf)
			{
				unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
				unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
				unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
				
				pidmotion(centre_sensor);
				if(centre_sensor > q  && left_sensor > p && right_sensor > p)
				{
					x=xf;
				}
			}
		}
	}
	
}


void block_pick()
{
	int e=1;
	int f=1;
	
	stop();
	_delay_ms(100);
	turn_left();
	right();
	_delay_ms(30);
	stop();
	_delay_ms(1000);
	
	while(e==1)
	{
		unsigned int left_sensor=ADC_Conversion(1);
		unsigned int right_sensor=ADC_Conversion(3);
		unsigned int centre_sensor=ADC_Conversion(2);
		prox_value1 = ADC_Conversion(9);
		prox = Sharp_GP2D12_estimation(prox_value1); //taking values from proximity sensor1 placed at the front of the bot
		lcd_print(2,14,prox,3);

		if(prox<400)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			natural_behavprox();
			
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1); //taking values from proximity sensor1 placed at the front of the bot
			lcd_print(2,14,prox,3);

			if(prox > 100)
			{
				velocity(90,90);
				forward();
			}
			else if(prox > 90 && prox < 99)//90
			{
				velocity(0,0);
				stop();
				_delay_ms(1000);

				down_pick_up();
				_delay_ms(1000);

				stop();
				_delay_ms(1000);

				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					back_behav();

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						velocity(140,140);
						forward_mm(30);
						turn_right();
						//left();
						//_delay_ms(70);
						stop();
						_delay_ms(500);
						e=2;
						break;
					}
				}
			
			}
			else if(prox < 89)//89
			{
				velocity(90,90);
				back();
			}
		}
		else
		{
			velocity(140,140);
			right_degrees(210);
			left_degrees(15); 
			//right();
			//_delay_ms(70);
			stop();
			_delay_ms(500);
			
			while (f==1)
			{
				prox_value1 = ADC_Conversion(9);
				prox = Sharp_GP2D12_estimation(prox_value1); //taking values from proximity sensor1 placed at the front of the bot
				lcd_print(2,14,prox,3);

				if(prox > 100)
				{
					velocity(90,90);		//natural behav
					forward();
				}

				else if(prox > 90 && prox < 99)//90
				{
					stop();
					_delay_ms(1000);

					down_pick_up();
					_delay_ms(1000);

					stop();
					_delay_ms(1000);

					while(1)
					{
						unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
						unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
						unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

						
						back_behav();

						if(left_sensor>p && centre_sensor>q && right_sensor>p)
						{
							velocity(140,140);
							forward_mm(30);
							turn_left();
							//right();
							//_delay_ms(70);
							stop();
							_delay_ms(500);
							f=2;
							e=2;
							break;
						}
						
					}

				}
				else if(prox< 89)//89
				{
					velocity(90,90);
					back();
				}

			}
		}
	}

	
}		


void place_block_LH_forxf1(int xf, int yf)
{	int c=1;
	while(xf==1 && c==1)
	{
		if((xf==1 && yf==3)||(xf==2 && yf ==5)) //condition of low rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);


				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						
						turn_right();
						left();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
					
				}
			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
		else //condition of high rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);

				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_right();
						left();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}

			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
	}
}

void place_block_LH_forxf2(int xf, int yf)
{int c=1;
	while(xf==2 && c==1)
	{
		if((xf==1 && yf==3)||(xf==2 && yf ==5)) //condition of low rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);


				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_left();
						right();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					
					else
					back_behav();
				}
			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
		else //condition of high rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);

				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_left();
						right();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}

			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
	}
}





void place_block_HL_forxf1(int xf,int yf)
{
	int c=1;
	while(xf==1 && c==1)
	{
		if((xf==1 && yf==3)||(xf==2 && yf ==5)) //condition of low rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);


				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_left();
						right();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}
			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
		else //condition of high rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);

				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_left();
						right();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}

			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
	}
}

void place_block_HL_forxf2(int xf,int yf)
{int c=1;
	while(xf==2)
	{
		if((xf==1 && yf==3)||(xf==2 && yf ==5)) //condition of low rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);


				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_right();
						left();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}
			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
		else //condition of high rise
		{
			prox_value1 = ADC_Conversion(9);
			prox = Sharp_GP2D12_estimation(prox_value1);
			lcd_print(2,14,prox,3);


			if(prox >80 && prox <84)
			{
				stop();
				_delay_ms(1000);

				place();
				_delay_ms(1000);

				while(1)
				{
					unsigned int left_sensor=ADC_Conversion(1); //value from left sensor
					unsigned int right_sensor=ADC_Conversion(3); //value from right sensor
					unsigned int centre_sensor=ADC_Conversion(2); //value from centre sensor

					if(left_sensor>p && centre_sensor>q && right_sensor>p)
					{
						turn_right();
						left();
						_delay_ms(30);
						stop();
						_delay_ms(500);
						c=2;
						break;
					}
					else
					back_behav();
				}

			}
			else if (prox >84)
			{
				velocity(80,80);
				forward();
			}
		}
	}
}

		
		//this function is used for aligning the bot on the black line while moving forward
		void natural_behav(void)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			if(left_sensor<p && centre_sensor>q && right_sensor<p)
			{
				velocity(190,190);
				forward();
			}
			if(left_sensor<p && centre_sensor<q && right_sensor>p)
			{
				velocity(100,100);
				right();
			}
			if(left_sensor>p && centre_sensor<q && right_sensor<p)
			{
				velocity(100,100);
				left();
			}
		}
		
		void back_behav(void)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			
			if(left_sensor<p && centre_sensor>q && right_sensor<p)
			{
				velocity(190,190);
				back();
			}
			if(left_sensor<p && centre_sensor<q && right_sensor>p)
			{
				velocity(100,100);
				right();
			}
			if(left_sensor>p && centre_sensor<q && right_sensor<p)
			{
				velocity(100,100);
				left();
			}

		}		
		
		
		void natural_behavprox(void)
		{
			unsigned int left_sensor=ADC_Conversion(1);
			unsigned int right_sensor=ADC_Conversion(3);
			unsigned int centre_sensor=ADC_Conversion(2);
			if(left_sensor<p && centre_sensor>q && right_sensor<p)
			{
				velocity(110,110);
				forward();
			}
			if(left_sensor<p && centre_sensor<q && right_sensor>p)
			{
				velocity(90,90);
				right();
			}
			if(left_sensor>p && centre_sensor<q && right_sensor<p)
			{
				velocity(90,90);
				left();
			}
		}
		flag=0;
		void turn_right()
		{
			forward_mm(25);
			right();
			_delay_ms(200);
		
			int z=1;
			while(z==1)
			{
				unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
				unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
				unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
				
				if(left_sensor < q)
				{
					velocity(100,100);
					right();
				}
				else
				{
					stop();
					lcd_cursor(1,17);
					lcd_string("done");
					_delay_ms(1000);
					z++;
					break;
				}
			}
	
		}


		void turn_left()
		{
			forward_mm(25);
			left();
			_delay_ms(200);
		
			int z = 1;
			while(z==1)
			{
				
				unsigned int left_sensor=ADC_Conversion(1);			//value from left sensor
				unsigned int right_sensor=ADC_Conversion(3);		//value from right sensor
				unsigned int centre_sensor=ADC_Conversion(2);		//value from centre sensor
				
				if(left_sensor < q)
				{
					velocity(100,100);
					left();
				}
				else
				{
					stop();
					lcd_cursor(1,17);
					lcd_string("done");	
					_delay_ms(1000);
					z++;
					break;
				}
			}
	
		}
		
		
	

	