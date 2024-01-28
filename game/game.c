#include <stdio.h>
#include <math.h>
#include <ctype.h>

struct player_coordinates
{
	int x;
	int y;
}p1_boxes[5] , p2_boxes[5];

void Coordinate_Intialize(int a[] , int b[]);
void Print_board();

void Input(int a[] , int b[] , char c , char Ai);
void AI(int p1 , int p2);
void ai(int p1 , int p2);
int box_check(int x , int y);
void Update_board(char c , char Ai);
int Player_boxes(int x , int y);

int Win_check(int a[] , int b[]);
void Result(int W);


int main()
{	
	unsigned short int turns = 1;
	int Winner = -1;
	int a[5] , b[5];
	int i; // Extra integer has no purpose.
	char Player;
	char Ai;
	
	Coordinate_Intialize(a , b);

	top :

	printf("To use cross type : x\nTo use zero type : o\n");
	scanf("%c%*c" , &Player);

	if(toupper(Player) != 'X' && toupper(Player) != 'O')
	{
		printf("Please select an appropriate option !\n");
		goto top;
	}
	else
	{
		if(toupper(Player) == 'X')
			Ai = 'O';
		else
			Ai = 'X';
	}
	
	Print_board();
	
	while(turns <= 9)
	{
		Input(a , b , toupper(Player) , Ai);
		
		if(turns >= 5)
			Winner = Win_check(a , b);
		
		if(Winner != -1)
			break;
			
		turns++;
	}

	Update_board(Player , Ai);
	
	Result(Winner);
	
	scanf("%*c%*c");
	
	return 0;
	
}

void Coordinate_Intialize(int a[] , int b[])
{
	int i = 0;
	
	for(;i < 5 ; i++)
	{
		p1_boxes[i].x = -1;
		p1_boxes[i].y = -1;
		a[i] = -1;
		
		p2_boxes[i].x = -1;
		p2_boxes[i].y = -1;
		b[i] = -1;
	}
}

void Print_board()
{
	printf(" 0,0  | 0,1  | 0,2\n");
	printf("______ ______ ______\n\n");
	printf(" 1,0  | 1,1  | 1,2\n");
	printf("______ ______ ______\n\n");	
	printf(" 2,0  | 2,1  | 2,2\n");
}

void Input(int a[] , int b[] , char c , char Ai)
{

	static int p = 1; //1 = X = Player 1
	static int p1_turn = 0 , p2_turn = 0;
	int i , j;
	int check;

	start :

    if(p == 1)
    {
        printf("Please enter the cordinate of choice : ");
        scanf("%d %d" , &i , &j);
        
        check = box_check(i , j);

        if(check == 1)
        {
            p1_boxes[p1_turn].x = i;
			p1_boxes[p1_turn].y = j;
			
			a[p1_turn] = Player_boxes(p1_boxes[p1_turn].x , p1_boxes[p1_turn].y);
			
			p1_turn++;
        }

        else
	    {
		    printf("Box already occupied.\n Please select another box : ");
		    goto start;
	    }
    }
	
	else if(p == 0)
	{
        if(p2_turn == 0)
	        AI(0,0);
		
		else
			ai(p1_turn-1 , p2_turn);
        
        b[p2_turn] = Player_boxes(p2_boxes[p2_turn].x , p2_boxes[p2_turn].y);
        
        p2_turn++;

		printf("\n\n");
	
		Print_board();
    	printf("\n\n");
		Update_board(c , Ai);
		printf("\n\n");
    }
	
	p = !p;
	

}

void AI (int p1 , int p2)
{
    int i , j;
    int x , y;

    i = p1_boxes[p1].x;
    j = p1_boxes[p1].y;

    for(x = 0 ; x < 3 ; x++)
    {
        for(y = 0 ; y < 3 ; y++)
        {
            if(box_check(i+x , j+y) == 1)
            {
                p2_boxes[p2].x = i+x;
                p2_boxes[p2].y = j+y;
                return;
            }
            else if (box_check(i-x , j-y) == 1)
            {
                p2_boxes[p2].x = i-x;
                p2_boxes[p2].y = j-y;
                return;
            }
            else if(box_check(i-x , j+y) == 1)
            {
                p2_boxes[p2].x = i-x;
                p2_boxes[p2].y = j+y;
                return;
            }
            else if(box_check(i+x , j-y) == 1)
            {
                p2_boxes[p2].x = i+x;
                p2_boxes[p2].y = j-y;
                return;
            }
        }
    }
}

void ai(int p1 , int p2)
{
	int x , y;

	x = p1_boxes[p1].x - p1_boxes[p1-1].x;
	y = p1_boxes[p1].y - p1_boxes[p1-1].y;

	if(x == 0 || y == 0 || fabs(x) == fabs(y))
	{
		if( fabs(x) == 1 || fabs(y) == 1)
		{
			if(box_check(p1_boxes[p1].x + x , p1_boxes[p1].y + y) == 1)
			{
				p2_boxes[p2].x = p1_boxes[p1].x + x;
				p2_boxes[p2].y = p1_boxes[p1].y + y;
				return;
			}
			else if(box_check(p1_boxes[p1].x + x + x , p1_boxes[p1].y + y + y) == 1)
			{
				p2_boxes[p2].x = p1_boxes[p1].x + x + x;
				p2_boxes[p2].y = p1_boxes[p1].y + y + y;
				return;
			}
			else if(box_check(p1_boxes[p1].x - x , p1_boxes[p1].y - y) == 1)
			{
				p2_boxes[p2].x = p1_boxes[p1].x - x;
				p2_boxes[p2].y = p1_boxes[p1].y - y;
				return;
			}
			else if(box_check(p1_boxes[p1].x - x - x , p1_boxes[p1].y - y - y) == 1)
			{
				p2_boxes[p2].x = p1_boxes[p1].x - x - x;
				p2_boxes[p2].y = p1_boxes[p1].y - y - y;
				return;
			}
		}
		else if(fabs(x) == 2 || fabs(y) == 2)
		{
			if (box_check(p1_boxes[p1].x - x/2 ,p1_boxes[p1].y - y/2) == 1)
			{
				p2_boxes[p2].x = p1_boxes[p1].x - x/2;
				p2_boxes[p2].y = p1_boxes[p1].y - y/2;
				return;
			}
			else
			{
				AI(p1 , p2);
				return;
			}
		}
	}
	else
	{
		AI(p1 , p2);
		return;
	}

	printf("\nno\n");

}

