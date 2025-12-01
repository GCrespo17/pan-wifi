#include "WifiController.h"
#include "WifiData.h"
#include "WifiList.h"
#include <stdio.h>
#include <stdlib.h>
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

bool isDangerousInput(const char *input) {
    const char *danger = "\'";

    if (strpbrk(input, danger) != NULL) {
        return true;
    } else {
        return false;
    }
}

int connectNetwork(char *ssid, char *password) {
    if (!isDangerousInput(ssid) && !isDangerousInput(password)) {
        char cleanNetworkCommand[150] = "nmcli connection delete ";
        char command[150] = "nmcli device wifi connect ";
        strcat(command, ssid);
        strcat(command, " password ");
        strcat(command, password);
        strcat(command, " > /dev/null 2>&1");
        // Para limpiar la red
        strcat(cleanNetworkCommand, ssid);
        strcat(cleanNetworkCommand, " > /dev/null 2>&1");
        int status;
        system(cleanNetworkCommand);
        status = system(command);
        return status;
    } else {
        return -1;
    }
}
