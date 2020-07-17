/**
*
* \brief This is the main source file of the example project 1 using 3D Tune-In Toolkit
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

#include "BasicSpatialisationPortAudio.h"
#if defined(__linux__) || defined(linux)
    #include <bits/stdc++.h>
#endif

#define MAX_SOURCES 6

int main()
{
	times.reserve(2000);
	///////////////////////////////////////////////////////////////////////////////////////////////
	//	Audio output configuration, using PortAudio (more info in http://www.portaudio.com/docs.html)
	//	It requires the PortAudio .dll and .lib to be generated compiling "portaudio" proyect. 
	//	They will be in \3dti_AudioToolkit_Examples\third_party_libraries\portaudio\build\msvc\x64\Release\portaudio_x64.lib and portaudio_x64.dll
	//	If any other configuration for portaudio is needed, the project can be compilled again adding the files copying them.
	//	
	//	This project needs the portaudio.dll file to be copied into the aplication/solution folder
	//
	//  To add PortAdio verbose mode add PA_ENABLE_DEBUG_OUTPUT flag into the portaudio project properties -> C/C++ -> preprocessor -> preprocessor definitions
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Initialization of PortAudio	 
	PaError err;
	ScopedPaHandler paInit;
	err = paInit.result();
	if (err != paNoError)
	{
		cout << "\nERROR WITH PORTAUDIO INIT\t";
		exit(1);
	}
	// Setting the output parameters
	PaStreamParameters outputParameters;
	outputParameters.channelCount = 2;											// Setting output as stereo 
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = 0.050;									// Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	// Choose output device
	char cInput;
	int iDeviceIndex;
	do
	{
		cout << "Do you want to use the default (" << Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->name;
		cout << ") output device? (Y/n)\t"; fflush(stdin); cInput = getchar();
	} while (cInput != 'y' && cInput != 'n' && cInput != '\n');
	if (cInput == 'y' || cInput == '\n')  iDeviceIndex = Pa_GetDefaultOutputDevice();			// Give user no option for choose the output device, choose default	one
	else                                  iDeviceIndex = (PaDeviceIndex)SelectAudioDevice();	// Give user the option to choose the output device	
	outputParameters.device = iDeviceIndex;
	cout << "Selected audio device :\t" << Pa_GetDeviceInfo(iDeviceIndex)->name << endl;
	do
	{
		cout << "\nHow many fonts do you want to reproduce?";
		cin >> iNumberOfSources;
	} while (iNumberOfSources<1);
	cin.ignore();
	if (cInput == 'y' || cInput == '\n')
	{
		bOneSource=true;
	}else if(cInput == 'n')
	{
		bOneSource=false;
	}
	// Input sample rate
	do
	{
		cout << "\nDo you want to use the default sample rate (" << Pa_GetDeviceInfo(iDeviceIndex)->defaultSampleRate;
		cout << ") for your device ? (Y/n) \t";
		fflush(stdin); cInput = getchar();
	} while (cInput != 'y' && cInput != 'n' && cInput != '\n');
	if (cInput == 'y' || cInput == '\n')
	{
		iSampleRate = (Pa_GetDeviceInfo(iDeviceIndex)->defaultSampleRate);
	}else if(cInput == 'n')
	{
		do
		{
			cout << endl << "Please, insert sample rate (44100, 48000, 88200...) :\t";
			cin >> iSampleRate; cin.clear();
		} while (iSampleRate < 0);//Add default sample rate conditions
	}
	cout << "Setting sample rate to value : " << iSampleRate << endl;
	cout << "\nInsert wished buffer size (256, 512, 1024, 2048, 4096...):\t";
	cin >> iBufferSize; cin.clear();
	cin.ignore(INT_MAX, '\n');
	do
	{
		cout << "\nDo you want reverb? (Y/n) : "; cInput = getchar();
	} while (cInput != 'y' && cInput != 'n' && cInput != '\n');
	if (cInput == 'y' || cInput == '\n') bEnableReverb = true;
	else                                 bEnableReverb = false;
	// Core setup
	Common::TAudioStateStruct audioState;											// Audio State struct declaration
	audioState.bufferSize = iBufferSize;											// Setting buffer size and sample rate
	audioState.sampleRate = iSampleRate;
	myCore.SetAudioState(audioState);												// Applying configuration to core
	myCore.SetHRTFResamplingStep(15);												// Setting 15-degree resampling step for HRTF
	ERRORHANDLER3DTI.SetVerbosityMode(VERBOSITYMODE_ERRORSANDWARNINGS);
	ERRORHANDLER3DTI.SetErrorLogStream(&std::cout, true);
	// Listener setup
	listener = myCore.CreateListener();												// First step is creating listener
	Common::CTransform listenerPosition = Common::CTransform();						// Setting listener in (0,0,0)
	listenerPosition.SetPosition(Common::CVector3(0, 0, 0));
	listener->SetListenerTransform(listenerPosition);
	listener->DisableCustomizedITD();												// Disabling custom head radius
	///////////////////////////////////////////////////////////////////////////////////////////////
	//	HRTF can be loaded in either SOFA (more info in https://sofacoustics.org/) or 3dti-hrtf format.
	//	These HRTF files are provided with 3DTI Audio Toolkit. They can be found in 3dti_AudioToolkit/resources/HRTF 
	//	Comment the following line and uncomment next two lines to load the default HRTF in 3dti-hrtf format instead of in SOFA format
	//HRTF::CreateFrom3dti("hrtf.3dti-hrtf", listener);								
	bool specifiedDelays;
	HRTF::CreateFromSofa("hrtf.sofa", listener, specifiedDelays);	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Environment setup
	environment = myCore.CreateEnvironment();											// Creating environment to have reverberated sound
	environment->SetReverberationOrder(TReverberationOrder::BIDIMENSIONAL);				// Setting number of ambisonic channels to use in reverberation processing
	BRIR::CreateFromSofa("brir.sofa", environment);										// Loading SOFAcoustics BRIR file and applying it to the environment
	// sources setup
	t = 0;
	AudioSamplesVector.reserve(iNumberOfSources);
	wavSamplePosition.reserve(iNumberOfSources);//initiate variables for audio process function
	positionEndFrame.reserve(iNumberOfSources);
	for (int iCountOfSources = 0; iCountOfSources < iNumberOfSources; iCountOfSources++)
	{
		sources.push_back(myCore.CreateSingleSourceDSP());								// Creating audio source
		AudioSamplesVector.push_back(vector<float>());
		wavSamplePosition.push_back(*(new unsigned int));
		positionEndFrame.push_back(*(new unsigned int));
		switch (iCountOfSources % 6)
		{
		case 0:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "speech.wav"); // Loading .wav file
			break;
		case 1:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "3DTI_Sample_44.1kHz_MusicJazzPiano.wav");
			break;
		case 2:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "3DTI_Sample_44.1kHz_MusicJazzGuitar.wav");
			break;
		case 3:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "3DTI_Sample_44.1kHz_MusicJazzGuitar.wav");
			break;
		case 4:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "3DTI_Sample_44.1kHz_MusicJazzGuitar.wav"); // Loading .wav files
			break;
		case 5:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "steps.wav"); // Loading .wav file
			break;
		default:
			LoadWav(AudioSamplesVector.at(iCountOfSources), "steps.wav"); // Loading .wav file
			break;
		}
		sourcePosition.push_back(Common::CTransform());
		sourcePosition.at(iCountOfSources).SetPosition(Common::CVector3(((int)(rand() % 7)) + 1, ((int)(rand() % 7)) + 1, ((int)(rand() % 7))+1)); // Setting source position XYZ
		sources.at(iCountOfSources)->SetSourceTransform(sourcePosition.at(iCountOfSources));
		sources.at(iCountOfSources)->SetSpatializationMode(Binaural::TSpatializationMode::HighQuality); //HighPerformance vs HighQuality // Choosing high quality mode for anechoic processing
		sources.at(iCountOfSources)->DisableNearFieldEffect();											// Audio source will not be close to listener, so we don't need near field effect
		sources.at(iCountOfSources)->EnableAnechoicProcess();											// Setting anechoic and reverb processing for this source
		sources.at(iCountOfSources)->EnableDistanceAttenuationAnechoic();
		sources.at(iCountOfSources)->EnableDistanceAttenuationReverb();
	}
	
	// Declaration and initialization of stereo buffer
	outputBufferStereo.left.resize(iBufferSize);
	outputBufferStereo.right.resize(iBufferSize);
	// Opening of audio stream
	unsigned int frameSize = iBufferSize;       // Declaring and initializing frame size variable because next statement needs it
	outputParameters.hostApiSpecificStreamInfo = NULL;
	err = Pa_OpenStream(
		&stream,						// stream to be open
		NULL,							// Unspecified input parameters because there will not be input stream
		&outputParameters,				// Specified output parameters			                  
		iSampleRate,			        // Sample rate will be 44.1 kHz, 48kHz...
		frameSize,		                // Frame size will be iBufferSize samples
		paClipOff,						// we won't output out of range samples so don't bother clipping them
		&paCallback,					// Pointer to the function that will be called every time RtAudio needs the buffer to be filled
		nullptr		                    // Unused pointer to get feedback
		);
	if (err != paNoError)
	{
		cout << "\nERROR WITH PORTAUDIO WHILE STREAM IS BEING OPENED\t" << endl;
		exit(1);
	}
	// Informing user by the console to press any key to start the execution
	cout << "\nPress ENTER to start\n";
	cin.ignore();
	Pa_StartStream(stream);
	// Informing user by the console to press any key to end the execution
	cout << "\nPress ENTER to stop and exit...\n";
	cin.ignore();
	// Stopping and closing the stream;
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	string name;
	cout << "introduzca el nombre del fichero (sin el .csv) :";
	cin >> name;
	string sBufferSize;
	sBufferSize=to_string(iBufferSize);
	string sNumberOfSources = to_string(iNumberOfSources);
	ofstream myFile("./"+name+"_"+sNumberOfSources+"_Fuentes_"+"_"+sBufferSize+".csv");
	cout << "Archivo guardado en :" << "./"+name+"_"+sNumberOfSources+"_Fuentes_"+"_"+sBufferSize+".csv";
	double sum = std::accumulate(times.begin(), times.end(), 0.0);
	double mean = sum / times.size();
	myFile << "La media es : " << mean << endl;
	for(int muestra = 0; muestra < countMeasures; muestra++){
		myFile << times.at(muestra) << "\tns" << endl;
	}
	cout << endl << "La media de tiempos es de : " << mean << " ns";
	myFile.close();
	return 0;
}// main() code ends

int SelectAudioDevice() {
	PaStreamParameters inputParameters, outputParameters;
	PaError err;
	int     i, numDevices, defaultDisplayed, audioApiSelected;
	const   PaDeviceInfo *deviceInfo;
	//Get information of audio devices
	numDevices = Pa_GetDeviceCount();
	if (numDevices <= 0)
	{
		printf("\nERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
		err = numDevices;
		exit(1);
	}
	cout << endl << endl << "These are the audio APIs in the computer: " << endl;
	for (i = 0; i < Pa_GetHostApiCount(); i++) {
		cout << i << " - " << Pa_GetHostApiInfo(i)->name << endl;
	}
	do {
		cout << "\nPlease choose which audio API you wish to use:\t";
		cin >> audioApiSelected;
		cin.clear();cin.ignore(INT_MAX, '\n');
	} while (!(audioApiSelected > -1 && audioApiSelected <= Pa_GetHostApiCount()));
	cout << endl;
	//Go arround each audio device, there are inputs and outputs souces so we must filter that.
	for (i = 0; i < numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		// Mark global and API specific default devices
		if ((deviceInfo->maxOutputChannels) > 0 && (audioApiSelected == deviceInfo->hostApi))
		{
			printf("----------------------------------------\n");
			printf(" INFORMATION OF AUDIO DEVICE NUMBER #%d\n", i);
			printf("----------------------------------------\n");
			//Shows whats the default output device of the system and of each API
			if (i == Pa_GetDefaultOutputDevice())
			{
				printf("DEFAULT OUTPUT\n");
			}
			else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultOutputDevice) 
			{
				const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
				printf("DEFAULT %s OUTPUT\n", hostInfo->name);
			}//end if else default output detection
			// print device info fields
			printf("Name                      \t=  %s\n",		deviceInfo->name);
			printf("Host API                  \t=  %s\n",		Pa_GetHostApiInfo(deviceInfo->hostApi)->name);
			printf("Max outputs\t\t\t= %d\n",					deviceInfo->maxOutputChannels);
			printf("Default low output latency\t= %8.4f\n",		deviceInfo->defaultLowOutputLatency);
			printf("Default high output latency\t= %8.4f\n",	deviceInfo->defaultHighOutputLatency);
			printf("Default frame rate\t\t= %d\n",				deviceInfo->defaultSampleRate);
		}//if ends
	}//for ends
	//Select the desired audio device
	int selectAudioDevice;
	do
	{
		cout << "\nPlease choose which audio output device you wish to use:";
		cin >> selectAudioDevice;cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl;
	} while (!(selectAudioDevice > -1 && selectAudioDevice <= numDevices));
	return selectAudioDevice;
}//SelectAudioDevice() ends


void audioProcess(Common::CEarPair<CMonoBuffer<float>> & bufferOutput, int uiBufferSize)
{
	if(countMeasures<2000)
		start=chrono::high_resolution_clock::now();
	// Declaration, initialization and filling mono buffers
	for (int iCountOfSources = 0; iCountOfSources < iNumberOfSources; iCountOfSources++)
	{
		CMonoBuffer<float> audioInput(uiBufferSize);
		FillBuffer(audioInput, wavSamplePosition.at(iCountOfSources), positionEndFrame.at(iCountOfSources), AudioSamplesVector.at(iCountOfSources));
		Common::CEarPair<CMonoBuffer<float>> bufferProcessed; // Declaration of stereo buffer
		sources.at(iCountOfSources)->SetBuffer(audioInput);				  // Anechoic process of speech source
		sources.at(iCountOfSources)->ProcessAnechoic(bufferProcessed.left, bufferProcessed.right);
		bufferOutput.left += bufferProcessed.left; // Adding anechoic processed speech source to the output mix
		bufferOutput.right += bufferProcessed.right;
	}
	if (bEnableReverb)
	{
		// Reverberation processing of all sources
		Common::CEarPair<CMonoBuffer<float>> bufferReverb;			// Declaration and initialization of separate buffer needed for the reverb
		environment->ProcessVirtualAmbisonicReverb(bufferReverb.left, bufferReverb.right);
		bufferOutput.left += bufferReverb.left;					// Adding reverberated sound to the output mix
		bufferOutput.right += bufferReverb.right;
	}
	if(countMeasures<2000)
	{
		final = chrono::high_resolution_clock::now();
		elapsedtime = chrono::duration_cast<chrono::nanoseconds>(final - start).count();
		times.push_back(elapsedtime);
		countMeasures++;
	}
}//audioProcess() ends

void FillBuffer(CMonoBuffer<float> &output, unsigned int& position, unsigned int& endFrame, std::vector<float>& samplesVector)
{
	position = endFrame + 1;											// Set starting point as next sample of the end of last frame
	if (position >= samplesVector.size())					// If the end of the audio is met, the position variable must return to the beginning
		position = 0;

	endFrame = position + output.size() - 1;			 // Set ending point as starting point plus frame size
	for (int i = 0; i < output.size(); i++)
	{
		if ((position + i) < samplesVector.size())
			output[i] = (samplesVector[position + i]);	 // Fill with audio
		else
			output[i] = 0.0f;							 // Fill with zeros if the end of the audio is met
	}
}//FillBuffer() ends

void LoadWav(std::vector<float>& samplesVector, const char* stringIn)
{
	struct WavHeader								 // Local declaration of wav header struct type (more info in http://soundfile.sapp.org/doc/WaveFormat/)
	{												 // We only need the number of samples, so the rest will be unused assuming file is mono, 16-bit depth and 44.1kHz sampling rate
		char		  fill[40];
		uint32_t	bytesCount;
	} wavHeader;

	FILE* wavFile = fopen(stringIn, "rb");											 // Opening of the wav file
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
}//LoadWav() ends

int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags)
{
	outputBufferStereo.left.Fill(framesPerBuffer, 0.0f);	// Initializes buffer with zeros
	outputBufferStereo.right.Fill(framesPerBuffer, 0.0f);
	// Prevent unused variable warnings.
	(void)timeInfo;
	(void)statusFlags;
	(void)inputBuffer;
	// Process audio data and interlace them
	float *out = (float*)outputBuffer;
	audioProcess(outputBufferStereo, framesPerBuffer);
	CStereoBuffer<float> iOutput;
	iOutput.Interlace(outputBufferStereo.left, outputBufferStereo.right);
	for (auto it = iOutput.begin(); it != iOutput.end(); it++)
	{
		*out++ = *it;										// Setting of value in actual buffer position
	}
	// Moving the steps source
	//float tiempo = float((*timeInfo).currentTime);		
	/*sourcePosition.SetPosition(Common::CVector3(sourcePosition.GetPosition().x,
	sourcePosition.GetPosition().y - tiempo / 110.0f,
	sourcePosition.GetPosition().z > 10 ? sourcePosition.GetPosition().z : sourcePosition.GetPosition().z + tiempo / 110.0f));*/
	//t += 0.005;
	//sourcePosition.SetPosition(Common::CVector3(10 * cos(t), 10 * sin(t), sourcePosition.GetPosition().z));
	//sourceSteps->SetSourceTransform(sourcePosition);
	return paContinue;
}//paCallbackMethod() ends

// This routine will be called by the PortAudio engine when audio is needed.
// It may called at interrupt level on some machines so don't do anything
// that could mess up the system like calling malloc() or free().
static int paCallback(const void						*inputBuffer, 
					  void								*outputBuffer,
					  unsigned long						framesPerBuffer,
					  const PaStreamCallbackTimeInfo*	timeInfo,
					  PaStreamCallbackFlags				statusFlags,
					  void								*userData){
	return paCallbackMethod(inputBuffer,
						outputBuffer,
						framesPerBuffer,
						timeInfo,
						statusFlags);
}//paCallback() ends
