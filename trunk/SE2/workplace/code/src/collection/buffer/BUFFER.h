#ifndef BUFFER_H
#define BUFFER_H
#include "TYPES.h"

#define BUFFER_SIZE   1024
typedef struct _buffer{
  U32 readIdx;
  U32 writeIdx;
  PU8 bufferbase;
  U32 buffersize;
}BUFFER,*pBUFFER;

void buffer_init(pBUFFER ringBuffer, PU8 bufferspace, U32 buffersize);
void buffer_get(pBUFFER ringBuffer, PU8 outdata);
U8 buffer_put(pBUFFER ringBuffer,U8* data, U16 size);
U8 buffer_isEmpty(pBUFFER ringBuffer);
U8 buffer_isFull(pBUFFER ringBuffer);
U32 buffer_size(pBUFFER ringBuffer);
U16 buffer_nextSize(pBUFFER ringBuffer);

#endif