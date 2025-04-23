#include <windows.h>
#include <mmsystem.h> // For WinMM API
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>   // For system()
#include <stdexcept> // For exceptions

// --- Configuration ---
const int SAMPLE_RATE = 16000;
const int CHANNELS = 1; // Mono
const int BITS_PER_SAMPLE = 16;
const int RECORD_SECONDS = 15; // Duration of recording

// Buffer settings for WinMM
const int NUM_BUFFERS = 3; // Use multiple buffers for smoother recording
const int BUFFER_SIZE = (SAMPLE_RATE * BITS_PER_SAMPLE / 8) * 1; // 1 second worth of data per buffer

// Define paths carefully
const std::string TEMP_OUTPUT_DIR = "C:\\Users\\prath\\Temp_Files\\"; // Writable temporary location on Windows
const std::string TEMP_OUTPUT_FILENAME = "recorded_audio.wav";
const std::string TEMP_OUTPUT_FULL_PATH = TEMP_OUTPUT_DIR + TEMP_OUTPUT_FILENAME;
// --- Add these lines in the Configuration section near the top ---

// WSL Specific paths for the new function
const std::string WSL_DISTRO_NAME = "Ubuntu"; // Your WSL distribution name
const std::string WSL_TARGET_PATH_INSIDE = "\\home\\icelake2\\capstone_ASR\\"; // Path within WSL (use double backslashes for C++)
const std::string WSL_TARGET_FILENAME = "recorded_audio.wav"; // This should already be there

// --- Make sure they are declared before the main() function starts ---
// --- End Configuration ---

// --- Global Variables for WinMM ---
HWAVEIN hWaveIn = nullptr; // Handle for the recording device
WAVEHDR waveHeaders[NUM_BUFFERS] = { 0 }; // Headers for the buffers
char* audioBuffers[NUM_BUFFERS] = { nullptr }; // Actual audio buffers
std::vector<int16_t> recordedData; // Vector to accumulate recorded samples
volatile bool recording = false; // Flag to control recording state
volatile int buffersProcessed = 0; // Counter for processed buffers
// --- End Global Variables ---

// --- Function Declarations ---
bool saveWavFile(const std::string& filename, const std::vector<int16_t>& audioData);
bool moveToWSL(const std::string&, const std::string&, const std::string&, const std::string&);
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
void cleanupRecording(); // Function to free resources

