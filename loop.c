#include "funcs.h" 

//If you don't understand some ncurses you should learn it

int main(int argc,char *argv[])
{
    FILE *fp;

    if(argc > 1)
    {
        short time = configt();
        start_ncurses();
        char buff[200];
        short count = 1;
        /*A loop to animate between file,basically it opens the file that you pass them by read
        them and apply color effects,finally it sleep for a second then moves to another file*/
        while (1)
        {
            fp = fopen(argv[count], "r");
            fgets(buff, sizeof(buff), fp);
            attroff(COLOR_PAIR(1));
            init_pair(1, buff[0] - '0', buff[2] - '0');
            attron(COLOR_PAIR(1));

            while (fgets(buff, sizeof(buff), fp) != NULL)
            {
                for (int i = 0; i < strlen(buff); i++)
                {
                    addch(buff[i]);
                }
            }
            refresh();
            sleep(time);
            count++;
            if(count == argc) count = 1;
            clear();
            fclose(fp);
        }
    }
    else
    {
        int *p;
        p = configWH();//It shows a startup message and asks you for WIDTH and HEIGHT and return a pointer
        start_ncurses();
        

        int WIDTH, HEIGHT;
        WIDTH = *p;
        HEIGHT = *(p + 1);

        WINDOW *win = newwin(WIDTH, HEIGHT, 0, 0);

        int ch = '*';
        int fg = 7;
        int bg = 0;

        int input;
        short emode = 0; //Erase mode
        short x=0;short y=0;
        
        int chars[WIDTH][HEIGHT];//2d array for storing your art and what you are typing

        clear_table(&chars[0][0], WIDTH, HEIGHT);

        while(input = getch())//Getting input from user using a while loop
        {  
            switch (input)
            {
                case KEY_UP:
                    if(y > 0)
                    y--;
                    break;
                case KEY_DOWN:
                    if(y < HEIGHT - 1)
                    y++;
                    break;
                case KEY_RIGHT:
                    if(x < WIDTH - 1)
                    x++;
                    break;
                case KEY_LEFT:
                    if(x > 0)
                    x--;
                    break;
                case KEY_DC:
                    clear();
                    clear_table(&chars[0][0], WIDTH, HEIGHT);
                    move(y ,x);
                    refresh();
                    break;
                case KEY_BACKSPACE:
                    emode = (emode == 0) ? 1 : 0;
                    break;
                case 'c'://To change a char if you wish
                    move(0, 0);
                    addstr("Choose you char:");
                    refresh();
                    ch = getch();
                    for(int i = 0;i < 20;i++)
                    {
                        move(0, i);
                        addch(' ');
                    }
                    move(y, x);
                    refresh();
                    break;
                case 'x':
                    move(0, 0);
                    addstr("Now choose your color(FOREGROUND, BACKGROUND:");
                    refresh();
                    fg = getch();
                    addch(' ');
                    bg = getch();
                    refresh();
                    for(int i = 0;i < 45;i++)//Move the cursor to 0,0 then clears the message
                    {
                        move(0, i);
                        addch(' ');
                    }
                    move(y, x);
                    refresh();
                    attroff(COLOR_PAIR(1));
                    fg = fg - '0';
                    bg = bg - '0';
                    init_pair(1, fg , bg);
                    attron(COLOR_PAIR(1));
                    break;
                case 's'://To save a file after hard work,it also quits
                    move(0, 0);
                    char filename[10];
                    addstr("Provide a filename to save");
                    getstr(filename);
                    fp = fopen(filename, "w+");
                    fprintf(fp, "%d %d", fg, bg);
                    fprintf(fp, "\n");

                    for (int i = 0; i < HEIGHT; i++)
                    {
                        for (int j = 0; j < WIDTH; j++)
                        {
                            fputc(chars[i][j], fp);
                        }
                        fputs("\n", fp);
                    }
                    fclose(fp);
                    endwin();
                    exit(0);
                    break;
            }                                          //backspave
            if(emode == 0)//Checking if the user pressed <-- ,however if its zero it means no erase
            {
                addch(ch);
                move(y, x);
                refresh();
                chars[y][x] = ch;

            }
            else
            {
                addch(' ');
                move(y ,x);
                refresh();
                chars[y][x] = ' ';
            }
        }

    }
    endwin();
}
