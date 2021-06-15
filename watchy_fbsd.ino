#include <Watchy.h>
#include "daemon.h"
#include "led_723pt7b.h"

class WatchyFBSD : public Watchy{
    public:
        void drawWatchFace(){
          display.drawBitmap(0, 0, daemon, 200, 200, GxEPD_WHITE);
          display.setFont(&led_display_723pt7b);
          display.setTextColor(GxEPD_WHITE);
          display.setCursor(104, 123);
          char time[6];
          time[0] = '0' + ((currentTime.Hour/10)%10);
          time[1] = '0' + (currentTime.Hour%10);
          time[2] = ':';
          time[3] = '0' + ((currentTime.Minute/10)%10);
          time[4] = '0' + (currentTime.Minute%10);
          time[5] = 0;
          display.print(time);
        }
};

WatchyFBSD m;

void setup() {
  m.init();
}

void loop() {

}
