#include <jni.h>
#include <string>
#include <stdlib.h>
#include <android/log.h>
#include <pthread.h>
#define LOG_TAG "NativeThreadTest"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C"
jstring
Java_de_uni_1passau_sec_threadtester2_ThreadTester_stringFromJNI(
        JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" jdouble
Java_de_uni_1passau_sec_threadtester2_RunnerThread_nativeRun(
        JNIEnv* env, jobject thiz, jint length, jintArray data, jdouble cookie) {
    pthread_t pt = pthread_self();
    LOGD("This is Thread %lld (%f)", pt, cookie);

    if (data == NULL) {
        LOGD("thread %lld: sorting native array", pt);
        int nums[length];
        for (int i = 0; i < length; i++)
            nums[i] = rand();

        //bubble sort array
        for (int i = 0; i < length; i++)
            for (int j = 1; j < length - i; j++)
                if (nums[j] < nums[j - 1]) {
                    //Log.d(TAG, "swapping "+j+":"+nums[j]+"and "+(j-1)+":"+nums[j-1]);
                    double temp = nums[j];
                    nums[j] = nums[j - 1];
                    nums[j - 1] = temp;
                }

        //verify
        for (int i = 1; i < length; i++)
            if (nums[i] < nums[i - 1]) LOGD("Error %f>%f", nums[i - 1], nums[i]);
    } else {
        LOGD("thread %lld: sorting java array", pt);
        int* nums = (int*)env->GetPrimitiveArrayCritical(data, 0);
        for (int i = 0; i < length; i++)
            for (int j = 1; j < length - i; j++)
                if (nums[j] < nums[j - 1]) {
                    //Log.d(TAG, "swapping "+j+":"+nums[j]+"and "+(j-1)+":"+nums[j-1]);
                    double temp = nums[j];
                    nums[j] = nums[j - 1];
                    nums[j - 1] = temp;
                }

        //verify
        for (int i = 1; i < length; i++)
            if (nums[i] < nums[i - 1]) LOGD("Error %f>%f", nums[i - 1], nums[i]);
        env->ReleasePrimitiveArrayCritical(data, nums, 0);
        //free(nums);
    }
    LOGD("thread %lld (%f): finished sorting array", pt, cookie);
    return cookie;
}