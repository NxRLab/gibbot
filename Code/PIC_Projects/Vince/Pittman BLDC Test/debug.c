#include <libpic30.h>
#include <stdio.h>
#include <p33EP512MC806.h>
#include "initialize.h"
#include "debug.h"

volatile struct buffer_t error_buffer;

/* Add an entry at the end of the error log */
void log_error(char log){
    LinkedList *l; //Create temporary pointer
    l = (LinkedList *) malloc(sizeof (LinkedList)); //Point to allocated memory
    if (l == NULL) {   //If pointer is empty there is no remaining memory
        read_error(); //Drop the last error code
        log = ERR_BUFF_FULL; //Write buffer full error code to error log
        return;
    }

    // add data
    l->c = log;       //Write data to variable in element

    // link
    l->next = NULL; //clear pointer
    if (error_buffer.first == NULL) {//If no elements in uart_buffer
        error_buffer.first = l;      //First and last both point to the only
        error_buffer.last = l;       //  element
    } else {
        error_buffer.last->next = l; //Set next ptr of last element to new element
        error_buffer.last = l;       //Set last ptr to new element
    }

    error_buffer.len++;              //Increment tally
}

/* Returns the first error code from the error log and erases that code from
 * the log. */
char read_error(void){
    unsigned char c = ERR_BUFF_EMPT;
    LinkedList *l;                   //Create temporary pointer

    if (error_buffer.first != NULL) { //If elements remain in the buffer
        l = error_buffer.first;       //Point temp ptr to first element
        error_buffer.first = l->next; //Change pointer to first element to
                                      //point to the second element
        c = l->c;                     //Store value from first element
        free(l);                      //Clear the first element
        error_buffer.len--;           //Decrement tally
    }
    //error_buffer.len=0;
    return c;                        //If no elements remain return ERR_BUFF_EMPT
                                     //otherwise return value in element
}
/* Clears every entry in the error log. */
void clear_error(void){
    LinkedList *l;                      //Create temporary pointer

    while (error_buffer.first != NULL) { //While elements remain in the buffer
        l = error_buffer.first;          //Point temp ptr to first element
        error_buffer.first = l->next;    //Change pointer to first element to
                                         //   point to the second element
        free(l);                         //Clear the first element
    }
    error_buffer.last = NULL;            //Clear pointer to last element
    error_buffer.len = 0;                //Clear tally
}

void print_error(void){
    char e = 0;
    printf("\r");
    while (error_buffer.len > 0){
        e = read_error();
        if(e==ERR_BUFF_FULL){
            printf("Error Buffer Full\r");
        } else if(e==ERR_I2C_READ){
            printf("I2C Read\r");
        } else if(e==ERR_I2C_WRITE){
            printf("I2C Write\r");
        } else if(e==ERR_I2C_START){
            printf("I2C Start\r");
        } else if(e==ERR_I2C_RESTART){
            printf("I2C Restart\r");
        } else if(e==ERR_I2C_STOP){
            printf("I2C Stop\r");
        } else if(e==ERR_I2C_ADDNACK1){
            printf("I2C Add Nack\r");
        } else if(e==ERR_I2C_ADDNACK2){
            printf("I2C Disconnected\r");
        } else if(e==ERR_I2C_DATANACK){
            printf("I2C Data Nack\r");
        } else if(e==ERR_I2C_BUSY1){
            printf("I2C Busy1\r");
        } else if(e==ERR_I2C_BUSY2){
            printf("I2C Busy2\r");
        } else if(e==ERR_I2C_TBF){
            printf("I2C Tran BF\r");
        } else if(e==ERR_I2C_RCVTMOUT){
            printf("I2C RCV Timeout\r");
        } else if(e==ERR_I2C_RADDNACK){
            printf("I2C Restart Address Nack\r");
        } else if(e==ERR_I2C_RADDNACK){
            printf("I2C TRN Timeout\r");
        } else if(e==ERR_I2C_I2COV){
            printf("I2C RCV Overflow\r");
        } else if(e==ERR_I2C_IWCOL){
            printf("I2C TRN Collision\r");
        } else{
            printf("Unknown\r");
        }
    }
}