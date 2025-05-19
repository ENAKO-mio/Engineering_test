#ifndef WAV_PROCESSOR_H
#define WAV_PROCESSOR_H

#include <vector>
#include <string>
#include <cstdint>

// WAV file header structure
struct WAVHeader {
    char riff[4];           // RIFF identifier
    int32_t chunkSize;      // File size - 8 bytes
    char wave[4];           // WAVE identifier
    char fmt[4];            // fmt identifier
    int32_t subchunk1Size;  // Subchunk1 size: usually 16 for PCM
    int16_t audioFormat;    // Audio format: PCM = 1
    int16_t numChannels;    // Number of channels
    int32_t sampleRate;     // Sample rate
    int32_t byteRate;       // Byte rate
    int16_t blockAlign;     // Block align
    int16_t bitsPerSample;  // Bits per sample
    char data[4];           // "data" identifier
    int32_t dataSize;       // Total number of bytes in audio data
};


std::vector<double> readWAV(const std::string& filename, WAVHeader& header);
void processSignal(std::vector<float>& signal);

#endif // WAV_PROCESSOR_H