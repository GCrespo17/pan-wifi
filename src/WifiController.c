#include "WifiController.h"
#include "WifiData.h"
#include "WifiList.h"
#include <stdio.h>
#include <string.h>

void printAvailableNetworks() {
    FILE *fp;
    char buffer[1024];

    fp = popen("nmcli -t -f SSID,SIGNAL,SECURITY dev wifi", "r");
    if (fp == NULL) {
        perror("popen failed");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

void fillWifiList(WifiList *wifiList) {
    FILE *fp;
    char buffer[1024];

    fp = popen("nmcli -t -f SSID,SIGNAL,SECURITY dev wifi", "r");
    if (fp == NULL) {
        perror("popen failed");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *ssidScanned = strtok(buffer, ":");
        char signalScanned[4];
        strcpy(signalScanned, strtok(NULL, ":"));
        // addNetwork(wifiList, createData(ssidScanned, signalScanned));
        WifiData data = createData(ssidScanned, signalScanned);
        addNetwork(wifiList, data);
    }

    pclose(fp);
}
