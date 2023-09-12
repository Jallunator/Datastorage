/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hed.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:35:07 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 18:52:16 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HED_H
#define HED_H

#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// STRUCTURES//
typedef struct student
{
	char 	*name; //(char *)
	int 	age; //*(int *)
	float 	gradeavg;//*(float *)

	struct student *left;
	struct student *right;

}student;   //tree

typedef struct patient
{
	void	*name;
	void	*diagnosis;
	void	*ssn;

	struct patient *next;

} patient;  // linkedlist


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
int			app_mainloop(WINDOW *timewin,WINDOW *notesubwin,WINDOW *storedata,WINDOW *middlew, student *root);

void handleMovement(int *highlight, int move, int *ret);
int handleChoice(WINDOW *timewin, WINDOW *notesubwin, WINDOW* datawindow,WINDOW *middlew, int highlight, student *root);
void writenote(WINDOW *notewin, WINDOW *timewin);

void updateTimeDisplay(WINDOW *timewin);
void helpbar(WINDOW *timewin);

WINDOW *subwincalendar(WINDOW* parent, int xMax, int yMax, int *calwidth);
WINDOW *subwinmiddle(WINDOW* parent, int xMax, int yMax, int calendarwidth);
WINDOW *subwinnote(WINDOW* parent, int xMax, int yMax);

//data storage
student *storeDataMain(WINDOW* datawindown, WINDOW* timewin, WINDOW *notew, WINDOW *midw);
student *choiceStruct(WINDOW *datawin, WINDOW *timewin, WINDOW *notew, WINDOW *midw, int choice);
void freshScreen(WINDOW* datawindow, WINDOW *timewin, int which, int calwidth);
void movementData(int *highlight, int move);

//STUDENT BTREE CREATE
student *storeStudent(WINDOW *dataw, WINDOW *timew);
int studentAmount(WINDOW *dataw);
int insertStudentBtree(student **root, WINDOW *dataw, int (*cmp)(const char *, const char *), int studi);
student* CreatestudentNode(WINDOW *dataw, int studi);
int getStudentData(WINDOW *dataw, struct student **stud, int studi);
void freeStudents(student *root);

//BTREE SEARCH MID
int searchDataMain(WINDOW *midw, WINDOW *timew, student *root);


#endif
