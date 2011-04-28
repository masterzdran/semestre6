#include "BUFFER.h"
#include <stdio.h>
#define IS_EMPTY(A)                ((A)->readIdx == (A)->writeIdx)
#define IS_FULL(A)                 (((((A)->w + 1) >= (A)->buffersize)?0:(A)->readIdx + 1) == (A)->writeIdx)
#define SET_THE_RECORD(A,B)           {(*(A))++;if((*(A)) >= (B)){*(A) = 0;}}


void buffer_init(pBUFFER ringBuffer, U32 buffersize){
    ringBuffer->readIdx = ringBuffer->writeIdx = 0;
    ringBuffer->buffersize = buffersize;
}

U8 buffer_get(pBUFFER ringBuffer){
  U8 c;
  if(buffer_isEmpty(ringBuffer)){printf ("is empty;");return 0;}
  c=ringBuffer->bufferbase[ringBuffer->readIdx];
  ringBuffer->bufferbase[ringBuffer->readIdx] = '-';
  ringBuffer->readIdx++;
  /*SET_THE_RECORD(&(ringBuffer->readIdx),ringBuffer->buffersize);
  */
  if (ringBuffer->readIdx >= ringBuffer->buffersize) {ringBuffer->readIdx=0;}
  
  return c;
}

void buffer_put(pBUFFER ringBuffer,U8 c){
  if (buffer_isFull(ringBuffer)) {printf ("is full;");return;}
  ringBuffer->bufferbase[ringBuffer->writeIdx] = c;
  ringBuffer->writeIdx++;
  /*SET_THE_RECORD(&(ringBuffer->writeIdx),ringBuffer->buffersize);*/
  if (ringBuffer->writeIdx >= ringBuffer->buffersize) {ringBuffer->writeIdx=0;}
}


U8 buffer_isEmpty(pBUFFER ringBuffer){ return ringBuffer->readIdx == ringBuffer->writeIdx;}

  
U32 buffer_size(pBUFFER ringBuffer){
  return (ringBuffer->readIdx > ringBuffer->writeIdx)?(ringBuffer->buffersize - ( ringBuffer->readIdx - ringBuffer->writeIdx) + 1 ):(ringBuffer->writeIdx - ringBuffer->readIdx + 1);
}
  
  
U8 buffer_isFull(pBUFFER ringBuffer){
  int aux = ringBuffer->writeIdx + 1;
  if (aux  >= ringBuffer->buffersize){aux=0;}
  return (aux == ringBuffer->readIdx);
}


/*
#define IN_SIZE   16
#define OUT_SIZE  16
int main (){
  BUFFER in;
  BUFFER out;
  U8 inBuffer[IN_SIZE];
  U8 outBuffer[OUT_SIZE];
  U8 txt[20] = "Long Live the Queen";
  U8 idx=0;
  U8 c=0;
  in.bufferbase=(PU8)&inBuffer;
  out.bufferbase=(PU8)&outBuffer;
  
  buffer_init(&in,IN_SIZE);
  buffer_init(&out,OUT_SIZE);
  
  printf("\n[1]%s\n",txt);
  while(idx<20){
    if(buffer_isFull(&in)) break;
    buffer_put(&in,txt[idx]);
    idx++;
  }
  printf("\n[2]%s [%i][%i]\n",in.bufferbase,in.readIdx,in.writeIdx);
 
  while(--idx){
    if(buffer_isEmpty(&in)) break;
    c=buffer_get(&in);
    buffer_put(&in,txt[idx]);
  }
  printf("\n[3]%s [%i][%i]\n",in.bufferbase,in.readIdx,in.writeIdx);

  return 0;
}
  */