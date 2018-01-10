/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <oboe/Oboe.h>
#include <android/log.h>
#include <thread>
#include "AudioEngine.h"

oboe::DataCallbackResult
AudioEngine::onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "In callback");
    return oboe::DataCallbackResult::Continue;
}


void AudioEngine::startStream() {

    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION START: open");

    oboe::AudioStreamBuilder builder;
    builder.setCallback(this);

    auto result = builder.openStream(&mStream);

    printStreamState();
    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION END: open");

    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, "OboeCrashTest", "Could not open stream");
    }

    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION START: start");
    result = mStream->requestStart();
    printStreamState();
    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION END: start");

    if (result !=  oboe::Result::OK){
        __android_log_print(ANDROID_LOG_ERROR, "OboeCrashTest", "Could not start stream");
    }
}

void AudioEngine::stopStream() {

    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION START: stop");
    mStream->stop();
    printStreamState();
    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION END: stop");

    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION START: close");
    mStream->close();
    printStreamState();
    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "ACTION END: close");
}

void AudioEngine::runTest() {
    __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "\n\nSTARTING TEST\n---");

    printStreamState();

    std::function<void(void)> restartStreamForever = std::bind(&AudioEngine::restartStreamForever, this);
    mWorkerThread = new std::thread(restartStreamForever);
}

void AudioEngine::restartStreamForever() {

    for (int i = 0; i < 10000000; ++i) {

        __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "Restarting stream. Run #%d", i);

        printStreamState();
        startStream();
        printStreamState();
        stopStream();
        printStreamState();
    }
}

void AudioEngine::printStreamState(){

    if (mStream == nullptr){
        __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "Stream state: NULLPTR");
    } else {
        __android_log_print(ANDROID_LOG_DEBUG, "OboeCrashTest", "%s", oboe::convertToText(mStream->getState()));
    }
}