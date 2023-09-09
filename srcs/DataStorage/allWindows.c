/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allWindows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:00:00 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/09 03:58:19 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

WINDOW *app_createmainwin(int *xMax, int *yMax) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // COLORS
    use_default_colors();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    // Get screen size
    getmaxyx(stdscr, *yMax, *xMax);

    // Create timewindow
    char *companyname = "[ COMPANY NAME ]";
    WINDOW *timewin = newwin(35, *xMax, 0, 0); // (Height, Width, Startx, Starty)
    wattron(timewin, COLOR_PAIR(1));
    box(timewin, 0, 0);
    mvwprintw(timewin, 0, *xMax / 2 - strlen(companyname),"%s", companyname);
    wbkgd(timewin, COLOR_PAIR(1)); // Set window background color to default.
    wattroff(timewin, COLOR_PAIR(1));

    refresh();
    wrefresh(timewin);

    return timewin;
}

WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax, int *calwidth) {
    (void)yMax;

    int temp = 0;
    if (calwidth == NULL){ // For clear screen function so can be made again !
        calwidth = &temp;
    }
    int sheight = 24, starty = 2, startx = 2;
    *calwidth = xMax / 3; 
    WINDOW *subwindow = subwin(parent, sheight, *calwidth , starty , startx); // (Parent, subheight, width, starty, startx)
    if (!subwindow)return NULL;
    
    wattron(subwindow, COLOR_PAIR(1));
    box(subwindow, 0,0);
    mvwprintw(subwindow, 0, *calwidth / 2 - 6, "| ENTER DATA |");
    wattroff(subwindow, COLOR_PAIR(1));

    wrefresh(subwindow);
    wrefresh(parent);
    refresh();
    return subwindow;
}

WINDOW *subwinnote(WINDOW* parent, int xMax, int yMax)
{
    int sheight = 24, swidth = xMax / 3, starty = 2, startx = xMax - swidth - 2;
    WINDOW *subwindow = subwin(parent, sheight, swidth , starty , startx); // (Parent, subheight, width, starty, startx)
    if (!subwindow)return NULL;
    
    wattron(subwindow, COLOR_PAIR(1));
    box(subwindow, 0,0);
    mvwprintw(subwindow, 0, swidth / 2 - 4, "| NOTES |");
    wattroff(subwindow, COLOR_PAIR(1));

    wrefresh(subwindow);
    wrefresh(parent);
    refresh();
    return subwindow;   
}

WINDOW *subwinmiddle(WINDOW* parent, int xMax, int yMax, int calendarwidth)
{
    int sheight = 24, swidth = xMax / 3 - 2, starty = 2, startx = calendarwidth + 2;
    WINDOW *subwindow = subwin(parent, sheight, swidth , starty , startx); // (Parent, subheight, width, starty, startx)
    if (!subwindow)return NULL;
    
    wattron(subwindow, COLOR_PAIR(1));
    box(subwindow, 0,0);
    mvwprintw(subwindow, 0, swidth / 2 - 8, "| SEARCH DATA |");
    wattroff(subwindow, COLOR_PAIR(1));

    wrefresh(subwindow);
    wrefresh(parent);
    refresh();
    return subwindow;   
}

