//tic tac toe
#include <avr/io.h>
#include "delay.h"
#include "uart.h"

int rep[9],fin[9];
int p,j=0;
int w=2; //win decider
void  main()
{
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0Xff;
	DDRD=0xff;
	
	uartinit();
	delayms(1);
	
	int i,q=0;//i for counting turn
	char ch;
	for(i=1;i<=9;rep[i]=0,i++);
	i=0;
	for(i=0;i<=8;fin[i]=2,i++);
	i=0;
	
	printstring("WELCOME TO TIC TAC TOE\n");printchar(13);
	printstring("rules: select ur pos from numpad 1 to 9\n");printchar(13);
	printstring("at any point press r to reset,press any other key to start\n");printchar(13);
	while(1)
	{
		ch=dispdata();
		PORTA=0x00;
		PORTB=0x00;
		PORTC=0x00;
		printstring("new game\n");printchar(13);
		while(ch!='r')
		{
			if((i%2)==0)
			{
				q=0;
				select(q);
			}
			else
			{
				q=1;
				select(q);
			}
			//winner
			rows();
			coloumns();
			diagonal();

			if(w==1)
			{
				printstring("WINNER IS PLAYER 1\n");printchar(13);	
				break;
			}
			else if(w==0)
			{
				printstring("WINNER IS PLAYER 2\n");printchar(13);	
				break;
			}
			else if(i==9)
			{	
				printstring("MATCH DRAW\n");printchar(13);
				break;
			}
			else
				i++;
		}
	}
	
}

void select(x)
int x;
{
	unsigned char ch;
	int y,z=0;
	if(x==0)
	{
		printstring("PLAYER 1 TURN\n");printchar(13);
		ch=dispdata();
		y=ch-48;
		z=y-1;
		check(x,y);// x=q y=1
		if(y==9)
			PORTC|=(1<<0);
		else
			PORTA|=(1<<z);
	}
	else
	{
		printstring("PLAYER 2 TURN\n");printchar(13);
		ch=dispdata();
		y=ch-48;
		z=y-1;
		check(x,y);
		if(y==9)
			PORTC|=(1<<1);
		else
			PORTB|=(1<<z);
	}
	j=z;
	fill(x);
}

void check(r,s)
int r,s;
{
	int i;
	for(i=1;i<=9;i++)
	{
		if(rep[i]==s)
		{
			printstring("ALREADY TAKEN\n");printchar(13);
			select(r);
		}	
	}
	rep[p]=s;
	p++;
}

void fill(y)// conversion from 1 to 9 -> 0 to 8
int y;
{
	if(y==0)
		fin[j]=1;
	else
		fin[j]=0;
}

void rows()
{
	int y;
	for(y=0;y<=6;)
	{
		if((fin[y]==1)&&(fin[y+1]==1)&&(fin[y+2]==1))
			w=1;
		else if((fin[y]==0)&&(fin[y+1]==0)&&(fin[y+2]==0))
			w=0;
		y+=3;
	}
}

void coloumns()
{
	int y;
	for(y=0;y<=2;)
	{
		if((fin[y]==1)&&(fin[y+3]==1)&&(fin[y+6]==1))
			w=1;
		else if((fin[y]==0)&&(fin[y+3]==0)&&(fin[y+6]==0))
			w=0;
		y+=1;
	}
}

void diagonal()
{
	if((fin[0]==1)&&(fin[4]==1)&&(fin[8]==1)||(fin[2]==1)&&(fin[4]==1)&&(fin[6]==1))
		w=1;
	else if((fin[0]==0)&&(fin[4]==0)&&(fin[8]==0)||(fin[2]==0)&&(fin[4]==0)&&(fin[6]==0))
		w=0;
}