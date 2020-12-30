//
// ZGUtilTools.h
//
// Copyright 2018Äê Zego. All rights reserved.
// 

#ifndef ZGUtilTools_h__
#define ZGUtilTools_h__

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <memory>
#include <string>
#include <vector>

std::string StringFormat(const char *fmt, ...);
std::string GetExePath();
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);

std::vector<uint8_t> AppSignStrToVecData(std::string& str);


std::string GBKToUTF8(const char* str_gbk);

std::string UTF8ToGBK(const char * str_utf8);

#endif // ZGUtilTools_h__

