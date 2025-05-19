/*
 * @file      sim_signal.cpp
 * @brief     Implements functions to generate synthetic audio signals.
 * @details
 *            - Generates single-frequency sine waves.
 *            - Generates chords by combining multiple sine waves.
 *            - Generates white noise signals with specified amplitude.
 * @author    Erick
 * @date      2025.5
 */

#include "sim_signal.h"
#include <cmath>
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897
#endif

std::vector<double> generateSineWave(int sampleRate, double frequency, double duration, double amplitude) {
    int numSamples = static_cast<int>(sampleRate * duration);
    std::vector<double> signal(numSamples);

    for (int i = 0; i < numSamples; i++) {
        double time = static_cast<double>(i) / sampleRate;
        signal[i] = amplitude * std::sin(2.0 * M_PI * frequency * time);
    }
    return signal;
}

std::vector<double> generateChordSignal(int sampleRate, const std::vector<double>& frequencies, double duration, double amplitude) {
    int numSamples = static_cast<int>(sampleRate * duration);
    std::vector<double> signal(numSamples, 0.0);

    for (double freq : frequencies) {
        for (int i = 0; i < numSamples; i++) {
            double time = static_cast<double>(i) / sampleRate;
            signal[i] += (amplitude / frequencies.size()) * std::sin(2.0 * M_PI * freq * time);
        }
    }
    return signal;
}

std::vector<double> generateNoiseSignal(int numSamples, double amplitude) {
    std::vector<double> signal(numSamples);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-amplitude, amplitude);

    for (int i = 0; i < numSamples; i++) {
        signal[i] = dist(gen);
    }
    return signal;
}