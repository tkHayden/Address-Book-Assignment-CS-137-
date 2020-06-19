/*
 ============================================================================
 Name        : main.c
 Author      : Tyler
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Contact.h"
#include <string.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	Contact *head = NULL;
	Contact *cursor = NULL;
	int index;
	char indexChar[BUFSIZ + 1];
	char info[BUFSIZ + 1];
	printf("Ready\n");
	while (1) {

		char code = (fgetc(stdin));
		fgetc(stdin);
		switch (code) {
		case 'a':							// add command
			fgets(indexChar, BUFSIZ, stdin);
			fgets(info, BUFSIZ, stdin);
			index = atoi(indexChar);
			info[strlen(info) - 1] = '\0';
			cursor = insertContact(info, &head, index);

			break;

		case 'd':						// delete command
			fgets(indexChar, BUFSIZ, stdin);
			index = atoi(indexChar);
			if (!(head)) {
				printf("Complete\n");
				return 0;
			}
			cursor = getContact(&head, index);
			cursor = deleteContact(&head, cursor);

			break;
		case 'g':				   // get contact command
			fgets(indexChar, BUFSIZ, stdin);
			index = atoi(indexChar);
			cursor = getContact(&head, index);
			printf("%s\n", cursor->data);
			break;
		case 'f':			       // get field command
			fgets(indexChar, BUFSIZ, stdin);
			index = atoi(indexChar);
			fgets(info, BUFSIZ, stdin);
			info[strlen(info) - 1] = '\0';
			cursor = getContact(&head, index);
			getField(cursor, info);
			break;
		case 'n':		          // get list size command
			index = getCount(&head);
			printf("%d\n", index);
			break;
		case 'l':			      // load file to list command
			fgets(info, BUFSIZ, stdin);
			info[strlen(info) - 1] = '\0';
			loadFile(&head, info);

			break;
		case 's':			     // save list to file command
			fgets(info, BUFSIZ, stdin);
			info[strlen(info) - 1] = '\0';
			saveFile(&head, info);
			break;
		case 'e':			   // edit contact command
			fgets(indexChar, BUFSIZ, stdin);
			fgets(info, BUFSIZ, stdin);
			char newField[BUFSIZ + 1];
			fgets(newField, BUFSIZ, stdin);
			index = atoi(indexChar);
			editContact(&head, index, info, newField);
			break;
		case 'o':			   // sort command
			sort(&head);

			break;
		case 'q':			  // quit command
			printf("Complete\n");

			return 0;

		}

	}

	return EXIT_SUCCESS;
}
