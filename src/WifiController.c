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
        // Salta las wifi vacias
        if (buffer[0] != ' ' && buffer[0] != ':') {
            char *ssidScanned = strtok(buffer, ":");
            char signalScanned[4];
            strcpy(signalScanned, strtok(NULL, ":"));
            // Si el nombre es nulo o vacio lo salta
            if (ssidScanned != NULL && ssidScanned[0] != '\0') {
                WifiData data = createData(ssidScanned, signalScanned);
                addNetwork(wifiList, data);
            }
        }
    }

    pclose(fp);
}
