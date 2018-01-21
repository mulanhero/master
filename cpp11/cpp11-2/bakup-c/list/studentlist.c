/*
 * studentlist.c
 *
 *  Created on: Sep 11, 2012
 *      Author: caoj7
 */
#include<stdio.h>
#include<stdlib.h>
#include"student.h"

STUDENT *head = NULL;

void createList(){
	STUDENT *tmp = head;
	int i;
	for(i = 0; i < 10; i++){
		STUDENT *s = (STUDENT*)malloc(sizeof(STUDENT));
		s->age = i;
		sprintf(s->name, "%d", 10000+i);
		s->next = NULL;
		tmp->next = s;
		tmp = s;
	}
}

void tranvseList(){
	STUDENT* tmp = head->next;
	while(tmp != NULL){
		printf("Name = %s, Age = %d\n", tmp->name, tmp->age);
		tmp = tmp->next;
	}
}



int main(){
	head = (STUDENT*)malloc(sizeof(STUDENT));
	head->next = NULL;
	createList();
	tranvseList();
	return 0;
}

