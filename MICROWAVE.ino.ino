#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

int check, check2;
int OVEN = 30;
int COUNTER,FAN;
char TEMP;
bool DOOR, TABLE;
bool LOCK = false;

void setup(void) {
  while (!Serial);
  Serial.begin(9600);
  Serial.println("MW OVEN");

  CircuitPlayground.begin();
}

void loop() {

 if (CircuitPlayground.rightButton() && LOCK == false){ //SETTING DIAL TO SELECT TEMPERATURE SETTING
      if (check > 3) {check = 1;}
        
  switch(check){
        case 1: TEMP = 'L';
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(7,0xffff00);
                Serial.println("Temperature set to "); Serial.println(TEMP); Serial.println(" power");
                break;
        case 2: TEMP = 'M';
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(7,0xffA500);
                Serial.println("Temperature set to "); Serial.println(TEMP); Serial.println(" power");
                break;
        case 3: TEMP = 'H';
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(7,0xff0000);
                Serial.println("Temperature set to "); Serial.println(TEMP); Serial.println(" power");
                break;
        }
  check++;
  delay(140);  
  }

if (CircuitPlayground.leftButton() && LOCK == false){ //SETTING DIAL TO SELECT TIMER FOR COOKING
    
    if (check2 > 61) {check2 = 10;}
    
 switch(check2){
        case 10: COUNTER = 10;
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0x0000ff);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        case 20: COUNTER = 20;
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0x73cdfb);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        case 30: COUNTER = 30;
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0x00ff00);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        case 40: COUNTER = 40;
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0xffffff);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        case 50: COUNTER = 50;
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0xfa8072);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        case 60: COUNTER = 60;
                Serial.println("AT 60");
                //CircuitPlayground.clearPixels();
                CircuitPlayground.setPixelColor(2,0xc21807);
                Serial.println("Timer set to "); Serial.println(COUNTER); Serial.println(" seconds");
                break;
        }
  check2++;
  delay(25);  
  }

  if(CircuitPlayground.readCap(0) >= 100) // IF DOOR IS OPEN
  {  CircuitPlayground.setPixelColor(9,0xffffff);
      DOOR = true;
      LOCK = true;
      Serial.println("Door Open");
      delay(125);
  }
  if(CircuitPlayground.readCap(1) >= 100) // IF DOOR IS CLOSED
      {  CircuitPlayground.setPixelColor(9,0x000000);
          DOOR = false;
          LOCK = false;
          Serial.println("Door Closed");
          delay(125);}

if(CircuitPlayground.readCap(3) >= 100 && LOCK == false){ //ONCE MICROWAVE IS TURNED ON

  LOCK = true;
  FAN = 0;
  
  CircuitPlayground.clearPixels(); 
  CircuitPlayground.setPixelColor(9,0xfff000);
  Serial.println("MW ON - COOKING AT "); Serial.println( TEMP);
  Serial.println("TIME REMAINING...");
  while(COUNTER >= 0 && LOCK == true){ //WHILE THE TIMER IS COUNTING DOWN
    Serial.println( COUNTER );
    
    CircuitPlayground.setPixelColor(6,0xff0000); //MAGNATRON
    
    CircuitPlayground.setPixelColor(8,0x00ff00); //FAN
    delay(100);
    CircuitPlayground.setPixelColor(8,0x000000);
    
    CircuitPlayground.setPixelColor(7,0x0000FF); //TURNTABLE
    delay(50);
    CircuitPlayground.setPixelColor(7,0x000000); 

   
    
    COUNTER--;
    
    if(DOOR == true){break;}
    
    //if(OVEN >= 100) {CircuitPlayground.setPixelColor(6,0x000000);}

    delay(850);
    
    CircuitPlayground.setPixelColor(7,0x0000FF);
    delay(50);
    CircuitPlayground.setPixelColor(7,0x000000); 
  }

  Serial.println("DONE!"); //SETTING FOR TIMER DONE, NOW EMITS NOISE
  int countDown = 20;  
  OVEN = 100;
  Serial.println("TIME REMAINING...");
  while(countDown >= 0) //WHILE MICROWAVE IS EMITTING NOISE AND COUNTING DOWN 20 SECS
  {
   CircuitPlayground.setPixelColor(6,0x000000);
    
   if(CircuitPlayground.readCap(0) >= 100){
     CircuitPlayground.setPixelColor(9,0xffffff);
     break; 
    }
   delay(100);
   if(FAN < 10) {
    CircuitPlayground.setPixelColor(8,0x00ff00);
    delay(100);
    CircuitPlayground.setPixelColor(8,0x000000);
   }
   else {CircuitPlayground.setPixelColor(8,0x000000); delay(100);}

   
    CircuitPlayground.playTone(440,100);
    Serial.println( countDown );
    FAN++;
    countDown--;
    delay(800);
    
    }
    CircuitPlayground.playTone(880,200);
    Serial.println("MW OFF.");
    CircuitPlayground.clearPixels();
    LOCK = false;
}

}

