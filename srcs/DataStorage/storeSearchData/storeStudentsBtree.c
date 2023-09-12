/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeStudentsBtree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:47:54 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/12 18:53:37 by Alex P           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hed.h"

void freeStudents(student *root) {
	if (root == NULL)
		return;

	// Recur left subtree
	freeStudents(root->left);

	// Recur right subtree
	freeStudents(root->right);

	// Free memory for the current node
    // Postfix
    free(root->name);
	free(root);
}

// CONTINUE HERE !
int getStudentData(WINDOW *dataw, struct student **stud, int studi)
{
    student *node = *stud;      //easier to handle
    int xMax, yMax;
    getmaxyx(dataw, yMax, xMax);
    char buff[40]; 
    int ch;

    nodelay(dataw, FALSE);      // Makes getstr blocking so can be used
    keypad(dataw, TRUE);
    mvwprintw(dataw, 2, xMax / 2 - 10, "::::::::::::::::::::");
    mvwprintw(dataw, 3, xMax / 2 - 10, ":: STUDENT [ %d ]  ::", studi);
    mvwprintw(dataw, 4, xMax / 2 - 10, "::::::::::::::::::::");
    mvwprintw(dataw, 8, 8, "Name: ");
    
    //NAME
    echo();
    wgetnstr(dataw, buff, 39);
    node->name = strdup(buff);
    if (!(node->name))return 3;
    memset(buff, '\0', sizeof(buff) / sizeof(buff[0]));

    //AGE
    agenotvalid:
	mvwprintw(dataw, 12, 8, "Age: ");
	wgetnstr(dataw, buff, 39);
	while((node->age = atoi(buff)) <= 0){
	    mvwprintw(dataw, 12 , xMax / 2, "ENTER VALID NUMBER!"); 
	    memset(buff, '\0', (sizeof(buff) / sizeof(buff[0])));
	    goto agenotvalid;
    }
    memset(buff, '\0', (sizeof(buff) / sizeof(buff[0])));             //fix echo bug works fine but lefts old echo

    //GRADEAVG
    avgnotvalid:
	mvwprintw(dataw, 16, 8, "GradeAverage: ");
	wgetnstr(dataw, buff, 39);
	while(((node->gradeavg = atof(buff)) <= 0)){
	    mvwprintw(dataw, 16, xMax / 2, "ENTER VALID NUMBER!");
	    memset(buff, '\0', (sizeof(buff) / sizeof(buff[0])));
	    goto avgnotvalid;
	}
    noecho();
    wrefresh(dataw);
    return 0;
}

student* CreatestudentNode(WINDOW *dataw, int studi)
{
    student     *newnode = (student *)malloc(sizeof(student));
    if (!newnode){puts(strerror(errno)); return NULL;}
    
    //DATA TO STRUCT
    if (getStudentData(dataw, &newnode, studi))
        return NULL;

    newnode->left = NULL;
    newnode->right = NULL;

   return (newnode); 
}

//BST CREATED WITH CMP NAMES
int insertStudentBtree(student **root, WINDOW *dataw, int (*cmp)(const char *, const char *), int studi)
{
    student *current = *root;
    student *parent = NULL;
    student *newnode = CreatestudentNode(dataw, studi);
    if (!newnode) return 3;
    
    //FIND NODES PLACE
    while (current){
	parent = current;
	if((*cmp)(current->name, newnode->name) >= 0)
	    current = current->left;
	else
	    current = current->right;

    }
    
    //COMPARE WITH PARENT 
    if (parent == NULL)// Tree is empty
	*root = newnode;
    
    else if ((*cmp)(parent->name, newnode->name) >= 0)
	    parent->left = newnode;
    else
	parent->right = newnode;

    return 0;
}

int studentAmount(WINDOW *dataw)
{
    int studentcount = 0;
    char buff[20];

    //GET AMOUNT OF STUDENTS
    echo();
    nodelay(dataw, FALSE);
    mvwprintw(dataw, 5, 8, "How many students? ");
    wgetnstr(dataw, buff, 19);
    noecho();

    if ((studentcount = atoi(buff)) <= 0)
	return -1;
    
    return studentcount;
}

//MAIN CALLING OTHERS
student *storeStudent(WINDOW *dataw, WINDOW *timew)
{
    student *list = NULL;
    int i = 0;
    int ch;
    int studentcount;
    wattron(dataw, COLOR_PAIR(2));
    //GET AMOUNT OF STUDENTS
    while((studentcount = studentAmount(dataw)) < 0){

	mvwprintw(dataw, 5, 8, "Enter valid number! ---Press Enter--");
	while ((ch = wgetch(dataw)) != '\n');
	freshScreen(dataw, timew, 1, 0);
    }
    freshScreen(dataw, timew, 1, 0);
    
    //INSERT STUDENTS DATA TO STRUCTS
    while (i++ < studentcount){
	
	if((insertStudentBtree(&list,dataw, &strcmp, i) == 3)){
	    return NULL;
	}
	if (list == NULL) return NULL;

	freshScreen(dataw, timew, 1, 0);

    }
    wattroff(dataw, COLOR_PAIR(2));


    //freeStudents(list);
    return list;
}

