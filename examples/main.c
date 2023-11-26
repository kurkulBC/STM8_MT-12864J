#define DISPLAY_TICK 5
//#include "display_base.h"
#include "pdrawer.h"
main()
{
	int i, j;
	pdrawer_init();
	pdrawer_clear();
	for(i = 0; i < 7; i++) {
		for(j = 0; j < 13; j++) {
			pdrawer_set(j*10, i*10, COLOR_BLACK);
		}
	}
	
	pdrawer_line(10, 10, 127, 63, COLOR_BLACK);
	pdrawer_rectangle(20, 20, 60, 60, COLOR_BLACK);
	pdrawer_refresh();
}