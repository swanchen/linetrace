#include <limits.h>
#include "general.h"
#include "trainer.h"

void wait_fix(void);
unsigned int get_iflag_sw2(void);

int check_sensor(void);
void delay_ms(unsigned int x);
unsigned char rotate_r(unsigned char data);
unsigned char rotate_l(unsigned char data);
void lmotor(int time);
void rmotor(int time);

void stop(void);

unsigned char buf_l = 0x99;
unsigned char buf_r = 0x99;

void main( void )
{
	unsigned int chk_sw2;
	ei();
	wait_fix();			/* �ŏ��̓��̓o�b�t�@�����O�������I���̂�҂� */
	chk_sw2 = get_iflag_sw2();				/* chk_sw2������ */	
	FOREVER
	{
		chk_sw2 = get_iflag_sw2();				/* chk_sw2������ */			
		if (get_iflag_sw2() != chk_sw2) 		/* SW2�����G�b�W */
		{
			unsigned int t;
			chk_sw2++;
			for(t=100;t>5;t-5)
			{
				if(check_sensor()==9)
				{
           			lmotor(t);
       	   			rmotor(t);
				}				
				if(check_sensor()==13||check_sensor()==12||check_sensor()==1||check_sensor()==2)
				{
           			rmotor(t);
           			lmotor(t);
           			rmotor(t);
           			lmotor(t);
           			rmotor(t);
				}
				if(check_sensor()==14)
				{
        			rmotor(t);
        			lmotor(t);
        			rmotor(t);
        			lmotor(t);
        			rmotor(t);
				}
        		if(check_sensor()==11||check_sensor()==3||check_sensor()==8||check_sensor()==4)
        		{
            		lmotor(t);
            		rmotor(t);
            		lmotor(t);
            		rmotor(t);
            		lmotor(t);
        		}
        		if(check_sensor()==7)
        		{
            		lmotor(t);
            		rmotor(t);
            		lmotor(t);
            		rmotor(t);
            		lmotor(t);
        		}
			}
			while(check_sensor()!=15)
			{
				if(check_sensor()==9)
				{
           			lmotor(7);
       	   			rmotor(7);
				}				
				if(check_sensor()==13||check_sensor()==12||check_sensor()==1||check_sensor()==2)
				{
           			rmotor(7);
           			lmotor(7);
           			rmotor(7);
           			lmotor(7);
           			rmotor(7);
				}
				if(check_sensor()==14)
				{
        			rmotor(7);
        			lmotor(10);
        			rmotor(7);
        			lmotor(10);
        			rmotor(7);
				}
        		if(check_sensor()==11||check_sensor()==3||check_sensor()==8||check_sensor()==4)
        		{
            		lmotor(7);
            		rmotor(7);
            		lmotor(7);
            		rmotor(7);
            		lmotor(7);
        		}
        		if(check_sensor()==7)
        		{
            		lmotor(7);
            		rmotor(10);
            		lmotor(7);
            		rmotor(10);
            		lmotor(7);
        		}
			}	
		}
	}	
}
/*------------------ end of main() ------------------------- EJECT ---*/
int check_sensor(void)
{
	return inp(SENSER)&0x0f;
}
/*�E���*/
unsigned char rotate_l(unsigned char data)
{
	unsigned char msb2lsb;
	msb2lsb = data >> CHAR_BIT - 1;
	data <<= 1;
	data |= msb2lsb;

	return data;
}
/*�����*/
unsigned char rotate_r(unsigned char data)
{
	unsigned char msb2lsb;

	msb2lsb = data << CHAR_BIT - 1;
	data >>= 1;
	data |= msb2lsb;

	return data;
}
/*�����[�^*/
void lmotor(int time)
{
    
    outp(MOTOR1,buf_l);
    delay_ms(time);
    buf_l = rotate_r(buf_l);
}
/*�E���[�^*/
void rmotor(int time)
{
    
    outp(MOTOR2,buf_r);
    delay_ms(time);
    buf_r = rotate_l(buf_r);
}
/*------------------------- end of main.c ----------------------*/