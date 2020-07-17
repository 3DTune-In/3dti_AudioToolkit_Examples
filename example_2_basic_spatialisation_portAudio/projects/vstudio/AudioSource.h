#pragma once

#ifndef _AUDIOSOURCEDANI_H_
#define _AUDIOSOURCEDANI_H_



#include <BinauralSpatializer/3DTI_BinauralSpatializer.h>

class AudioSource 
{
public:
	vector<float> 							samplesVector;	 	// Storages the audio from the wav files
	unsigned int							wavSamplePosition;	// Storages, respectively, the starting and ending position of the frame being rendered for each source
	unsigned int							positionEndFrame;
	float									volume;

	shared_ptr<Binaural::CSingleSourceDSP>	singleSourceDSP;									// Pointers to each audio source interface
	Common::CTransform						sourcePosition;										// Storages the position of the steps source


	AudioSource() {
		samplesVector = vector<float>();
		wavSamplePosition = 0;
		positionEndFrame = 0;
		volume = 0.0f;
	}
};
#endif