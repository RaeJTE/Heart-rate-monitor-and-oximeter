#include "buffer.h"

// The hidden definition of our circular buffer structure
struct circular_buf_t {
	uint8_t * buffer;
	size_t head;	//The pointer that stores data in the buffer
	size_t tail;	//The pointer that reads data out of the buffer
	size_t max; //of the buffer
	bool full;
};

//Initialises buffer
cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size)
{
	assert(buffer && size);

	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
	assert(cbuf);

	cbuf->buffer = buffer;
	cbuf->max = size;
	circular_buf_reset(cbuf);

	assert(circular_buf_empty(cbuf));

	return cbuf;
}

//Destroys buffer container
void circular_buf_free(cbuf_handle_t me)
{
	assert(me);
	free(me);
}

//Puts buffer into an empty state
void circular_buf_reset(cbuf_handle_t me)
{
    assert(me);

    me->head = 0;
    me->tail = 0;
    me->full = false;
}

//Function to check if the buffer is full
bool circular_buf_full(cbuf_handle_t me)
{
	assert(me);
	return me->full;
}

//Function to check if the buffer is empty
bool circular_buf_empty(cbuf_handle_t me)
{
	assert(me);
	return (!me->full && (me->head == me->tail));
}

//Function to check the max size of the buffer
size_t circular_buf_capacity(cbuf_handle_t me)
{
	assert(me);
	return me->max;
}

//Returns number of elements currently stored in the buffer
size_t circular_buf_size(cbuf_handle_t me)
{
	assert(me);
	size_t size = me->max;
	if(!me->full)
	{
		if(me->head >= me->tail)
		{
			size = (me->head - me->tail);
		}
		else
		{
			size = (me->max + me->head - me->tail);
		}
	}
	return size;
}

//A function that creates the logic that will be used for managing the forward movement of the pointers in later functions
static void advance_pointer(cbuf_handle_t me)
{
	assert(me);
	if(me->full)
   	{
		if (++(me->tail) == me->max) 
		{ 
			me->tail = 0;
		}
	}
	if (++(me->head) == me->max) 
	{ 
		me->head = 0;
	}
	me->full = (me->head == me->tail);
}

//A function that creates the logic that will be used for managing the reverse movement of the pointers in later functions
static void retreat_pointer(cbuf_handle_t me)
{
	assert(me);
	me->full = false;
	if (++(me->tail) == me->max) 
	{ 
		me->tail = 0;
	}
}

// Put - continues to add data if the buffer is full
// Old data is overwritten
void circular_buf_put(cbuf_handle_t me, uint8_t data)
{
	assert(me && me->buffer);
   me->buffer[me->head] = data;
   advance_pointer(me);
}

//Reads from circular buffer - if empty we do not read a value or advance the pointer
int circular_buf_get(cbuf_handle_t me, uint8_t * data)
{
    assert(me && data && me->buffer);
    int r = -1;
    if(!circular_buf_empty(me))
    {
        *data = me->buffer[me->tail];
        retreat_pointer(me);
        r = 0;
    }
    return r;
}