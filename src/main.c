#include "WifiController.h"
#include "WifiList.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    WifiList *wifiList = malloc(sizeof(WifiList));

    wifiListConstructor(wifiList);

    fillWifiList(wifiList);

    for (int i = 0; i < wifiList->size; i++) {
        printf("%s\n", wifiList->data[i].ssid);
    }

    freeWifiList(wifiList);

    return 0;
}
