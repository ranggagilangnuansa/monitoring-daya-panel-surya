#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_INA219.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

RTC_DS1307 rtc;

char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};


Adafruit_INA219 ina219(0x40);

LiquidCrystal_I2C lcd(0x27 , 16, 2);

void setup() {
  Serial.begin(9600);

 Wire.begin();
  lcd.init();
  lcd.init();

  lcd.backlight();
  SD.begin();
  ina219.begin();
  ! rtc.begin();
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));        

}

void loop() 
{
lcd.clear();
  float w;
  float A = 0;
  float I = 0;
  float V = 0;
  float P = 0;
  for(float W = 0; W = W + w;)
{
  A = ina219.getCurrent_mA();
  I = fabs(A - (0.41 * A))/1000;
  V = ((analogRead(A0)*0.0049)*5);
  P = V * I;
  w = P * 0.0167;
 
  DateTime now =  rtc.now();

  Serial.print(V);
  Serial.print("|");
  Serial.print(I,4);
  Serial.print("|");
  Serial.println(W,2);
  Serial.println();
  
  
  lcd.setCursor(0,0);
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
  lcd.print("(");
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(")");
  
  lcd.setCursor(0,1);
  lcd.print(V,1);
  lcd.print("V|");
  lcd.print(I,2);
  lcd.print("A|");
  lcd.print(W,1);
  lcd.print("Wh");

delay (300);
  
File myFile = SD.open("Data.txt", FILE_WRITE);


if (myFile) {
DateTime now = rtc.now();
myFile.print(namaHari[now.dayOfTheWeek()]);  
myFile.print(',');    
myFile.print(now.day(), DEC);
myFile.print('/');
myFile.print(now.month(), DEC);
myFile.print('/');
myFile.print(now.year(), DEC);
myFile.print(" (");   
myFile.print(now.hour(), DEC);
myFile.print(':');
myFile.print(now.minute(), DEC);
myFile.print(")");
myFile.print("   Tegangan = ");
myFile.print(V);
myFile.print(" Volt"); 
myFile.print(" ");
myFile.print("||");
myFile.print(" Arus = ");
myFile.print(I);
myFile.print(" Ampere");
myFile.print(" ");
myFile.print("||");
myFile.print(" Daya = ");
myFile.print(P);
myFile.print(" Watt");
myFile.print(" ");
myFile.print("||");
myFile.print(" Energi = ");
myFile.print(W);
myFile.print(" Wh");
myFile.println("        ");
myFile.println("        ");
myFile.close();}
else {
  Serial.println("error opening datalog.txt");
}
delay(300);}}  
