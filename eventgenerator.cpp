/*
 * (c)2014 James Hudson - www.disconnectionist.com
 * Released under GPL v2.0
 */

#include "eventgenerator.h"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

// see here for mappings: http://web.archive.org/web/20100501161453/http://www.classicteck.com/rbarticles/mackeyboard.php

EventGenerator::EventGenerator(QObject *parent) :
    QObject(parent)
{
}

void EventGenerator::keyPressDownArrow()
{
    generateKeypressEvent(125);
}

void EventGenerator::keyPressUpArrow()
{
    generateKeypressEvent(126);
}


void EventGenerator::generateKeypressEvent(int code)
{
    CGEventRef push = CGEventCreateKeyboardEvent(NULL, code, true);
    CGEventRef release = CGEventCreateKeyboardEvent(NULL, code, false);

    CGEventPost(kCGHIDEventTap, push);
    CGEventPost(kCGHIDEventTap, release);
}
