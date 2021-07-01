#include "ofApp.h"

#define SAMPLERATE 44100
#define BUFFERSIZE 512

//--------------------------------------------------------------
void ofApp::setup(){
	
	// Core setup
	Common::TAudioStateStruct audioState;	    // Audio State struct declaration
	audioState.bufferSize = BUFFERSIZE;			// Setting buffer size 
	audioState.sampleRate = SAMPLERATE;			// Setting frame rate 
	myCore.SetAudioState(audioState);		    // Applying configuration to core
	myCore.SetHRTFResamplingStep(15);		    // Setting 15-degree resampling step for HRTF


	// Listener setup
	listener = myCore.CreateListener();								 // First step is creating listener
	Common::CTransform listenerPosition = Common::CTransform();		 // Setting listener in (0,0,0)
	listenerPosition.SetPosition(Common::CVector3(0, 0, 0));
	listener->SetListenerTransform(listenerPosition);
	listener->DisableCustomizedITD();								 // Disabling custom head radius
	// HRTF can be loaded in SOFA (more info in https://sofacoustics.org/) Some examples of HRTF files can be found in 3dti_AudioToolkit/resources/HRTF
	bool specifiedDelays;
	bool sofaLoadResult = HRTF::CreateFromSofa("hrtf.sofa", listener, specifiedDelays);			
	if (!sofaLoadResult) { 
		cout << "ERROR: Error trying to load the SOFA file" << endl<<endl;
	}																			

	// Source 1 setup
	source1DSP = myCore.CreateSingleSourceDSP();									// Creating audio source
	LoadWavFile(source1Wav, "speech_female.wav");											// Loading .wav file										   
	Common::CTransform source1Position = Common::CTransform();
	source1Position.SetPosition(Common::CVector3(0, 2, 0));							//Set source position on the listener left side				 
	source1DSP->SetSourceTransform(source1Position);
	source1DSP->SetSpatializationMode(Binaural::TSpatializationMode::HighQuality);	// Choosing high quality mode for anechoic processing
	source1DSP->DisableNearFieldEffect();											// Audio source will not be close to listener, so we don't need near field effect
	source1DSP->EnableAnechoicProcess();											// Enable anechoic processing for this source
	source1DSP->EnableDistanceAttenuationAnechoic();								// Do not perform distance simulation

	// Source 2 setup
	source2DSP = myCore.CreateSingleSourceDSP();									// Creating audio source
	LoadWavFile(source2Wav, "speech_male.wav");											// Loading .wav file										  
	Common::CTransform source2Position = Common::CTransform();
	source2Position.SetPosition(Common::CVector3(0, -2, 0));						//Set source position on the listener right side
	source2DSP->SetSourceTransform(source2Position);
	source2DSP->SetSpatializationMode(Binaural::TSpatializationMode::HighQuality);	// Choosing high quality mode for anechoic processing
	source2DSP->DisableNearFieldEffect();											// Audio source will not be close to listener, so we don't need near field effect
	source2DSP->EnableAnechoicProcess();											// Enable anechoic processing for this source
	source2DSP->EnableDistanceAttenuationAnechoic();								// Do not perform distance simulation

	//AudioDevice Setup
	//// Before getting the devices list for the second time, the strean must be closed. Otherwise,
	//// the app crashes when systemSoundStream.start(); or stop() are called.
	systemSoundStream.close();
	SetDeviceAndAudio(audioState);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

/// Read de audio the list of devices of the user computer, allowing the user to select which device to use. Configure the Audio using openFramework
void ofApp::SetDeviceAndAudio(Common::TAudioStateStruct audioState) {
	// This call could block the app when the motu audio interface is unplugged
	// It gives the message: 
	// RtApiAsio::getDeviceInfo: error (Hardware input or output is not present or available).
	// initializing driver (Focusrite USB 2.0 Audio Driver).
	deviceList = systemSoundStream.getDeviceList();


	for (int c = deviceList.size() - 1; c >= 0; c--)
	{
		if (deviceList[c].outputChannels == 0)
			deviceList.erase(deviceList.begin() + c);
	}

	//Show list of devices and return the one selected by the user
	int deviceId = GetAudioDeviceIndex(deviceList);

	if (deviceId >= 0)
	{
		systemSoundStream.setDevice(deviceList[deviceId]);

		ofSoundDevice &dev = deviceList[deviceId];

		//Setup Aduio
		systemSoundStream.setup(this,		// Pointer to ofApp so that audioOut is called									  
			2,								//dev.outputChannels, // Number of output channels reported
			0,								// Number of input channels
			audioState.sampleRate,			// sample rate, e.g. 44100 
			audioState.bufferSize,			// Buffer size, e.g. 512
			4   // -> Is the number of buffers that your system will create and swap out.The more buffers, 
			   // the faster your computer will write information into the buffer, but the more memory it 
			  // will take up.You should probably use two for each channel that you’re using.Here’s an 
			 // example call : ofSoundStreamSetup(2, 0, 44100, 256, 4);
			//     http://openframeworks.cc/documentation/sound/ofSoundStream/
		);
		cout << "Device selected : " << "ID: " << dev.deviceID << "  Name: " << dev.name << endl;

	}
	else
	{
		cout << "Could not find any usable sound Device" << endl;
	}
}

/// Ask the user to select the audio device to be used and return the index of the selected device
int ofApp::GetAudioDeviceIndex(std::vector<ofSoundDevice> list)
{
	//Show in the console the Audio device list
	int numberOfAudioDevices = list.size(); 
	cout << "     List of available audio outputs" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < numberOfAudioDevices; i++) {
		cout << "ID: " << i << "-" << list[i].name << endl;
	}
	int selectedAudioDevice;

	do {
		cout << "Please choose which audio output you wish to use: ";
		cin >> selectedAudioDevice;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	} while (!(selectedAudioDevice > -1 && selectedAudioDevice <= numberOfAudioDevices));

	// First, we try to retrieve the <Conf.audioInterfaceIndex> th suitable device in the list:
	for (int c = 0; c < numberOfAudioDevices; c++)
	{
		ofSoundDevice &dev = list[c];

		if ((dev.outputChannels >= 0) && c == selectedAudioDevice)
			return c;
	}

	// Otherwise, we try to get the defult device
	for (int c = 0; c < numberOfAudioDevices; c++)
	{
		ofSoundDevice &dev = list[c];

		// dev.isDefaultOutput is not really the same that windows report
		// TODO: update to latest openFrameworks that really can report all drivers present
		// via ofSoundStream::getDevicesByApi 
		//if ((dev.outputChannels >= NUMBER_OF_SPEAKERS) && dev.isDefaultOutput)
		if ((dev.outputChannels >= 0) && dev.isDefaultOutput)
			return c;
	}
	return -1;
}


