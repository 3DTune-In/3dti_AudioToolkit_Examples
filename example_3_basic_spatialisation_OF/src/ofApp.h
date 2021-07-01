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
