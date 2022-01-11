#include <jni.h>
#include <string>

#include "mip/android.h"
#include "mip/mip_context.h"

#include <android/log.h>

#include "mip/protection/protection_descriptor_builder.h"
#include "mip/protection_descriptor.h"
#include "mip/protection/protection_profile.h"
#include "observers/protection_engine_observer.h"
#include "observers/protection_profile_observer.h"
#include "consent/consent_delegate_impl.h"

using std::promise;
using std::future;
using std::make_shared;
using std::shared_ptr;

using mip::ApplicationInfo;
using mip::ProtectionProfile;using mip::ProtectionEngine;
using mip::ProtectionDescriptor;
using mip::ProtectionDescriptorBuilder;
using mip::ProtectionHandler;

JavaVM *javaVm = 0;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVm = vm;
    return JNI_VERSION_1_4;
}


    shared_ptr<ProtectionEngine::Observer> CreateProtectionEngineObserver() {
        return make_shared<ProtectionEngineObserverImpl>();
    }

int SetJVM(JavaVM *jvm, jclass contextClass, jobject contextObject) {
    return mip::SetJVM(jvm, contextClass, contextObject);
}


shared_ptr<ProtectionProfile> CreateProtectionProfile(
        const shared_ptr<ConsentDelegateImpl>& consentDelegate,
        const std::shared_ptr<mip::MipContext> mipContext,
        mip::CacheStorageType cacheStorageType) {
    shared_ptr<ProtectionProfileObserverImpl> profileObserver = make_shared<ProtectionProfileObserverImpl>();
    mip::ProtectionProfile::Settings settings(
            mipContext,
            cacheStorageType,
            consentDelegate,
            profileObserver);
    auto loadPromise = make_shared<promise<shared_ptr<mip::ProtectionProfile>>>();
    future<shared_ptr<mip::ProtectionProfile>> loadFuture = loadPromise->get_future();
    mip::ProtectionProfile::LoadAsync(settings, loadPromise);
    return loadFuture.get();
}

extern "C" JNIEXPORT int JNICALL
Java_com_example_informationprotection_MipLibrary_Init(
        JNIEnv* env,
        jobject /* this */,
        jclass contextClass,
        jobject context) {

    JavaVM *jvm = mip::GetJVM();

    if (jvm == 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "MIPTEST", "%s", "JavaVM empty");
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "MIPTEST", "%s", "JavaVM is set");
    }

    __android_log_print(ANDROID_LOG_DEBUG, "MIPTEST", "%s", "Start MIP Test");

    int sjvm_res = SetJVM(javaVm, contextClass, context);

    __android_log_print(ANDROID_LOG_DEBUG, "MIPTEST", "%s", sjvm_res);

    jvm = mip::GetJVM();

    if (jvm == 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "MIPTEST", "%s", "JavaVM empty");
    }
    else
    {
        __android_log_print(ANDROID_LOG_ERROR, "MIPTEST", "%s", "JavaVM is set");
    }


    auto protectionEngineObserver = CreateProtectionEngineObserver();

    const std::string appId = "3321afa6-4223-4c86-9844-2cdeb59f87ac";
    const std::string account = "user@contoso.com";

    // Construct/initialize objects required by the application's profile object
    // ApplicationInfo object (App ID, name, version)
    ApplicationInfo appInfo{appId,
                            "MIPTestApp",
                            "1.0"};

    std::shared_ptr<mip::MipConfiguration> mipConfiguration = std::make_shared<mip::MipConfiguration>(
            appInfo,
            "/sdcard",
            mip::LogLevel::Trace,
            true);

    auto mMipContext = mip::MipContext::Create(mipConfiguration);

    auto consentDelegateImpl = make_shared<ConsentDelegateImpl>(); // Consent delegate object

    CreateProtectionProfile(consentDelegateImpl, mMipContext, mip::CacheStorageType::InMemory);

    return 0;
}
