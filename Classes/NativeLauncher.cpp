//
//  NativeLauncher.cpp
//  Positions
//

#include "NativeLauncher.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#define JNICLASSNAME "co/yuukiar/fragmentofeternity/SocialActivity"
#define TWEET "tweet"

using namespace cocos2d;
void NativeLauncher::openTweetDialog(const char* tweet){
    JniMethodInfo methodInfo;
    if(JniHelper::getStaticMethodInfo(methodInfo, JNICLASSNAME, TWEET, "(Ljava/lang/String;)V")){
        jstring str = methodInfo.env->NewStringUTF(tweet);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, str);
        methodInfo.env->DeleteLocalRef(str);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
