/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:39:20 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/07 13:15:12 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

void createhelpwin(void) {
    
    int yMax, xMax;
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
    
    

    char ch = wgetch(helpwin);
    refresh();
    wrefresh(helpwin);
    endwin();

}

