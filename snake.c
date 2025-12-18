#include <stdio.h>
#include <stdbool.h>

#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_LEN 40
typedef struct snake
{
    int position[MAX_LEN][2];
    int len;
} snake;

void draw(snake *s)
{
    
    printf("##########################################\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("#");
        for (int j = 0; j < WIDTH; j++)
        {
            for (int n = 0; n < s->len; n++)
            {

                if (s->position[n][0] == i && s->position[n][1] == j)
                {
                    printf("o");
                    
                    break;
                }
            }
        }
        printf("#");
        printf("\n");
    }
    printf("##########################################");
}

void move(int *x, int *y, int *c)
{
    if (*x == 0 && *y == 0)
    {
        if ((*c == 90 || *c == 122))
        {
            (*x)++;
            *c = 68;
        }
        else
        {
            (*y)++;
            *c = 115;
        }

    } // top left corner
    else if (*x == 0 && *y == (HEIGHT - 1))
    {
        if (*c == 115 || *c == 83)
        {
            (*x)++;
            *c = 68;
        }
        else
        {
            (*y)--;
            *c = 90;
        }
    } // top right corner
    else if (*x == WIDTH - 1 && *y == 0)
    {
        if ((*c == 68 || *c == 100))
        {
            (*y)++;
            *c = 115;
        }
        else
        {
            (*x)--;
            *c = 81;
        }
    } // bot left corner
    else if (*x == WIDTH - 1 && *y == HEIGHT - 1)
    {
        if (*c == 115 || *c == 83)
        {
            (*x)--;
            *c = 81;
        }
        else
        {
            (*y)--;
            *c = 90;
        }
    } // bot right corner
    else if (*x == 0 && (*c == 81 || *c == 113))
    {
        *c = 90;
        (*y)--;
    } // left wall behaviour
    else if (*x == WIDTH - 1 && (*c == 68 || *c == 100))
    {
        *c = 115;
        (*y)++;
    } // right wall behaviour
    else if (*y == 0 && (*c == 90 || *c == 122))
    {
        (*x)++;
        *c = 68;
    } // top wall behaviour
    else if (*y == HEIGHT - 1 && (*c == 115 || *c == 83))
    {
        (*x)++;
        *c = 68;
    }
    else
    {

        if (kbhit())
        {
            *c = getch();
            if ((*c == 90 || *c == 122) && *y > 0)
            {
                (*y)--;
            }

            if ((*c == 115 || *c == 83) && *y < HEIGHT - 1)
            {
                (*y)++;
            }

            if ((*c == 81 || *c == 113) && *x > 0)
            {
                (*x)--;
            }

            if ((*c == 68 || *c == 100) && *x < WIDTH - 1)
            {
                (*x)++;
            }
        }
        else
        {
            if ((*c == 90 || *c == 122) && *y > 0)
            {
                (*y)--;
            }

            if ((*c == 115 || *c == 83) && *y < (HEIGHT - 1))
            {
                (*y)++;
            }

            if ((*c == 81 || *c == 113) && *x > 0)
            {
                (*x)--;
            }

            if ((*c == 68 || *c == 100) && *x < (WIDTH - 1))
            {
                (*x)++;
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
    s.len = 2;
    s.position[0][0] = x;
    s.position[0][1] = y;
    s.position[1][0] = x - 1;
    s.position[1][1] = y - 1;

    while (true)
    {
        system("cls");
        move(&x, &y, &c);

        draw(&s);
        Sleep(120);
    }
}