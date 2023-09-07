/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hed.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:35:07 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/07 21:38:03 by Alex P           ###   ########.fr       */
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


//RESERVATION
int			reservationwindow(void);
WINDOW *createmainwin(int *xMax, int *yMax);
int mainloop(WINDOW *timewin,WINDOW *notesubwin, int xMax);

void updateTimeDisplay(WINDOW *timewin);
void helpbar(WINDOW *timewin);


WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax, int *calwidth);
WINDOW *subwinmiddle(WINDOW* parent, int xMax, int yMax, int calendarwidth);
WINDOW *subwinnote(WINDOW* parent, int xMax, int yMax);



#endif
