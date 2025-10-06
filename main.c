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
    for(size_t i = 0; i<num_bytes; ++i){
        printf("%x", file_contents[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){
    char* contents;

    // Read the input file
    size_t num_bytes = read_file(argv[1], &contents);
    printf("%s\n", argv[1]);
    printf("%lu bytes read.\n", num_bytes);

    // Print the file contents in hex
    print_file(contents, num_bytes);

    // Write the file to the output
    write_file(argv[2], contents, num_bytes);

    free(contents); // Always free allocated memory

    struct wav_file* wf = wav_load(argv[1]);
    
    //checks to make sure it is a riff file. 
    int is_riff = strncmp(wf->header->riff,"RIFF",4);
    if (is_riff != 0){
        printf("Error: not a riff file.\n");
        wav_free(wf);
        return 1;
    }
    //checks to make sure it is a wave file
    int is_wave = strncmp(wf->header->type,"WAVE",4);
    if (is_wave != 0){
        printf("Error: not a wave file.\n");
        wav_free(wf);
        return 1;
    }
    //checks to see if the file has the required channels
    if (wf->header->channels != 2){
        printf("Error: file does not have 2 channels.\n");
        wav_free(wf);
        return 1;
    }
    //checks to see if format type is 1.
    if (wf->header->formattype != 1){
        printf("Error: format type is not 1.\n");
        wav_free(wf);
        return 1;
    }

    //gets the size of the audio data
    uint32_t data_size = wf ->header->datasize;
    // points to the start of the audio data
    char* data = wf->data;
    //2 per channel
    int samplesize = 4;
    //calculates the total number of samples
    int numsamples = data_size / samplesize;

    printf("Input file: %s\n",argv[1]);
    printf("output file: %s\n",argv[2]);
    printf("sample rate: %u Hz\n",wf->header->samplerate);
    printf("File size: %lu bytes\n",wf->filesize);
    printf("Number of channels: %u\n",wf->header->channels);
    
    //loops through half the samples and swaps them with the back half
    for(int i = 0; i < numsamples /2;i++){
        //temp storage for audio samples
        char temp_sample[4];
        // copys the front data into temp
        memcpy(temp_sample,data + i * samplesize,samplesize);
        // replaces the front audio sample with the back audio sample
        memcpy(data + i * samplesize, data + ((numsamples - 1 - i)*samplesize),samplesize);
        // replaces the the back audio sample with the front audio sample
        memcpy(data+(numsamples-1-i) * samplesize,temp_sample,samplesize);
    }


    // writes the new reversed wav file
    if (wav_write(wf,argv[2]) == 0){
        printf("Reversed file write successful.\n");
    }
    else{
        printf("Reversed file write failed.\n");
    }

    // frees the allocated memory
    wav_free(wf);
    return 0;
}
