# include <stdint.h>
# include <stddef.h>

// Struct to hold the wav file header
struct wav_header{
    char riff[4]; // "RIFF"
    uint32_t size; // Size of the entire file in bytes minus 8 bytes for "RIFF" and size
    char type[4]; // File Type, should be "WAVE"
    char format[4]; // Format chunk, must be "fmt"
    uint32_t lengthformat; // Length of formart data
    uint16_t channels; // Number of channels
    uint32_t samplerate; // Sample rate
    uint32_t bytecalc; // Sample rate * numChannels * bitsPerSample/8
    uint16_t bitcalc; // Bits per sample * numChannels/ data type size
    uint16_t bitspersample; // Bits per sample
    char data[4]; // data header, must be "data"
    uint32_t datasize; // data section size
};

// Struct to hold the wav file data
struct wav_file{
    wav_header* header; // Pointer to the header
    size_t filesize;// Size of the entire file
    char* data; // Pointer to the data
};



