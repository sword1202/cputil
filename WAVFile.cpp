//
// Created by Semyon Tikhonenko on 8/19/16.
//

#include <assert.h>
#include "WAVFile.h"
#include <iostream>

#ifndef NO_BOOST
#include <boost/iostreams/stream.hpp>
#endif

static const int SAMPLE_RATE_SIZE = 4;
static const int SAMPLE_RATE_POSITION = 24;
static const int CHANNELS_NUMBER_SIZE = 2;
static const int CHANNELS_NUMBER_POSITION = 22;
static const int BITS_PER_CHANNEL_SIZE = 2;
static const int BITS_PER_CHANNEL_POSITION = 34;
static const int AUDIO_FORMAT_POSITION = 20;

WAVFile::WAVFile(std::istream *stream) {
    init(stream);
}

void WAVFile::init(std::istream *stream) {
    assert(*stream && " stream is invalid");
    this->stream = stream;
    stream->seekg(CHANNELS_NUMBER_POSITION, std::ios_base::beg);
    stream->read((char*)&numberOfChannels, CHANNELS_NUMBER_SIZE);
    stream->seekg(SAMPLE_RATE_POSITION, std::ios_base::beg);
    stream->read((char*)&sampleRate, SAMPLE_RATE_SIZE);
    int bitsPerChannel = 0;
    stream->seekg(BITS_PER_CHANNEL_POSITION, std::ios_base::beg);
    stream->read((char*)&bitsPerChannel, BITS_PER_CHANNEL_SIZE);
    assert(bitsPerChannel >= 8);
    bytesPerChannel = bitsPerChannel / 8;
    stream->seekg(AUDIO_FORMAT_POSITION, std::ios_base::beg);
    stream->read((char*)&audioFormat, sizeof(short));
    moveToTheFirstDataByte();
}

#ifndef NO_BOOST

WAVFile::WAVFile(const char *array, int size) {
    stream =  new boost::iostreams::stream<boost::iostreams::array_source>(array, size);
    deleteStreamOnDestructor = true;
    init(stream);
}

#endif

bool WAVFile::isValid() const {
    return !stream->fail();
}

int WAVFile::getNumberOfChannels() const {
    return numberOfChannels;
}

int WAVFile::getBytesPerChannel() const {
    return bytesPerChannel;
}

int WAVFile::getSampleRate() const {
    return sampleRate;
}

void WAVFile::moveToTheFirstDataByte() {
    stream->seekg(DATA_POSITION, std::ios::beg);
}

int WAVFile::readData(void *buf, int size) {
    stream->read((char*)buf, size);
    return (int) stream->gcount();
}

int WAVFile::readData(void *buf, int size, int seek) {
    stream->seekg(DATA_POSITION + seek, std::ios::beg);
    stream->read((char*)buf, size);
    return (int) stream->gcount();
}

bool WAVFile::shouldDeleteStreamOnDestructor() const {
    return deleteStreamOnDestructor;
}

void WAVFile::setDeleteStreamOnDestructor(bool deleteStreamOnDestructor) {
    WAVFile::deleteStreamOnDestructor = deleteStreamOnDestructor;
}

WAVFile::~WAVFile() {
    if (deleteStreamOnDestructor) {
        delete stream;
    }
}

bool WAVFile::isWavFile(const char *data, int size) {
    assert(size >= 0);
    if (size <= DATA_POSITION) {
        return false;
    }

    return data[0] == 'R' &&
    data[1] == 'I' &&
    data[2] == 'F' &&
    data[3] == 'F' && 
    data[8] == 'W' &&
    data[9] == 'A' &&
    data[10] == 'V' &&
    data[11] == 'E' &&
    data[12] == 'f' && 
    data[13] == 'm' &&
    data[14] == 't';
}

int WAVFile::getAudioFormat() const {
    return audioFormat;
}

WavConfig WAVFile::parseWavHeader(const char *data) {
    WavConfig config;
    config.numberOfChannels = *reinterpret_cast<const uint16_t*>(data + CHANNELS_NUMBER_POSITION);
    config.sampleRate = *reinterpret_cast<const uint32_t*>(data + SAMPLE_RATE_POSITION);
    config.bitsPerChannel = *reinterpret_cast<const uint16_t*>(data + BITS_PER_CHANNEL_POSITION);
    return config;
}

bool WavConfig::operator==(const WavConfig &rhs) const {
    return sampleRate == rhs.sampleRate &&
            numberOfChannels == rhs.numberOfChannels &&
            bitsPerChannel == rhs.bitsPerChannel;
}

bool WavConfig::operator!=(const WavConfig &rhs) const {
    return !(rhs == *this);
}
