Folder Content
-

- projects: project files for Windows (Visual Studio).
- resources: files needed by the example program to work (HRTF, BRIR and audio files). These files must be copied into the same folder as executable file.
- src: source files of the BasicSpatialisationWithPortaudio example project (`BasicSpatialisationPortAudio.cpp` and `BasicSpatialisationPortAudio.h`).

How to Build and Run in Windows
-
1. Clone the repository and its submodules ("3dti_AudioToolkit" and "third_party_libraries/portaudio").

2. Download the AUDIO SDK from its creator web page. The text below is copied from the file portaudio ASIO-README.txt

>----------------------
>Obtaining the ASIO SDK
>
>In order to build PortAudio with ASIO support, you need to download 
>the ASIO SDK (version 2.0 or later) from Steinberg. Steinberg makes the ASIO 
>SDK available to anyone free of charge, however they do not permit its 
>source code to be distributed.
>
>NOTE: In some cases the ASIO SDK may require patching, see below for further details.
>
>`http://www.steinberg.net/en/company/developer.html`
>
>If the above link is broken search Google for: "download steinberg ASIO SDK"
>
>----------------------

3. Create the folder ASIOSDK as it is shown in the following path 
`localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\src\hostapi\asio\ASIOSDK`
and copy those files and folders which are inside the main folder of the zip (asiosdk_2.3.3_2019-06-14) into the ASIOSDK folder

4. Open the solution `BasicSpatialisationPortAudio.sln` located at 
`localPath\3dti_AudioToolkit_Examples\example_2_basic_spatialisation_portAudio\projects\vstudio` 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. To be able to build the 'libsofa' project, add (using VS Installer) the Visual C++ build tool called "VC++ 2015.3 v140 toolset".

5. Compile the project for the first time. 

6. Run the project

**Note 1**: To run the project from VisualStudio, copy all the files from the folder 
`localPath\3dti_AudioToolkit_Examples\example_2_portAudio\resources`
into the same folder as the project solution or the folder containing the exe file if you are going to run it directly.

**Note 2:** The use of the third party library Libsofa may require the user to add to the environment variable PATH the **absolute** path of the folder containing the libsofa libs. For example, in a 64-bit Microsoft Windows, you can find that folder in `3dti_AudioToolkit\3dti_ResourceManager\third_party_libraries\sofacoustics\libsofa\dependencies\lib\win\x64`





