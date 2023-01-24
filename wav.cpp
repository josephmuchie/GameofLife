#include <iostream>
#include <fstream>

using namespace std;

// Riff Chunk
const string chunk_id = "RIFF";
const string chunk_size = "----";
const string format = "WAVE";

// FMT sub-chunk 
const string subchunk1_id = "fmt ";
const int subchunk1_size = 16;
const int audio_format = 1;
const int num_channels = 2;
const int sample_rate = 44100;
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_align = num_channels * (subchunk1_size / 8);
const int bits_per_sample = 16;

//Data sub-chunk
const string subchunk2_id = "data";
const string subchunk2_size = "----";

void write_as_bytes(ofstream &file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

int main() {
    ofstream wav;
    wav.open("test.wav", ios::binary);

    return 0;
}

