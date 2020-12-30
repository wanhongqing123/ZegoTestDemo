//
// AppIDHelper.h
//
// Copyright 2018 Zego. All rights reserved.
// 
#ifndef AppIDHelper_h__
#define AppIDHelper_h__
#include <string>
#include <vector>
#include "AppSupport/ZGUtilTools.h"
using std::string;
using std::vector;
// appid
unsigned int GetAppId()
{
    // 向zego申请获取，然后把appid和sign存放于自己的服务器上，运行时通过网络请求动态获取，防止泄露
    return   4094740804;
}
// app sign
unsigned char * GetAppSign(int & len)
{
    // 向zego申请获取，然后把appid和sign存放于自己的服务器上，运行时通过网络请求动态获取，防止泄露
    // 格式  "0x01, 0x03, 0x44, ...."
    string sig_str = "0x5c, 0x96, 0x31, 0x45, 0xbf, 0x41, 0xcb, 0x86, 0xf7, 0x17, 0x7e, 0x97, 0xb4, 0x13, 0x94, 0x8a, 0x79, 0x1c, 0x46, 0xc5, 0x90, 0x04, 0x4a, 0x35, 0xa8, 0xc8, 0x62, 0x8b, 0xe6, 0x2c, 0x08, 0x67"      ;
    vector<string> sig_str_vec;
    static vector<unsigned char> sig_data;
    SplitString(sig_str, sig_str_vec, ",");
    sig_data.clear();
    for (int i = 0; i < sig_str_vec.size(); ++i)
    {
        int data;
        sscanf_s(sig_str_vec[i].c_str(), "%x", &data);
        sig_data.push_back(data);
    }
    len = sig_data.size();
    return &sig_data[0];
}
#endif // AppIDHelper_h__
