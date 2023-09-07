/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subwindows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:00:00 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/07 14:00:17 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax, int *calwidth) {
    (void)yMax;
    
    int sheight = 24, starty = 2, startx = 2;
    *calwidth = xMax / 3; 
    WINDOW *subwindow = subwin(parent, sheight, *calwidth , starty , startx); // (Parent, subheight, width, starty, startx)
    if (!subwindow)return NULL;
    
    wattron(subwindow, COLOR_PAIR(1));
    box(subwindow, 0,0);
    mvwprintw(subwindow, 0, *calwidth / 2 - 4, "CALENDAR");
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
    mvwprintw(subwindow, 0, swidth / 2 - 4, "NOTIFICATIONS");
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
    mvwprintw(subwindow, 0, swidth / 2 - 8, "YOUR APPOINTMENTS");
    wattroff(subwindow, COLOR_PAIR(1));

    wrefresh(subwindow);
    wrefresh(parent);
    refresh();
    return subwindow;   
}

