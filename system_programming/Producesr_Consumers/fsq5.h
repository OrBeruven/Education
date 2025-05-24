#ifndef ___ILRD__OL139_FSQ5__
#define ___ILRD__OL139_FSQ5__

#include <stddef.h>

#define PEEK_ERROR ((size_t)-1)

typedef struct fsq fsq_t; 

enum status
{
    SUCCESS = 0,
    QUEUE_IS_FULL = -1,
    QUEUE_IS_EMPTY = -2
};

fsq_t *FSQCreate(size_t size);
void FSQDestroy(fsq_t *fsq);
void FSQEnqueue(fsq_t *fsq, int input);
void FSQDequeue(fsq_t *fsq);
int FSQPeek(fsq_t *fsq);

#endif
