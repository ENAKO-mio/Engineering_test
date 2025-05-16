#ifndef SIM_SIGNAL_H
#define SIM_SIGNAL_H

#include <vector>

// Generate a sine wave signal
std::vector<double> generateSineWave(int sampleRate, double frequency, double duration, double amplitude = 1.0);

// Generate a chord signal (sum of multiple sine waves)
std::vector<double> generateChordSignal(int sampleRate, const std::vector<double>& frequencies, double duration, double amplitude = 1.0);

// Generate a noise signal
std::vector<double> generateNoiseSignal(int numSamples, double amplitude = 0.5);

#endif // SIM_SIGNAL_H