// --- Main Application ---
int main() {
    WAVEFORMATEX wfx = {};
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = CHANNELS;
    wfx.nSamplesPerSec = SAMPLE_RATE;
    wfx.wBitsPerSample = BITS_PER_SAMPLE;
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0; // No extra format information

    MMRESULT mmResult;

    // 1. Open Wave Input Device
    mmResult = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION);
    if (mmResult != MMSYSERR_NOERROR) {
        char errorText[MAXERRORLENGTH];
        waveInGetErrorTextA(mmResult, errorText, MAXERRORLENGTH);
        std::cerr << "Error opening wave input device: " << errorText << std::endl;
        return 1;
    }

    // 2. Allocate and Prepare Buffers
    recordedData.reserve(SAMPLE_RATE * CHANNELS * (RECORD_SECONDS + 1)); // Pre-allocate some space
    for (int i = 0; i < NUM_BUFFERS; ++i) {
        audioBuffers[i] = new (std::nothrow) char[BUFFER_SIZE];
        if (!audioBuffers[i]) {
            std::cerr << "Error allocating buffer " << i << std::endl;
            cleanupRecording();
            return 1;
        }

        waveHeaders[i].lpData = audioBuffers[i];
        waveHeaders[i].dwBufferLength = BUFFER_SIZE;
        waveHeaders[i].dwFlags = 0;
        waveHeaders[i].dwLoops = 0;

        mmResult = waveInPrepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
        if (mmResult != MMSYSERR_NOERROR) {
            std::cerr << "Error preparing header " << i << std::endl;
            cleanupRecording();
            return 1;
        }

        // 3. Add Buffers to the Queue
        mmResult = waveInAddBuffer(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
        if (mmResult != MMSYSERR_NOERROR) {
            std::cerr << "Error adding buffer " << i << std::endl;
            cleanupRecording();
            return 1;
        }
    }

    // 4. Start Recording
    recording = true;
    buffersProcessed = 0;
    mmResult = waveInStart(hWaveIn);
    if (mmResult != MMSYSERR_NOERROR) {
        std::cerr << "Error starting recording." << std::endl;
        cleanupRecording();
        return 1;
    }

    std::cout << "Recording for " << RECORD_SECONDS << " seconds using WinMM..." << std::endl;

    // 5. Wait for Recording Duration
    Sleep(RECORD_SECONDS * 1000);

    // 6. Signal Stop
    recording = false; // Signal callback to stop requeueing

    std::cout << "Stopping recording..." << std::endl;

    // 7. Stop Recording Input
    // It's better to reset to mark all buffers as done and return them quickly
    mmResult = waveInReset(hWaveIn);
    if (mmResult != MMSYSERR_NOERROR) {
        std::cerr << "Error resetting wave input." << std::endl;
        // Continue cleanup regardless
    }

    // Optional: Small sleep to allow final callbacks to process, though waveInReset should handle it
    Sleep(200);

    // 8. Cleanup (Unprepare headers, close device, free memory) is done in cleanupRecording
    cleanupRecording(); // This also unprepares headers

    std::cout << "Recording finished. Recorded " << recordedData.size() << " samples." << std::endl;


    // 9. Save the recorded data
    if (recordedData.empty()) {
        std::cerr << "Error: No audio data was recorded." << std::endl;
        return 1;
    }
    if (!saveWavFile(TEMP_OUTPUT_FULL_PATH, recordedData)) {
        return 1; // Exit if saving failed
    }

    // 10. Move the temporary file to the WSL path
// --- Inside main() function, after saveWavFile ---

// Move the temporary file to the WSL path using the NEW function signature
    if (!moveToWSL(TEMP_OUTPUT_FULL_PATH, WSL_DISTRO_NAME, WSL_TARGET_PATH_INSIDE, WSL_TARGET_FILENAME)) {
        std::cerr << "File remains in temporary Windows location: " << TEMP_OUTPUT_FULL_PATH << std::endl;
        return 1; // Exit if moving failed
    }

    std::cout << "Process completed successfully." << std::endl;
    return 0;
}

// --- WinMM Callback Function ---
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    switch (uMsg) {
    case WIM_OPEN:
        // std::cout << "Wave Input Device Opened." << std::endl;
        break;

    case WIM_DATA:
    {
        WAVEHDR* pHeader = (WAVEHDR*)dwParam1;
        if (pHeader->dwBytesRecorded > 0) {
            // Append recorded data to our vector
            size_t numSamples = pHeader->dwBytesRecorded / sizeof(int16_t);
            int16_t* recordedSamples = reinterpret_cast<int16_t*>(pHeader->lpData);
            recordedData.insert(recordedData.end(), recordedSamples, recordedSamples + numSamples);
        }

        buffersProcessed++; // Increment counter

       // If still recording, requeue this buffer
        if (recording) {
            waveInAddBuffer(hwi, pHeader, sizeof(WAVEHDR));
        }
    }
    break;

    case WIM_CLOSE:
        // std::cout << "Wave Input Device Closed." << std::endl;
        break;

    default:
        break;
    }
}

// --- Cleanup Function ---
void cleanupRecording() {
    if (hWaveIn) {
        // Stop recording if it hasn't been stopped already (might return error if already stopped/reset)
        waveInStop(hWaveIn);
        // Reset might be redundant if already called, but ensures all buffers are returned
        waveInReset(hWaveIn);

        // Unprepare headers
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            if (waveHeaders[i].dwFlags & WHDR_PREPARED) {
                waveInUnprepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
            }
        }

        // Close the device
        waveInClose(hWaveIn);
        hWaveIn = nullptr;
    }

    // Free allocated buffer memory
    for (int i = 0; i < NUM_BUFFERS; ++i) {
        delete[] audioBuffers[i];
        audioBuffers[i] = nullptr;
    }
    //std::cout << "Recording resources cleaned up." << std::endl;
}


