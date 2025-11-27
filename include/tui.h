#ifndef HEADER_TUI
#define HEADER_TUI

#include "WifiList.h"

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
#define CLR_LINE "\033[K"
// Mueve el cursor a 0,0
#define RESET_CURSOR "\033[1;1H"
#define MV_CURSOR "\033[1;1H"
#define CLR_AND_HOME "\033[2J\033[H" // Mueve el cursor y limpia
/***************** END CURSOR SEGMENT **************************/

/***************** KEYS SEGMENT **************************/
#define KEY_UP "\033[A"
#define KEY_DOWN "\033[B"
#define KEY_RIGHT "\033[C"
#define KEY_LEFT "\033[D"
#define KEY_ENTER '\n'
#define KEY_QUIT 'q'
/***************** END KEYS SEGMENT **************************/

/***************** INVERT SELECTED TEXT **************************/
#define INV_TEXT "\033[7m"
#define UNINV_TEXT "\033[27m"
/***************** END KEYS SEGMENT **************************/

/***************** DRAWING SEGMENT **************************/
#define BOX_TOP_LEFT "┌"
#define BOX_TOP_RIGHT "┐"
#define BOX_BOTTOM_LEFT "└"
#define BOX_BOTTOM_RIGHT "┘"
#define BOX_HORIZONTAL "─"
#define BOX_VERTICAL "│"
#define BOX_T_DOWN "┬"
#define BOX_T_UP "┴"
#define BOX_T_RIGHT "├"
#define BOX_T_LEFT "┤"



struct winsize getWindowSize();
void setCursorPosition(int x, int y);
void configureTerminal();
void resetTerminal();
int readInput();
int readkey(char *buffer, int key);
void updateSelection(WifiList *wifiList, int selection);
void showAllNetworks(WifiList *wifiList, int selection);
void resetSelection(WifiList *wifiList, int selection);
void drawPanel();

#endif
