#ifndef FBSD_H
#define FBSD_H

#include <Watchy.h>
#include "daemon.h"
#include "conso17pt7b.h"
#include "conso12pt7b.h"

class WatchyFBSD : public Watchy{
    public:
        WatchyFBSD();
        void drawWatchFace();
        void drawDate();
        void drawTime();
        void drawSteps();
        void drawBattery();
};

#endif
