#include "fbsd.h"

WatchyFBSD::WatchyFBSD(){}

void WatchyFBSD::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.drawBitmap(0, 0, daemon, 200, 200, GxEPD_WHITE);
    drawTime();
    drawSteps();
    drawBattery();
}

void WatchyFBSD::drawTime(){
    display.setFont(&conso17pt7b);
    display.setCursor(110, 107);
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
    display.print(stepStr);
}

void WatchyFBSD::drawBattery(){
    display.setFont(&conso12pt7b);
    display.setCursor(132, 152);
    float voltage = getBatteryVoltage();
    uint8_t percentage = 2808.3808 * pow(voltage, 4)
                      - 43560.9157 * pow(voltage, 3)
                      + 252848.5888 * pow(voltage, 2)
                      - 650767.4615 * voltage
                      + 626532.5703;
    percentage = min((uint8_t) 100, percentage);
    percentage = max((uint8_t) 0, percentage);
    display.print(percentage);
}
