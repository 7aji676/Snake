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
void LOOSE_CHECK(snake *s, int *LOST)
{
    if (s->position[0][1] == -1)
    {
        system("cls");
        printf("YOU LOST \n");
        printf("YOUR SCORE");
        exit(0);
    } // left wall behaviour
    else if (s->position[0][1] == WIDTH && s->dir == RIGHT)
    {
        system("cls");
        printf("YOU LOST \n");
        printf("YOUR SCORE");
        exit(0);

    } // right wall behaviour
    else if (s->position[0][0] == -1 && s->dir == UP)
    {
        system("cls");
        printf("YOU LOST \n");
        printf("YOUR SCORE");
        exit(0);
    } // top wall behaviour
    else if (s->position[0][0] == HEIGHT   && s->dir == DOWN)
    {
        system("cls");
        printf("YOU LOST \n");
        printf("YOUR SCORE");
        exit(0);
    }
}
void MOVE_UP(snake *s)
{
    tail_displacement(s);
    (s->position[0][0])--;
    s->dir = UP;
}
void MOVE_DOWN(snake *s)
{
    tail_displacement(s);
    (s->position[0][0])++;
    s->dir = DOWN;
}
void MOVE_RIGHT(snake *s)
{
    tail_displacement(s);
    (s->position[0][1])++;
    s->dir = RIGHT;
}
void MOVE_LEFT(snake *s)
{
    tail_displacement(s);
    (s->position[0][1])--;
    s->dir = LEFT;
}

bool generate(int *x, int *y)
{
}
void move(snake *s, int *c, int *LOST)
{

    if (kbhit())
    {
        *c = getch();
        
        if ((*c == 90 || *c == 122) && s->dir != DOWN)
        {
            MOVE_UP(s);
        } // move up

        else if ((*c == 115 || *c == 83) && s->dir != UP)
        {
            MOVE_DOWN(s);
        } // move down

        else if ((*c == 81 || *c == 113) && s->dir != RIGHT)
        {
            MOVE_LEFT(s);
        } // move left

        else if ((*c == 68 || *c == 100) && s->dir != LEFT)
        {
            MOVE_RIGHT(s);
        } // move right
    }
    else
    {
        
        if (s->dir == UP)
        {
            MOVE_UP(s);
        }

        else if (s->dir == DOWN)
        {
            MOVE_DOWN(s);
        }

        else if (s->dir == LEFT)
        {
            MOVE_LEFT(s);
        }

        else if (s->dir == RIGHT)
        {
            MOVE_RIGHT(s);
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
    int LOST = 0;
    while (LOST == 0)
    {

        system("cls");
        move(&s, &c, &LOST);
        LOOSE_CHECK(&s, &LOST);
        draw(&s);
        Sleep(120);
    }
}