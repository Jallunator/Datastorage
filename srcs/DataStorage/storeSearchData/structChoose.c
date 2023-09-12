/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structChoose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:51:01 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 18:55:57 by Alex P           ###   ########.fr       */
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

student *choiceStruct(WINDOW *datawin,WINDOW *timewin, WINDOW *notew, WINDOW *midw, int choice)  // 0. Student 1. pat 2. emp 3. pass
{
    student *root = NULL;
    switch (choice){
        
        //STUDENT STRUCT BTREE/////
        case 0:
            root = storeStudent(datawin, timewin);
            if (!root)
                return NULL;
            wrefresh(datawin);
            return root;



        //OTHERS NON
        default:
            freshScreen(datawin, timewin,1, 0);
            app_mainloop(timewin, notew, datawin, midw ,root);
    }       
    

    return NULL;
}

student *storeDataMain(WINDOW *datawindow, WINDOW* timewin, WINDOW *notew, WINDOW *midw)
{
    int move, xMax, yMax, y;
    int highlight = 0;
    char *choices[4] = {"{ Student }", "{ Patient }", "{ Employee }", "{ Passenger }"};
    student *root = NULL;
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
            freshScreen(datawindow, timewin, 1, 0);
            root = choiceStruct(datawindow,timewin,notew,midw,highlight);
            return root;
        }

        updateTimeDisplay(timewin);//Keeps the clock running.
    }   
    return 0;
}

