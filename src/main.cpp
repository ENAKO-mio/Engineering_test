#include <iostream>
#include "signal_source.h"
#include "signal_processor.h"

int main() {

    // Get signal from modular input system
    SignalSource signalSource;
    auto [signal, sourceInfo, actualSampleRate] = signalSource.getSignal();

    if (signal.empty()) {
        std::cerr << "Failed to acquire signal." << std::endl;
        return 1;
    }
;
    // Display signal information
    std::cout << "Signal source: " << sourceInfo << std::endl;
    std::cout << "Sample rate: " << actualSampleRate << " Hz" << std::endl;
    std::cout << "Signal size: " << signal.size() << " samples" << std::endl;


    // Process the signal using the signal processor module
    const int BUFFER_SIZE = 4096;

    SignalProcessor processor;


    processor.processSignal(signal, actualSampleRate, BUFFER_SIZE, ProcessMode::Streaming);

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    return 0;
}