#include <TimerOne.h>

double kp = 0.005, ki = 0.3;
unsigned long currentTime = 0;
unsigned long previousTime = 0;
double setpoint = 0;
double cumError, rateError, lastError;

#define pin 12
#define pot 11
#define out_pin 20

float input = 0.0;
float output = 0.0;
float pi_out = 0.0;

void setup() {

  pinMode(pin, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(out_pin, INPUT);
  Timer1.initialize(100);                              //100us = 10khz

}

void loop() {

  input = float(analogRead(pot));
  setpoint = map(input, 1, 5, 0, 30);
  output = float(analogRead(out_pin));
  pi_out = pi();
  Timer1.pwm(pin, pi_out);

}

float pi() {
  currentTime = millis();                            //get current time
  double elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation

  double error = setpoint - input;                   // determine error
  cumError += error * elapsedTime;                   // compute integral

  double out = kp * error + ki * cumError;           //PI output

  lastError = error;                                 //remember current error
  previousTime = currentTime;                        //remember current time

  return out;                                        //have function return the PI output
}
