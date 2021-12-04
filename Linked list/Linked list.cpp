#include <stdio.h>
#include <stdlib.h>

/*	Definition of self-referential struct	*/
typedef struct Student {
	int id;
	struct Student* next;
}student_t;

/*prototypes*/
void insert(student_t** sPtr, int value);
int Delete(student_t** sPtr, int value);
int isEmpty(student_t* sPtr);
void printList(student_t* currentPtr);
void instruction(void);

int main(void) {

	student_t* startPtr = NULL;	// initially no element
	int choice = 0;
	int id;

	while (choice != 4) {
		instruction();
		scanf("%d", &choice);
		switch (choice) {
		case 1: // insert element into the list
			printf("id: ");
			scanf("%d", &id);
			insert(&startPtr, id);
			printList(startPtr);
			break; // end case 1
		case 2: // delete an element from the list
			if (!(isEmpty(startPtr))) { // if the list is not empty
				printf("enter id to be deleted: ");
				scanf("%d", &id);
				if (Delete(&startPtr, id)) {
					printf("%d has been deleted from the list\n", id);
					printList(startPtr);
				} // end if
				else { // value to be deleted is not in the list
					printf("%d not found\n", id);
				} // end else
			} // end if 
			else { // if the list is empty
				printf("List is empty\n");
			} // end else
			break;  // end case 2
		case 3:  // print the list
			printList(startPtr);
			break;  // end case 3
		case 4: // exit
			printf("press any key to exit");
			exit(1);
			break;  // end case 4
		default:
			printf("Invalid selection\n");
			break;
		}  // end switch


	} // end while



	return 0;
}

/*display instructions to the user*/
void instruction(void) {
	printf("1-add element into the list\n");
	printf("2-delete an element from the list\n");
	printf("3-display the list\n");
	printf("4-exit\n");
	printf("enter your selection: ");

}
/* a function to check if the list is empty  */
int isEmpty(student_t* sPtr) {
	if (sPtr == NULL) { // the list is empty
		return 1;
	}
	else {
		return 0;
	}
}

/*Insert a new value into the list in ascending order*/
void insert(student_t** sPtr, int value) {

	student_t* newPtr = NULL; // pointer to new node 
	student_t* previousPtr = NULL; // pointer to previous node
	student_t* currentPtr = NULL; // pointer to current node

	newPtr = (student_t*)malloc(sizeof(student_t)); // create new node on heap

	if (newPtr != NULL) { //  the list is not empty
		newPtr->id = value; // place value in node
		newPtr->next = NULL;
		currentPtr = *sPtr;

		/* a loop to find the correct location*/
		while (currentPtr != NULL && value > currentPtr->id) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		} // end while

		/* insert a new node at the beginning of the list*/
		if (previousPtr == NULL) {
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		} // end if
		else { // insert a new node between previous and current
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		} // end else


	} // end if
	else {
		printf("%d could not be inserted. No space\n", value);
	} // end else


} /*end insert function*/

/* delete an element from the list*/
int Delete(student_t** sPtr, int value) {
	student_t* previousPtr = NULL; // pointer the previous node in the list
	student_t* currentPtr = NULL; // pointer to current node in the list
	student_t* temp = NULL; // temporary node pointer

	/* delete the first element */
	if (value == (*sPtr)->id) {
		temp = *sPtr; // hold the beginning node removed
		*sPtr = (*sPtr)->next;;
		free(temp);
		return value;
	} // end if
	else {
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->next;

		/* a loop to find the correct location on the list */
		while (currentPtr != NULL && currentPtr->id != value) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		} // end while

		/* delete node at currentPtr*/
		if (currentPtr != NULL) {
			temp = currentPtr;
			previousPtr->next = currentPtr->next;
			free(temp);
			return value;
		} // end if

	} // end else

	return NULL;
} // end delete function

void printList(student_t* currentPtr) {

	if (isEmpty(currentPtr)) { // if the list is empty
		printf("The list is empty\n");
	} // end if
	else { // if the list is not empty
		printf("the list:\n");
		while (currentPtr != NULL) {
			printf("%d -->", currentPtr->id);
			currentPtr = currentPtr->next;
		} // end while
	}
	printf("NULL\n");
} // end  print function
