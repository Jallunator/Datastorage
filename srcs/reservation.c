/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reservation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:51:22 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/05 13:53:54 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hed.h"

int timeswindow(void)
{
    /*  START OF NCURSES  */
    initscr();
    noecho();
    cbreak();  
    curs_set(0); //Hides cursos

    //COLORS
    use_default_colors();  
    start_color();
    init_pair(1, COLOR_BLACK,  COLOR_WHITE);  //Punainen teksti, valkoinen tausta   


    // Get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    
    //Create menuwindow
    WINDOW * menuwin = newwin(25, 40, yMax - yMax, xMax / 2 - 40);     /* (height, width, starty, startx)  */
    box(menuwin, 0, 0);
    
    //Set window backround colors to 1 pair.
    wbkgd(menuwin, COLOR_PAIR(1));

    //HEADER
    wattron(menuwin, COLOR_PAIR(1));
    mvwprintw(menuwin, 1, 40 / 2 - 8  ,"*_______________*");
    mvwprintw(menuwin, 2, 40 / 2 - 8  ,"|               |");
    mvwprintw(menuwin, 3, 40 / 2 - 8  ,"|  RESERVATION  |");
    mvwprintw(menuwin, 4, 40 / 2 - 8  ,"|               |");
    mvwprintw(menuwin, 5, 40 / 2 - 8  ,"*---------------*");
    wattroff(menuwin, COLOR_PAIR(1));

    refresh();
    wrefresh(menuwin);


    //SHOW CHOICES 
    keypad(menuwin, TRUE); 
    char    *choices[12] = {"Check times","-----------","      ","About us"," --------  ","           ", "Help", " ----  ","   ", "Exit", "  ----   ","   "};
    int     choice;
    int     highlight = 0;

    while (1)
    {
        for (int i = 0 ; i < 12 ; i++ )
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE );
            mvwprintw(menuwin, 8 + i, 40 / 2 - strlen(choices[i]) / 2 , "%s", choices[i]); 
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice)
        {
            case KEY_UP:
            {
                if (highlight == 0)
                    break;
                highlight -= 3;
                break;
            }
            case KEY_DOWN:
            {
                if (highlight == 9)
                    break;
                highlight += 3;
                break;
            }
            default:
                break;
        }
        if (choice == '\n')
            break;
    }
    return (highlight);
}

