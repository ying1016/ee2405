#include "mbed.h"
#include "uLCD_4DGL.h"
#include <cstdlib>

const int NUM_OF_KEY = 3;
BusIn keyboard( D3, D4, D5);
 
Serial pc(USBTX, USBRX);
uLCD_4DGL uLCD(D1, D0, D2);
volatile int sum = 0b0000;
int number[3] = {0b0001,0b0010,0b0100};
// Return a key number whose corresponding hardware key is being pressed.
int read_one_key(int key_num) {
	int _press = keyboard.read();
	// scan
	for (int i = 0; i < key_num; i++) {
		if (_press & (1 << i)) return i;
	}

	// no key is pressed
	return -1;
}
 
int main(void) {
    char s[40];
    int times = 0;
	while (1) {
		int key = read_one_key(NUM_OF_KEY);
	
		if (key == -1) {
			pc.printf("No key is pressed. \r\n");
            
		}
		else {
            times ++;
			pc.printf("The key is pressed: %d\r\n", key);
            sum += number[key];
            if (times >2){
                uLCD.printf("sum: %s\r\n", itoa(sum, s, 2));
            } 
		}
	 
		wait(0.5);
	}
}
