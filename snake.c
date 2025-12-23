#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_LEN 40

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
   
} Direction;

typedef struct snake
{
    int position[MAX_LEN][2];
    int len;
    Direction dir;
} snake;

void draw(snake *s, int *food_x, int *food_y)
{
    char table[HEIGHT][WIDTH];
    memset(table, ' ', sizeof(table));
    table[*food_y][*food_x] = '@';
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
void LOOSE_CHECK(snake *s, int *score)
{
    if (s->position[0][1] == -1 || s->position[0][1] == WIDTH || s->position[0][0] == -1 || s->position[0][0] == HEIGHT)
    {
        system("cls");
        printf("YOU LOST \n");
        printf("YOUR SCORE %d", (*score));
        exit(0);
    } 
    for (int i = 1; i < s->len; i++)
    {
        if (s->position[0][0] == s->position[i][0] && s->position[0][1] == s->position[i][1])
        {
            system("cls");
            printf("YOU LOST \n");
            printf("YOUR SCORE %d", (*score));
            exit(0);
        }
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

bool check_in(snake *s, int *x, int *y)
{
    for (int i = 0; i < s->len; i++)
    {
        if (s->position[i][0] == *y && s->position[i][1] == *x)
        {
            return true;
        }
    }
    return false;
}

void eat_check(snake *s, int *x, int *y, bool *eaten, int *score)
{
    if (s->position[0][1] == *x && s->position[0][0] == *y)
    {
        *eaten = true;
        s->len++;
        s->position[s->len - 1][0] = s->position[s->len - 2][0];
        s->position[s->len - 1][1] = s->position[s->len - 2][1];
        (*score)++;
    }
}

void generate(snake *s, bool *eaten, int *rand_x, int *rand_y)
{
    if (!*eaten)
    {
        return;
    }
    else
    {
        srand(time(NULL));
        int rx;
        int ry;
        do
        {
            rx = rand() % WIDTH;
            ry = rand() % HEIGHT;
        } while (check_in(s, &rx, &ry));
        *rand_x = rx;
        *rand_y = ry;
        *eaten = false;
    }
}
void move(snake *s, int *c)
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
    int score = 0;

    snake s;
    
    s.len = 1;
    s.position[0][0] = y;
    s.position[0][1] = x;


    int rand_x;
    int rand_y;
    bool eaten = true;
    while (true)
    {

        system("cls");

        move(&s, &c);
        LOOSE_CHECK(&s , &score);
        generate(&s, &eaten, &rand_x, &rand_y);
        eat_check(&s, &rand_x, &rand_y, &eaten, &score);
        draw(&s, &rand_x, &rand_y);
        Sleep(120);
    }
}