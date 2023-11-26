#include <stdlib.h>
#include "pdrawer.h"

char* buffer;
char* change_buffer;
void pdrawer_init(void) {
	char i;
	displayInit();
	clear();
	
	buffer = malloc(1024 * sizeof(char));
	pdrawer_clear();
	change_buffer = malloc(128 * sizeof(char));
	for(i = 0; i < 128; i++)
		change_buffer[i] = 0;
}

void pdrawer_clear(void) {
	int i;
	for(i = 0; i < 1024; i++) {
		buffer[i] = 0;
	}
}

void pdrawer_refresh(void) {
	char i,j,k;
	char shift;
	int ptr;
	
	CEa();
	shift = 0;
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 64; j++) {
			if(change_buffer[j+shift] != 0) {
			//if(1) {
				change_buffer[j+shift] = 0;
				setPage(j/8);
				setCol(j%8*8);
				ptr = (j+shift) * 8;
				for(k = 0; k < 8; k++) {
					writeData(buffer[ptr]); 
					ptr++;
				}
			}
		}
		CEb();
		shift = 64;
	}
}

void pdrawer_set(char x, char y, char color) {
	int crshift;
	
	if((y > 63) || (x > 255))
		return;
	
	crshift = x/64 * 64;
	change_buffer[crshift + y/8 * 8 + (x-crshift)/8] = 1;
	if(color == COLOR_BLACK) {
	  buffer[x/64 * 512 + y/8 * 64 + x%64] |= 1 << y%8;
	}
	else {
		buffer[x/64 * 512 + y/8 * 64 + x%64] &= ~(1 << y%8);
	}
}

void pdrawer_line(char x1, char y1, char x2, char y2, 
									char color) {
	int k;
	char y;
	char i;
	char deltax;
	char deltay;
	
	if(y1 > y2)
		deltay = y1 - y2;
	else
		deltay = y2 - y1;
	
	if(x1 > x2)
		deltax = x1 - x2;
	else
		deltax = x2 - x1;
	
	if(deltax > deltay) {
		if(x1 > x2) {
			i = x1;
			x1 = x2;
			x2 = i;
		
			i = y1;
			y1 = y2;
			y2 = y1;
		}
		k = ((int)(y1 - y2) * 100) / (x1 - x2);
		
		for(i = x1; i < x2; i++) {
			y = (k * (i - x1))/100 + y1;
			if((y > 63) || (i > 255))
				break;
			pdrawer_set(i, y, color);
		}
	}
	else {
		if(y1 > y2) {
			i = x1;
			x1 = x2;
			x2 = i;
		
			i = y1;
			y1 = y2;
			y2 = y1;
		}
		k = ((int)(x1 - x2) * 100) / (y1 - y2);
		
		for(i = y1; i < y2; i++) {
			y = (k * (i - y1))/100 + x1;
			pdrawer_set(y, i, color);
		}
	}
}

void pdrawer_rectangle(char x1, char y1, char x2, char y2, 
									char color) {
	char small;
	char big;
	char i;
	
	if(x2 > x1) {
		big = x2;
		small = x1;
	}
	else {
		big = x1;
		small = x2;
	}
	for(i = small; i < big; i++) {
		pdrawer_set(i, y1, COLOR_BLACK);
		pdrawer_set(i, y2, COLOR_BLACK);
	}
	if(y2 > y1) {
		big = y2;
		small = y1;
	}
	else {
		big = y1;
		small = y2;
	}
	for(i = small; i < big; i++) {
		pdrawer_set(x1, i, COLOR_BLACK);
		pdrawer_set(x2, i, COLOR_BLACK);
	}
}
