#include<i2cmaster.h>
void setup() {
  Serial.begin(9600);
  i2c_init(); // Makes the Arduino Master
  PORTC = (1 << PORTC4) | (1 << PORTC5); 
}
void loop(){
  int dev = 0x5A<<1;
int data_low = 0;
int data_high = 0;
int pec = 0;

i2c_start_wait(dev+I2C_WRITE);
i2c_write(0x07);

i2c_rep_start(dev+I2C_READ);
data_low = i2c_readAck();
data_high = i2c_readAck();
pec = i2c_readNak();
i2c_stop();

double tempFactor = 0.02;
double tempData = 0;
int frac; 

tempData = (double)(((data_high & 0x007F) << 8) + data_low);
tempData = (tempData * tempFactor)-0.01;

float celcius = tempData - 273.15;
//float fahrenheit = (celcius*1.8) + 32;

Serial.print("Celcius: ");
Serial.println(celcius);

//Serial.print("Fahrenheit: ");
//Serial.println(fahrenheit);

delay(1000);
  }
