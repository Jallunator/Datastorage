/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   studentBtreeSearch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 02:23:13 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 16:27:13 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"
#include <curses.h>

student *searchStudent(char *name, int age, student *root, WINDOW *midw)
{
    if (root == NULL)
	return NULL;
    wrefresh(midw);
    searchStudent(name, age, root->left, midw);

    if ((strcmp(root->name, name) == 0) && age == root->age)
	return root;

    searchStudent(name, age, root->right, midw);

}

void foundStudent(student *student, WINDOW *midw)
{
    mvwprintw(midw, 7, 8, "Student found !");
    mvwprintw(midw, 8, 8, "---------------");
    mvwprintw(midw, 9, 8,"Name: %s ", student->name);
    mvwprintw(midw, 11, 8,"Age: %d" , student->age);
    mvwprintw(midw,  13, 8,"Grade average: %.2f", student->gradeavg);
    mvwprintw(midw, 14, 8,"_________________________________Press Enter.");
    wrefresh(midw);
    int ch;
    while ((ch = wgetch(midw)) != '\n');
}

int getInfo(char **name , int *age, WINDOW *midw)
{
    int xMax, yMax;
    char buff[40];
    getmaxyx(midw, yMax, xMax);

    //HEADER
    mvwprintw(midw, 1, xMax / 2 - 12,":::::::::::::::::::::");
    mvwprintw(midw, 2, xMax / 2 - 12,"::: SEARCH STUDENT ::");
    mvwprintw(midw, 3, xMax / 2 - 12,":::::::::::::::::::::");
    wrefresh(midw);
    nodelay(midw, FALSE);
    echo();
    
    //NAME
    mvwprintw(midw, 9, 8,"Name of student: ");
    wgetnstr(midw, buff, 39);
    *name = strdup(buff);
    if (*name == NULL){
	mvwprintw(midw, 9, 8, "Error in allocating memory for name! Press key.");
	wrefresh(midw);
	wgetch(midw);
	return 3;
    }

    //AGE
    mvwprintw(midw, 11, 8, "Enter age of the student: ");
    wscanw(midw, "%d", age);
    mvwprintw(midw, 9, 8,"                                           ");
    mvwprintw(midw, 11, 8, "                                          ");
    wrefresh(midw);
    noecho();
    return 0;
}



int searchDataMain(WINDOW *midw, WINDOW *timew, student *root)
{
    student *answ = NULL;
    int	    xMax, yMax, age;
    char    *name;
    nodelay(midw, FALSE);
    wattron(midw, COLOR_PAIR(2));
    if (root == NULL){
	mvwprintw(midw, 5, 8,"There is nothing to search! ---Press enter." );
	wrefresh(midw);
	int ch;
	while ((ch =wgetch(midw)) != '\n');
	return 0;
    }
   if(getInfo(&name, &age, midw))
	return 3;

    answ = searchStudent(name, age, root, midw);
    
    if (answ){
	foundStudent(answ, midw);
	wrefresh(midw);
    }
    else{
	mvwprintw(midw, 8, 8, "There is no student matching you description.");
	mvwprintw(midw, 10, 8, "-------Press enter----------");
	wrefresh(midw);
	int ch;
	while ((ch = wgetch(midw)) != '\n');
    }
    free(name);
    wattroff(midw, COLOR_PAIR(2));
    return 0;
}



