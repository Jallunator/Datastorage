/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storedata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:51:01 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/09 04:19:06 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

void movementData(int *highlight, int move) {
    switch (move) {
        case KEY_UP: // Up arrow key
            if (*highlight > 0) {
                (*highlight)--;
            }
            break;
        case KEY_DOWN: // Down arrow key
            if (*highlight < 3) {
                (*highlight)++;
            }
            break;
        default:
            break;
    }
}

void freshScreen(WINDOW* datawindow, WINDOW *timewin)
{
    int xmax, ymax;
    wclear(datawindow);
    getmaxyx(timewin, ymax, xmax);
    subwincalendar(timewin, xmax, ymax, NULL);
    wrefresh(datawindow);
}

int choiceData(WINDOW *datawin, int choice)  // 0. Student 1. pat 2. emp 3. pass
{
    switch (choice){

        case 0:
            // HERE HANDLE STUDENT STRUCT BINTREE JEA
            mvwprintw(datawin, 10, 10, "PASKA KAKKA");
            wrefresh(datawin);
            return 0;

        default:
            return 0;
    }
}

int storedata(WINDOW *datawindow, WINDOW* timewin)
{
    int move, xMax, yMax, y;
    int highlight = 0;
    char *choices[4] = {"{ Student }", "{ Patient }", "{ Employee }", "{ Passenger }"};
    nodelay(datawindow, TRUE);
    timeout(1000);
    getmaxyx(datawindow, yMax, xMax);
    keypad(datawindow, TRUE);
    
    while (1) {
        y = 2;
        move = wgetch(datawindow); 
        for (int i = 0 ; i < 4 ; i++){
            if (i == highlight){
                wattron(datawindow, A_REVERSE);
            }
            wattron(datawindow, COLOR_PAIR(2));
            mvwprintw(datawindow, y += 4, xMax / 2 - strlen(choices[i]) / 2,"%s", choices[i]);
            wattroff(datawindow, COLOR_PAIR(2));
            
            wattroff(datawindow, A_REVERSE);
        }
        
        movementData(&highlight, move);
        


        //Continue here
        if (move == '\n'){
            freshScreen(datawindow, timewin);
            choiceData(datawindow, highlight);
            return 0;
        }

        updateTimeDisplay(timewin);//Keeps the clock running.
    }   
    return 0;
}

