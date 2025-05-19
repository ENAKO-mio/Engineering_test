/*
 * @file      wav_processor.cpp
 * @brief     Implements reading, processing, and writing of WAV audio files.
 * @details
 *            - Provides functions to read WAV files into normalized floating-point vectors.
 *            - Supports PCM WAV files with 8, 16, or 24 bits per sample.
 *            - Includes basic audio processing (e.g., volume adjustment).
 *            - Supports writing processed audio data back to WAV files.
 * @author    Erick
 * @date      2025.5
 */


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
        throw std::runtime_error("Unable to open file: " + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    if (std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE") {
        throw std::runtime_error("Not a valid WAV file");
    }

    if (header.audioFormat != 1) {
        throw std::runtime_error("Unsupported audio format (only PCM supported)");
    }

    std::vector<double> audioData;
    audioData.reserve(header.dataSize / (header.bitsPerSample / 8));  // Calculate the number of audio samples in the file

    std::vector<char> buffer(header.dataSize);
    file.read(buffer.data(), header.dataSize);

    for (size_t i = 0; i < buffer.size(); i += header.bitsPerSample / 8)  // Bit depth divided by 8 converts bits to bytes, 1 byte = 8 bits; i skips the bytes for one complete audio sample, pointing to the start of the next sample.
    {
        double sample = 0;
        if (header.bitsPerSample == 8) {
            sample = static_cast<double>(static_cast<uint8_t>(buffer[i])) / 128.0 - 1.0;
            // Convert current byte data to uint8_t (unsigned 8-bit integer), then to double, and finally normalize
        }
        else if (header.bitsPerSample == 16) {
            sample = static_cast<double>(*reinterpret_cast<int16_t*>(&buffer[i])) / 32768.0;
            // The two bytes starting from buffer[i] are interpreted as a 16-bit signed integer
        }
        else if (header.bitsPerSample == 24) {
            int32_t sample24 = (static_cast<uint8_t>(buffer[i]) |
                (static_cast<uint8_t>(buffer[i + 1]) << 8) |
                (static_cast<uint8_t>(buffer[i + 2]) << 16));
            if (sample24 & 0x800000) sample24 |= 0xFF000000; // Sign extension
            sample = static_cast<double>(sample24) / 8388608.0;
        }
        else {
            throw std::runtime_error("Unsupported bit depth");
        }
        audioData.push_back(sample);
    }

    return audioData;
}

void processSignal(std::vector<double>& signal) {
    // Adjust the volume
    for (auto& sample : signal) {
        sample *= 1.5;
    }
}

void writeWAV(const std::string& filename, const WAVHeader& header, const std::vector<float>& audioData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to create file: " + filename);
    }

    // Write WAV file header
    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));

    // Convert floating point data back to raw format and write to file
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
            throw std::runtime_error("Unsupported bit depth");
        }
    }
}