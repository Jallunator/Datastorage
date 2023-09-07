/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:50:54 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/07 23:59:37 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"


/*****************BOTTOM BAR START **/ 

void updateTimeDisplay(WINDOW *timewin) {
    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char timeString[50]; // To accommodate a longer time format
    strftime(timeString, sizeof(timeString), "[ %Y-%m-%d  |  %H:%M:%S ]", timeinfo);

    // Print the updated time in the window
    wattron(timewin, COLOR_PAIR(1));
    mvwprintw(timewin, 34, 5 , "Time: %s", timeString);
    wattroff(timewin, COLOR_PAIR(1));
    wrefresh(timewin);
}
void helpbar(WINDOW *timewin) {
    
    wattron(timewin, COLOR_PAIR(1));
    int x = 50;
    char *choices[6] = {"M: Menu","Q: Quit", "Enter: Select", "h: Left", "l: Right", "::Company name::"};
    for (int i = 0; i < 6; i++) {
        mvwprintw(timewin, 34, x, "%s", choices[i]);
        x += 24; // Increment the x-coordinate to print the next choice
    }
    wattroff(timewin, COLOR_PAIR(1));
    wrefresh(timewin);
}
/*****************BOTTOM BAR END **/



WINDOW *createmainwin(int *xMax, int *yMax) {
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






//HERE MAKE A SUBWINDOW WHERE WRITED AND PRINT IT TO BOARD.
void writenote(WINDOW *notewin)
{
    int yMax, xMax;
    int x = 1;
    int y = 1;
    int i = 0;
    int ch;
    getmaxyx(notewin,yMax,xMax);
    echo();
    
    while (i < xMax * yMax - 1){

    ch = mvwgetch(notewin, y, x);
   
    if (x == xMax - 2){
        x = 1;
        y++;
        continue;
    }
    x++;
    i++;
    };

}


void handleChoice(WINDOW *timewin, WINDOW *notesubwin, int highlight) {
    
    switch (highlight) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            wattron(notesubwin, COLOR_PAIR(2));
            writenote(notesubwin);
            wattroff(notesubwin, COLOR_PAIR(2));
            wrefresh(notesubwin);
            break;
    }
}

void handleMovement(int *highlight, int move, int *ret) {
    switch (move) {
        //MOVEMENT
        case KEY_RIGHT:
        case 'l':
        case 'L':{
            if (*highlight == 3) {
                return;
            }
            *highlight += 1;
            break;
        }
        case KEY_LEFT:
        case 'h':
        case 'H':{
            if (*highlight == 0) {
                return;
            }
            *highlight -= 1;
            break;
        }
        //BOTTOMBAR
        case 'q':
        case 'Q':{
            *ret += 1;
            break;
        }
        case 'm':
        case 'M':{
            *ret +=2;
            break;
        }

    }

}


int mainloop(WINDOW *timewin,WINDOW *notesubwin,int xMax)
{
    helpbar(timewin);
    keypad(timewin, TRUE);

    nodelay(timewin, TRUE);     /* Makes getch non blocking so time can be updated. Multithreading not possible in curses*/ 
    timeout(1000);
    int move;
    int x = 0;
    int ret = 0;
    int highlight = 0;
    char *choices[4] = {"[ Make appointment ]", "[ Do something ]", "[ Leave review ]", "[ Write notification ]"};

    while (1) {
        move = wgetch(timewin); 
        for (int i = 0 ; i < 4 ; i++){
            if (i == highlight){
                wattron(timewin, A_REVERSE);}

            
            wattron(timewin, COLOR_PAIR(1));
            x =  i * 47 + 18;   // Position calc for choices
            mvwprintw(timewin, 29, x,"%s", choices[i]);
            wattroff(timewin, COLOR_PAIR(1));
            
            wattroff(timewin, A_REVERSE);
        }
        
        handleMovement(&highlight, move, &ret);        
        updateTimeDisplay(timewin);

        if (ret) return ret; // Q OR M
        if (move == '\n'){
            handleChoice(timewin, notesubwin, highlight);
        }
    }
    return 0;
}

int reservationwindow(void) {

    //CREATE MAIN WINDOW   ////START CURSES////
    int yMax = 0, xMax = 0;
    WINDOW *timewin = createmainwin(&yMax, &xMax);
    if (time == NULL){
        exit(EXIT_FAILURE);
    }

    // SUBWINDOWS 
    int calendarwidth = 0;
    WINDOW* subwinc = subwincalendar(timewin, yMax, xMax, &calendarwidth);
    if (subwinc == NULL) {
        exit(EXIT_FAILURE);
    }
    WINDOW* subwinn = subwinnote(timewin, yMax, xMax);
    if (subwinn == NULL){
        exit(EXIT_FAILURE);
    }
    WINDOW* subwinm = subwinmiddle(timewin, yMax, xMax, calendarwidth);
    if (subwinm == NULL){
        exit(EXIT_FAILURE);
    }

    //MAIN LOOP FOR INPUT AND TIME AND HELPBAR.
    int ret = mainloop(timewin, subwinn, xMax);


    delwin(subwinm);
    delwin(subwinn);
    delwin(subwinc);
    delwin(timewin);
    endwin();   ///END CURSES ////
    if (ret == 2){
        menuwin();      //Pressed M and goes back to menu.
    }
    return 0;
}
