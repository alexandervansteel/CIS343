#include <stdio.h>
#include <stdlib.h>

/* Demonstration of self-referential structures. */

struct linked_list {
  int val;
  struct linked_list * next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT * LINK;

// function prototypes/declarations
LINK create_list(int [], int);
int count_items(LINK);
void print_list(LINK);

int maiin() {
  int a[] = {5,10,15,20,25,30};
  LINK head;
  head = create_list(a,6);
  printf("The linked list has %d elements.\n",count_items(head));
  printf("the list is\n");
  print_list(head);
  printf("\n");
  return 0;
}
/*
 * OUTPUT:
 * "The linked list has 6 elements."
 * "the list is"
 * "5-->10-->15-->20-->25-->30-->NULL"
 */

/*
 * Creates a linked list from the the array of ints a with n being the size
 * of the list.
 */
LINK create_list(int a[],int n) {
  // initializes a list with a nothing before the first item, but something
  // following
  LINK head = NULL, tail;
  int i;
  // checks to see if the list has a size of at least 1
  if(n>=1) {
    // allocates the size of the ELEMENT from memory into the head
    // using a pointer
    head = malloc(sizeof(ELEMENT));
    // points to the value of head and assigns it the value of the first item
    // in the array
    head->val = a[0];
    // makes the head into the tail to increment down the list
    tail = head;
    // loops through the array and incremnts down the linked list
    for(i=1;i<n;i++) {
      // takes the tail's pointer to the next node, and allocates
      // the memory for it
      tail->next = malloc(sizeof(ELEMENT));
      //increments to the next item of the list
      tail = tail->next;
      // assigns the value from the array to the linked list node
      tail->val = a[i];
    }
  // makes the last node in the list point to null to end the list
  tail->next = NULL;
  }
  // returns the first item of the list
  return head;
}

/*
 * Counts the items of a linked list.
 */
int count_items(LINK head) {
  // checks if the list is null
  if(head==NULL) {
    printf("NULL");
  } else {
    // recursively counts the list. when it reaches the end it prints null
    return (1 + count_items(head->next));
  }
}

/*
 * Prints the Linked list.
 */
void print_list(LINK head) {
  // checks prints null if the head returns null
  if(head==NULL) {
    printf("NULL");
  } else {
    // prints the data from the current node in the list
    printf("%d -->", head->val);
    // recursively increments through the list
    print_list(head->next);
  }
}
