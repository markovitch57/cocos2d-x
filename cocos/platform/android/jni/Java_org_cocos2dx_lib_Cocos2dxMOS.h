//  This file is my addition

/****************************************************************************
Copyright (c) 2012 cocos2d-x.org
=======
﻿/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.
>>>>>>> f74438372c40a85f563d93386f34968357ff9b4c:cocos/editor-support/cocostudio/TriggerBase.h

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __AUDIO_JNI_H__
#define __AUDIO_JNI_H__

#include <string>

//void setKeepScreenOnFlagInJni(bool yVal);
bool getAudioFocus_JNI(void);
int getNativeHardwareBufferFrames_JNI(void);
int getNativeHardwareSampleRate_JNI(void);
bool headsetStatusChanged_JNI(void);
//char * pcGetRelaunchString(void);
std::string sGetBrowserString_JNI(void);
std::string sGetDeviceDescription_JNI(void);
std::string sGetAndroidId_JNI(void);
std::string sGetAndroidMacAddress_JNI(void);
//void openURL(const char* pszUrl);
//std::string getStringWithEllipsisJni(const char* pszText, float width, float fontSize);
// ======== Billing functions =========
bool P_yBillingInitialised(void);
void P_initialise(void);
bool P_yResponseReady(void);
bool P_ySucceeded(void);
void P_checkForUnconsumedTokens(void);
bool P_yUnconsumedToken(void);
void P_purchaseTokens(int iTokens);
void P_consumeUnconsumedToken(void);
// ======== End of Billing functions =========

#endif // __AUDIO_JNI_H__
