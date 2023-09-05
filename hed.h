/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hed.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex P <alexxpyykonen@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:35:07 by Alex P            #+#    #+#             */
/*   Updated: 2023/09/05 18:49:16 by Alex P           ###   ########.fr       */
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

void		menuwin(void);
void		checkchoices(int choice);
int			menuchoices(WINDOW *menuwin);
int			timeswindow(void);
WINDOW		*createmenuwin(void);

#endif
