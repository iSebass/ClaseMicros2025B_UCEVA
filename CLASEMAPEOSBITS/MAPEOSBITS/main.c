#include "CONFIG/Config.h"


int main(void){
	
	DDRDbits.BIT0 = 1;
	
    while(1){
		PORTDbits.BIT0 = 1;
		_delay_ms(500);
		PORTDbits.BIT0 = 0;
		_delay_ms(500);	
    }
}

