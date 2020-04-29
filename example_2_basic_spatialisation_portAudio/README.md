Folder Content
-

- projects: project files for Windows (Visual Studio).
- resources: files needed by the example program to work (HRTF, BRIR and audio files). These files must be copied into the same folder as executable file.
- src: source files of the BasicSpatialisationWithPortaudio example project (`example.cpp` and `example.h`).

How to Build and Run in Windows
-
1. Download the repository

2. Download the portaudio submodule

3. Download the AUDIO SDK from its creator web page. The text below is copied from the file portaudio ASIO-README.txt

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

4. Create the folder ASIOSDK as it is shown in the following path 
`localPath\3dti_AudioToolkit_Examples\third_party_libraries\portaudio\src\hostapi\asio\ASIOSDK`
and copy those files and folders which are inside the main folder of the zip (asiosdk_2.3.3_2019-06-14) into the ASIOSDK folder

5. Open the solution `example.sln` located at 
`localPath\3dti_AudioToolkit_Examples\example_2_portAudio\projects\vstudio\example.sln.` 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. 

6. Compile the project for the first time. 

7. Run the project

**Note 1**: To run the project from VisualStudio, copy all the files from the folder 
`localPath\3dti_AudioToolkit_Examples\example_2_portAudio\resources`
into the same folder as the project solution or the folder containing the exe file if you are going to run it directly.





