#include "signal_source.h"
#include "wav_processor.h"
#include "sim_signal.h"
#include <iostream>

std::tuple<std::vector<double>, std::string, int> SignalSource::getSignal() {
    // Display menu for signal source selection
    std::cout << "Select signal source:" << std::endl;
    std::cout << "1. WAV file" << std::endl;
    std::cout << "2. Sine wave" << std::endl;
    std::cout << "3. Chord" << std::endl;
    std::cout << "4. Noise" << std::endl;

    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer

    // Call appropriate method based on user selection
    switch (choice - 1) {
    case WAV_FILE:
        return getWavSignal("D:\\Users\\Desktop\\dataset\\GuitarChord\\chord1.0\\major\\B_major.wav");
    case SINE_WAVE:
        return getSineWave();
    case CHORD:
        return getChord();
    case NOISE:
        return getNoise();
    default:
        std::cerr << "Invalid choice" << std::endl;
        return std::make_tuple(std::vector<double>(), "Invalid", 0);
    }
}

// Implementation of getWavSignal
std::tuple<std::vector<double>, std::string, int> SignalSource::getWavSignal(const std::string& filename) {
    WAVHeader header;
    std::vector<double> audioData = readWAV(filename, header);

    if (audioData.empty()) {
        std::cerr << "Failed to read WAV file." << std::endl;
        return std::make_tuple(std::vector<double>(), "Failed WAV", 0);
    }

    // Display WAV file information
    std::cout << "Sample rate: " << header.sampleRate << " Hz" << std::endl;
    std::cout << "Channels: " << header.numChannels << std::endl;
    std::cout << "Bit depth: " << header.bitsPerSample << " bits" << std::endl;
    std::cout << "Data size: " << header.dataSize << " bytes" << std::endl;

    return std::make_tuple(audioData, "WAV File: " + filename, header.sampleRate);
}

// Add implementations for other methods (getSineWave, getChord, getNoise)