#include "wav.h"
#include "file_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function to parse the header from raw bytes
struct wav_header* wavheaderfunc(char* bytes44) {
    struct wav_header* myHeader = malloc(sizeof(struct wav_header)); // Allocate memory for the header
    if (!myHeader) { // Check for allocation failure
        return NULL; // Indicate failure
    }

    memcpy(myHeader, bytes44, sizeof(struct wav_header)); // Copy the first 44 bytes into the header struct
    return myHeader; // Return the filled header struct
};

/* Function to load a wav file from disk. we use a loop becasue the data chunk may not be at byte 44 
(printing showed it wasn't (at least for the wav's we tried)) */
struct wav_file* wav_load(char* path) {
    char* buf = NULL; // Pointer to hold the entire file contents
    size_t sz = read_file(path, &buf); // Read the file into memory
    if (sz < 44) { // File too small to be a valid wav file
        free(buf); // free the buffer if allocated
        return NULL; // Indicate failure
    }

    struct wav_file* wf = malloc(sizeof *wf); // Allocate memory for the wav_file struct
    if (!wf) { // Check for allocation failure
        free(buf); // free the buffer if allocated
        return NULL; // Indicate failure
    }

    wf->buffer = buf; // Store the full file buffer
    wf->filesize = sz; // Store the file size
    wf->header = wavheaderfunc(buf); // Parse and store the header
    wf->data = NULL; // Initialize data pointer to NULL

    char* p = (char*)buf + 12; // Start after "RIFF" and size and "WAVE"
    while (p + 8 <= (char*)buf + sz) { // loop until we reach the end of the file to find the "data" chunk
        uint32_t n; // variable to hold chunk length
        memcpy(&n, p + 4, 4); /* copies the chunk length into n, p is at the start of the chunk, p+4 
        is where the length is stored, 4 is the size of the length field */

        if (p[0]=='d' && p[1]=='a' && p[2]=='t' && p[3]=='a') { // check for "data" chunk
            wf->data = (char*)(p+8); // Point to the data section
            wf->header->datasize = n; // Store data size in header
            break; // stop after finding "data" chunk
        }
        p += 8 + n + (n & 1); // Move to the next chunk, account for padding byte if n is odd.
    }
    if (!wf->data) { // check if data chunk was found
        free(wf->header); free(wf); free(buf); // free allocated memory
        return NULL; // Indicate failure
    }
    return wf; // Return the filled wav_file struct
}

// Function to write a wav file to disk
int wav_write(struct wav_file* wf, char* path) {
    if (!wf || !wf->buffer || wf->filesize == 0 || !path) { // Check for valid input of wf and path
        return 1; // failure
    }
    
    size_t written = write_file(path, wf->buffer, wf->filesize);  // Write the entire buffer to disk
    if (written != wf->filesize) { // Check if all bytes were written
        return 1; // failed
    }
    return 0; // success
}

// Function to free the allocated memory for a wav_file struct
void wav_free(struct wav_file* wf) {
    free(wf->header); // Free the header memory
    free(wf->buffer);  // free the full file buffer
    free(wf); // Free the wav_file struct memory

}