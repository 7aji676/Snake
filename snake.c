#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_LEN 40

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STATIC
} Direction;

typedef struct snake
{
    int position[MAX_LEN][2];
    int len;
    Direction dir;
} snake;

void draw(snake *s)
{
    char table[HEIGHT][WIDTH];
    memset(table, ' ', sizeof(table));
    for (int i = 0; i < s->len; i++)
    {
        table[s->position[i][0]][s->position[i][1]] = 'o';
    }
    printf("##########################################\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("#");
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", table[i][j]);
        }
        printf("#");
        printf("\n");
    }

    printf("##########################################");
}

void tail_displacement(snake *s)
{

    if (s->len > 1)
    {
        for (int i = s->len - 1; i > 0; i--)
        {
            s->position[i][0] = s->position[i - 1][0];
            s->position[i][1] = s->position[i - 1][1];
        }
    }
}


bool generate(int * x , int * y){
    
}
void move(snake *s, int *c)
{
    
    if (s->position[0][1] == 0 && s->position[0][0] == 0)
    {
        if ((*c == 90 || *c == 122))
        {
            (s->position[0][1])++;
            *c = 68;
            s->dir = RIGHT;
        }
        else
        {
            (s->position[0][0])++;
            *c = 115;
            s->dir = DOWN;
        }

    } // top left corner
    else if (s->position[0][1] == 0 && s->position[0][0] == (HEIGHT - 1))
    {
        if (*c == 115 || *c == 83)
        {
            (s->position[0][1])++;
            *c = 68;
            s->dir = RIGHT;
        }
        else
        {
            (s->position[0][0])--;
            *c = 90;
            s->dir = UP;
        }
    } // bot left corner
    else if (s->position[0][1] == WIDTH - 1 && s->position[0][0] == 0)
    {
        if ((*c == 68 || *c == 100))
        {
            (s->position[0][0])++;
            *c = 115;
            s->dir = DOWN;
        }
        else
        {
            (s->position[0][1])--;
            *c = 81;
            s->dir = LEFT;
        }
    } // top right corner
    else if (s->position[0][1] == WIDTH - 1 && s->position[0][0] == HEIGHT - 1)
    {
        if (*c == 115 || *c == 83)
        {
            (s->position[0][1])--;
            *c = 81;
            s->dir = LEFT;
        }
        else
        {
            (s->position[0][0])--;
            *c = 90;
            s->dir = UP;
        }
    } // bot right corner
    else if (s->position[0][1] == 0 && (*c == 81 || *c == 113))
    {
        *c = 90;
        (s->position[0][0])--;
        s->dir = UP;
    } // left wall behaviour
    else if (s->position[0][1] == WIDTH - 1 && (*c == 68 || *c == 100))
    {
        *c = 115;
        (s->position[0][0])++;
        s->dir = DOWN;
    } // right wall behaviour
    else if (s->position[0][0] == 0 && (*c == 90 || *c == 122))
    {
        (s->position[0][1])++;
        *c = 68;
        s->dir = RIGHT;
    } // top wall behaviour
    else if (s->position[0][0] == HEIGHT - 1 && (*c == 115 || *c == 83))
    {
        (s->position[0][1])++;
        *c = 68;
        s->dir = RIGHT;
    }
    else
    {

        if (kbhit() )
        {

            *c = getch();
            if ((*c == 90 || *c == 122) && s->position[0][0] > 0 && s->dir != DOWN)
            {
                tail_displacement(s);
                (s->position[0][0])--;
                s->dir = UP;
            } // moove up

            else if ((*c == 115 || *c == 83) && s->position[0][0] < HEIGHT - 1 && s->dir != UP)
            {
                tail_displacement(s);
                (s->position[0][0])++;
                s->dir = DOWN;
            } // moove down

            else if ((*c == 81 || *c == 113) && s->position[0][1] > 0 && s->dir != RIGHT)
            {
                tail_displacement(s);
                (s->position[0][1])--;
                s->dir = LEFT;
            } // moove left

            else if ((*c == 68 || *c == 100) && s->position[0][1] < WIDTH - 1 && s->dir != LEFT)
            {
                tail_displacement(s);
                (s->position[0][1])++;
                s->dir = RIGHT;
            } // moove right

        }
        else
        {
            if (s->dir == UP && s->position[0][0] > 0)
            {
                tail_displacement(s);
                (s->position[0][0])--;
                s->dir = UP;
            }

            if (s->dir == DOWN && s->position[0][0] < (HEIGHT - 1))
            {
                tail_displacement(s);
                (s->position[0][0])++;
                s->dir = DOWN;
            }

            if (s->dir == LEFT && s->position[0][1] > 0)
            {
                tail_displacement(s);
                (s->position[0][1])--;
                s->dir = LEFT;
            }

            if (s->dir == RIGHT && s->position[0][1] < (WIDTH - 1))
            {
                tail_displacement(s);
                (s->position[0][1])++;
                s->dir == RIGHT;
            }
        }
    }
}

int main()
{

    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int c;

    snake s;
    s.dir = STATIC;
    s.len = 3;
    s.position[0][0] = y;
    s.position[0][1] = x;
    s.position[1][0] = y;
    s.position[1][1] = x - 1;
    s.position[2][0] = y;
    s.position[2][1] = x - 2;

    while (true)
    {

        system("cls");
        move(&s, &c);
        draw(&s);
        Sleep(120);
    }
}