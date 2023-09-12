/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:50:54 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 18:58:15 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"
#include <curses.h>

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


// NOTEPAD ******************************************
void writenote(WINDOW *notewin, WINDOW *timewin)
{
    int yMax, xMax;
    static int x = 4;
    static int y = 2;
    static int i = 0;
    int ch;
    getmaxyx(notewin,yMax,xMax);
    keypad(notewin, TRUE); //Enabling specialkeys
    char *exitmsg = "Enter: save     c: clear";
    mvwprintw(notewin, 1, xMax - strlen(exitmsg) - 2,"%s", exitmsg);
    echo();

    while (i < xMax * ((yMax / 2) ) - 10){
        ch = mvwgetch(notewin, y, x);
        if (x == 4)mvwaddch(notewin, y, x - 2, '+'); 
        if (ch == KEY_BACKSPACE || ch == 127) {
            
            if (x >= 4) {
                if (x == 4 && y > 2){
                    y -=2;
                    x = xMax - 1;
                }
                
                if (x == 4 && y == 2)continue;

                mvwaddch(notewin, y, x - 1, ' ');
                x--;
                wrefresh(notewin);
            }

        } 
        else if (ch == '\n'){
            break;  // Exit loop when Enter key is pressed
        }
        else if (ch == 'c'){
            freshScreen(notewin, timewin, 3, 0);
            x = 4;
           // mvwaddch(notewin, y, x - 1, ' ');
            break;
        }
        else{
            
            mvwaddch(notewin, y, x, ch);
            x++;
            
            if (x >= xMax - 3) {
                x = 4;
                y += 2;
            }
            wrefresh(notewin);
        }
        i++;
    }
    mvwprintw(notewin, 1, xMax - strlen(exitmsg) - 2,"                        ");
    noecho();
    keypad(notewin, FALSE);
}
// *************************************************************



// MOVEMENT / LOGIC ***********************************************

// CHOICES
int handleChoice(WINDOW *timewin, WINDOW *notesubwin,WINDOW *datawindow,WINDOW *middlew, int highlight, student *root) {
    int xmax, ymax;
    switch (highlight) {
        case 0:
            root = storeDataMain(datawindow, timewin, notesubwin, middlew);      // RETURNS PTR TO BST ROOT !
            if (!(root)) return 3;   //Error check
            wrefresh(datawindow);
            app_mainloop(timewin, notesubwin, datawindow, middlew, root);
            break;
        case 1:
            searchDataMain(middlew, timewin, root);
            getmaxyx(datawindow, ymax, xmax);
            freshScreen(middlew, timewin, 2, xmax);
            break;
        case 2:
            wattron(notesubwin, COLOR_PAIR(2));
            writenote(notesubwin, timewin);
            wattroff(notesubwin, COLOR_PAIR(2));
            wrefresh(notesubwin);
            break;
    }
    return 0;
}

void handleMovement(int *highlight, int move, int *ret) {
    
    switch (move) {
        //MOVEMENT
        case KEY_RIGHT:
        case 'l':
        case 'L':{
            if (*highlight == 2) {
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
// ****************************************



int app_mainloop(WINDOW *timewin,WINDOW *notesubwin,WINDOW *storedata,WINDOW *middlew, student *root)
{
    helpbar(timewin);
    keypad(timewin, TRUE);
    nodelay(timewin, TRUE);     /* Makes getch non blocking so time can be updated. Multithreading not possible in curses*/ 
    timeout(1000);
    int move;
                //x = xMax / 2 - strlen(choices[i + 1]);
    int ret = 0;
    int highlight = 0;
    char *choices[3] = {"[ Store data ]", "[ Search data ]", "[ Write notification ]"};
    int x;

    while (1) {
        move = wgetch(timewin); 
        for (int i = 0 ; i < 3 ; i++){
            if (i == highlight){
                wattron(timewin, A_REVERSE);
            }
            x = i * 55 + 25;
            wattron(timewin, COLOR_PAIR(1));
            mvwprintw(timewin, 29, x,"%s", choices[i]);
            wattroff(timewin, COLOR_PAIR(1));
            
            wattroff(timewin, A_REVERSE);
        }
        handleMovement(&highlight, move, &ret);        
        updateTimeDisplay(timewin);

        if (ret) return ret; // Q OR M
        if (move == '\n'){
            if(handleChoice(timewin, notesubwin,storedata,middlew, highlight, root))
                return 3; //Had error
        }

    }
    return 0;
}




// MAIN FUNCTION CALLER **************

int appointmentwindow(void) {
    

    student *studentroot = NULL;
    //CREATE MAIN WINDOW   ////START CURSES////
    int yMax = 0, xMax = 0;
    WINDOW *timewin = app_createmainwin(&yMax, &xMax);
    if (timewin == NULL){
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
    int ret = app_mainloop(timewin, subwinn,subwinc, subwinm, studentroot);


    delwin(subwinm);
    delwin(subwinn);
    delwin(subwinc);
    delwin(timewin);
    endwin();   ///END CURSES ////
    if (ret == 2){
        menuwin();      //Pressed M and goes back to menu.
    }
    //FREE MEM AFTER EXITING THE PROGRAM !
    freeStudents(studentroot);
    return 0;
}

// ************************************************************************





