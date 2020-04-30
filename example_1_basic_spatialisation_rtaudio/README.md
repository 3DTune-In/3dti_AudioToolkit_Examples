Folder Content
-

- projects: project files for Windows (Visual Studio).
- resources: files needed by the example program to work (HRTF, BRIR and audio files). These files must be copied into the same folder as executable file.
- src: source files of the BasicSpatialisationWithPortaudio example project (`BasicSpatialisationRTAudio.cpp` and `BasicSpatialisationRTAudio.h`).

How to Build and Run in Windows
-
1. Download the repository

2. Download the rtaudio submodule

3. Before using RtAudio:

The developer needs to specify by the use of preprocessor definitions which APIs they want to use in order to RtAudio to compile them and be able to use them. By default, the Visual Studio solution provided compiles WASAPI by defining ____WINDOWS_WASAPI____. Depending on the audio output device and the OS used, this may be subject to change by the user. Further information can be found in: https://www.music.mcgill.ca/~gary/rtaudio/compiling.html

4. Open the solution `BasicSpatializationRTAudio.sln` located at 
`localPath\3dti_AudioToolkit_Examples\example_1_basic_spatialisation_rtaudio\projects\vstudio` 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. 

5. Compile the project. 

6. Run the project

**Note 1:** To run the project from VisualStudio, copy all the files from the folder 
`localPath\3dti_AudioToolkit_Examples\example_1_basic_spatialisation_rtaudio\resources`
into the same folder as the project solution or the folder containing the exe file if you are going to run it directly.

**Note 2:** The use of the third party library Libsofa may require the user to add to the environment variable PATH the **absolute** path of the folder containing the libsofa libs. For example, in a 64-bit Microsoft Windows, you can find that folder in `3dti_AudioToolkit\3dti_ResourceManager\third_party_libraries\sofacoustics\libsofa\dependencies\lib\win\x64`
