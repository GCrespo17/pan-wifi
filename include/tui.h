#ifndef HEADER_TUI
#define HEADER_TUI

/***************** COLOR SEGMENT **************************/
#define FONT_RESET "\033[0m"
#define FONT_RED "\033[1;31m"
#define FONT_GRN "\033[1;32m"
#define FONT_YEL "\033[1;33m"
#define FONT_BLU "\033[1;34m"
#define FONT_MAG "\033[1;35m"
#define FONT_CYN "\033[1;36m"
#define FONT_WHT "\033[1;37m"


#define FONT_B_RED "\033[0;31m"
#define FONT_B_GRN "\033[0;32m"
#define FONT_B_YEL "\033[0;33m"
#define FONT_B_BLU "\033[0;34m"
#define FONT_B_MAG "\033[0;35m"
#define FONT_B_CYN "\033[0;36m"
#define FONT_B_WHT "\033[0;37m"

#define BG_RESET "\033[40m"
#define BG_RED "\033[41m"
#define BG_GRN "\033[42m"
#define BG_YEL "\033[43m"
#define BG_BLU "\033[44m"
#define BG_MAG "\033[45m"
#define BG_CYN "\033[46m"
#define BG_WHT "\033[47m"

/***************** END COLOR SEGMENT **************************/

/***************** CURSOR SEGMENT **************************/
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CLR_SCREEN "\033[2J"
// Mueve el cursor a 0,0
#define MV_CURSOR "\033[0;0H"
/***************** END CURSOR SEGMENT **************************/

/***************** KEYS SEGMENT **************************/
#define KEY_UP "\033[A"
#define KEY_DOWN "\033[B"
#define KEY_RIGHT "\033[C"
#define KEY_LEFT "\033[D"
#define KEY_ENTER '\n'
#define KEY_QUIT 'q'

/***************** END KEYS SEGMENT **************************/


void configureTerminal();
void resetTerminal();
int readInput();
int readkey(char *buffer, int key);

#endif
