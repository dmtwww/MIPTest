/*
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief This files contains android specifics global 
 * functions used to set the android runtime environment.
 * 
 * @file android.h
 */

#ifndef API_MIP_ANDROID_H_
#define API_MIP_ANDROID_H_

#ifdef __ANDROID__
#include <jni.h>
#include <string>

#include "mip_export.h"
#include "mip_namespace.h"

MIP_NAMESPACE_BEGIN
/**
 * @brief Sets a global JavaVM pointer to be used for all calls to Android platform API via JNI.
 * This MUST be done before calling any other public API (on Android only) and must be called from a java thread. 
 *
 * @param javaVm a pointer the JavaVM object.
 * @param contextClass the application conext class. 
 * @param contextObject the application object. 
 * @return 0 if successful, returns < 0 error codes. 
 */
MIP_API int SetJVM(JavaVM* javaVm, jclass contextClass, jobject contextObject);
/**
 * @brief Gets the global JavaVM pointer previously set.
 * @return javaVm a pointer the JavaVM object.
 */
MIP_API JavaVM* GetJVM();
/**
 * @brief Gets the global application class previously set.
 * @return the context class previously set. 
 */
MIP_API jclass GetContextClass();
/**
 * @brief Gets the global application object previously set.
 * @return the context object previously set.
 */
MIP_API jobject GetContextObject();


MIP_NAMESPACE_END

#endif  // __ANDROID__
#endif  // API_MIP_ANDROID_H_
