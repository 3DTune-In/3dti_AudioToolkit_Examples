/**
*
* \brief This is the main source file of the example project 1 using 3D Tune-In Toolkit
* \date	April 2018
*
* \authors A. Rodr�guez-Rivero, as part of the 3DI-DIANA Research Group (University of Malaga)
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

#include "example.h"

#define SAMPLERATE 44100
int iBufferSize;
bool bEnableReverb;
int main()
{
    //Introduce buffer size and reverb
    cout << "Insert wished buffer size (1024, 2048, 4096...2048 recommended) :\t";
    cin >> iBufferSize;
    cin.ignore();
    char cInput;
    do{
    	cout << "\nDo you want reverb? (Y/n) : "; cInput=getchar();
    }while(cInput != 'y' && cInput != 'n' && cInput != '\n');
    if(cInput=='y' || cInput == '\n')
    	bEnableReverb = true;
    else
    	bEnableReverb = false;

    // Core setup
    Common::TAudioStateStruct audioState;	    // Audio State struct declaration
    audioState.bufferSize = iBufferSize;			// Setting buffer size and sample rate
    audioState.sampleRate = SAMPLERATE;       //44100;
    myCore.SetAudioState(audioState);		      // Applying configuration to core
    myCore.SetHRTFResamplingStep(15);		      // Setting 15-degree resampling step for HRTF

  	ERRORHANDLER3DTI.SetVerbosityMode(VERBOSITYMODE_ERRORSANDWARNINGS);
  	ERRORHANDLER3DTI.SetErrorLogStream(&std::cout, true);

    // Listener setup
    listener = myCore.CreateListener();								 // First step is creating listener
    Common::CTransform listenerPosition = Common::CTransform();		 // Setting listener in (0,0,0)
    listenerPosition.SetPosition(Common::CVector3(0, 0, 0));
    listener->SetListenerTransform(listenerPosition);
    listener->DisableCustomizedITD();								 // Disabling custom head radius
	   /* HRTF can be loaded in either SOFA (more info in https://sofacoustics.org/) or 3dti-hrtf format.
	   These HRTF files are provided with 3DTI Audio Toolkit. They can be found in 3dti_AudioToolkit/resources/HRTF */
	   HRTF::CreateFrom3dti("hrtf.3dti-hrtf", listener);			 // Comment this line and uncomment next lines to load the default HRTF in SOFA format instead of in 3dti-hrtf format
    /*
    bool bSpecifiedDelays;
    HRTF::CreateFromSofa("hrtf.sofa", listener, bSpecifiedDelays);
    */

    // Environment setup
    environment = myCore.CreateEnvironment();									// Creating environment to have reverberated sound
  	environment->SetReverberationOrder(TReverberationOrder::BIDIMENSIONAL);		// Setting number of ambisonic channels to use in reverberation processing
    BRIR::CreateFromSofa("brir.sofa", environment);								// Loading SOFAcoustics BRIR file and applying it to the environment

    // Speech source setup
    sourceSpeech = myCore.CreateSingleSourceDSP();										 // Creating audio source
    LoadWav(samplesVectorSpeech, "speech.wav");											 // Loading .wav file
    Common::CTransform sourceSpeechPosition = Common::CTransform();
    sourceSpeechPosition.SetPosition(Common::CVector3(0, 2, 0));						 // Setting source in x=0,y=2,z=0 (on the left)
    sourceSpeech->SetSourceTransform(sourceSpeechPosition);
    sourceSpeech->SetSpatializationMode(Binaural::TSpatializationMode::HighQuality);	//HighPerformance vs HighQuality // Choosing high quality mode for anechoic processing
    sourceSpeech->DisableNearFieldEffect();												 // Audio source will not be close to listener, so we don't need near field effect
    sourceSpeech->EnableAnechoicProcess();												 // Setting anechoic and reverb processing for this source
    sourceSpeech->EnableDistanceAttenuationAnechoic();

    // Steps source setup
    sourceSteps = myCore.CreateSingleSourceDSP();										 // Creating audio source
    LoadWav(samplesVectorSteps, "steps.wav");											   // Loading .wav file
    Common::CTransform sourceStepsPosition = Common::CTransform();
    sourceStepsPosition.SetPosition(Common::CVector3(-3, 10, -10));						 // Setting source in (-3,-10,-10)
    sourceSteps->SetSourceTransform(sourceStepsPosition);
    sourceSteps->SetSpatializationMode(Binaural::TSpatializationMode::HighQuality);		 // Choosing high quality mode for anechoic processing
    sourceSteps->DisableNearFieldEffect();												 // Audio source will not be close to listener, so we don't need near field effect
    sourceSteps->EnableAnechoicProcess();												   // Setting anechoic and reverb processing for this source
    sourceSteps->EnableDistanceAttenuationAnechoic();
    sourcePosition = sourceStepsPosition;												 // Saving initial position into source position to move the steps audio source later on

  	// Declaration and initialization of stereo buffer
  	outputBufferStereo.left.resize(iBufferSize);
  	outputBufferStereo.right.resize(iBufferSize);

    // Audio output configuration, using RtAudio (more info in https://www.music.mcgill.ca/~gary/rtaudio/)

    audio = std::shared_ptr<RtAudio>(new RtAudio());  // Initialization of RtAudio
													  // It uses the first API it founds compiled and requires of preprocessor definitions
													  // which depends on the OS used and the audio output device (more info in https://www.music.mcgill.ca/~gary/rtaudio/compiling.html)

    // Setting the output parameters
    RtAudio::StreamParameters outputParameters;
    outputParameters.nChannels = 2;									 // Setting output as stereo
    outputParameters.deviceId = audio->getDefaultOutputDevice();	 // Choosing default output device

    // Setting the audio stream options
    RtAudio::StreamOptions options;
    char flag;
    do{
  	    cout << "\nFlags :\t0 - CONTINUE\n\t1 - REALTIME\n\t2 - MINIMIZE_LATENCY\n\t3 - HOG_DEVICE\n";
  	    cin >> flag;
  	    if(flag == '1'){
  	    	  options.flags |= RTAUDIO_SCHEDULE_REALTIME;
  	    }else if(flag == '2'){
  	    	  options.flags |= RTAUDIO_MINIMIZE_LATENCY;
  	    }else if(flag == '3'){
  	    	  options.flags |= RTAUDIO_HOG_DEVICE;
  	    }
    }while(flag!='0');
    //options.flags = RTAUDIO_SCHEDULE_REALTIME;						 // Setting real-time audio output
    options.numberOfBuffers = 4;//4							 // Setting number of buffers used by RtAudio
    options.priority = 1;											 // Setting stream thread priority
    unsigned int frameSize = iBufferSize;									 // Declaring and initializing frame size variable because next statement needs it

    // Opening of audio stream
    try{
	       audio->openStream(&outputParameters,     // Specified output parameters
		               nullptr,			                  // Unspecified input parameters because there will not be input stream
		               RTAUDIO_FLOAT32,	              // Output buffer will be 32-bit float
		               44100,			                    // Sample rate will be 44.1 kHz
		               &frameSize,		                // Frame size will be iBufferSize samples
		               &rtAudioCallback,	            // Pointer to the function that will be called every time RtAudio needs the buffer to be filled
		               nullptr,			                  // Unused pointer to get feedback
		               &options			                  // Stream options (real-time stream, 4 buffers and priority)
		              );

     }catch ( RtAudioError& e ) {
    	    std::cout << "\nERROR:\t" << e.getMessage() << '\n' << std::endl;
    	    exit( 0 );
     }

    // Starting the stream
    audio->startStream();

    // Informing user by the console to press any key to end the execution
    cout << "Press ENTER to finish... \n";
    cin.ignore();
    getchar();

	// Stopping and closing the stream
	audio->stopStream();
	audio->closeStream();

    return 0;
}

