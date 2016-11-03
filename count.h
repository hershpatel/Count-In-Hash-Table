//
//  count.h
//  Assignment2
//
//  Created by Hersh Patel on 10/8/16.
//  Copyright © 2016 Hersh Patel. All rights reserved.
//

#ifndef count_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void insert(long int a);
void rehash();

//linkedlist node
typedef struct node{
	long int data;
	struct node *next;
} node;

//hash table
typedef struct hash {
	node *root;
} hash;

//hash table pointer, length, and unique elements
hash *table;
int length;
int size;

//checks if each line is a hexadecimal address
int filecheck(char* line) {
	if(line[0]!='0' || line[1]!='x') return 0;
	else if(line[2]=='\0') return 0;
	int i;
	for (i=2; i<sizeof(line); i++) if(!isxdigit(line[i])) return 0;
	return 1;
}

//returns hash index
int getKey(long int a) {
	return a%length;
}

//returns load factor
int getLoad() {
	if((((double)size+1)/(double)length)>.5) return 1;
	return 0;
}

//creates the hash table
void createHash() {
	length=1000, size=0;
	table=(hash*)(malloc(sizeof(hash)*length));
	int i=0;
	for(i=0; i<length;i++) table[i].root=NULL;
}

//rehashes hash table
void rehash() {
	length=length*2;
	hash *old;
	old=table;
	table = (hash*)(malloc(sizeof(hash)*length));
	int i=0;
	for(i=0; i<length; i++) table[i].root=NULL;
	int j=0;
	size=-1;
	for(j=0; j<(length/2); j++) {
		node* ptr=(node*)malloc(sizeof(node));
		ptr=old[j].root;
		if(ptr==NULL) continue;
		while(ptr!=NULL) {
			insert(ptr->data);
			ptr=ptr->next;
		}
	}
	return;
}

//inserts values into hash table
void insert(long int a) {
	int key=getKey(a);
	node* ptr=(node*)malloc(sizeof(node));
	ptr=table[key].root;
	if(ptr==NULL) {
		if(getLoad()==1) {
			rehash();
			insert(a);
		}
		size++;
		node* insert=(node*)malloc(sizeof(node));
		insert->data=a;
		table[key].root=insert;
		return;
	}
	while(ptr!=NULL) {
		if(ptr->data==a) return;
		else if(ptr->next==NULL) {
			if(getLoad()==1) {
				rehash();
				insert(a);
			}
			size++;
			node* insert=(node*)malloc(sizeof(node));
			insert->data=a;
			insert->next=table[key].root;
			table[key].root=insert;
			return;
		}
		ptr=ptr->next;
	}
	return;
}




#endif
