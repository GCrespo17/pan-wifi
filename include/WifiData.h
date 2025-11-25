#ifndef HEADER_WifiData
#define HEADER_WifiData

// Aqui estan los datos que tiene mi red wifi que voy a recibir de la PC
typedef struct WifiData {
    int id;
    char *ssid;
    char signal[4];
} WifiData;

WifiData createData(char *ssid, char signal[]);

#endif
