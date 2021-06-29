
#ifndef _SOUND_SOURCE_H_
#define _SOUND_SOURCE_H_

//#include "ofxMaxim.h"
#include <vector>
#include <Common/Buffer.h>
#include "ofMain.h"

class SoundSource {

public :

	SoundSource() : position{ 0 }, endFrame{ 0 }, endChunk{ 0 }, initialized{false} {}

		/** \brief Dumps data from mySample to bInput
	* \param [inout] bInput buffer to be filled with samples
	* \param [in] mySample audio maxisample to be split and copy to bInput buffer
	* \param [out] endchunk will store the last position of the maxisample copied to the buffer
	* \param [in] isLooped when true, it indicates that copying to buffer should start again from the beginning
	* of the maxisample when it is finished
	* \retval boolean Returns false when the audio sample is finished playing and the loop is not activated.
	* Therefore in this case the bInput parameter will not have been modified. Returns true in all other cases.
	*/
	//bool MaxiSampleToBuffer(CMonoBuffer<float> &bInput, maxiSample *mySample, int &endchunk, bool isLooped);


	/** \brief Loads a mono, 16-bit, 44.1kHz ".wav" file
*	\param [out] samplesVector float vector that will storage the whole audio
*	\param [in] stringIn name of the ".wav" file to open
*/
	bool LoadWav(const char* stringIn);


	/** \brief Fills a buffer with the correct audio frame from the input float vector
*	\param [out] output output buffer
*	\param [in,out] position starting position of the frame to be processed
*	\param [in,out] endChunk ending position of the frame to be processed
*	\param [in] samplesVector float vector containing the whole audio
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