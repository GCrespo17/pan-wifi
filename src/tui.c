#include "tui.h"
#include "WifiController.h"
#include "WifiList.h"
#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

// Estados de mi terminal
static struct termios oldTermios, newTermios;

struct winsize getWindowSize() {
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    return w;
}

int getWifiListPanelLength() {
    int length = getWindowSize().ws_row;
    length = (int)(length / 1.25);
    return length;
}

int getWifiListPanelWidth() {
    int width = getWindowSize().ws_col;
    width = (int)(width / 1.3);
    return width;
}

void setCursorPosition(int x, int y) { printf("\033[%d;%dH", x, y); }

void resetTerminal() {
    printf(CLR_SCREEN);
    printf(RESET_CURSOR);
    printf(FONT_RESET);
    printf(SHOW_CURSOR);
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

void configureTerminal() {
    // Obtiene la configuracion actual de entrada
    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios =
        oldTermios; // Guardamos la configuracion inicial de mi terminal

    newTermios.c_lflag &= ~(ICANON | ECHO); // Apagamos modo canonico y echo
    newTermios.c_cc[VMIN] =
        1; // Retorna algo solamente cuando se ingresa un input
    newTermios.c_cc[VTIME] = 0; // Le dice espera para siempre si es necesario

    // Aplica la configuracion nueva de entrada
    // TCSANOW es que aplicara los cambios ahora mismo
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    fflush(stdout);
    printf(HIDE_CURSOR);
    // printf(CLR_SCREEN);
    printf(RESET_CURSOR);
    fflush(stdout);
    atexit(resetTerminal);
}

void normalInputMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    printf(SHOW_CURSOR);
    fflush(stdout);
}

int readKey(char *buffer, int key) {
    if (buffer[key] == '\033' && buffer[key + 1] == '[') {
        switch (buffer[key + 2]) {
        case 'A':
            return 1; // Arriba
        case 'B':
            return 2; // Abajo
        case 'C':
            return 3; // Derecha
        case 'D':
            return 4; // Izquierda
        }
    } else if (buffer[key] == KEY_ENTER) {
        return 5; // Enter
    } else if (buffer[key] == KEY_QUIT) {
        return 6; // Salir
    }

    return 0;
}

int readInput() {
    char buffer[4096]; // Maximo input buffer
    int n = read(STDIN_FILENO, buffer, sizeof(buffer));
    int finalKey = 0;
    if (n == 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        int key = readKey(buffer, i);
        // Como estoy leyendo bit por bit, tengo que verificar si se esta
        // ingresando un ESC ANSII Code, que posee 3 bits, si es asi
        // tengo que saltar al siguiente input
        if (buffer[i] == '\033') {
            if (i + 1 < n && buffer[i + 1] == '[') {
                i += 2;
            }
        }
        if (key == 0) {
            continue;
        }
        finalKey = key;
    }
    return finalKey;
}

void showAllNetworks(WifiList *wifiList, int selection) {
    int selectionPosition = selection + 3;
    setCursorPosition(selectionPosition - 1, 2);
    printf("Networks");
    setCursorPosition(selectionPosition - 1, getWifiListPanelWidth() / 2 + 1);
    printf("Signal Porcentage");
    fflush(stdout);
    for (int i = 0; i < 35; i++) {
        setCursorPosition(selectionPosition + i, 2);
        if (i < 50) {
            if (selection == i) {
                printf(INV_TEXT);
                printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
                       wifiList->data[i].ssid);
                setCursorPosition(selectionPosition + i,
                                  getWifiListPanelWidth() / 2 + 1);
                printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
                       wifiList->data[i].signal);
                printf(UNINV_TEXT);
            } else {
                printf("%s\n", wifiList->data[i].ssid);
                setCursorPosition(selectionPosition + i,
                                  getWifiListPanelWidth() / 2 + 1);
                printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
                       wifiList->data[i].signal);
            }
        }
    }
    fflush(stdout);
}

void resetSelection(WifiList *wifiList, int selection) {
    int selectionPosition = selection + 3;
    setCursorPosition(selectionPosition, 2);
    printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
           wifiList->data[selection].ssid);
    setCursorPosition(selectionPosition, getWifiListPanelWidth() / 2 + 1);
    printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
           wifiList->data[selection].signal);
    fflush(stdout);
}

void updateSelection(WifiList *wifiList, int selection) {
    int selectionPosition = selection + 3;
    setCursorPosition(selectionPosition, 2);
    printf(INV_TEXT);
    printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
           wifiList->data[selection].ssid);
    setCursorPosition(selectionPosition, getWifiListPanelWidth() / 2 + 1);
    printf("%-*s\n", getWifiListPanelWidth() / 2 - 2,
           wifiList->data[selection].signal);
    printf(UNINV_TEXT);
    fflush(stdout);
}

void drawPanel() {

    printf(CLR_SCREEN);

    int altoInicial = 1;
    int anchoInicial = 1;
    int altoFinal = getWifiListPanelLength();
    int anchoFinal = getWifiListPanelWidth();

    setCursorPosition(altoInicial, anchoInicial);
    printf(BOX_TOP_LEFT);
    fflush(stdout);
    setCursorPosition(altoFinal, anchoFinal);
    printf(BOX_BOTTOM_RIGHT);
    fflush(stdout);
    setCursorPosition(altoInicial, anchoFinal);
    printf(BOX_TOP_RIGHT);
    fflush(stdout);
    setCursorPosition(altoFinal, anchoInicial);
    printf(BOX_BOTTOM_LEFT);
    fflush(stdout);

    // Lineas verticales de la izquierda y la derecha
    for (int i = altoInicial + 1; i <= altoFinal - 1; i++) {
        setCursorPosition(i, anchoInicial);
        printf(BOX_VERTICAL);
        setCursorPosition(i, anchoFinal);
        printf(BOX_VERTICAL);
    }
    fflush(stdout);

    for (int i = anchoInicial + 1; i <= anchoFinal - 1; i++) {
        setCursorPosition(altoInicial, i);
        printf(BOX_HORIZONTAL);
        setCursorPosition(altoFinal, i);
        printf(BOX_HORIZONTAL);
    }
    fflush(stdout);

    // Lineas verticales en la mitad de mi panel
    for (int i = altoInicial; i <= altoFinal; i++) {
        setCursorPosition(i, anchoFinal / 2);
        if (i == 1) {
            printf(BOX_T_DOWN);
        } else if (i == altoFinal) {
            printf(BOX_T_UP);
        } else {
            printf(BOX_VERTICAL);
        }
    }
    fflush(stdout);
}

void setPassword(char *ssid) {
    char temp[68];
    normalInputMode();
    setCursorPosition(getWifiListPanelLength() + 2, 1);
    printf(CLR_LINE);
    printf("Password: ");
    // Limito el buffer a solo 67 caracters
    scanf("%67s", temp);
    configureTerminal();
    setCursorPosition(getWifiListPanelLength() + 2, 1);
    printf(CLR_LINE);
    int connection = connectNetwork(ssid, temp);
    if (connection == 0) {
        printf("You are now connected to %s", ssid);
    } else {
        printf("Failed to connect to %s. Error %d", ssid, connection);
    }
    fflush(stdout);
}