// --- WAV File Saving Function (Identical to previous RtAudio version) ---
bool saveWavFile(const std::string& filename, const std::vector<int16_t>& audioData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open temporary WAV file for writing: " << filename << std::endl;
        return false;
    }

    // --- WAV Header ---
    const int16_t BITS_PER_SAMPLE_WAV = BITS_PER_SAMPLE; // Use constant
    const int16_t NUM_CHANNELS_WAV = CHANNELS; // Use constant
    const int32_t SAMPLE_RATE_32 = SAMPLE_RATE; // Use constant
    const int16_t AUDIO_FORMAT = 1; // 1 = PCM

    // RIFF chunk descriptor
    file.write("RIFF", 4);
    int32_t dataSizeBytes = audioData.size() * sizeof(int16_t);
    int32_t chunkSize = 36 + dataSizeBytes; // 36 (header size without RIFF/chunkSize) + data size
    file.write(reinterpret_cast<const char*>(&chunkSize), 4);
    file.write("WAVE", 4);

    // fmt sub-chunk
    file.write("fmt ", 4);
    int32_t subchunk1Size = 16; // 16 for PCM
    file.write(reinterpret_cast<const char*>(&subchunk1Size), 4);
    file.write(reinterpret_cast<const char*>(&AUDIO_FORMAT), 2);
    file.write(reinterpret_cast<const char*>(&NUM_CHANNELS_WAV), 2);
    file.write(reinterpret_cast<const char*>(&SAMPLE_RATE_32), 4);
    int32_t byteRate = SAMPLE_RATE * NUM_CHANNELS_WAV * BITS_PER_SAMPLE_WAV / 8;
    file.write(reinterpret_cast<const char*>(&byteRate), 4);
    int16_t blockAlign = NUM_CHANNELS_WAV * BITS_PER_SAMPLE_WAV / 8;
    file.write(reinterpret_cast<const char*>(&blockAlign), 2);
    file.write(reinterpret_cast<const char*>(&BITS_PER_SAMPLE_WAV), 2);

    // data sub-chunk
    file.write("data", 4);
    file.write(reinterpret_cast<const char*>(&dataSizeBytes), 4); // Size of audio data

    // --- Write Audio Data ---
    file.write(reinterpret_cast<const char*>(audioData.data()), dataSizeBytes);

    if (!file.good()) {
        std::cerr << "Error: Failed to write all data to WAV file." << std::endl;
        file.close();
        return false;
    }

    file.close();
    std::cout << "Temporarily saved WAV file: " << filename << std::endl;
    return true;
}

// --- WSL File Moving Function (Identical to previous RtAudio version) ---
// --- WSL File Moving Function (Should NOT need changes) ---
// --- WSL File Moving Function (Using PowerShell Move-Item) ---
// --- Replace your OLD moveToWSL function definition with THIS ---

// --- WSL File Moving Function (Using PowerShell Move-Item) ---
// PASTE THIS ENTIRE BLOCK where the old function was:

// --- WSL File Moving Function (Using PowerShell Move-Item) ---
bool moveToWSL(const std::string& windowsSourcePath, const std::string& wslDistroName, const std::string& wslTargetPathInsideDistro, const std::string& wslTargetFilename) {

    // Construct the target WSL UNC path: \\wsl$\<DistroName>\<TargetPath>\<TargetFilename>
    std::string wslUncDest = "\\\\wsl$\\" + wslDistroName + wslTargetPathInsideDistro + wslTargetFilename;

    // Construct the PowerShell command.
    std::string command = "powershell.exe -ExecutionPolicy Bypass -NoProfile -Command \"";
    command += "Move-Item -Force -LiteralPath '";
    command += windowsSourcePath;
    command += "' -Destination '";
    command += wslUncDest;
    command += "'"; // Close destination path single quote
    command += "\""; // Close the -Command double quote

    std::cout << "Executing PowerShell command: " << command << std::endl;

    int result = system(command.c_str()); // Execute the command

    if (result != 0) {
        std::cerr << "Error: Failed to move file using PowerShell. 'system' call returned " << result << std::endl;
        std::cerr << "Check if PowerShell is in PATH, the command syntax is correct, paths exist, and permissions are sufficient." << std::endl;
        std::cerr << "Source: [" << windowsSourcePath << "]" << std::endl;
        std::cerr << "Destination: [" << wslUncDest << "]" << std::endl;
        return false;
    }

    std::cout << "Successfully moved file to WSL path via PowerShell: " << wslUncDest << std::endl;
    return true;
}
// --- End of function definition to paste ---