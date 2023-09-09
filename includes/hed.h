/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hed.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:35:07 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/09 04:18:29 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HED_H
#define HED_H

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>
#include <unistd.h>

typedef struct customer
{
	char 	*name;
	int 	age;
	int 	id;

	struct customer *left;
	struct customer *right;

}customer;

//MAIN MENU
void		menuwin(void);
void		checkchoices(int choice);
int			menuchoices(WINDOW *menuwin);
WINDOW		*createmenuwin(void);


//HELP
void		createhelpwin(void);
int			helpmainloop(WINDOW *helpwin, int xMax, int yMax);

//DATASTORAGE
int			appointmentwindow(void);
WINDOW		*app_createmainwin(int *xMax, int *yMax);
int			app_mainloop(WINDOW *timewin,WINDOW *notesubwin,WINDOW *storedata, int xMax);

void handleMovement(int *highlight, int move, int *ret);
int handleChoice(WINDOW *timewin, WINDOW *notesubwin, WINDOW* datawindow, int highlight);
void writenote(WINDOW *notewin);

void updateTimeDisplay(WINDOW *timewin);
void helpbar(WINDOW *timewin);

WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax, int *calwidth);
WINDOW *subwinmiddle(WINDOW* parent, int xMax, int yMax, int calendarwidth);
WINDOW *subwinnote(WINDOW* parent, int xMax, int yMax);

//data storage
int storedata(WINDOW* datawindown, WINDOW* timewin);
int choiceData(WINDOW *datawin, int choice);
void freshScreen(WINDOW* datawindow, WINDOW *timewin);
void movementData(int *highlight, int move);


#endif
