#ifndef SIGNAL_PROCESSOR_H
#define SIGNAL_PROCESSOR_H

#include <vector>
#include <string>

// Enumeration for processing mode
enum class ProcessMode {
    Streaming,   // Streaming mode: process by buffer chunks
    Batch        // Batch mode: process the whole signal at once
};

// SignalProcessor class handles audio signal processing
class SignalProcessor {
public:

    void processSignal(const std::vector<double>& signal,
        int sampleRate,
        int bufferSize,
        ProcessMode mode = ProcessMode::Streaming);


    void processBuffer(const std::vector<double>& buffer);


    void processWhole(const std::vector<double>& signal);


    void displayResults();

private:
    int sampleRate = 44100;   // Sampling rate
    int bufferSize = 4096;    // Buffer size
    // Add your processor members here, for example:
    // MainComponent mainComponent;
    // AudioSignalProcessor processor;
};

#endif // SIGNAL_PROCESSOR_H