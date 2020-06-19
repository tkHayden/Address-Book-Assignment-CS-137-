/*
 * Contact.c
 *
 *  Created on: Nov 28, 2019
 *      Author: tylerhayden
 */

#include "Contact.h"
/*
 * Takes in a character array of info and a new Contact.
 * splits the string containing a comma delimited list of contact info and
 * adds them all to the correct info fields
 *
 */
void assignFields(char *info, Contact *newContact) {

	int count = 0;
	char *pStart = info;
	char *fields = NULL;
	int index = 0;
	fields = strtok(info, ",");
	while (fields != NULL) {

		if (count == 0) {
			strcpy(newContact->lastName, fields);
		}
		if (count == 1) {
			strcpy(newContact->firstName, fields);
		}
		if (count == 2) {
			strcpy(newContact->email, fields);
		}
		if (count == 3) {

			strcpy(newContact->number, fields);
		}
		fields = strtok(NULL, ",");

		count++;

	}

}
/*
 * Takes in a string containing a comma delimited list of contact property values
 * Allocates memory for a new Contact, passes the Contact into another function to
 * assign the correct info into the fields.
 * Returns pointer to the Contact
 */
Contact* createContact(char info[]) {

	Contact *newContact = (Contact*) malloc(sizeof(Contact));
	if (newContact) {
		strcpy(newContact->data, info);
		// assigns correct info to each field in the Contact struct
		assignFields(info, newContact);
		newContact->next = NULL;
		newContact->prev = NULL;

	}
	return newContact;
}

// Inserting at the top of the list
Contact* insertAtHead(char *info, pContact *head) {
	Contact *newContact = createContact(info);
	//if list is empty
	if (!(*head)) {
		(*head) = newContact;
		(*head)->prev = NULL;
		return newContact;
	} else {
		newContact->next = (*head);
		(*head)->prev = newContact;
		(*head) = newContact;
	}
	return newContact;
}
/*
 * Takes in char array of contact info, pointer to head of list, and pointer to the index of the Contact
 * that newContact will be inserted
 * Returns pointer to newContact at the correct index
 */
Contact* insertContact(char *info, pContact *head, int index) {
	Contact *cursor = (*head);
	int count = 0;
	Contact *newContact = createContact(info);
	if (index == 0) {
		if (!(*head)) {
			(*head) = newContact;
			(*head)->prev = NULL;
			return newContact;
		}
		newContact->next = (*head);
		(*head)->prev = newContact;
		(*head) = newContact;
		return newContact;
	}

	while (count < index) {
		if (!(cursor->next) && count < index) {
			cursor->next = newContact;
			newContact->prev = cursor;
			return newContact;
		}
		cursor = cursor->next;
		count++;
	}

	//inserting between two contacts
	newContact->next = cursor;
	newContact->prev = cursor->prev;
	cursor->prev->next = newContact;
	cursor->prev = newContact;

	return newContact;
}
// Takes in pointer to head of list and index
// Iterates through the list until it finds the contact at that index
// returns pointer to that contact
Contact* getContact(pContact *head, int index) {
	int position = index;
	Contact *cursor = (*head);
	int counter = 0;
	if (index == 0) {
		return cursor;
	}
	while (counter < index) {
		cursor = cursor->next;
		counter++;
	}
	return cursor;
}
/*
 * Passes in pointer to head of list and current contact
 * Deletes the contact that was passed in
 * Returns pointer to next contact in the list
 */
Contact* deleteContact(pContact *head, Contact *position) {
	Contact *cursor = position;
	// if deleting the head of list
	if (cursor == (*head)) {
		if (!(cursor->next)) {
			cursor = cursor->next;
			(*head) = cursor;
			free(position);
			return cursor;
		}
		cursor = cursor->next;
		cursor->prev = NULL;
		(*head) = cursor;
		free(position);
	}
	// deleting a Contact between two other contacts
	else if (cursor->next) {
		cursor = cursor->next;
		cursor->prev = position->prev;
		position->prev->next = cursor;
		free(position);
	}
	// deleting a Contact at the end of the list
	else if ((!(cursor->next))) {
		cursor = cursor->prev;
		cursor->next = NULL;
		free(position);
	}
	return cursor;

}
// Takes in pointer of Contact and char array of a field
// Get the field from the Contact is asking for.
// Return char pointer of the field
void getField(Contact *position, char *field) {

	if (strstr(field, "lastName")) {
		printf("%s\n", position->lastName);
	} else if (strstr(field, "firstName")) {

		printf("%s\n", position->firstName);
	} else if (strstr(field, "phoneNumber")) {
		printf("%s\n", position->number);
	} else if (strstr(field, "email")) {
		printf("%s\n", position->email);
	} else {
		printf("That field does not exist");
	}

}

