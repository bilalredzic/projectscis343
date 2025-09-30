#include "wav.h"
#include "file_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function to parse the header from raw bytes
struct wav_header* wavheaderfunc(char* bytes44) {
    struct wav_header* myHeader = malloc(sizeof(struct wav_header)); // Allocate memory for the header
    memcpy(myHeader, bytes44, sizeof(struct wav_header)); // Copy the first 44 bytes into the header struct
    return myHeader; // Return the filled header struct
};

// Function to load a wav file from disk
struct wav_file* wav_load(char* path) {
    char* buffer = NULL; // Pointer to hold the entire file contents
    size_t size; // Variable to hold the size of the file
    size = read_file(path, &buffer);
    if (size < sizeof(struct wav_header)) { // Ensure the file is at least as large as the header
        free(buffer);
        return NULL; // File too small to be a valid WAV file
    }
    struct wav_file* wf = malloc(sizeof(struct wav_file)); // Allocate memory for the wav_file struct
    wf->filesize = size; // Store the total file size
    wf->header = wavheaderfunc(buffer); // Parse the header from the first 44 bytes
    wf->buffer = buffer;  // save the original pointer
    wf->data = buffer + sizeof(struct wav_header); // Point to the data section
    return wf; // Return the filled wav_file struct
}

// Function to write a wav file to disk
int wav_write(struct wav_file* wf, char* path) {
    size_t written = write_file(path, (char*)wf->header, wf->filesize); // Write the header first
    if (written != wf->filesize) { // Check if the write was successful
        return 1; // Write failed
    } else {
        return 0; // Write succeeded
    }
}

// Function to free the allocated memory for a wav_file struct
void wav_free(struct wav_file* wf) {
    free(wf->header); // Free the header memory
    free(wf->buffer);  // free the full file buffer
    free(wf); // Free the wav_file struct memory

}