/// Audio output management by openFramework
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {

	// The requested frame size is not allways supported by the audio driver:
	if (myCore.GetAudioState().bufferSize != bufferSize)
		return;

	// Prepare output chunk
	Common::CEarPair<CMonoBuffer<float>> bOutput;
	bOutput.left.resize(bufferSize);
	bOutput.right.resize(bufferSize);
	
	// Process audio
	audioProcess(bOutput, bufferSize);
	// Build float array from output buffer
	int i = 0;
	CStereoBuffer<float> iOutput;
	iOutput.Interlace(bOutput.left, bOutput.right);
	for (auto it = iOutput.begin(); it != iOutput.end(); it++)
	{
		float s = *it;
		output[i++] = s;
	}
}

/// Process audio using the 3DTI Toolkit methods
void ofApp::audioProcess(Common::CEarPair<CMonoBuffer<float>> & bufferOutput, int uiBufferSize)
{
	// Declaration, initialization and filling mono buffers
	CMonoBuffer<float> source1(uiBufferSize);
	source1Wav.FillBuffer(source1);
	CMonoBuffer<float> source2(uiBufferSize);
	source2Wav.FillBuffer(source2);

	// Declaration of stereo buffer
	Common::CEarPair<CMonoBuffer<float>> bufferProcessed;
	// Anechoic process of first source
	source1DSP->SetBuffer(source1);
	source1DSP->ProcessAnechoic(bufferProcessed.left, bufferProcessed.right);
	// Adding anechoic processed first source to the output mix
	bufferOutput.left += bufferProcessed.left;
	bufferOutput.right += bufferProcessed.right;
	// Anechoic process of second source
	source2DSP->SetBuffer(source2);
	source2DSP->ProcessAnechoic(bufferProcessed.left, bufferProcessed.right);
	// Adding anechoic processed second source to the output mix
	bufferOutput.left += bufferProcessed.left;
	bufferOutput.right += bufferProcessed.right;
}



void ofApp::LoadWavFile(SoundSource & source, const char* filePath)
{	
	if (!source.LoadWav(filePath)) {
		cout << "ERROR: file " << filePath << " doesn't exist." << endl<<endl;
	}
}

