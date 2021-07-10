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
  //drawTemperature();
    drawBattery();
    drawX();
    for(uint8_t i=0; i<3; i++){
        display.display(true);
    }
}

void WatchyFBSD::drawWDay(){
    display.setFont(&conso10pt7b);
    int16_t  x1, y1;
    uint16_t w, h;
    String dayOfWeek = dayShortStr(currentTime.Wday);
    display.getTextBounds(String(dayOfWeek), 0, 0, &x1, &y1, &w, &h);
    display.setCursor(150 - w/2, 69);
    display.println(String(dayOfWeek));
}

void WatchyFBSD::drawDate(){
    display.setFont(&conso12pt7b);
    int16_t  x1, y1;
    uint16_t w, h;
    String monthStr = String(currentTime.Month);
    String dayStr = String(currentTime.Day);
    monthStr = currentTime.Month < 10 ? "0" + monthStr : monthStr;
    dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
    String dateStr = dayStr + "/" + monthStr;
    display.getTextBounds(String(dateStr), 0, 0, &x1, &y1, &w, &h);
    display.setCursor(150 - w/2, 91);
    display.println(String(dateStr));
}

void WatchyFBSD::drawTime(){
    display.setFont(&conso17pt7b);
    display.setCursor(110, 119);
    if(currentTime.Hour < 10){
        display.print("0");
    }
    display.print(currentTime.Hour);
    display.print(":");
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.print(currentTime.Minute);
}

void WatchyFBSD::drawSteps(){
    display.setFont(&conso11pt7b);
    int16_t  x1, y1;
    uint16_t w, h;
    uint32_t stepCount = sensor.getCounter();
    String stepStr = String(stepCount);
    for(int i=1; i<5; i++){
        stepStr = stepCount < pow(10, i) ? "0" + stepStr : stepStr;
    }
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.getTextBounds(String(stepStr), 0, 0, &x1, &y1, &w, &h);
    display.setCursor(150 - w/2, 141);
    display.println(String(stepStr));
}

void WatchyFBSD::drawTemperature(){
    display.setFont(&conso10pt7b);
    display.setCursor(4, 18);
    uint8_t temperatureRTC = RTC.temperature() / 4;
    if(temperatureRTC < 10){
    display.print("0");
    }
    display.print(temperatureRTC);
    display.setCursor(22, 11);
    display.print(".");
    display.setCursor(29, 16);
    display.print("c");
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
    else if(BATTV > 3.85 && BATTV <= 4.1){
        display.print(" **");
    }
    else if(BATTV > 3.60 && BATTV <= 3.85){
        display.print("  *");
    }
}

void WatchyFBSD::drawX(){
    display.setFont(&conso11pt7b);
    display.setCursor(148, 157);
    display.print("x");
}
