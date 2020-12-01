//
// Created by Semyon Tikhonenko on 9/17/16.
//

#ifndef PITCHDETECTION_AUDIOUTILS_H
#define PITCHDETECTION_AUDIOUTILS_H


#include <cstdint>
#include <vector>
#include <string>

namespace AudioUtils {
    double GetSampleTimeInSeconds(int sampleSize, int sampleRate);
    int64_t GetSampleTimeInMicroseconds(int sampleSize, int sampleRate);
    int GetSamplesByteIndexFromTime(double time, int sampleRate, int sampleSize);

    void MakeLinearFadeInAtBeginning(short *array, int size, int affectedSize);
    void MakeLinearFadeOutAtEnding(short *array, int size, int affectedSize);

    void Int16SamplesIntoFloatSamples(const short* in, int size, float* out);
    void FloatSamplesIntoInt16Samples(const float* in, int size, short* out);

    std::vector<short> ResizePreviewSamples(const std::string& rawPcm, int newSize);
    std::vector<short> ResizePreviewSamples(const short* samples, int samplesSize, int newSize);

    void Mix2Sounds(const short* soundA, const short* soundB, int size, short* out);
    void Mix2Sounds(const short* soundA, const short* soundB, int sizeA, int sizeB, short* out);
    
    template <typename SoundCollection, typename SoundBufferSizeCollection>
    void MixSounds(const SoundCollection& sounds, const SoundBufferSizeCollection& soundBufferSize, short* out) {
        int soundsCount = sounds.size();
        if (soundsCount == 0) {
            return;
        } else if(soundsCount == 1) {
            std::copy(sounds[0], sounds[0] + soundBufferSize[0], out);
            return;
        }

        const short* mix = sounds[0];
        int mixSize = soundBufferSize[0];
        for (int i = 1; i < soundsCount; ++i) {
            Mix2Sounds(mix, sounds[i], mixSize, soundBufferSize[i], out);
            mix = out;
            mixSize = std::max(soundBufferSize[i], mixSize);
        }
    }
};


#endif //PITCHDETECTION_AUDIOUTILS_H
