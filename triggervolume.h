#ifndef TRIGGERVOLUME_H
#define TRIGGERVOLUME_H

#include "objectinstance.h"
#include <QObject>
#include <QVector3D>

class TriggerVolume : public QObject, public ObjectInstance
{
    Q_OBJECT

    public:
        TriggerVolume();
        ~TriggerVolume();
        void onEnter();
        void onExit();

    signals:
        void entered();
        void exited();

    private:
        bool mTriggered;

};

#endif // TRIGGERVOLUME_H
