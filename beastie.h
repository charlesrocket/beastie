#ifndef BEASTIE_H
#define BEASTIE_H

#include <Watchy.h>
#include "fonts/conso17pt7b.h"
#include "fonts/conso12pt7b.h"
#include "fonts/conso11pt7b.h"
#include "fonts/conso10pt7b.h"
#include "daemon.h"

class WatchyFBSD : public Watchy {
    using Watchy::Watchy;
    public:
      void drawWatchFace();
      void drawWDay();
      void drawDate();
      void drawTime();
      void drawSteps();
      void drawTemperature();
      void drawBattery();
      void drawX();
};

#endif
