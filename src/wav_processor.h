#ifndef WAV_PROCESSOR_H
#define WAV_PROCESSOR_H

#include <vector>
#include <string>
#include <cstdint>

// WAV文件头结构
struct WAVHeader {
    char riff[4];           // RIFF标志
    int32_t chunkSize;      // 文件大小 -8
    char wave[4];           // WAVE标志
    char fmt[4];            // fmt 标志
    int32_t subchunk1Size;  // Subchunk1大小:16
    int16_t audioFormat;    // 音频格式: PCM = 1
    int16_t numChannels;    // 通道数
    int32_t sampleRate;     // 采样率
    int32_t byteRate;       // 字节率
    int16_t blockAlign;     // 块对齐
    int16_t bitsPerSample;  // 每个采样点的位数
    char data[4];           // "data" 标志
    int32_t dataSize;       // 音频数据的总字节数
};


std::vector<double> readWAV(const std::string& filename, WAVHeader& header);
void processSignal(std::vector<float>& signal);



#endif // WAV_PROCESSOR_H