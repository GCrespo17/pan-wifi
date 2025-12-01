#include "WifiController.h"
#include "WifiList.h"
#include "tui.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    WifiList *wifiList = malloc(sizeof(WifiList));
    int selection = 0;
    int key = 0;

    wifiListConstructor(wifiList);

    fillWifiList(wifiList);

    static int exitLoop = 0;
    configureTerminal();
    drawPanel();
    showAllNetworks(wifiList, selection);
    // printf(CLR_SCREEN);
    while (!exitLoop) {
        key = readInput();
        if (key == 1) {
            if (selection > 0) {
                resetSelection(wifiList, selection);
                selection--;
            }
        }
        if (key == 2) {
            if (selection < wifiList->size - 1) {
                resetSelection(wifiList, selection);
                selection++;
            }
        }
        if (key == 3)
            printf("Right\n");
        if (key == 4)
            printf("Left\n");
        if (key == 5) {
            setPassword(wifiList->data[selection].ssid);
        }
        if (key == 6) {
            printf("Quit\n");
            exitLoop = 1;
            key = 0;
        }
        if (key != 0) {
            updateSelection(wifiList, selection);
        }
    }

    freeWifiList(wifiList);
    free(wifiList);

    return 0;
}
