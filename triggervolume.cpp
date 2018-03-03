#include "triggervolume.h"


TriggerVolume::TriggerVolume() : mTriggered(false)
{

}


TriggerVolume::~TriggerVolume()
{

}


//Is triggered when object enters the volume
void TriggerVolume::onEnter()
{
    if(!mTriggered)
    {
        mTriggered = true;
        emit entered();
    }
}


//Resets to untriggered state once object exits
void TriggerVolume::onExit()
{
    if(mTriggered)
    {
        mTriggered = false;
        emit exited();
    }
}
