#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

void move(snake *s, int *c)
{
    int temp = *c;
    if (s->position[0][1] == 0 && s->position[0][0] == 0)
    {
        if ((*c == 90 || *c == 122))
        {
            (s->position[0][1])++;
            *c = 68;
        }
        else
        {
            (s->position[0][0])++;
            *c = 115;
        }

    } // top left corner
    else if (s->position[0][1] == 0 && s->position[0][0] == (HEIGHT - 1))
    {
        if (*c == 115 || *c == 83)
        {
            (s->position[0][1])++;
            *c = 68;
        }
        else
        {
            (s->position[0][0])--;
            *c = 90;
        }
    } // top right corner
    else if (s->position[0][1] == WIDTH - 1 && s->position[0][0] == 0)
    {
        if ((*c == 68 || *c == 100))
        {
            (s->position[0][0])++;
            *c = 115;
        }
        else
        {
            (s->position[0][1])--;
            *c = 81;
        }
    } // bot left corner
    else if (s->position[0][1] == WIDTH - 1 && s->position[0][0] == HEIGHT - 1)
    {
        if (*c == 115 || *c == 83)
        {
            (s->position[0][1])--;
            *c = 81;
        }
        else
        {
            (s->position[0][0])--;
            *c = 90;
        }
    } // bot right corner
    else if (s->position[0][1] == 0 && (*c == 81 || *c == 113))
    {
        *c = 90;
        (s->position[0][0])--;
    } // left wall behaviour
    else if (s->position[0][1] == WIDTH - 1 && (*c == 68 || *c == 100))
    {
        *c = 115;
        (s->position[0][0])++;
    } // right wall behaviour
    else if (s->position[0][0] == 0 && (*c == 90 || *c == 122))
    {
        (s->position[0][1])++;
        *c = 68;
    } // top wall behaviour
    else if (s->position[0][0] == HEIGHT - 1 && (*c == 115 || *c == 83))
    {
        (s->position[0][1])++;
        *c = 68;
    }
    else
    {

        if (kbhit())
        {
            *c = getch();
            if ((*c == 90 || *c == 122) && s->position[0][0] > 0)
            {
                tail_displacement(s);
                (s->position[0][0])--;
            }//moove up

            if ((*c == 115 || *c == 83) && s->position[0][0] < HEIGHT - 1)
            {
                tail_displacement(s);
                (s->position[0][0])++;
            }//moove down

            if ((*c == 81 || *c == 113) && s->position[0][1] > 0)
            {
                tail_displacement(s);
                (s->position[0][1])--;
            }//moove left

            if ((*c == 68 || *c == 100) && s->position[0][1] < WIDTH - 1)
            {
                tail_displacement(s);
                (s->position[0][1])++;
            }//moove right
        }
        else
        {
            if ((*c == 90 || *c == 122) && s->position[0][0] > 0)
            {
                tail_displacement(s);
                (s->position[0][0])--;
            }

            if ((*c == 115 || *c == 83) && s->position[0][0] < (HEIGHT - 1))
            {
                tail_displacement(s);
                (s->position[0][0])++;
            }

            if ((*c == 81 || *c == 113) && s->position[0][1] > 0)
            {
                tail_displacement(s);
                (s->position[0][1])--;
            }

            if ((*c == 68 || *c == 100) && s->position[0][1] < (WIDTH - 1))
            {
                tail_displacement(s);
                (s->position[0][1])++;
            }
        }
    }
}

int main()
{
    printf("test");
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int c;

    snake s;
    s.len = 8;
    s.position[0][0] = y;
    s.position[0][1] = x;
    s.position[1][0] = y;
    s.position[1][1] = x - 1;
    s.position[2][0] = y;
    s.position[2][1] = x - 2;
    s.position[2][0] = y;
    s.position[3][1] = x - 3;
    s.position[4][0] = y;
    s.position[4][1] = x - 4;
    s.position[5][0] = y;
    s.position[5][1] = x - 5;
    s.position[6][0] = y;
    s.position[6][1] = x - 6;
    s.position[7][0] = y;
    s.position[7][1] = x - 7;

    while (true)
    {

        system("cls");
        move(&s, &c);
        draw(&s);
        Sleep(120);
    }
}