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

    void Mix2Sounds(const short* soundA, const short* soundB, int size, short* out,
            float aVolume = 1.0f,
            float bVolume = 1.0f);
};


#endif //PITCHDETECTION_AUDIOUTILS_H
