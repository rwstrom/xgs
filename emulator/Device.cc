/**
 * XGS: The Linux GS Emulator
 * Written and Copyright (C) 1996 - 2016 by Joshua M. Thompson
 *
 * You are free to distribute this code for non-commercial purposes
 * I ask only that you notify me of any changes you make to the code
 * Commercial use is prohibited without my written permission
 */

/*
 * The Device class is the base class for objects that handle accesses
 * to one or more addresses in the I/O space at $C0xx.
 */

#include <vector>

#include "emulator/common.h"

#include "System.h"
#include "Device.h"

void Device::attach(System *parent)
{
    system = parent;

    for (auto loc : ioReadList()) {
        system->setIoRead(loc, this);
    }

    for (auto loc : ioWriteList()) {
        system->setIoWrite(loc, this);
    }
}
