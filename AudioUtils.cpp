//
// Created by Semyon Tikhonenko on 9/17/16.
//

#include <cmath>
#include <assert.h>
#include "AudioUtils.h"
#include "Algorithms.h"

namespace AudioUtils {
    int64_t GetSampleTimeInMicroseconds(int sampleSize, int sampleRate) {
        return int16_t(round(1000000.0 * sampleSize / (double)sampleRate));
    }

    double GetSampleTimeInSeconds(int sampleSize, int sampleRate) {
        return (double)sampleSize / (double)sampleRate;
    }

    int GetSamplesByteIndexFromTime(double time, int sampleRate, int sampleSize) {
        return time * sampleRate * sampleSize;
    }

    void MakeLinearFadeInAtBeginning(short *array, int size, int affectedSize) {
        assert(affectedSize <= size);
        double volumePercentageIncrement = 1.0 / affectedSize;
        double multiplier = 0.0;
        for (int i = 0; i < affectedSize; ++i) {
            multiplier += volumePercentageIncrement;
            array[i] *= multiplier;
        }
    }

    void MakeLinearFadeOutAtEnding(short *array, int size, int affectedSize) {
        assert(affectedSize <= size);
        double volumePercentageIncrement = 1.0 / affectedSize;
        double multiplier = 0.0;
        for (int i = 0; i < affectedSize; ++i) {
            multiplier += volumePercentageIncrement;
            array[size - i] *= multiplier;
        }
    }

    void Int16SamplesIntoFloatSamples(const short* in, int size, float* out) {
        const float div = 1.0f/32768.0f;

        for (int i = 0; i < size; ++i) {
            out[i] = in[i] * div;
        }
    }

    void FloatSamplesIntoInt16Samples(const float* in, int size, short* out) {
        const float div = 32768.0f;
        for (int i = 0; i < size; ++i) {
            out[i] = static_cast<short>(in[i] * div);
        }
    }

    std::vector<short> ResizePreviewSamples(const short* samples, int samplesSize, int newSize) {
        assert(newSize > 0 && samplesSize > 0);

        std::vector<short> result;
        // reserve a bit more
        result.reserve(static_cast<size_t>(newSize) + 100);
        double resultSummarySize = 0;
        int samplesSeek = 0;

        if (samplesSize > newSize) {
            double batchSize = double(samplesSize) / newSize;
            while (samplesSeek < samplesSize) {
                resultSummarySize += batchSize;
                int intBatchSize = int(round(resultSummarySize - samplesSeek));
                intBatchSize = std::min(intBatchSize, samplesSize - samplesSeek);

                int average = CppUtils::AbsoluteAverage<int>(samples + samplesSeek, intBatchSize);
                result.push_back(short(average));

                samplesSeek += intBatchSize;
            }
        } else if(samplesSize < newSize) {
            double batchSize = double(newSize) / samplesSize;
            int sampleIndex = 0;

            while (samplesSeek < samplesSize) {
                resultSummarySize += batchSize;
                int intBatchSize = int(round(resultSummarySize - samplesSeek));
                intBatchSize = std::min(intBatchSize, newSize - samplesSeek);

                auto sample = short(abs(samples[sampleIndex++]));
                for (int i = 0; i < intBatchSize; ++i) {
                    result.push_back(sample);
                }

                samplesSeek += intBatchSize;
            }
        } else {
            return result;
        }

        while (result.size() < newSize) {
            result.push_back(result.back());
        }

        result.resize(static_cast<size_t>(newSize));

        return result;
    }

    std::vector<short> ResizePreviewSamples(const std::string& rawPcm, int newSize) {
        int size = int(rawPcm.size() / sizeof(short));
        return ResizePreviewSamples(reinterpret_cast<const short*>(rawPcm.data()), size, newSize);
    }
};