static int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int uiBufferSize, double streamTime, RtAudioStreamStatus status, void *data)
{
    // Setting the output buffer as float
    float * floatOutputBuffer = (float *)outputBuffer;

    // Checking if there is underflow or overflow
    if (status) cout << "stream over/underflow detected";

  	// Initializes buffer with zeros
	 outputBufferStereo.left.Fill(uiBufferSize, 0.0f);
	 outputBufferStereo.right.Fill(uiBufferSize, 0.0f);

    // Getting the processed audio
    audioProcess(outputBufferStereo, uiBufferSize);

    // Declaration and initialization of interlaced audio vector for correct stereo output
    CStereoBuffer<float> iOutput;
    iOutput.Interlace(outputBufferStereo.left, outputBufferStereo.right);

    // Buffer filling loop
    for (auto it = iOutput.begin(); it != iOutput.end(); it++)
    {
        floatOutputBuffer[0] = *it;								 // Setting of value in actual buffer position
        floatOutputBuffer = &floatOutputBuffer[1];				 // Updating pointer to next buffer position
    }

    // Moving the steps source
    sourcePosition.SetPosition(Common::CVector3(sourcePosition.GetPosition().x,
                                                sourcePosition.GetPosition().y - streamTime / 110.0f,
                                                sourcePosition.GetPosition().z > 10 ? sourcePosition.GetPosition().z : sourcePosition.GetPosition().z + streamTime / 110.0f));
    sourceSteps->SetSourceTransform(sourcePosition);
    return 0;
}

