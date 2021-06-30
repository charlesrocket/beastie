#include "fbsd.h"

WatchyFBSD::WatchyFBSD(){}

void WatchyFBSD::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.drawBitmap(0, 0, daemon, 200, 200, GxEPD_WHITE);
    drawWDay();
    drawDate();
    drawTime();
    drawSteps();
    drawBattery();
    for(uint8_t i=0; i<3; i++){
        display.display(true);
      }
}

void WatchyFBSD::drawWDay(){
    display.setFont(&conso10pt7b);
    display.setCursor(139, 59);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    display.print(dayOfWeek);
}

void WatchyFBSD::drawDate(){
    display.setFont(&conso12pt7b);
    display.setCursor(126, 80);
    if(currentTime.Day < 10){
    display.print("0");
    }
    display.print(currentTime.Day);
    display.print("/");
    display.print(currentTime.Month);
}

void WatchyFBSD::drawTime(){
    display.setFont(&conso17pt7b);
    display.setCursor(110, 108);
    if(currentTime.Hour < 10){
        display.print("0");
    }
    display.print(currentTime.Hour);
    display.print(":");
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.println(currentTime.Minute);
}

void WatchyFBSD::drawSteps(){
    display.setFont(&conso12pt7b);
    display.setCursor(124, 130);
    uint32_t stepCount = sensor.getCounter();
    String stepStr = String(stepCount);
    for(int i=1; i<5; i++){
        stepStr = stepCount < pow(10, i) ? "0" + stepStr : stepStr;
    }
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.print(stepStr);
}

void WatchyFBSD::drawBattery(){
    display.setFont(&conso10pt7b);
    display.setCursor(188, 17);
    display.print(">");
    display.setFont(&conso11pt7b);
    display.setCursor(156, 15);
    float BATTV = getBatteryVoltage();
    if(BATTV > 4.1){
        display.print("***");
    }
    else if(BATTV > 3.75 && BATTV <= 4.1){
        display.print(" **");
    }
    else if(BATTV > 3.50 && BATTV <= 3.75){
        display.print("  *");
    }
}
