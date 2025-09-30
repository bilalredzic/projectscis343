#ifndef WAV_H
#define WAV_H

#include <stdint.h>
#include <stddef.h>

// Struct to hold the wav file header
struct wav_header{
    char riff[4]; // "RIFF"
    uint32_t size; // Size of the entire file in bytes minus 8 bytes for "RIFF" and size
    char type[4]; // File Type, should be "WAVE"
    char format[4]; // Format chunk, must be "fmt"
    uint32_t lengthformat; // Length of format data
    uint16_t formattype; // Format type
    uint16_t channels; // Number of channels
    uint32_t samplerate; // Sample rate
    uint32_t bytecalc; // Sample rate * bitsPerSample * channels/8
    uint16_t bitcalc; // (Bits per sample * numChannels)/ data type size
    uint16_t bitspersample; // Bits per sample
    char data[4]; // data header, must be "data"
    uint32_t datasize; // data section size
};

// Struct to hold the wav file data
struct wav_file{
    struct wav_header* header; // Pointer to the header
    size_t filesize;// Size of the entire file
    char* data; // Pointer to the data
    char* buffer; // Pointer to hold the entire file contents
};

struct wav_header* wavheaderfunc(char* bytes44); // Takes first 44 bytes of a file and returns them as a wav_header pointer.

struct wav_file* wav_load(char* path); // Loads a .wav file from disk using read_file. Returns a wav_file wrapper.

int wav_write(struct wav_file* wf, char* path); // Writes a wav_file to disk at given path. Returns 0 on success, 1 on failure.

void wav_free(struct wav_file* wf); // Function to free the allocated memory for a wav_file struct.

#endif // WAV_H

