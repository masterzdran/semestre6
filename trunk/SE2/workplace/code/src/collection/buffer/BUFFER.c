#include "BUFFER.h"
#define IS_EMPTY(A)                ((A)->readIdx == (A)->writeIdx)
#define IS_FULL(A)                 (((((A)->w + 1) >= (A)->buffersize)?0:(A)->readIdx + 1) == (A)->writeIdx)
#define SET_THE_RECORD(A,B)           {(*(A))++;if((*(A)) >= (B)){*(A) = 0;}}


void buffer_init(pBUFFER ringBuffer, U8* bufferspace, U32 buffersize){
		ringBuffer->readIdx = ringBuffer->writeIdx = 0;
		ringBuffer->bufferbase = bufferspace;
    ringBuffer->buffersize = buffersize;
}

void buffer_get(pBUFFER ringBuffer, U8* outdata, U16 outdata_size){
  U16 size, i=0;
	if(buffer_isEmpty(ringBuffer)){return;}
  size = ringBuffer->bufferbase[ringBuffer->readIdx++];
	if (ringBuffer->readIdx >= ringBuffer->buffersize) {ringBuffer->readIdx=0;}
	size &= (ringBuffer->bufferbase[ringBuffer->readIdx++]<<8 & 0xF0);
	for (i=0; i<size; i++){
		if (ringBuffer->readIdx >= ringBuffer->buffersize) {ringBuffer->readIdx=0;}
		outdata[i++]=ringBuffer->bufferbase[ringBuffer->readIdx];
		ringBuffer->bufferbase[ringBuffer->readIdx++]='-';
	}
	/*memcpy(outdata,ringBuffer->readIdx,size);*/
  /*SET_THE_RECORD(&(ringBuffer->readIdx),ringBuffer->buffersize);
  */
}

U8 buffer_put(pBUFFER ringBuffer,U8* data, U16 size){
  int i=0;
	if (buffer_isFull(ringBuffer)) {return 0;}
	if (buffer_size(ringBuffer)<(size+2)) {return 0;}
	ringBuffer->bufferbase[ringBuffer->writeIdx++] = (size & 0xF);
	if (ringBuffer->writeIdx >= ringBuffer->buffersize) {ringBuffer->writeIdx=0;}
	ringBuffer->bufferbase[ringBuffer->writeIdx++] = (size>>8 & 0xF);
	for (i=0; i<size; i++){
		if (ringBuffer->writeIdx >= ringBuffer->buffersize) {ringBuffer->writeIdx=0;}
		ringBuffer->bufferbase[ringBuffer->writeIdx++]=data[i];
  }
	return i;
	/*SET_THE_RECORD(&(ringBuffer->writeIdx),ringBuffer->buffersize);*/
}

U16 buffer_nextSize(pBUFFER ringBuffer) {	return (ringBuffer->bufferbase[ringBuffer->readIdx] & (ringBuffer->bufferbase[ringBuffer->readIdx+1]<<8));}

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