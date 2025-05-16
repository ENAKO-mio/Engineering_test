#ifndef SIGNAL_SOURCE_H
#define SIGNAL_SOURCE_H

#include <vector>
#include <string>
#include <tuple>

// Class to handle different signal sources
class SignalSource {
public:
    // Returns tuple of: signal data, source description, and sample rate
    std::tuple<std::vector<double>, std::string, int> getSignal();

private:
    // Source type enumeration
    enum SourceType {
        WAV_FILE = 0,
        SINE_WAVE,
        CHORD,
        NOISE
    };

    // Source-specific methods
    std::tuple<std::vector<double>, std::string, int> getWavSignal(const std::string& filename);
    std::tuple<std::vector<double>, std::string, int> getSineWave();
    std::tuple<std::vector<double>, std::string, int> getChord();
    std::tuple<std::vector<double>, std::string, int> getNoise();
};

#endif // SIGNAL_SOURCE_H#pragma once