void audioProcess(Common::CEarPair<CMonoBuffer<float>> & bufferOutput, int uiBufferSize)
{
    // Declaration, initialization and filling mono buffers
    CMonoBuffer<float> speechInput(uiBufferSize);	FillBuffer(speechInput, wavSamplePositionSpeech, positionEndFrameSpeech, samplesVectorSpeech);
    CMonoBuffer<float> stepsInput (uiBufferSize);  FillBuffer(stepsInput,  wavSamplePositionSteps,  positionEndFrameSteps,  samplesVectorSteps );

    // Declaration of stereo buffer
    Common::CEarPair<CMonoBuffer<float>> bufferProcessed;

    // Anechoic process of speech source
    sourceSpeech->SetBuffer(speechInput);
    sourceSpeech->ProcessAnechoic(bufferProcessed.left, bufferProcessed.right);

    // Adding anechoic processed speech source to the output mix
   	bufferOutput.left += bufferProcessed.left;
  	bufferOutput.right += bufferProcessed.right;

    // Anechoic process of steps source
    sourceSteps->SetBuffer(stepsInput);
    sourceSteps->ProcessAnechoic(bufferProcessed.left, bufferProcessed.right);

    // Adding anechoic processed steps source to the output mix
    bufferOutput.left += bufferProcessed.left;
    bufferOutput.right += bufferProcessed.right;

    // Declaration and initialization of separate buffer needed for the reverb
    Common::CEarPair<CMonoBuffer<float>> bufferReverb;

    // Reverberation processing of all sources
    if(bEnableReverb){
           environment->ProcessVirtualAmbisonicReverb(bufferReverb.left, bufferReverb.right);
	    // Adding reverberated sound to the output mix
	    bufferOutput.left += bufferReverb.left;
	    bufferOutput.right += bufferReverb.right;
    }
}

void FillBuffer(CMonoBuffer<float> &output, unsigned int& position, unsigned int& endFrame, std::vector<float>& samplesVector)
{
    position = endFrame + 1;							 // Set starting point as next sample of the end of last frame
    if (position >= samplesVector.size())				 // If the end of the audio is met, the position variable must return to the beginning
        position = 0;

    endFrame = position + output.size() - 1;			 // Set ending point as starting point plus frame size
    //cout << "Position - " << position << "\tendFrame - " << endFrame << "\toutputSize - " << samplesVector.size() << endl;
    for (int i = 0; i < output.size(); i++) {
        //cout << "Dentro del for, i#" << i << "\toutputPre #" << output[i];
        if ((position + i) < samplesVector.size())
            output[i] = (samplesVector[position + i]);	 // Fill with audio
        else
            output[i] = 0.0f;							 // Fill with zeros if the end of the audio is met
        //cout << "\toutputPost #" << output[i] << endl;
    }
    //cout << endl << endl;
}

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
}

