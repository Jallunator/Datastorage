/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:50:54 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/07 13:14:54 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hed.h"

void updateTimeDisplay(WINDOW *timewin) {
    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char timeString[50]; // To accommodate a longer time format
    strftime(timeString, sizeof(timeString), "[ %Y-%m-%d  |  %H:%M:%S ]", timeinfo);

    // Print the updated time in the window
    wattron(timewin, COLOR_PAIR(2));
    mvwprintw(timewin, 34, 5 , "Time: %s", timeString);
    wattroff(timewin, COLOR_PAIR(2));
    wrefresh(timewin); // Refresh the window to show changes
}

void helpbar(WINDOW *timewin) {
    // HELP BAR
    wattron(timewin, COLOR_PAIR(2));
    int x = 50;
    char *choices[6] = {"M: Menu","Q: Quit", "Enter: Select", "h: Left", "l: Right", "::Company name::"};
    for (int i = 0; i < 6; i++) {
        mvwprintw(timewin, 34, x, "%s", choices[i]);
        x += 24; // Increment the x-coordinate to print the next choice
    }
    wattroff(timewin, COLOR_PAIR(2));
    wrefresh(timewin); // Refresh the window to show changes
}

WINDOW *createtimewin(int *xMax, int *yMax) {
    initscr();
    noecho();
    cbreak();
    curs_set(0); // Hides cursor

    // COLORS
    use_default_colors();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Get screen size
    getmaxyx(stdscr, *yMax, *xMax);

    // Create timewindow
    char *companyname = "[ COMPANY NAME ]";
    WINDOW *timewin = newwin(35, *xMax, 0, 0); // (Height, Width, Startx, Starty)
    wattron(timewin, COLOR_PAIR(2));
    box(timewin, 0, 0);
    mvwprintw(timewin, 0, *xMax / 2 - strlen(companyname),"%s", companyname);
    wbkgd(timewin, COLOR_PAIR(1)); // Set window background color to default.
    wattroff(timewin, COLOR_PAIR(2));

    refresh();
    wrefresh(timewin);

    return timewin;
}

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

void checkenterchoice(int choice)
{
    






}

int choices_time_help(WINDOW *timewin, int xMax)
{
    helpbar(timewin);
    keypad(timewin, TRUE);

    nodelay(timewin, TRUE);     /* Makes getch non blocking so time can be updated. Multithreading not possible in curses*/ 
    timeout(1000);
    int choice;
    int x = 0;
    int highlight = 0;
    char *choices[4] = {"[ Make appointment ]", "[ Do something ]", "[ Leave review ]", "[ Write notification ]"};

    while (1) {
        choice = wgetch(timewin); 
        for (int i = 0 ; i < 4 ; i++){
            if (i == highlight){
                wattron(timewin, A_REVERSE);}

            
            wattron(timewin, COLOR_PAIR(1));
            x =  i * 47 + 18;   // Position calc for choices
            mvwprintw(timewin, 29, x,"%s", choices[i]);
            wattroff(timewin, COLOR_PAIR(1));
            
            wattroff(timewin, A_REVERSE);
        }
        switch(choice){
            
            //ChoiceCases
            case KEY_RIGHT:{
             
                if (highlight == 3)
                    break;

                highlight++;
                break;
            }
            case KEY_LEFT:{
               
                if (highlight == 0)
                    break;
                highlight--;
                break;
            }

            //CASES HELPBAR
            case 'q':
            case 'Q':{
                return 0;
            }
            case 'M':
            case 'm':{
                return 2;
            }

            default:
                break;

        }
        updateTimeDisplay(timewin);
        //Check what user wants to do.
        if (choice == '\n');
            checkenterchoice(highlight);   // 0. Make appointment 1.Do something 2.Leave review 3.Write notification
    }
    return 0;
}

int reservationwindow(void) {

    //CREATE MAIN WINDOW   ////START CURSES////
    int yMax = 0, xMax = 0;
    WINDOW *timewin = createtimewin(&yMax, &xMax);
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
    int chck = choices_time_help(timewin, xMax);



    delwin(subwinm);
    delwin(subwinn);
    delwin(subwinc);
    delwin(timewin);
    endwin();   ///END CURSES ////
    if (chck == 2)
    {
        menuwin();      //Pressed M and goes back to menu.
    }
    return 0;
}

int main(void) {
timeswindow();
    return 0;
}

