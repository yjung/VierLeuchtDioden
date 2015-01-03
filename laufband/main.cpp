#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

enum Pins {
    _17_ = 0, 
    _18_, 
    _27_, 
    _22_, 
    _23_
};

//void ( *signal(int signum, void (*handler)(int)) ) (int);

void sigCallback(int sig)
{
    signal(SIGINT, SIG_IGN);
    
    printf("Programm stopped!\n");
    
    // Cleanup
    digitalWrite(_17_, 0);
    digitalWrite(_18_, 0);
    digitalWrite(_27_, 0);
    digitalWrite(_22_, 0);
    
    exit(0);
}

int main(int argc, char* argv[])
{
    // Starte die WiringPi-Api (wichtig)
    if (wiringPiSetup() == -1) {
        printf("Couldn't init wiring!\n");
        return 1;
    }
    
    if (signal(SIGINT, sigCallback) == SIG_ERR) {
        printf("Error on installing signal handler\n");
    }
    
    /*const*/ int DELAY = M_PI * 100;
    if (argc > 1) {
        DELAY = (int)atof(argv[1]);
        DELAY = (DELAY < 1) ? 1 : DELAY;
        printf("Delay = %d\n", DELAY);
    }

    // Schalte GPIO 17 (=WiringPi Pin 0) auf Ausgang
    // Wichtig: Hier wird das WiringPi Layout verwendet (Tabelle oben)
    pinMode(_17_, OUTPUT);
    pinMode(_18_, OUTPUT);
    pinMode(_27_, OUTPUT);
    pinMode(_22_, OUTPUT);
    
    pinMode(_23_, INPUT);
    
    int dir, oldDir = digitalRead(_23_);
    unsigned char i = 0;
    
    while (true) {
        dir = digitalRead(_23_);
        
        if (!dir) {
            //hochzaehlen
            if (oldDir != dir) {
                i = ++i % 4;
                digitalWrite((i+1) % 4, 0);
            }
            else {
                // LED aus
                digitalWrite(!i ? 3 : i-1, 0);
                // LED an
                digitalWrite(i, 1);
                // Warte
                delay(DELAY);
            }
            
            i = ++i % 4;
        }
        else {
            //runterzaehlen
            if (oldDir != dir) {
                i = --i % 4;
                digitalWrite(!i ? 3 : i-1, 0);
            }
            else {
                // LED aus
                digitalWrite((i+1) % 4, 0);
                // LED an
                digitalWrite(i, 1);
                // Warte
                delay(DELAY);
            }
            
            i = --i % 4;
        }
        
        oldDir = dir;
    }
    
    digitalWrite(_17_, 0);
    digitalWrite(_18_, 0);
    digitalWrite(_27_, 0);
    digitalWrite(_22_, 0);

    return 0;
}
