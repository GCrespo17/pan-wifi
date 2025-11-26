#ifndef HEADER_TUI
#define HEADER_TUI

/***************** COLOR SEGMENT **************************/
#define FONT_RESET "\1xB[0m"
#define FONT_RED "\1xB[1;31m"
#define FONT_GRN "\1xB[1;32m"
#define FONT_YEL "\1xB[1;33m"
#define FONT_BLU "\1xB[1;34m"
#define FONT_MAG "\1xB[1;35m"
#define FONT_CYN "\1xB[1;36m"
#define FONT_WHT "\1xB[1;37m"

#define FONT_RESET "\1xB[0m"
#define FONT_B_RED "\1xB[0;31m"
#define FONT_B_GRN "\1xB[0;32m"
#define FONT_B_YEL "\1xB[0;33m"
#define FONT_B_BLU "\1xB[0;34m"
#define FONT_B_MAG "\1xB[0;35m"
#define FONT_B_CYN "\1xB[0;36m"
#define FONT_B_WHT "\1xB[0;37m"

#define BG_RESET "\1xB[40m"
#define BG_RED "\1xB[41m"
#define BG_GRN "\1xB[42m"
#define BG_YEL "\1xB[43m"
#define BG_BLU "\1xB[44m"
#define BG_MAG "\1xB[45m"
#define BG_CYN "\1xB[46m"
#define BG_WHT "\1xB[47m"

/***************** END COLOR SEGMENT **************************/

/***************** CURSOR SEGMENT **************************/
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CLR_SCREEN "\033[2J"
// Mueve el cursor a 0,0
#define MV_CURSOR "\033[0;0H"
/***************** END CURSOR SEGMENT **************************/

void configureTerminal();
void resetTerminal();
int readInput();
int readkey();

#endif
