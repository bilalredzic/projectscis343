#include <stdio.h>
#include <stdlib.h>
#include "file_lib.h"
#include <string.h>
#include <stdint.h>
#include "wav.h"

/**
 * The contents of the file are a char*, but that doesn't
 * mean it is a "string".  When working with "strings" in C
 * though, we normally NULL terminate.  This is not NULL
 * terminated.  Nor could it be, as we then wouldn't be
 * able to represent NULL in the file.  So, we need to print
 * each character separately.  Here, we are printing as bytes
 * (base 16).
 * 
 * @parameters
 * char* file_contents - The file's bytes.
 * size_t num_bytes - The number of bytes to print.
 */
void print_file(char* file_contents, size_t num_bytes){
    // Note this is printing the bytes in hex
    // for(size_t i = 0; i<num_bytes; ++i){
    //     printf("%x", file_contents[i]);
    // }
    // printf("\n");
}

int main(int argc, char** argv){
    if (argc != 3) { // Check for correct number of arguments
        printf("Not correct usage. Proper Usage: %s input.wav output.wav\n", argv[0]); // Print usage message
        return 1; // Return error code
    }

    struct wav_file* wf = wav_load(argv[1]); // Load the wav file
    if (!wf) { // Check if loading was successful
        printf("Error: failed to load WAV (bad file or no 'data' chunk).\n"); // Print error message
        return 1; // Return error code
    }       
    
    int is_riff = strncmp(wf->header->riff,"RIFF",4); // check for "RIFF"
    if (is_riff != 0){ // not "RIFF"
        printf("Error: not a riff file.\n"); // print error message
        wav_free(wf); // free memory
        return 1; // return error code
    }
    int is_wave = strncmp(wf->header->type,"WAVE",4); // check for "WAVE"
    if (is_wave != 0){ // not "WAVE"
        printf("Error: not a wave file.\n"); // print error message
        wav_free(wf); // free memory
        return 1;  // return error code
    }
    if (wf->header->channels < 1) { // check for valid number of channels
        printf("Error: invalid channels\n"); // print error message
        wav_free(wf); // free memory
        return 1; // return error code
    } 
    if (wf->header->bitspersample == 0) { // check for valid bits per sample
        printf("Error: invalid bps\n");  // print error message
        wav_free(wf); // free memory
        return 1; // eturn error code
    }

    if (wf->header->formattype != 1){ // check for PCM format
        printf("Error: format type is not 1.\n"); // print error message
        wav_free(wf); // free memory
        return 1; // return error code
    }
    
    // Print the information about the wav file
    printf("Input file name: %s\n",argv[1]);
    printf("Output file name: %s\n",argv[2]);
    printf("Sample rate (Hz): %u Hz\n",wf->header->samplerate);
    printf("File size (bytes): %lu bytes\n",wf->filesize);
    printf("Number of channels: %u\n",wf->header->channels);
    
    uint32_t data_size = wf ->header->datasize; // Size of the data section
    char* data = wf->data; // Pointer to the data section
    int bytes_per_sample = wf->header->bitspersample / 8; // Bytes per sample
    int samplesize = bytes_per_sample * wf->header->channels; // Size of one sample (all channels)
    int numsamples = data_size / samplesize; // Total number of samples
    int bps = wf->header->bitspersample / 8; // bytes per sample per channel
    int frame = bps * wf->header->channels; // bytes per frame (all channels)

    if (wf->data == NULL || wf->header->datasize == 0) { // check if data chunk was found
        printf("Error: no audio data found.\n"); // print error message
        wav_free(wf); // free memory
        return 1; // return error code
    }
    if (samplesize <= 0 || (wf->header->datasize % samplesize) != 0) {
        printf("Error: invalid frame sizing (channels/bits).\n");
        wav_free(wf);
        return 1;
    }

    for(int i = 0; i < numsamples /2;i++){ // loop to reverse the samples
        char temp_sample[40]; // temporary storage for one sample (multiple channels possible)
        memcpy(temp_sample,data + i * samplesize,samplesize); // copy the sample to temporary storage
        memcpy(data + i * samplesize, data + ((numsamples - 1 - i)*samplesize),samplesize); // copy the sample from the end to the front
        memcpy(data+(numsamples-1-i) * samplesize,temp_sample,samplesize); // copy the sample from temporary storage to the end
    }

    if (wav_write(wf,argv[2]) == 0){ // check if write was successful
        printf("Reversed file write successful.\n"); // print success message
    }
    else{
        printf("Reversed file write failed.\n"); // print failure message
    }
    wav_free(wf); // free memory
    return 0; // return success code
}
