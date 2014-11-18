#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "GoogleAnalyticsTracker_JNI.h"

#define CLASS_NAME "co/yuukiar/app10secburst/SocialActivity"

void sendScreenJNI(const char* screenName) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sendScreen", "(Ljava/lang/String;)V")) {
        jstring jScreenName = t.env->NewStringUTF(screenName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jScreenName);
        
        t.env->DeleteLocalRef(jScreenName);
        t.env->DeleteLocalRef(t.classID);
    }
}
