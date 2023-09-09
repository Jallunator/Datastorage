/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:39:20 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/08 16:07:01 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

int helpmainloop(WINDOW *helpwin, int xMax, int yMax)
{
    int ch;

    while (1)
    {
        ch = wgetch(helpwin);

        if (ch == 'q' || ch == 'Q'){
            endwin();
            exit(EXIT_SUCCESS);
        }
        else if (ch == 'm' || ch == 'M'){
            return 2;
        }


    }
    return 0;
    
}

void createhelpwin(void) {
    
    int yMax, xMax, ret = 0;
    initscr();
    noecho();
    cbreak();
    curs_set(0); // Hides cursor

    // COLORS
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    // Get screen size
    getmaxyx(stdscr, yMax, xMax);

    // Create timewindow
    char *companyname = "[ MANUAL / HELP ]";
    WINDOW *helpwin = newwin(35, xMax, 0, 0); // (Height, Width, Startx, Starty)
    wattron(helpwin, COLOR_PAIR(1));
    box(helpwin, 0, 0);
    mvwprintw(helpwin, 0, xMax / 2 - strlen(companyname),"%s", companyname);
    wbkgd(helpwin, COLOR_PAIR(1)); // Set window background color to default.
    wattroff(helpwin, COLOR_PAIR(1));
    
    
    ret = helpmainloop(helpwin, xMax, yMax);
    
    refresh();
    wrefresh(helpwin);
    endwin();
    if (ret == 2){
        menuwin();   //M goes back to menu.
    }

}

