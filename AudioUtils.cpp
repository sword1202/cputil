//
// Created by Semyon Tikhonenko on 9/17/16.
//

#include <cmath>
#include <assert.h>
#include "AudioUtils.h"
#include "Algorithms.h"
#include "MathUtils.h"

using namespace CppUtils;

namespace AudioUtils {
    constexpr short MAX_SAMPLE = std::numeric_limits<short>::max();
    constexpr short MIN_SAMPLE = std::numeric_limits<short>::min();

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
        const float div = 1.0f / (MAX_SAMPLE + 1);

        for (int i = 0; i < size; ++i) {
            out[i] = in[i] * div;
        }
    }

    void FloatSamplesIntoInt16Samples(const float* in, int size, short* out) {
        const float div = MAX_SAMPLE + 1;
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

    void Mix2Sounds(const short* soundA, const short* soundB, int size, short* out) {
        for (int i = 0; i < size; ++i) {
            auto a = uint16_t(soundA[i]);
            auto b = uint16_t(soundB[i]);

            unsigned int result = a + b;
            auto max = std::numeric_limits<uint16_t>::max();
            result -= Math::RoundToInt((a * b) / double(max));
            if (result > max) {
                result = max;
            }

            out[i] = short(result);
        }
    }

    void Mix2Sounds(const short* soundA, const short* soundB, int sizeA, int sizeB, short* out) {
        for (int i = 0; i < std::max(sizeA, sizeB); ++i) {
            auto a = uint16_t(i < sizeA ? soundA[i] : 0);
            auto b = uint16_t(i < sizeB ? soundB[i] : 0);

            unsigned int result = a + b;
            auto max = std::numeric_limits<uint16_t>::max();
            result -= Math::RoundToInt((a * b) / double(max));
            if (result > max) {
                result = max;
            }

            out[i] = short(result);
        }
    }
};