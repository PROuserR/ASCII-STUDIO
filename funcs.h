#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>

int* config()
{
    static int size[1];
    puts("Hi welcome to ASCII STUDIO, here you can make ASCII art and make some \
    \namazing animations so you give life to your art to quit simply press ctrl+c,let's start");
    puts("Now enter the size of your border(ROW,COLUMN):");
    scanf("%d", &size[0]);
    putchar(' ');
    scanf("%d", &size[1]);

    return size;
}

void start_ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    start_color();
}

void clear_table(int *table, int WIDTH, int HEIGHT)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        *(table + i) = ' ';
    }
    
}
