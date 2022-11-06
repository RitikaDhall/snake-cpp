#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

const int width=20, height=20;
int gameOver, level=1, t=0, x, y, nFruit=0, fruitX, fruitY, stoneX, stoneY, score, tailX[100], tailY[100], nTail;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{	gameOver=0;
	dir=STOP;
	x= width/2;
	y= height/2;

	randomize();
	fruitX= rand() % width;
	fruitY= rand() % height;
	score=0;
}

void Display()
{	clrscr;
	int i;
	cout<<"i-Up\tj-Left\tk-Down\tl-Right\tx-Exit\n";
	cout<<"Level-"<<level<<"\t\tScore: "<<score<<endl;
	for(i=0; i<width+2; i++)
		cout<<"#";
	cout<<endl;

	for (i=0; i < height; i++)
	{	for (int j=0;j<width;j++)
		{	if (j == 0)
				cout<<"#";
			if (i == y && j == x)
			{       textcolor(2);
				cprintf("O");
			}

			else if (i == fruitY && j == fruitX)
			{	textcolor(5);
				cprintf("*");
			}
			else if ( (level==3) && (i == stoneY && j == stoneX))
			{      	 textcolor(4);
				 cprintf("*");
			}
			else
			{       int print = 0;
				for (int k=0; k<nTail; k++)
				{       if (tailX[k] == j && tailY[k] == i)
					{       textcolor(2);
						cprintf("o");
						print = 1;
					}
				}
				if (!print)
				{       textcolor(15);
					cout<<" ";
				}
			}
			if (j == width - 1)
				cout<<"#";
		}
		cout<< endl;
	}

	for (i=0;i<width+2;i++)
		cout<<"#";
	cout<<endl;
}

void Input()
{	if (kbhit())
	{	switch (getch())
		{	case 'j': dir= LEFT;
				  break;
			case 'l': dir= RIGHT;
				  break;
			case 'i': dir= UP;
				  break;
			case 'k': dir= DOWN;
				  break;
			case 'x': gameOver= 1;
				  break;
			default : ;
				  break;
		}
	}
}

void Logic()
{       int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i<nTail; i++)
	{	prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{	case LEFT : --x;
				break;
		case RIGHT: ++x;
				break;
		case UP   : --y;
				break;
		case DOWN : ++y;
				break;
		default   : ;
				break;
	}

	if (level == 1)
	{	if (x >= width)
			x=0;
		else if (x < 0)
			x = width-1;
		if (y >= height)
			y=0;
		else if (y < 0)
			y = height-1;
	}
	else
		if(x==width || y==height || x<0 || y<0 )
			gameOver=1;

	for (i=0; i<nTail ; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = 1;

	if (x == fruitX && y == fruitY)
	{       score +=10;
		t+=5;
		fruitX= rand() % width;
		fruitY= rand() % height;
		nTail++;
		nFruit++;

		if (level==3)
		{	stoneX= rand() % width;
			stoneY= rand() % height;
		}
	}

	if (level==3)
	{	if (x == stoneX && y == stoneY)
		{       score -=5;
			stoneX= rand() % width;
			stoneY= rand() % height;
			nTail--;
		}
		if (nTail < 0)
			gameOver=1;
	}
}

void main()
{	system("clear");
	Setup();
	while(!gameOver)
	{	Display();
		Input();
		Logic();
		if(t<=70)
			delay(225-t);
		else
			delay(200);

		if (nFruit>5 && nFruit<10)
			level=2;
		else if (nFruit>10 && nFruit<15)
			level=3;
	}
	textcolor(14);
	cprintf("GAME OVER");
	return 0;
}
