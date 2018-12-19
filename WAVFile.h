//
// Created by Semyon Tikhonenko on 8/19/16.
//

#ifndef PITCHDETECTION_WAVFILE_H
#define PITCHDETECTION_WAVFILE_H

#include <fstream>
#include <vector>

struct WavConfig {
    unsigned int sampleRate = 44100;
    unsigned int numberOfChannels = 2;
    unsigned int bitsPerChannel = 16;
};

class WAVFile {
    int sampleRate = 0;
    int numberOfChannels = 0;
    int bytesPerChannel = 0;
    int audioFormat = 0;
    std::istream* stream;
    bool deleteStreamOnDestructor = false;

    void init(std::istream *stream);
public:
    static const int DATA_POSITION = 44;
    static const int PCM_AUDIO_FORMAT = 1;

    WAVFile(const WAVFile&) = delete;
    WAVFile(std::istream* stream);
    WAVFile(const char* data, int size);
    int getSampleRate() const;
    int getNumberOfChannels() const;
    int getAudioFormat() const;

    bool isValid() const;
    int getBytesPerChannel() const;
    void moveToTheFirstDataByte();
    int readData(void *buf, int size);
    int readData(void *buf, int size, int seek);
    ~WAVFile();

    // tested only for 16 bits per channel.
    template <typename ResultContainer>
    static ResultContainer addWavHeaderToRawPcmData(const char *data, size_t size, const WavConfig &config) {
        auto totalDataLen = size + DATA_POSITION;
        unsigned long sampleRate = config.sampleRate;
        unsigned int channels = config.numberOfChannels;
        unsigned long byteRate = (config.bitsPerChannel * sampleRate * channels) / 8;

        ResultContainer result(size + DATA_POSITION, 0);
        result[0] = 'R';  // RIFF/WAVE header
        result[1] = 'I';
        result[2] = 'F';
        result[3] = 'F';
        result[4] = (char) (totalDataLen & 0xff);
        result[5] = (char) ((totalDataLen >> 8) & 0xff);
        result[6] = (char) ((totalDataLen >> 16) & 0xff);
        result[7] = (char) ((totalDataLen >> 24) & 0xff);
        result[8] = 'W';
        result[9] = 'A';
        result[10] = 'V';
        result[11] = 'E';
        result[12] = 'f';  // 'fmt ' chunk
        result[13] = 'm';
        result[14] = 't';
        result[15] = ' ';
        result[16] = 16;  // 4 bytes: size of 'fmt ' chunk
        result[17] = 0;
        result[18] = 0;
        result[19] = 0;
        result[20] = 1;  // format = 1 for pcm and 2 for byte integer
        result[21] = 0;
        result[22] = (char) channels;
        result[23] = 0;
        result[24] = (char) (sampleRate & 0xff);
        result[25] = (char) ((sampleRate >> 8) & 0xff);
        result[26] = (char) ((sampleRate >> 16) & 0xff);
        result[27] = (char) ((sampleRate >> 24) & 0xff);
        result[28] = (char) (byteRate & 0xff);
        result[29] = (char) ((byteRate >> 8) & 0xff);
        result[30] = (char) ((byteRate >> 16) & 0xff);
        result[31] = (char) ((byteRate >> 24) & 0xff);
        result[32] = (char) (16*1)/8;  // block align
        result[33] = 0;
        result[34] = static_cast<char>(config.bitsPerChannel);  // bits per sample
        result[35] = 0;
        result[36] = 'd';
        result[37] = 'a';
        result[38] = 't';
        result[39] = 'a';
        result[40] = (char) (size & 0xff);
        result[41] = (char) ((size >> 8) & 0xff);
        result[42] = (char) ((size >> 16) & 0xff);
        result[43] = (char) ((size >> 24) & 0xff);

        std::copy(data, data + size, result.begin() + DATA_POSITION);

        return result;
    }

    template <typename ResultContainer>
    static ResultContainer addWavHeaderToRawPcmData(const char *data, size_t size) {
        return addWavHeaderToRawPcmData<ResultContainer>(data, size, WavConfig());
    }

    static WavConfig parseWavHeader(const char* data);

    template <typename Array>
    static WavConfig parseWavHeader(const Array& array) {
        if (array.size() < DATA_POSITION) {
            throw std::runtime_error("Invalid .wav file");
        }

        return parseWavHeader(array.data());
    }

    static bool isWavFile(const char* data, int size);

    bool shouldDeleteStreamOnDestructor() const;
    void setDeleteStreamOnDestructor(bool deleteStreamOnDestructor);
};


#endif //PITCHDETECTION_WAVFILE_H
