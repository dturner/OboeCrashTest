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

#ifndef OBOECRASHTEST_AUDIOENGINE_H
#define OBOECRASHTEST_AUDIOENGINE_H


#include <oboe/AudioStreamCallback.h>

class AudioEngine : public oboe::AudioStreamCallback {

public:
    void startStream();
    void stopStream();
    void runTest();

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;
private:

    oboe::AudioStream* mStream = nullptr;

    void restartStreamForever();

    std::thread *mWorkerThread;

    void printStreamState();
};


#endif //OBOECRASHTEST_AUDIOENGINE_H
