#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>


int gameover;
int direction;


int board_width;
int board_height;


int food_pos_x;
int food_pos_y;

int score;

int tailLength;

int x,y;

int tailX[100],tailY[100];

void setup(){
  srand(time(0));

  gameover=0;
  direction=0;

  board_width=40;
  board_height=20;

  score=0;

  tailLength=0;

  food_pos_x=rand()%board_width;
  food_pos_y=rand()%board_height;

   x=board_width/2;
   y=board_height/2;
}
void draw()
{
    system("cls");

    int i, j, k;

    // Top Border
    for(i = 0; i < board_width + 2; i++)
    {
        printf("#");
    }

    printf("\n");

    // Game Area
    for(i = 0; i < board_height; i++)
    {
        printf("#");

        for(j = 0; j < board_width; j++)
        {
            // Snake Head
            if(i == y && j == x)
            {
                printf("O");
            }

            // Food
            else if(i == food_pos_y && j == food_pos_x)
            {
                printf("*");
            }

            // Tail
            else
            {
                int printed = 0;

                for(k = 0; k < tailLength; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }

                if(!printed)
                {
                    printf(" ");
                }
            }
        }

        printf("#");
        printf("\n");
    }

    // Bottom Border
    for(i = 0; i < board_width + 2; i++)
    {
        printf("#");
    }

    printf("\n");

    printf("Score = %d\n", score);
    printf("Controls: W A S D\n");
}

 void input()
{
    if(kbhit())
    {
        switch(tolower(getch()))
        {
            case 'a':
                if(direction != 2)
                direction = 1;
                break;

            case 'd':
                if(direction != 1)
                direction = 2;
                break;

            case 'w':
                if(direction != 4)
                direction = 3;
                break;

            case 's':
                if(direction != 3)
                direction = 4;
                break;

            case 'x':
                gameover = 1;
                break;
        }
    }
}
void logic(){

	int prevX=tailX[0];
	int prevY=tailY[0];

	int prev2X,prev2Y;

	tailX[0]=x;
	tailY[0]=y;

	for(int i=1;i<tailLength;i++)
	{
		prev2X=tailX[i];
		prev2Y=tailY[i];

		tailX[i]=prevX;
		tailY[i]=prevY;

		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(direction)
	{
		case 1:
		x--;
		break;

		case 2:
		x++;
		break;

		case 3:
		y--;
		break;

		case 4:
		y++;
		break;

		
	}
                 // Wall Collision
   		 if(x < 0 || x >= board_width || y < 0 || y >= board_height)
   		 {
      			  gameover = 1;
   		 }

		for(int i = 0; i < tailLength; i++)
   		 {
     			   if(tailX[i] == x && tailY[i] == y)
     	        	 {
         			   gameover = 1;
     	       	         }
  		  }

		if(x==food_pos_x&&y==food_pos_y)
		{
			score=score+10;
			tailLength++;
			food_pos_x=rand()%board_width;
			food_pos_y=rand()%board_height;
		}
}
int main()
{
	setup();
	while(gameover==0){
		draw();
		input();
		logic();
		
		Sleep(100);
	}
	system("cls");
	printf("\n\n");
	printf("==========GAME OVER======\n");
	printf("Final score=%d\n",score);
	getch();
	return 0;
}

