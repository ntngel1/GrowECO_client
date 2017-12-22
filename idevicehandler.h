#ifndef IDEVICEHANDLER_H
#define IDEVICEHANDLER_H

#include <QString>

class IDeviceHandler
{
public:
    virtual void setDeviceID(QString id) = 0;
};

#endif // IDEVICEHANDLER_H
