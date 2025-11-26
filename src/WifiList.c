#include "WifiList.h"
#include "WifiData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dataId = 0;

// Inicializo mi lista de redes para tener 1 con valor 0;
void wifiListConstructor(WifiList *networks) {
    networks->size = 0;
    networks->data = malloc(10 * sizeof(WifiData));
    networks->capacity = 10;
}

// Creo un elemento, donde se va a tener mis datos de la red
WifiData createData(char *ssid, char signal[]) {
    WifiData data;
    data.id = dataId;
    data.ssid = strdup(ssid);
    strcpy(data.signal, signal);
    dataId++;
    return data;
}

// Agrego un nuevo elemento a mi arreglo dinamico
void addNetwork(WifiList *wifiList, WifiData wifiData) {
    // Verifico si el tamaño actual es igual al de lo que puede aguantar
    if (wifiList->size == wifiList->capacity) {
        // Coloco que mi nueva capacidad sea 50% mayor al de mi tamaño actual
        int newCapacity = wifiList->size * 1.5;
        // Creo una expansion de memoria, donde se hara una copia de mi puntero
        // pero con memoria expandida
        WifiData *memoryExpansion =
            realloc(wifiList->data, newCapacity * sizeof(WifiData));
        if (!memoryExpansion) {
            perror("Malloc failed");
            exit(EXIT_FAILURE);
        }

        // Se le asigna la nueva expansion de memoria a mi arreglo wifi data
        wifiList->data = memoryExpansion;
        // Se expande la capacidad
        wifiList->capacity = newCapacity;
    }
    // Se le agrega la data al final del arreglo
    wifiList->data[wifiList->size] = wifiData;
    wifiList->size++;
}

WifiData getData(WifiList *wifiList, int dataId) {
    return wifiList->data[dataId];
}

void freeWifiList(WifiList *wifiList) {
    for (int i = 0; i < wifiList->size; i++) {
        free(wifiList->data[i].ssid);
    }
    free(wifiList->data);
    wifiList->data = NULL;
    wifiList->capacity = 0;
    wifiList->size = 0;
}
