#ifndef PDRAWER
#define PDRAWER

#define COLOR_WHITE 0
#define COLOR_BLACK 1

#include "display_base.h"

void pdrawer_init(void);

void pdrawer_refresh(void);

void pdrawer_clear(void);

void pdrawer_set(char x, char y, char val);

void pdrawer_line(char x1, char y1, char x2, char y2, 
									char color);
									
void pdrawer_rectangle(char x1, char y1, char x2, char y2, 
									char color);

#endif