/**
 * NumberGuessGame.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "MemoryManager.h"

// Static field initialization
Timer MemoryManager::memoryTimer = Timer(MEMORY_REPORT_INTERVAL, true);

void MemoryManager::reportMemory() {
// Only include the memory reporting code when debug mode is enabled
#if DEBUG

    // Get the current memory available (bytes)
    int memFree = freeMemory();

    // Report the number of available memory
    Serial.println("M> " + String(memFree) + " bytes free");

#endif
}

void MemoryManager::update() {
// Only include the memory reporting code when debug mode is enabled
#if DEBUG

    // Make sure the timer is finished
    if(!MemoryManager::memoryTimer.isFinished())
        return;

    // Restart the timer
    MemoryManager::memoryTimer.start();

    // Report the memory to the log
    MemoryManager::reportMemory();

#endif
}
