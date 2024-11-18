#include <iostream>
#include <pthread.h>
#include <string>

// Shared variable
std::string sharedData = "";

// Mutex to protect access to shared variable
pthread_mutex_t mutex;

// Function for Thread_1 to write data
void* writeData(void* arg) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to safely write to shared data
    sharedData = "Hello from Irvin Lin Thread_1!";
    std::cout << "Thread_1 wrote: " << sharedData << std::endl;
    pthread_mutex_unlock(&mutex);  // Unlock the mutex after writing
    return nullptr;
}

// Function for Thread_2 to read data
void* readData(void* arg) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to safely read from shared data
    std::cout << "Thread_2 read: " << sharedData << std::endl;
    pthread_mutex_unlock(&mutex);  // Unlock the mutex after reading
    return nullptr;
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&mutex, nullptr);

    // Create threads
    pthread_t thread1, thread2;

    // Create Thread_1 to write data
    pthread_create(&thread1, nullptr, writeData, nullptr);
    // Create Thread_2 to read data
    pthread_create(&thread2, nullptr, readData, nullptr);

    // Wait for threads to finish
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
