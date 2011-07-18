#include <stdio.h>
#include <GPIO.h>

int main(){

	printf("HELLo eCos!");
	GPIO_CLEAR(1<<8);
	return 0;
}
