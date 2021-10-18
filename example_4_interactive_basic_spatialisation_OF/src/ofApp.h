/**
* \class ofApp
*
* \brief Declaration of example_4_interactive_basic_spatialisation_OF
* \details Example to handle deal with the 3DTI_Toolkit, using Openframeworks.
*
* \authors The author has been Paula García Jiménez. She has been supervised by Arcadio Reyes Lecuona (University of Malaga) with helped from Daniel Gonzalez Toledo.
* \b Contact: paulagarcianm@uma.es
*
* \b Copyright: University of Malaga
*
* \b Licence: This example of 3dti_AudioToolkit is licensed by MIT license.
*
*/

#pragma once

#include "ofMain.h"
#include <BinauralSpatializer/3DTI_BinauralSpatializer.h>
#include <HRTF/HRTFFactory.h>
#include <HRTF/HRTFCereal.h>
#include "SoundSource.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	ofImage image;										//Creating a ofImage variable for loading the imagen into the project
		
	private:	

		Binaural::CCore							myCore;												 // Core interface
		shared_ptr<Binaural::CListener>			listener;											 // Pointer to listener interface

		std::vector<ofSoundDevice> deviceList;
		ofSoundStream systemSoundStream;

		SoundSource source1Wav;
		SoundSource source2Wav;
		shared_ptr<Binaural::CSingleSourceDSP>	source1DSP;							 // Pointers to each audio source interface
		shared_ptr<Binaural::CSingleSourceDSP>	source2DSP;							 // Pointers to each audio source interface

		int GetAudioDeviceIndex(std::vector<ofSoundDevice> list);
		void SetDeviceAndAudio(Common::TAudioStateStruct audioState);
		void audioOut(float * output, int bufferSize, int nChannels);
		void audioProcess(Common::CEarPair<CMonoBuffer<float>> & bufferOutput, int uiBufferSize);
		void LoadWavFile(SoundSource & source, const char* filePath);
};
