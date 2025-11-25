#ifndef HEADER_WifiList
#define HEADER_WifiList

#include "WifiData.h"

typedef struct WifiList {
    WifiData *data;
    int size;
    int capacity;
} WifiList;

void wifiListConstructor(WifiList *wifiList);
void addNetwork(WifiList *wifiList, WifiData wifiData);
WifiData getData(WifiList *wifiList, int dataId);
void freeWifiList(WifiList *wifiList);

#endif
