
#include "SoundSource.h"


bool SoundSource::LoadWav(const char* stringIn)
{
	struct WavHeader								 // Local declaration of wav header struct type (more info in http://soundfile.sapp.org/doc/WaveFormat/)
	{												 // We only need the number of samples, so the rest will be unused assuming file is mono, 16-bit depth and 44.1kHz sampling rate
		char		  fill[40];
		uint32_t	bytesCount;
	} wavHeader;

	// Init vars
	position  =0;
	endFrame  =0;
	endChunk  =0;
	
	// Opening of the wav file
	if (FILE* wavFile = fopen(stringIn, "rb")) {
	
		fread(&wavHeader, sizeof(wavHeader), 1, wavFile);								 // Reading of the 44 bytes of header to get the number of samples of the file
		fseek(wavFile, sizeof(wavHeader), SEEK_SET);									 // Moving of the file pointer to the start of the audio samples

		unsigned int samplesCount = wavHeader.bytesCount / 2;							 // Getting number of samples by dividing number of bytes by 2 because we are reading 16-bit samples
		int16_t *sample; sample = new int16_t[samplesCount];							 // Declaration and initialization of 16-bit signed integer pointer
		memset(sample, 0, sizeof(int16_t) * samplesCount);								 // Setting its size

		uint8_t *byteSample; byteSample = new uint8_t[2 * samplesCount];				 // Declaration and initialization of 8-bit unsigned integer pointer
		memset(byteSample, 0, sizeof(uint8_t) * 2 * samplesCount);						 // Setting its size

		fread(byteSample, 1, 2 * samplesCount, wavFile);								 // Reading the whole file byte per byte, needed for endian-independent wav parsing

		for (int i = 0; i < samplesCount; i++)
			sample[i] = int16_t(byteSample[2 * i] | byteSample[2 * i + 1] << 8);		 // Conversion from two 8-bit unsigned integer to a 16-bit signed integer

		samplesVector.reserve(samplesCount);											 // Reserving memory for samples vector

		for (int i = 0; i < samplesCount; i++)
			samplesVector.push_back((float)sample[i] / (float)INT16_MAX);				 // Converting samples to float to push them in samples vector

		initialized = true;
		return true;
	}
	else
	{
		return false;
	}	
}


void SoundSource::FillBuffer(CMonoBuffer<float> &output)
{	
	if (!initialized) { return; }
	
	position = endFrame + 1;							 // Set starting point as next sample of the end of last frame
	if (position >= samplesVector.size())				 // If the end of the audio is met, the position variable must return to the beginning
		position = 0;

	endFrame = position + output.size() - 1;			 // Set ending point as starting point plus frame size
	for (int i = 0; i < output.size(); i++) {
		if ((position + i) < samplesVector.size())
			output[i] = (samplesVector[position + i]);	 // Fill with audio
		else
			output[i] = 0.0f;							 // Fill with zeros if the end of the audio is met
	}
}