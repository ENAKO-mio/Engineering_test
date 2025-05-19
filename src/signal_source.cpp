/*
 * @file      signal_source.cpp
 * @brief     Provides signal source selection and signal generation functions.
 * @details
 *            - Allows user to select the type of signal source via a menu.
 *            - Supports reading audio from a WAV file, generating sine waves, chords, and noise signals.
 *            - Each signal type supports parameter customization (sample rate, frequency, duration, amplitude, etc.).
 *            - Returns a tuple containing audio data, a description string, and the sample rate.
 * @author    Erick 
 * @date      2025.5
 */


#include "signal_source.h"
#include "wav_processor.h"
#include "sim_signal.h"
#include <iostream>

std::tuple<std::vector<double>, std::string, int> SignalSource::getSignal() {
    
    int choice = 0;

    //std::cin >> choice;
    //std::cin.ignore(); // Clear input buffer

    
    switch (choice - 1) {
    case WAV_FILE:
        return getWavSignal("D:\\Users\\Desktop\\dataset\\GuitarChord\\chord1.0\\major\\B_major.wav");
    case SINE_WAVE:
        return getSineWave();
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



// Implementation of getSineWave
std::tuple<std::vector<double>, std::string, int> SignalSource::getSineWave() {
    double frequency, duration, amplitude = 1.0;
    int sampleRate;

    std::cout << "Enter sample rate (e.g., 44100): ";
    std::cin >> sampleRate;
    std::cout << "Enter frequency (Hz): ";
    std::cin >> frequency;
    std::cout << "Enter duration (sec): ";
    std::cin >> duration;
    std::cout << "Enter amplitude (default 1.0): ";
    std::cin >> amplitude;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto signal = generateSineWave(sampleRate, frequency, duration, amplitude);
    std::string desc = "Sine Wave: " + std::to_string(frequency) + "Hz, " + std::to_string(duration) + "s";
    return std::make_tuple(signal, desc, sampleRate);
}


// Implementation of getNoise
std::tuple<std::vector<double>, std::string, int> SignalSource::getNoise() {
    int sampleRate;
    double duration, amplitude = 0.5;

    std::cout << "Enter sample rate (e.g., 44100): ";
    std::cin >> sampleRate;
    std::cout << "Enter duration (sec): ";
    std::cin >> duration;
    std::cout << "Enter amplitude (default 0.5): ";
    std::cin >> amplitude;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int numSamples = static_cast<int>(sampleRate * duration);
    auto signal = generateNoiseSignal(numSamples, amplitude);

    std::string desc = "Noise: " + std::to_string(duration) + "s";
    return std::make_tuple(signal, desc, sampleRate);
}