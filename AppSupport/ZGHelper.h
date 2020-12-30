//
// ZGHelper.h
//
// Copyright 2018�� Zego. All rights reserved.
// 

#ifndef ZGHelper_h__
#define ZGHelper_h__

#include <string>
#include <stdint.h>

#include "ZegoLiveRoom/video_format.h"

using std::string;

class ZGHelper
{
public:
    static ZGHelper * Instance()
    {
        static ZGHelper z;
        return &z;
    }

    string GetDeviceUUID();

    string GetMachineName();

    string GetPixelFormatDesc(AVE::VideoPixelFormat format);

    int64_t GetCurTimeStampMs();

    string GetRandomUUID();
private:
    ZGHelper();
    ~ZGHelper();
};

#define ZGHelperInstance ZGHelper::Instance

#endif // ZGHelper_h__

