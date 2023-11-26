#ifndef DISPLAY_BASE
#define DISPLAY_BASE
#include <iostm8s207.h>

void displayInit(void);

void CEa(void);

void CEb(void);

void setPage(char page);

void setCol(char column);

void writeData(char data);

void clear(void);

#endif