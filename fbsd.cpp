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
    display.setCursor(139, 58);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    display.print(dayOfWeek);
}

void WatchyFBSD::drawDate(){
    display.setFont(&conso12pt7b);
    display.setCursor(126, 79);
    if(currentTime.Day < 10){
    display.print("0");
    }
    display.print(currentTime.Day);
    display.print("/");
    display.print(currentTime.Month);
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
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.print(stepStr);
}

void WatchyFBSD::drawBattery(){
    display.setFont(&conso12pt7b);
    display.setCursor(132, 152);
    int8_t batt = getBattery();
    String battStr = String(batt);
    battStr = batt < 10 ? "0" + battStr : battStr;
    battStr = batt < 100 ? "0" + battStr : battStr;
    display.print(battStr);
    display.display(true);
}

uint8_t WatchyFBSD::getBattery(){
    float voltage = getBatteryVoltage();
    uint8_t percentage = 2808.3808 * pow(voltage, 4)
                        - 43560.9157 * pow(voltage, 3)
                        + 252848.5888 * pow(voltage, 2)
                        - 650767.4615 * voltage
                        + 626532.5703;
    percentage = min((uint8_t) 100, percentage);
    percentage = max((uint8_t) 0, percentage);
    return percentage;
}
