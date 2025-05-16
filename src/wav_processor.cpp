#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <cstring>

#include "wav_processor.h"



std::vector<double> readWAV(const std::string& filename, WAVHeader& header) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    if (std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE") {
        throw std::runtime_error("不是有效的WAV文件");
    }

    if (header.audioFormat != 1) {
        throw std::runtime_error("不支持的音频格式（仅支持PCM）");
    }

    std::vector<double> audioData;
    audioData.reserve(header.dataSize / (header.bitsPerSample / 8));  // 计算音频文件中有多少个音频样本

    std::vector<char> buffer(header.dataSize);
    file.read(buffer.data(), header.dataSize);



    for (size_t i = 0; i < buffer.size(); i += header.bitsPerSample / 8)  // 位深度除以 8，将位深度转换为字节数,1字节 = 8位;i 的值跳过一个完整的音频样本的字节数，指向下一个样本的开始位置。
    {
        double sample = 0;
        if (header.bitsPerSample == 8) {
            sample = static_cast<double>(static_cast<uint8_t>(buffer[i])) / 128.0 - 1.0;
            // 将当前字节数据转换为 uint8_t（无符号 8 位整数）,再将这个无符号整数转换为 double 型，最后归一化
        }
        else if (header.bitsPerSample == 16) {
            sample = static_cast<double>(*reinterpret_cast<int16_t*>(&buffer[i])) / 32768.0;
            // 从 buffer[i] 开始的 两个字节 被解释为一个 16 位有符号整数
        }
        else if (header.bitsPerSample == 24) {
            int32_t sample24 = (static_cast<uint8_t>(buffer[i]) |
                (static_cast<uint8_t>(buffer[i + 1]) << 8) |
                (static_cast<uint8_t>(buffer[i + 2]) << 16));
            if (sample24 & 0x800000) sample24 |= 0xFF000000; // 符号扩展
            sample = static_cast<double>(sample24) / 8388608.0;
        }
        else {
            throw std::runtime_error("不支持的位深度");
        }
        audioData.push_back(sample);
    }

    return audioData;
}

void processSignal(std::vector<double>& signal) {
    // 调整音量
    for (auto& sample : signal) {
        sample *= 1.5;
    }
}

void writeWAV(const std::string& filename, const WAVHeader& header, const std::vector<float>& audioData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("无法创建文件: " + filename);
    }

    // 写入WAV文件头
    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));

    // 将浮点数据转换回原始格式并写入文件
    for (const auto& sample : audioData) {
        switch (header.bitsPerSample) {
        case 8: {
            uint8_t intSample = static_cast<uint8_t>((sample + 1.0f) * 128.0f);
            file.write(reinterpret_cast<const char*>(&intSample), sizeof(uint8_t));
            break;
        }
        case 16: {
            int16_t intSample = static_cast<int16_t>(sample * 32768.0f);
            file.write(reinterpret_cast<const char*>(&intSample), sizeof(int16_t));
            break;
        }
        case 24: {
            int32_t intSample = static_cast<int32_t>(sample * 8388608.0f);
            uint8_t bytes[3] = {
                static_cast<uint8_t>(intSample & 0xFF),
                static_cast<uint8_t>((intSample >> 8) & 0xFF),
                static_cast<uint8_t>((intSample >> 16) & 0xFF)
            };
            file.write(reinterpret_cast<const char*>(bytes), 3);
            break;
        }
        default:
            throw std::runtime_error("不支持的位深度");
        }
    }
}
