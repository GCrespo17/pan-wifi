#include "tui.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// Estados de mi terminal
static struct termios oldTermios, newTermios;

void resetTerminal(){
    printf(FONT_RESET);
    printf(BG_RESET);
    printf(SHOW_CURSOR);
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

void configureTerminal() {
    //Obtiene la configuracion actual de entrada
    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios; // Guardamos la configuracion inicial de mi terminal

    newTermios.c_lflag &= ~(ICANON | ECHO); // Apagamos modo canonico y echo
    newTermios.c_cc[VMIN] = 1;  //Retorna algo solamente cuando se ingresa un input
    newTermios.c_cc[VTIME] = 0; //Le dice espera para siempre si es necesario

    //Aplica la configuracion nueva de entrada
    //TCSANOW es que aplicara los cambios ahora mismo
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    printf(HIDE_CURSOR);
    printf(CLR_SCREEN);
    printf(MV_CURSOR);
    atexit(resetTerminal);
}

int readKey(char *buffer, int key){
    if(buffer[key] == '\033' && buffer[key+1] == '['){
        switch(buffer[key+2]){
            case 'A':
                return 1; //Arriba
            case 'B':
                return 2; //Abajo
            case 'C':
                return 3; //Derecha
            case 'D': 
                return 4; //Izquierda 
        }
    }else if(buffer[key] == KEY_ENTER){
        return 5; //Enter
    }else if(buffer[key] == KEY_QUIT){
        return 6; //Salir
    }

    return 0;
}

int readInput(){
    char buffer[4096]; //Maximo input buffer
    int n = read(STDIN_FILENO, buffer, sizeof(buffer));
    int finalKey = 0;
    if(n == 0){
        return 0;
    }
    for (int i=0; i<n; i++){
        int key = readKey(buffer, i);
        if(buffer[i] == '\033'){
            if(i+1 < n && buffer[i+1] == '['){
                i+=2;
            }
        }
        if(key == 0){
            continue;
        }
        finalKey = key;
    }
    return finalKey;
}


