//////////////////////////////
//  Analog Clock with Hands //
// By Steve Groves Nov 2023 //
//////////////////////////////

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <RTCZero.h>

#define TFT_CS         7
#define TFT_RST        -1 // Or set to -1 
#define TFT_DC         A3
#define TFT_BL         A4
#define colour         ST77XX_WHITE  //change dial and hands colour

//using chip specific SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
/* Create an rtc object */
RTCZero rtc;
// use current time when complile the code
const char date[] = __DATE__;
const char time[] = __TIME__;
int hour;
int minute;
int second;

int tickLength=110;
float constant=PI/180;
int cenY = 240/2;
int cenX = 240/2;
  
void setup() {
  tft.init(240, 240);           // Init ST7789 240x240
  tft.setRotation(2);           // Due to using radians
  tft.fillScreen(ST77XX_BLACK);
  tft.drawCircle(cenX, cenY, 115, colour);
  ticks();
  tft.drawCircle(cenX, cenY, 90, colour);

  rtc.begin(); // initialize RTC
  hour = (time[0]-48)*10 + (time[1]-48);
  minute = (time[3]-48)*10 + (time[4]-48);
  second = (time[6]-48)*10 + (time[7]-48);
  rtc.setTime(hour, minute, second);
}

void loop() {
  byte min = rtc.getMinutes();
  byte hr = rtc.getHours();
  minutes(min);
  hours(hr);
  tft.fillCircle(cenX, cenY, 5, colour);
  delay(500);

}

int minutes(int mins) {
  Bminutes(mins-1);
  int minMinus15 = mins - 15;
  int minPlus15 = mins + 15;
  float radian = 6 * constant * mins;
  float x=80*cos(radian);
  float y=80*sin(radian);
  radian = 6 * constant * minMinus15;
  float xM15 = 5*cos(radian);
  float yM15 = 5*sin(radian);
  radian = 6 * constant * minPlus15;
  float xP15 = 5*cos(radian);
  float yP15 = 5*sin(radian);
  tft.drawTriangle(cenX+xM15,cenY+yM15,cenX+x,cenY+y,cenX+xP15,cenY+yP15,colour);
}

int Bminutes(int mins) {
  int minMinus15 = mins - 15;
  int minPlus15 = mins + 15;
  float radian = 6 * constant * mins;
  float x=80*cos(radian);
  float y=80*sin(radian);
  radian = 6 * constant * minMinus15;
  float xM15 = 5*cos(radian);
  float yM15 = 5*sin(radian);
  radian = 6 * constant * minPlus15;
  float xP15 = 5*cos(radian);
  float yP15 = 5*sin(radian);
  tft.drawTriangle(cenX+xM15,cenY+yM15,cenX+x,cenY+y,cenX+xP15,cenY+yP15,ST77XX_BLACK);
}

int hours(int hrs) {
  Bhours(hrs-1);
  int hrMinus15 = hrs - 15;
  int hrPlus15 = hrs + 15;
  float radian = 30 * constant * hrs;
  float x=50*cos(radian);
  float y=50*sin(radian);
  radian = 30 * constant * hrMinus15;
  float xM15=5*cos(radian);
  float yM15=5*sin(radian);
  radian = 30 * constant * hrPlus15;
  float xP15=5*cos(radian);
  float yP15=5*sin(radian);
  tft.drawTriangle(cenX+xM15,cenY+yM15,cenX+x,cenY+y,cenX+xP15,cenY+yP15,colour);
}

int Bhours(int hrs) {
  int hrMinus15 = hrs - 15;
  int hrPlus15 = hrs + 15;
  float radian = 30 * constant * hrs;
  float x=50*cos(radian);
  float y=50*sin(radian);
  radian = 30 * constant * hrMinus15;
  float xM15=5*cos(radian);
  float yM15=5*sin(radian);
  radian = 30 * constant * hrPlus15;
  float xP15=5*cos(radian);
  float yP15=5*sin(radian);
  tft.drawTriangle(cenX+xM15,cenY+yM15,cenX+x,cenY+y,cenX+xP15,cenY+yP15,ST77XX_BLACK);
}

void ticks() {
  for (int i=0; i<360; i=i+30) {
    float radian = i * constant;
    int x=tickLength*cos(radian);
    int y=tickLength*sin(radian);   
    if (i==0) {
      tft.drawLine(cenX,cenY,cenX+x,cenY+y,ST77XX_RED);
    } else if (i==90 or i==180 or i==270) {
         tft.drawLine(cenX,cenY,cenX+x,cenY+y,ST77XX_YELLOW);
    } else {
        tft.drawLine(cenX,cenY,cenX+x,cenY+y,colour);
    }
    for (int b=(tickLength-16); b<(tickLength-14); b++) {
      x=b*cos(radian);
      y=b*sin(radian);
      tft.drawLine(cenX,cenY,cenX+x,cenY+y,ST77XX_BLACK);
    }
  }
}
