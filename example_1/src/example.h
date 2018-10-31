/**
*
* \brief This is the header file of the example project 1 using 3D Tune-In Toolkit
* \date	April 2018
*
* \authors A. Rodríguez-Rivero, as part of the 3DI-DIANA Research Group (University of Malaga)
* \b Contact: A. Reyes-Lecuona as head of 3DI-DIANA Research Group (University of Malaga): areyes@uma.es
*
* \b Contributions: (additional authors/contributors can be added here)
*
* \b Project: 3DTI (3D-games for TUNing and lEarnINg about hearing aids) ||
* \b Website: http://3d-tune-in.eu/
*
* \b Copyright: University of Malaga - 2018
*
* \b Licence: GPLv3
*
* \b Acknowledgement: This project has received funding from the European Union's Horizon 2020 research and innovation programme under grant agreement No 644051
*
*/

#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <cstdio>
#include <cstring>
#include <HRTF/HRTFFactory.h>
#include <HRTF/HRTFCereal.h>
#include <BRIR/BRIRFactory.h>
#include <BRIR/BRIRCereal.h>
#include <BinauralSpatializer/3DTI_BinauralSpatializer.h>
#include <RtAudio.h>	


shared_ptr<RtAudio>						audio;												 // Pointer to RtAudio API

Binaural::CCore							myCore;												 // Core interface
shared_ptr<Binaural::CListener>			listener;											 // Pointer to listener interface
shared_ptr<Binaural::CSingleSourceDSP>	sourceSpeech, sourceSteps;							 // Pointers to each audio source interface
shared_ptr<Binaural::CEnvironment>		environment;										 // Pointer to environment interface

Common::CTransform						sourcePosition;										 // Storages the position of the steps source

Common::CEarPair<CMonoBuffer<float>>	outputBufferStereo;									 // Stereo buffer containing processed audio

vector<float>							samplesVectorSpeech, samplesVectorSteps;			 // Storages the audio from the wav files

unsigned int							wavSamplePositionSpeech, positionEndFrameSpeech,	 // Storages, respectively, the starting and ending position of the frame being rendered for each source
                                        wavSamplePositionSteps,  positionEndFrameSteps ;	



/** \brief This method gathers all audio processing (spatialization and reverberation)
*	\param [out] bufferOutput output buffer processed
*	\param [in] bufferSize size of buffer in samples 
*/
void audioProcess(Common::CEarPair<CMonoBuffer<float>>& bufferOutput, int bufferSize);

/** \brief Fills a buffer with the correct audio frame from the input float vector
*	\param [out] output output buffer
*	\param [in,out] position starting position of the frame to be processed
*	\param [in,out] endChunk ending position of the frame to be processed
*	\param [in] samplesVector float vector containing the whole audio
*/
void FillBuffer(CMonoBuffer<float>& output, unsigned int & position, unsigned int & endChunk, std::vector<float>& samplesVector);

/** \brief Loads a mono, 16-bit, 44.1kHz ".wav" file
*	\param [out] samplesVector float vector that will storage the whole audio
*	\param [in] stringIn name of the ".wav" file to open
*/
void LoadWav(std::vector<float>& samplesVector, const char* stringIn);

/** \brief This function is called each time RtAudio needs a buffer to output
*	\param [out] outputBuffer output buffer to be filled
*	\param [out] inputBuffer unused input buffer
*	\param [in] bufferSize size of buffer in samples
*	\param [in] streamTime time in seconds since the stream started
*	\param [in] status feedback that if does not equal zero indicates stream over/underflow
*	\param [in] data unused data pointer
*	\retval Integer value that equals 0 if we don't want the stream to stop
*/
static int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int bufferSize, double streamTime, RtAudioStreamStatus status, void *data);

#endif