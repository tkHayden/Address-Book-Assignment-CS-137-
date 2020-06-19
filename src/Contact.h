
/*
 * Contact.h
 *
 *  Created on: Nov 28, 2019
 *      Author: tylerhayden
 */

#ifndef CONTACT_H_
#define CONTACT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contact Contact;
typedef struct contact *pContact;
 struct contact {
	char data[BUFSIZ +1];
    char lastName[255];
    char firstName[255];
    char email[255];
    char number[255];
     Contact *next;
     Contact *prev;
};

void assignFields(char * info, Contact *newContact);
Contact *createContact(char *info);
Contact *insertContact(char info[], pContact *head,int index);
Contact *insertAtHead(char info[], pContact *head);
Contact *getContact(pContact *head,int index);
Contact *deleteContact (pContact *head, Contact *position);
void getField (Contact *position, char field[]);
int getCount (pContact *head);
void loadFile (pContact *head, char file []);
void saveFile(pContact *head, char *file);
void contactFormat(Contact *cursor);
void editContact(pContact *head, int index, char *field, char *newField);
void swap(Contact *after, Contact *before);
void sort(pContact *head);
#endif /* CONTACT_H_ */