int box_check(int x , int y)
{
	int i;
	
	for(i = 0 ; i < 5 ; i++)
	{
		if(p1_boxes[i].x == x && p1_boxes[i].y == y)
			return -1;
		else if(p2_boxes[i].x == x && p2_boxes[i].y == y)
			return -1;
		else if(x > 2 || y > 2)
			return -1;
	}
	
	return 1;
}

void Update_board(char c , char Ai)
{
	int i , j , k;
	int flag = 0;
	
	for(i = 0 ; i < 3 ; i++)
	{
		for(j = 0 ; j < 3 ; j++)
		{
			for(k = 0 ; k < 5 ; k++)
			{
				if(p1_boxes[k].x == i && p1_boxes[k].y == j)
				{
					if(j < 2)
						printf(" %c |" , c);
					else
						printf(" %c" , c);
					flag = 1;
					break;
				}
				else if(p2_boxes[k].x == i && p2_boxes[k].y == j)
				{
					if(j < 2)
						printf(" %c |" , Ai);
					else
						printf(" %c" , Ai);
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			
			if(flag);
			else
				if(j < 2)
					printf("   |");
		}
		if(i < 2 )
			printf("\n___ ___ ___\n\n");	
	}
	
	printf("\n");
}

int Player_boxes(int x , int y)
{
	if(x == 0 && y == 0)
		return 1;
	else if( x == 0 && y == 1)
		return 2;
	else if( x == 0 && y == 2)
		return 3;
	else if( x == 1 && y == 0)
		return 4;
	else if( x == 1 && y == 1)
		return 5;
	else if( x == 1 && y == 2)
		return 6;
	else if( x == 2 && y == 0)
		return 7;
	else if( x == 2 && y == 1)
		return 8;
	else if( x == 2 && y == 2)
		return 9;
	else if(x == -1 && y == -1)
		return -1;
}

int Win_check(int a[] , int b[])
{
	int i = 0;
	
	int r1 = 1 , r2 = 4 , r3 = 7;
	int c1 = 1 , c2 = 2 , c3 = 3;
	int d1 = 1 , d2 = 3;

	//A
	for(i = 0 ; i < 5 ; i++)
	{
		if(a[i] == r1)
		{
			r1++;
			i = 0;
		}
		if(a[i] == c1)
		{
			c1 += 3;
			i = 0;
		}
		if(a[i] == d1)
		{
			d1 += 4;
			i = 0;
		}
		if(a[i] == d2)
		{
			d2 += 2;
			i = 0;
		}

		if(r1 == 4 || c1 == 10 || d1 == 13 || d2 == 9)
		{
			return 1;
		}
	}
	
	for(i = 0 ; i < 5 ; i++)
	{
		if(a[i] == c2)
		{
			c2 += 3;
			i = 0;
		}
		if(a[i] == c3)
		{
			c3 += 3;
			i = 0;
		}

		if(c2 == 11 || c3 == 12)
		{
			return 1;
		}
	}
	
	for(i = 0 ; i < 5 ; i++)
	{
		if(a[i] == r2)
		{
			r2++;
			i = 0;
		}
		if(a[i] == r3)
		{
			r3++;
			i = 0;
		}

		if(r2 == 7 || r3 == 10)
		{
			return 1;
		}
	}
	
	r1 = 1 ; r2 = 4 ; r3 = 7;
	c1 = 1 ; c2 = 2 ; c3 = 3;
	d1 = 1 ; d2 = 3;
	
	//B
	for(i = 0 ; i < 5 ; i++)
	{
		if(b[i] == r1)
		{
			r1++;
			i = 0;
		}
		if(b[i] == c1)
		{
			c1 += 3;
			i = 0;
		}
		if(b[i] == d1)
		{
			d1 += 4;
			i = 0;
		}
		if(b[i] == d2)
		{
			d2 += 2;
			i = 0;
		}	

		if(r1 == 4 || c1 == 10 || d1 == 13 || d2 == 9)
			return 0;
	}
	
	for(i = 0 ; i < 5 ; i++)
	{
		if(b[i] == c2)
		{
			c2 += 3;
			i = 0;
		}
		if(b[i] == c3)
		{
			c3 += 3;
			i = 0;
		}

		if(c2 == 11 || c3 == 12)
			return 0;
	}
	
	for(i = 0 ; i < 5 ; i++)
	{
		if(b[i] == r2)
		{
			r2++;
			i = 0;
		}
		if(b[i] == r3)
		{
			r3++;
			i = 0;
		}

		if(r2 == 7 || r3 == 10)
			return 0;
	}

	return -1;
}

void Result(int w)
{

	printf("\n\n");

	if(w == 1)
		printf("The winner is : Player 1\n\n");
	else if(w == 0)
		printf("The winner is : Player 2\n\n");
	else if(w == -1)
		printf("DRAW\n\n");

	getchar();
}