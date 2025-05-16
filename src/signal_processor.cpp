#include "signal_processor.h"
#include <iostream>
#include <algorithm>

// Main processing interface with mode selection
void SignalProcessor::processSignal(const std::vector<double>& signal,
    int sampleRate,
    int bufferSize,
    ProcessMode mode) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;

    // Initialize processing components here if needed
    // mainComponent = MainComponent(sampleRate, bufferSize);
    // processor = AudioSignalProcessor(bufferSize);

    if (mode == ProcessMode::Streaming) {
        // Streaming: process signal in buffer-sized chunks
        for (int i = 0; i < signal.size(); i += bufferSize) {
            int remainingSize = std::min(bufferSize, static_cast<int>(signal.size()) - i);
            std::vector<double> buffer(signal.begin() + i, signal.begin() + i + remainingSize);

            // Pad buffer if it's not full
            if (remainingSize < bufferSize) {
                buffer.resize(bufferSize, 0.0);
            }
            std::cout << "Processing buffer " << (i / bufferSize + 1) << ":" << std::endl;
            processBuffer(buffer);
        }
    }
    else if (mode == ProcessMode::Batch) {
        // Batch: process the entire signal at once
        processWhole(signal);
    }

    // Show final processing results
    displayResults();
}

// Process a single buffer (used in streaming mode)
void SignalProcessor::processBuffer(const std::vector<double>& buffer) {
    // Handle processing for one buffer
    // Example:
    // std::string resultStr = processor.processSignal(buffer, mainComponent);
    // ... (additional processing if needed)
}

// Process the whole signal at once (used in batch mode)
void SignalProcessor::processWhole(const std::vector<double>& signal) {
    // Handle processing for the entire signal
    // Example:
    // std::string resultStr = processor.processSignal(signal, mainComponent);
    // ... (additional processing if needed)
}

// Display final results after processing
void SignalProcessor::displayResults() {
    std::cout << "Final results:" << std::endl;
    // Example:
    // mainComponent.displayChordResults();
    std::cout << "\n\n" << std::endl;
}