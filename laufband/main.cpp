#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

enum Pins {
    _17_ = 0, 
    _18_ = 1, 
    _27_ = 2, 
    _22_ = 3, 
    _23_ = 4,
    _19_ = 24
};

#define LOW 0
#define HIGH 1


#define motor1_Speed _18_
#define motor1_B _17_
#define motor1_A _27_ 

#define motor2_Speed _19_
#define motor2_B _22_
#define motor2_A _23_ 

void sigCallback(int sig)
{
    signal(SIGINT, SIG_IGN);
    
    printf("Programm stopped!\n");
    
    // Cleanup
    pwmWrite(_18_, 0);
    pwmWrite(_19_, 0);
    
    digitalWrite(_17_, 0);
    digitalWrite(_22_, 0);
    digitalWrite(_23_, 0);
    digitalWrite(_27_, 0);

    exit(0);
}

int main(int argc, char* argv[])
{
    // Starte die WiringPi-Api
    if (wiringPiSetup() == -1) {
        printf("Couldn't init wiring!\n");
        return 1;
    }
    
    if (signal(SIGINT, sigCallback) == SIG_ERR) {
        printf("Error on installing signal handler\n");
    }

    pinMode(_18_, PWM_OUTPUT);
    pinMode(_19_, PWM_OUTPUT);
    
    pinMode(_17_, OUTPUT);
    pinMode(_22_, OUTPUT);
    pinMode(_23_, OUTPUT);
    pinMode(_27_, OUTPUT);
    
    int speed = 1023;
    while (true) {
        //if (speed > 255)
        //    speed = 0;
        
        digitalWrite(motor1_B,LOW);
        digitalWrite(motor2_B,LOW);
        digitalWrite(motor1_A,HIGH);
        digitalWrite(motor2_A,HIGH);
        
        pwmWrite(motor1_Speed,speed);
        pwmWrite(motor2_Speed,speed);
        
        delay(1000);
        pwmWrite(motor1_Speed,0);
        pwmWrite(motor2_Speed,0);
        
        digitalWrite(motor1_A,LOW);
        digitalWrite(motor2_A,LOW);
        digitalWrite(motor1_B,HIGH);
        digitalWrite(motor2_B,HIGH);
        pwmWrite(motor2_Speed,speed);
        pwmWrite(motor1_Speed,speed);
        
        delay(1000);
        pwmWrite(motor1_Speed,0);
        pwmWrite(motor2_Speed,0);
        
        digitalWrite(motor1_A,LOW);
        digitalWrite(motor1_B,LOW);
        digitalWrite(motor2_A,LOW);
        digitalWrite(motor2_B,LOW);
        
        //speed += 10;
    }

    return 0;
}
