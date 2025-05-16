#include <iostream>
#include "signal_source.h"
#include "signal_processor.h"

int main() {
    const int BUFFER_SIZE = 4096;
    int sampleRate = 44100;

    // Get signal from modular input system
    SignalSource signalSource;
    auto [signal, sourceInfo, actualSampleRate] = signalSource.getSignal();

    if (signal.empty()) {
        std::cerr << "Failed to acquire signal." << std::endl;
        return 1;
    }

    sampleRate = actualSampleRate;

    // Display signal information
    std::cout << "Signal source: " << sourceInfo << std::endl;
    std::cout << "Sample rate: " << sampleRate << " Hz" << std::endl;
    std::cout << "Signal size: " << signal.size() << " samples" << std::endl;

    // Process the signal using the signal processor module
    SignalProcessor processor;

    ProcessMode mode = ProcessMode::Batch;    //  ProcessMode::Batch  || ProcessMode::Streaming;

    processor.processSignal(signal, sampleRate, BUFFER_SIZE);

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    return 0;
}