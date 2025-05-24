/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 9.2.2023

	Description : header file for linked list exercises

*****************************/

#ifndef _H
#define _H

typedef struct node
{
	void *data;
	struct node *next;
} node_t;



node_t *Flip(node_t *head);


int HasLoop(node_t *head);

node_t *FindIntersection(node_t *head_1, node_t *head_2);


#endif
