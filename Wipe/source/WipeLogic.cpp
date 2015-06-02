#include "WipeLogic.h"

using namespace mblsft;
using namespace mblsft::wipe;

WipeLogic::WipeLogic(QObject *parent) : QObject(parent)
{
    mPlatformFlag = 0;
#if defined(Q_OS_QNX)
    mPlatformFlag = 1;
#elif defined(Q_OS_ANDROID)
    mPlatformFlag = 2;
#elif defined(Q_OS_IOS)
    mPlatformFlag = 3;
#elif defined(Q_OS_WIN32)
    mPlatformFlag = 4;
#endif
    emit platformFlagChanged();
}

WipeLogic::~WipeLogic()
{

}

int WipeLogic::getPlatformFlag(){
    return mPlatformFlag;
}

int WipeLogic::getFontPointSizeM()
{
    if( mPlatformFlag == 1){
        return 8;
    }else if( mPlatformFlag == 2){
        return 14;
    }else{
        return 10;
    }
}

int WipeLogic::getFontPointSizeM2()
{
    if( mPlatformFlag == 1){
        return 10;
    }else if( mPlatformFlag == 2){
        return 16;
    }else{
        return 12;
    }
}

int WipeLogic::getFontPointSizeL()
{
    if( mPlatformFlag == 1){
        return 14;
    }else if( mPlatformFlag == 2){
        return 20;
    }else{
        return 16;
    }
}

