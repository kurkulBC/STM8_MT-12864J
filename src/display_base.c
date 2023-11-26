#include "display_base.h"

void chdelay(char del) {
	char i;
	for(i = 0; i < del; i++);
}

void delay(int del) {
	int i;
	for(i = 0; i < del; i++);
}

#ifndef DISPLAY_TICK
#define DISPLAY_TICK 10
#endif

void tick(void) {
	PF_ODR |= 0x80; //E - 1
	chdelay(DISPLAY_TICK);
	PF_ODR ^= 0x80; //E - 0
}

void displayInit(void){
	PB_DDR = 0xff;
	PF_DDR = 0xff;
	
	PB_CR1 = 0xff;
	PF_CR1 = 0xff;
	
	PF_ODR = 0x00;
	chdelay(1);
	PF_ODR = 0x10; //RES - 1
	chdelay(10);
	PF_ODR |= 0x09; //E1 & E2 - 1
	PB_ODR = 0b00111111; //enable
	chdelay(1);
	tick();
	//PF_ODR ^= 0x09; //E1 & E2 - 0
}

void dataMode(void) {
	PF_ODR |= 0x40;
}

void cmdMode(void) {
	PF_ODR &= ~0x40;
}

void CEa(void) {
	PF_ODR &= ~0x9;
	PF_ODR |= 0x1;
}

void CEb(void) {
	PF_ODR &= ~0x9;
	PF_ODR |= 0x8;
}

void setPage(char page) {
	cmdMode();
	PB_ODR = 0b10111000 | page;
	tick();
}

void setCol(char column) {
	cmdMode();
	PB_ODR = 0b01000000 | column;
	tick();
}

void writeData(char data) {
	dataMode();
	PB_ODR = data;
	tick();
}

void clear(void) {
	int col;
	int page;
	PF_ODR |= 0x09;
	for(page = 0; page < 8; page++) {
		setPage(page);
		setCol(0);
		for(col = 0; col < 64; col++) {
			writeData(0x00);
		}
	}
}