/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 04:45:24 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 14:53:20 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

// Main menufunction calls others
void menuwin(void)
{

    /*  START OF NCURSES  */

    //Creates the menuwindow
    WINDOW *menuwin = createmenuwin();

    //Creates choices to menu and ends mainwin.
    int choiced = menuchoices(menuwin);

   //Checks the choice and executes the program behind it. 
    checkchoices(choiced);
}

//Creates the menuwindow.
WINDOW *createmenuwin(void)
{
    initscr();
    noecho();
    cbreak();  
    curs_set(0);

    //COLORS
    use_default_colors();  
    start_color();
    init_pair(1, COLOR_CYAN,  COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    
    //Create menuwindow
    WINDOW * menuwin = newwin(25, 40, yMax - yMax, xMax / 2 - 20);     /* (height, width, starty, startx)  */
    box(menuwin, 0, 0);
    
    //Set window backround colors to 1 pair.
    wbkgd(menuwin, COLOR_PAIR(2));

    //HEADER
    wattron(menuwin, COLOR_PAIR(2));
    mvwprintw(menuwin, 1, 40 / 2 - 8  ,"*_______________*");
    mvwprintw(menuwin, 2, 40 / 2 - 8  ,"|               |");
    mvwprintw(menuwin, 3, 40 / 2 - 8  ,"|   MAIN MENU   |");
    mvwprintw(menuwin, 4, 40 / 2 - 8  ,"|               |");
    mvwprintw(menuwin, 5, 40 / 2 - 8  ,"*---------------*");
    wattroff(menuwin, COLOR_PAIR(2));

    refresh();
    wrefresh(menuwin);

    return (menuwin);
}

//Creates Choices in menu
int menuchoices(WINDOW *menuwin)
{
    keypad(menuwin, TRUE); 
    char    *choices[12] = {"Data Storage","------------","      ","About us"," --------  ","           ", "Help", " ----  ","   ", "Exit", "  ----   ","   "};
    int     choice;
    int highlight = 0;

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
    delwin(menuwin);
    endwin();
    return (highlight);
}

//Checks what choice user made in menu and continues to there
void checkchoices(int choice)
{
    //1.checktime 3.aboutus 6.Help 9.Exit 
    switch(choice)
    {
        //Main program checktimes and make reservation store data.
        // use time() func to free times in time and others
        case 0:
        {
            int x = appointmentwindow(); // Here starts the reservation program. 
            endwin();
            exit(EXIT_SUCCESS);
        }
        
        //Creates about us window do last 
        case 3:{
            endwin();
            exit(EXIT_SUCCESS);
        }
        


        //Help window more like a manual
        case 6:{
            
            endwin();
            createhelpwin();
            exit(EXIT_SUCCESS);

        }
    
        //Exit from menu
        case 9:{
            endwin();
            exit(EXIT_SUCCESS);
        }
        
        //Just incase 
        default:{
            endwin();
            exit(EXIT_FAILURE);
        }
    }
}
