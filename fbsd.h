#ifndef FBSD_H
#define FBSD_H

#include <Watchy.h>
#include "daemon.h"
#include "conso15pt7b.h"

class WatchyFBSD : public Watchy{
    public:
        WatchyFBSD();
        void drawWatchFace();
        void drawTime();
        void drawSteps();
        void drawBattery();
};

#endif
