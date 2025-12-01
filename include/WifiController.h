#ifndef HEADER_WifiController
#define HEADER_WifiController

#include "WifiList.h"

void printAvailableNetworks();

void fillWifiList(WifiList *wifiList);

int connectNetwork(char *ssid, char *password);

bool isDangerousInput(const char *input);
#endif