// Pass in the head of the list
// return the amount of contacts in the linked list
int getCount(pContact *head) {
	Contact *cursor = (*head);
	int count = 0;
	while (cursor) {
		count++;
		if (!(cursor->next)) {
			return count;
		}
		cursor = cursor->next;
	}
	return count;
}
/*
 * Takes in the head of the Contact list and the file name
 * Reads the file line by line and creates new Contacts
 * Appends to end of the list if list is not empty
 */

void loadFile(pContact *head, char *file) {
	FILE *fp;
	fp = fopen(file, "r");
	// head of new temp contact list
	Contact *tempHead = NULL;
	Contact *cur = NULL;
	int counter = 0;
	char info[BUFSIZ + 1];
	while (fgets(info, BUFSIZ, fp)) {
		// skips first line b/c it only contains headers
		if (counter >= 1) {
			info[strlen(info) - 1] = '\0';
			// if temp contact list is empty
			if (!(tempHead)) {
				cur = createContact(info);
				tempHead = cur;
			} else {
				cur = getContact(&tempHead, counter - 1);
				cur = insertContact(info, &tempHead, counter - 1);
			}

		}
		counter++;
	}
	cur = tempHead;
	// if original Contact list is empty then assign head of temp list to the head of the original list
	if (!(*head)) {
		(*head) = (tempHead);
		// else if original list is not empty, append the temp list to end of the original list
	} else {
		int index = getCount(head) - 1;
		cur = getContact(head, index);
		cur->next = tempHead;
	}
}
/*
 * Takes in a Contact
 * will append all fields of a contact, separated by commas, into a long string
 * set that string to the data field of the Contact
 */
void contactFormat(Contact *cursor) {
	char info[BUFSIZ + 1];
	strcat(info, cursor->lastName);
	strcat(info, ",");
	strcat(info, cursor->firstName);
	strcat(info, ",");
	strcat(info, cursor->email);
	strcat(info, ",");
	strcat(info, cursor->number);
	strcat(info, "\n");
	strcpy(cursor->data, info);
}

/*
 * Takes in head of the Contact list and the name of the file
 * Save each Contact data field to the file
 */
void saveFile(pContact *head, char *file) {
	FILE *fp;

	fp = fopen(file, "w");
	Contact *cursor = (*head);
	// header of the file
	char info[] = "lastName,firstName,email,phoneNumber\n";
	fprintf(fp, "%s", info);
	while (cursor) {
		fprintf(fp, "%s", cursor->data);
		fprintf(fp, "\n");
		if (!(cursor->next)) {
			break;
		}
		cursor = cursor->next;
	}
}
/*
 * Takes in the head of the Contact list, index of the Contact that we will edit, the field we want to edit, and the new info we will put in that field
 * Finds the correct field we want to edit and puts the new info into that field
 */
void editContact(pContact *head, int index, char *field, char *newField) {
	field[strlen(field) - 1] = '\0';
	newField[strlen(newField) - 1] = '\0';
	Contact *cur = getContact(head, index);
	if (strstr(field, "lastName")) {
		strcpy(cur->lastName, newField);
	} else if (strstr(field, "firstName")) {
		strcpy(cur->firstName, newField);
	} else if (strstr(field, "phoneNumber")) {
		strcpy(cur->number, newField);
	} else {
		strcpy(cur->email, newField);
	}
	// Passes that Contact to the contactFormat function to update the data field of Contact
	contactFormat(cur);

}
/*
 * Passes in the head of the Contact list
 * sorts the Contact list in ascending order
 */
void sort(pContact *head) {
	Contact *cursor;
	Contact *cursor2 = NULL;
	int swapping;
	// checks if list is empty
	if (!(head)) {
		return;
	}
	do {
		cursor = (*head);
		swapping = 0;
		while (cursor->next != cursor2) {
			if (strcmp(cursor->data, cursor->next->data) > 0) {
				swap(cursor, cursor->next);
				swapping = 1;
			}
			cursor = cursor->next;
		}
		cursor2 = cursor;
	} while (swapping);
}
// Passes in the two Contacts that are being swapped
// Swaps every field in the Contacts
void swap(Contact *after, Contact *before) {
	char temp[BUFSIZ];
	char data2[BUFSIZ];
	strcpy(temp, after->data);
	strcpy(data2, before->data);
	strcpy(before->data, temp);
	strcpy(after->data, data2);
	assignFields(data2, after);
	assignFields(temp, before);
}

