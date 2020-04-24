Folder Sructure
-

- projects: This folder contains the project files for Windows' Visual Studio, Mac OS X's Xcode, and Linux's Makefile, each one in a different folder.
- resources: This folder contains the files needed by the example program (HRTF, BRIR and audio files). Its contents must be copied to the same folder the executable file is located in order for it to work.
- src: This folder contains the source files of the example project (example.cpp and example.h).

How to Build
-
1.- Download the repository

2.- Download the portaudio submodule

3.- Download the AUDIO SDK from its creator web page and copy it into the folder:
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

4.- Open any of the available projects, they are available for visual studio, xcode and linux, see this folder: localPath\3dti_AudioToolkit_Examples\example_2_portAudio\projects\

>**Note**: For Visual Studio(Windows) you have to open the file localPath\3dti_AudioToolkit_Examples\example_2_portAudio\projects\vstudio\example.sln. 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. 

5.- Compile the project for the first time. 
Note. In Visual Studio - windows a crash will occur when running, because it does not find the portaudio library file, portaudio_xXX.dll. (See point 6).

6.- In windows, in order to execute the examplo, after the first compilation, you have to add the portaudio_xXX.dll to your system path, it should be located in: localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\build\msvc\[Platform]\Release\portaudio_xXX.dll
>Example with a 64bits compilation: localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\build\msvc\x64\Release\portaudio_x64.dll



