#ifndef buffer
#define buffer

#include <stm32f429xx.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


/*
**********************************************************************************************************
****Learned from: https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/	****
***************** and https://embedjournal.com/implementing-circular-buffer-embedded-c/	******************
**********************************************************************************************************
*/

// Opaque circular buffer structure
typedef struct circular_buf_t circular_buf_t;
// Handle type, the way to interface with Circular buffer in main
typedef circular_buf_t* cbuf_handle_t;

// Pass in a storage buffer and size 
// Returns a circular buffer handle
cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size);

// Free a circular buffer structure.
// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t me);

// Reset the circular buffer to empty, head == tail
void circular_buf_reset(cbuf_handle_t me);

// Returns true if the buffer is full
bool circular_buf_full(cbuf_handle_t me);

// Returns true if the buffer is empty
bool circular_buf_empty(cbuf_handle_t me);

// Returns the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t me);

// Returns the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t me);

//A function that creates the logic that will be used for managing the forward movement of the pointers in later functions
static void advance_pointer(cbuf_handle_t me);

//A function that creates the logic that will be used for managing the reverse movement of the pointers in later functions
static void retreat_pointer(cbuf_handle_t me);

// Put - continues to add data if the buffer is full
// Old data is overwritten
void circular_buf_put(cbuf_handle_t me, uint8_t data);

// Retrieve a value from the buffer
// Returns 0 on success, -1 if the buffer is empty
int circular_buf_get(cbuf_handle_t me, uint8_t * data);


#endif