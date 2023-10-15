#include <mega32a.h>

// Graphic Display functions
#include <glcd.h>
#include <delay.h>
#include <stdlib.h>
// Font used for displaying text
// on the graphic display
#include <font5x7.h>

#define N 16                                              //tashkhis toop tavasot cpu
#define M 8

// Declare your global variables here



 int m=1;
 int win=0;
 int ii=0;
 int moving = 0;
 int rst=0;


struct point
{       int x;
        int y;
};

struct player
{        struct point p[N];
};

struct ball
{       struct point p;
        int j ;
        int shib;
};

struct player me;

struct ball b = {64,32} ;

struct player com;


void print(struct point p)
{
        //glcd_circle(p.x,p.y,3);
        glcd_circle(p.x,p.y,1);
       //glcd_outtextxyf(p.x,p.y,"");
       //glcd_outtextxyf(p.x,p.y,".");
}

void printplayer(struct player pl)
{
        for(ii=0;ii<N;ii++)
        {
                print(pl.p[ii]);
        }
}





// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
      moving = -1;          //baraye taasir  harekat rocket bar toop
      for(ii=0;ii<N;ii++)
                 {
                        me.p[ii].y -= 1*M;
                 }
      moving = 0;
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
        moving = +1;            //baraye taasir  harekat rocket bar toop
       for(ii=0;ii<N;ii++)
                 {
                        me.p[ii].y += 1*M;
                 }
        moving = 0;
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0x0C;
// Place your code here

}

void main(void)
{
// Declare your local variables here
// Variable used to store graphic display
// controller initialization data
GLCDINIT_t glcd_init_data;

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 0.977 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 0.24986 s
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x0C;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: Off
GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);

// Graphic Display Controller initialization
// The KS0108 connections are specified in the
// Project|Configure|C Compiler|Libraries|Graphic Display menu:
// DB0 - PORTA Bit 0
// DB1 - PORTA Bit 1
// DB2 - PORTA Bit 2
// DB3 - PORTA Bit 3
// DB4 - PORTA Bit 4
// DB5 - PORTA Bit 5
// DB6 - PORTA Bit 6
// DB7 - PORTA Bit 7
// E - PORTB Bit 0
// RD /WR - PORTB Bit 1
// RS - PORTB Bit 2
// /RST - PORTB Bit 3
// CS1 - PORTB Bit 4
// CS2 - PORTB Bit 5

// Specify the current font for displaying text

// No function is used for reading
// image data from external memory
glcd_init_data.readxmem=NULL;
// No function is used for writing
// image data to external memory
glcd_init_data.writexmem=NULL;
glcd_init_data.font=font5x7;
glcd_init(&glcd_init_data);

// Global enable interrupts
#asm("sei")
glcd_clear();
//glcd_outtextxyf(0,31,"X=20 Y=10 Test");

b.j=3;
b.shib=0;
for(ii=0;ii<N;ii++)
        {
            me.p[ii].x = 1;
        }
                            //locate me

        for(ii=0;ii<N;ii++)
        {
            me.p[ii].y = 32-N+ii;
        }

        for(ii=0;ii<N;ii++)
        {
            com.p[ii].x = 126;
        }                        //locate com

        for(ii=0;ii<N;ii++)
        {
            com.p[ii].y = 32-N+ii;
        }


	while (1)
	{
		glcd_clear();
		print(b.p);
		printplayer(me);
		printplayer(com);



                 //if(com.p[0].y<=1) m = 1;
                 //if(com.p[N-1].y>=61) m =-1;

                 if(com.p[0].y<=b.p.y) m=1 ;
                 if(com.p[N-1].y>=b.p.y) m =-1;

                 if(rst<2)
                 {
                        for(ii=0;ii<N;ii++)
                        {
                                com.p[ii].y += m*M;
                        }
                        rst++;

                 }                             //move com
                 else
                        rst=0;   // player cpu , top ra donbal mikonad vali har 2 harekat , 1 esterahat mikonad

        if (b.p.y >= 62 || b.p.y <= 1)
                switch (b.j)
                {
                case 1: b.j = 2; break;
                case 2: b.j = 1; break;
                case 3: b.j = 4; break;
                case 4: b.j = 3; break;
                }                                //get wall

        if (b.p.x >= 127-M+1)
        {
                if(moving!=0)
                        b.shib=b.shib+moving  ;
                for(ii=0;ii<N;ii++)
                {
                        if(com.p[ii].y == b.p.y)
                        {
                        switch (b.j)
                        {
                        case 1: b.j = 3; break;
                        case 2: b.j = 4; break;
                        case 3: b.j = 1; break;
                        case 4: b.j = 2; break;
                        }
                        break;
                        }
                }
                                                //get  player
        }

        if (b.p.x <= 0+M+1)
        {
                for(ii=0;ii<N;ii++)
                {
                        if((me.p[ii].y == b.p.y))
                        {
                        switch (b.j)
                        {
                        case 1: b.j = 3; break;
                        case 2: b.j = 4; break;
                        case 3: b.j = 1; break;
                        case 4: b.j = 2; break;
                        }
                        break;
                        }
                }

        }



	switch (b.j)
	{
	case 1: b.p.x+=1*M; b.p.y-=(1+b.shib)*M; break;
	case 2: b.p.x+=1*M; b.p.y+=(1+b.shib)*M; break;
	case 3: b.p.x-=1*M; b.p.y-=(1+b.shib)*M; break;
	case 4: b.p.x-=1*M; b.p.y+=(1+b.shib)*M; break;
	}                                         //move ball


                if(b.p.x<=0)
                {
                 win=0;
                 break;
                }
                if(b.p.x>=127)                      //goal
                {
                 win=1;
                 break;
                }

	}

        glcd_clear();
        if(win==1)
                glcd_outtextxyf(30,10,"You Win! :)");
                else
                glcd_outtextxyf(30,10,"You Lose! :(");
}