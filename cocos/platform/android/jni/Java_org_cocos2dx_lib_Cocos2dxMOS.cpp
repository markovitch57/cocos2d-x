/*  This file is my addition
LINKS
	signatures - http://journals.ecs.soton.ac.uk/java/tutorial/native1.1/implementing/method.html
*/

#include "JniHelper.h"
#include <string.h>
#include "base/CCDirector.h"
#include "../CCApplication.h"
#include "platform/CCFileUtils.h"
#include "base/CCEventType.h"
#include "deprecated/CCNotificationCenter.h"
#include <jni.h>

#include "moslib/cc/LuaPlayer.h"

using namespace cocos2d;

#define  MOS_ACTIVITY_CLASS_NAME "com/mos/mindofsound/Cocos2dxMosActivity"


extern "C" {

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxMOS_nativeRelaunch(JNIEnv*  env, jobject thiz, jstring sBrowserString ) {
//	  LuaPlayer::sBrowserString.assign(JniHelper::jstring2string(sBrowserString).c_str());
//	  LuaPlayer::sharedInstance()->relaunch(false);
	  LuaPlayer::sharedInstance()->handleIncomingRequest(JniHelper::jstring2string(sBrowserString).c_str());

	 // CCLOG("Relaunching - sBrowserString = %s", LuaPlayer::sBrowserString.c_str());
    }
}

extern "C" {

	JNIEXPORT bool JNICALL Java_org_cocos2dx_lib_Cocos2dxMOS_yDEBUG(JNIEnv*  env, jobject thiz ) {
		#ifdef _DEBUG
			return true;
		#endif
		#ifdef DEBUG	
			return true;
		#endif
		return false;
    }
}

bool getAudioFocus(void) {
    int ret = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getAudioFocus", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

int getNativeHardwareSampleRate(void) {
    int ret = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getNativeHardwareSampleRate", "()I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

int getNativeHardwareBufferFrames(void) {
    int ret = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getNativeHardwareBufferFrames", "()I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

std::string sGetBrowserString(void) {

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getJavaBrowserStringAndEmptyIt", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			//t.env->DeleteLocalRef(t.classID);
            return JniHelper::jstring2string(str);
        }
	return std::string("");
}

/*
std::string getStringWithEllipsisJni(const char* pszText, float width, float fontSize) {
    std::string ret;
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxBitmap", "getStringWithEllipsis", "(Ljava/lang/String;FF)Ljava/lang/String;")) {
        jstring stringArg1;

        if (!pszText) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszText);
        }

        jstring retFromJava = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, width, fontSize);
        const char* str = t.env->GetStringUTFChars(retFromJava, 0);
        ret = str;

        t.env->ReleaseStringUTFChars(retFromJava, str);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}
*/

void openURL(const char* pszUrl){
	//int ret = 0;
    JniMethodInfo minfo;

    if(JniHelper::getStaticMethodInfo(minfo,
                                      "org/cocos2dx/lib/Cocos2dxActivity",
                                      "openURL",
                                      "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF(pszUrl);
        //ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
	//return ret; 
}

std::string sGetAndroidId(void) {
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getAndroidId", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
            return JniHelper::jstring2string(str);
        }
	return std::string("");
}

std::string sGetAndroidMacAddress(void) {
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getAndroidMacAddress", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
            return JniHelper::jstring2string(str);
        }
	return std::string("");
}

std::string sGetDeviceDescription(void) {

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxMOS", "getDeviceDescription", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			//t.env->DeleteLocalRef(t.classID);
            return JniHelper::jstring2string(str);
        }
	return std::string("");
}

// ===========================  Billing functions  =========================

void P_initialise(void) {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "initBilling", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool P_yResponseReady(void) {
    bool ret = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "yResponseReady", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

bool P_ySucceeded(void) {
    bool ret = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "ySucceeded", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

/*void P_checkForUnconsumedTokens(void) {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "checkForUnconsumedTokens", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}*/

bool P_yUnconsumedToken(void) {
    bool ret = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "yUnconsumedToken", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

bool P_yBillingInitialised(void) {
    bool ret = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "yBillingInitialised", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

void P_consumeUnconsumedToken(void) {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "consumeUnconsumedToken", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void P_purchaseTokens(int iTokens) {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, MOS_ACTIVITY_CLASS_NAME, "purchaseTokens", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, iTokens);
        t.env->DeleteLocalRef(t.classID);
    }
}


// ===========================  End of Billing functions  =========================
