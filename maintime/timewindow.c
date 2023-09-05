/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reservation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:51:22 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/05 18:24:47 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hed.h"

int timeswindow(void);



int main(void)
{

    timeswindow();
    


    return 0;
}

void helpbar(WINDOW *timewin)
{
    //HELP BAR
    wattron(timewin, COLOR_PAIR(1));
    int x = 10; 
    char *choices[6] = {"M: Menu","Q: Quit", "k: Up", "j: Down", "h: Left", "l: Right"};
    for (int i = 0; i < 6; i++) {
        mvwprintw(timewin, 34, x, "%s", choices[i]);
        x += 20; // Increment the x-coordinate to print the next choice
    }
    wattroff(timewin, COLOR_PAIR(1));
    wrefresh(timewin); // Refresh the window to show changes

}

void timebar(WINDOW *timewin) {
    while (1) {
        // Get the current time
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        char timeString[50]; // To accommodate a longer time format
        strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Clear the previous time display
        wattron(timewin, COLOR_PAIR(1));
        mvwprintw(timewin, 30, 10, "Time:                    "); // Clear previous time
        wattroff(timewin, COLOR_PAIR(1));

        // Print the updated time in the window
        wattron(timewin, COLOR_PAIR(1));
        mvwprintw(timewin, 30, 10, "Time: %s", timeString);
        wattroff(timewin, COLOR_PAIR(1));
        wrefresh(timewin); // Refresh the window to show changes
        refresh();

        // Sleep for 1 second before updating again
        napms(1000); 
    }

}

void bottombar(WINDOW *timewin)
{
    //Time and date bar.
    timebar(timewin);
    
    //Guide for controls
    helpbar(timewin);
    
}

WINDOW *createtimewin(int *xMax, int *yMax){

    initscr();
    noecho();
    cbreak();
    curs_set(0); // Hides cursor

    // COLORS
    use_default_colors();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    // Get screen size
    getmaxyx(stdscr, *yMax, *xMax);
    
    // Create timewindow
    WINDOW *timewin = newwin(35, *xMax, 0, 0); // (Height, Width, Startx, Starty)
    wattron(timewin, COLOR_PAIR(1));
    box(timewin, 0, 0);
    wbkgd(timewin, COLOR_PAIR(0)); // Set windowbackground color to default.
    wattroff(timewin, COLOR_PAIR(1));

    refresh();
    wrefresh(timewin);
    
    
    return (timewin);
}

WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax )
{

    (void)yMax;
    int sheight = 18 , swidth = xMax / 2, starty = 2, startx = 2;
    WINDOW *subwindow = subwin(parent, sheight, swidth , starty , startx);       //(Parent, subheight, width, starty, startx)
    box(subwindow, 0,0);
    
    wrefresh(subwindow);
    wrefresh(parent);
    refresh();
    return (subwindow);
}


// This is the main calls all others
int timeswindow(void) 
{
    int yMax = 0, xMax = 0;
    //Creates the window
    WINDOW *timewin = createtimewin(&yMax, &xMax);
    
    // BOTTOM BAR help and time
    bottombar(timewin);

    //Subwindow Calendar
    WINDOW* subwin = subwincalendar(timewin, yMax, xMax);
    
    (void)subwin;


    int choice;
    while (1) {
        choice = wgetch(timewin);
        if (choice == 'Q' || choice == 'q') {
            break; // Exit the loop on 'Q' or 'q'
        }
    }

    endwin();
    return choice;
}

