/* 
 * File:   linkedlist.h
 * Author: ajgriesemer
 *
 * Created on May 13, 2014, 9:12 AM
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H


struct linked_list_t {
    unsigned char c;            //Variable stored in linked list
    struct linked_list_t *next; //Pointer to next element in linked list
};

typedef struct linked_list_t LinkedList; //Shorten declaration of a new struct
                                         //to the syntax LinkedList name

struct buffer_t { //Create buffer type definition
    LinkedList *first; //Pointer to first element in buffer
    LinkedList *last;  //Pointer to last element in buffer
    int len;           //Tally of elements in buffer
};

#endif	/* LINKEDLIST_H */

