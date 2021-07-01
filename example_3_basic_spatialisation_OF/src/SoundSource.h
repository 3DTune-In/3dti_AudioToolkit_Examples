
#ifndef _SOUND_SOURCE_H_
#define _SOUND_SOURCE_H_

//#include "ofxMaxim.h"
#include <vector>
#include <Common/Buffer.h>
#include "ofMain.h"

class SoundSource {

public :

	SoundSource() : position{ 0 }, endFrame{ 0 }, endChunk{ 0 }, initialized{false} {}

	
	/** \brief Loads a mono, 16-bit, 44.1kHz ".wav" file
*	\param [out] bool to be true if the wav file is successfully loaded
*	\param [in] stringIn name of the ".wav" file to open
*/
	bool LoadWav(const char* stringIn);


	/** \brief Fills a buffer with the next N samples from the wav file
*	\param [in,out] CMonoBuffer vector that contains the next N samples of the wav file. Where N is the size of the buffer when the method is called.
*/
	void FillBuffer(CMonoBuffer<float> &output);

private:
	
	std::vector<float> samplesVector;
	unsigned int position;
	unsigned int endFrame;
	unsigned int endChunk;
	bool initialized;
};

#endif