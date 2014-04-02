/********************************************
*                                           *
* Author: Pranav Sharma                     *
* Rev.: 1                                   *
* Date: 28-03-14                            *
*                                           *
* Target: ATmega8                           *
*                                           *
* Pin Description:                          *
* D2 (4)  <-- Momentary Push Button to GND  *
* D9 (15) --> PWM output                    *
* A5 (28) <-- Potentiometer Input           *
*                                           *
********************************************/

#include <EEPROM.h>

unsigned char exp_map[256]={
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
  3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,5,5,5,
  5,5,5,5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,
  9,9,10,10,10,10,10,11,11,11,11,12,12,12,13,13,13,13,
  14,14,14,15,15,15,16,16,16,17,17,18,18,18,19,19,20,
  20,20,21,21,22,22,23,23,24,24,25,26,26,27,27,28,29,
  29,30,31,31,32,33,33,34,35,36,36,37,38,39,40,41,42,
  42,43,44,45,46,47,48,50,51,52,53,54,55,57,58,59,60,
  62,63,64,66,67,69,70,72,74,75,77,79,80,82,84,86,88,
  90,91,94,96,98,100,102,104,107,109,111,114,116,119,
  122,124,127,130,133,136,139,142,145,148,151,155,158,
  161,165,169,172,176,180,184,188,192,196,201,205,210,
  214,219,224,229,234,239,244,250,255
};

int light_pin = 9;          // Any PWM Pin
int button_pin = 2;
int pot_pin = A5;           // Any analog Pin
int eeprom_address = 76;    

boolean light_on = EEPROM.read(eeprom_address);

uint16_t prevMillis = millis();

int brightness=analogRead(pot_pin)/4;


void setup()
{
  pinMode(light_pin, OUTPUT);
  if(light_on) turn_on();
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(pot_pin, INPUT);
}

void loop(){
  if(digitalRead(button_pin)==LOW && millis()-prevMillis > 500){
    light_on ? turn_off() : turn_on();
    prevMillis = millis();
  }
  
  else if(light_on){
    brightness = analogRead(pot_pin)/4;
    analogWrite(light_pin, exp_map[brightness]);
    delay(5);
  }
}

void turn_on(){
  for (int i = 0; i<=brightness; i++){
    analogWrite(light_pin, exp_map[i]);
    delay(4);
  }
  light_on = true;
  EEPROM.write(eeprom_address, 1);
}

void turn_off(){
  for (int i = brightness; i>=0; i--){
    analogWrite(light_pin, exp_map[i]);
    delay(4);
  }
  light_on = false;
  EEPROM.write(eeprom_address, 0);
}
