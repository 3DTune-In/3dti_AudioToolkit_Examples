Folder Content
-

- projects: project files for Windows (Visual Studio), MacOS (Xcode), and Linux's Makefile, each one in a different folder.
- resources: files needed by the example program to work (HRTF, BRIR and audio files). These files must be copied into the same folder as executable file.
- src: source files of the example project (example.cpp and example.h).

How to Build and Run
-
1. Download the repository

2. Download the portaudio submodule

3. Download the AUDIO SDK from its creator web page (see instructions below), create the folder ASIOSDK as it is shown in the following path and copy all files into this new folder:
>localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\src\hostapi\asio\ASIOSDK

>The text below is copied from the file portaudio ASIO-README.txt
>----------------------
>Obtaining the ASIO SDK

>In order to build PortAudio with ASIO support, you need to download 
the ASIO SDK (version 2.0 or later) from Steinberg. Steinberg makes the ASIO 
SDK available to anyone free of charge, however they do not permit its 
source code to be distributed.

>NOTE: In some cases the ASIO SDK may require patching, see below 
for further details.

>http://www.steinberg.net/en/company/developer.html

>If the above link is broken search Google for:
"download steinberg ASIO SDK"
>----------------------

4. Open the project "example" from the folder that corresponds to your OS (vstudio, xcode, linux) available at: localPath\3dti_AudioToolkit_Examples\example_2_portAudio\projects\
>**Note**: For Visual Studio(Windows), open the file localPath\3dti_AudioToolkit_Examples\example_2_portAudio\projects\vstudio\example.sln. 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. 

5. Compile the project for the first time. 

6. Run the project
>**Note 1**: To run the project from VisualStudio, copy the files from the folder resources into the same folder as the project solution.
>**Note 2**: To run the example you also need to add the location of the portaudio_xXX.dll to your system path. This dll has been created in the previous compilation and should be located in: localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\build\msvc\[Platform]\Release\portaudio_xXX.dll
>Example with a 64bits compilation: localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\build\msvc\x64\Release\portaudio_x64.dll



