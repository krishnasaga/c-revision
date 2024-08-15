#include <stdio.h>
#include <stdlib.h>

struct WaveHeadrs {
  //[Master RIFF chunk]
  unsigned int FileTypeBlocID;  //(4 bytes) : Identifier « RIFF »  (0x52, 0x49, 0x46, 0x46)
  unsigned int FileSize;        // (4 bytes) : Overall file size minus 8 bytes
  unsigned int FileFormatID;    // (4 bytes) : Format = « WAVE »  (0x57, 0x41, 0x56, 0x45)
  //[Chunk describing the data format]
  unsigned int FormatBlocID;    //(4 bytes) : Identifier « fmt␣ »  (0x66, 0x6D, 0x74, 0x20)
  unsigned int BlocSize;        // (4 bytes) : Chunk size minus 8 bytes, which is 16 bytes here  (0x10)
  unsigned short AudioFormat;   // (2 bytes) : Audio format (1: PCM integer, 3: IEEE 754 float)
  unsigned short NbrChannels;   // (2 bytes) : Number of channels
  unsigned int Frequence;       //(4 bytes) : Sample rate (in hertz)
  unsigned int  BytePerSec;     //(4 bytes) : Number of bytes to read per second (Frequence * BytePerBloc).
  unsigned short  BytePerBlock; // (2 bytes) : Number of bytes per block (NbrChannels * BitsPerSample / 8).
  unsigned short BitsPerSample; // (2 bytes) : Number of bits per sample
} WaveHeadrs;

void read_samples_from_wave(FILE *fp,struct WaveHeadrs *headers,unsigned short *samples){
    double data_size = headers->FileSize - sizeof &headers;
    unsigned long i = 0;
    unsigned char *byts = (unsigned char*)samples;
    while(i <= data_size){
       byts[i] = getc(fp);
       ++i;
    }
};

void read_headers_from_wave(FILE *fp,struct WaveHeadrs *headers){
    fseek(fp,0,SEEK_SET);
    size_t bytesRead = fread(headers, sizeof(struct WaveHeadrs), 1, fp);
}

int main(void){

    FILE *fp;
    struct WaveHeadrs headers;
    fp = fopen("./world_clear.wav", "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    read_headers_from_wave(fp,&headers);

    unsigned short *samples;
    double data_size = headers.FileSize - sizeof headers;
    if(data_size < 0){
        perror("Invalied file format");
        return 1;
    }
    samples = malloc(data_size);
    read_samples_from_wave(fp,&headers,samples);
    int i = 0;
    while(i<(headers.FileSize - sizeof headers)){
        printf("%X ",samples[i]);
        ++i;
    }
    return 0;
}
