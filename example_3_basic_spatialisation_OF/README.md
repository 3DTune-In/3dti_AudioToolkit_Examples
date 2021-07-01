Example that shows how to use the 3DTI Toolkit using OpenFramework, with a Visual Studio project

Folder Content
-

- resources: files needed by the example program to work (HRTF, BRIR and audio files). These files must be copied into the same folder as the solution file.
- src: source files of the Example 3 project 
- VisualStudio proyect files

How to Build and Run in Windows
-
1. Download Openframework for Windows from https://openframeworks.cc/download/. Lastest version tested: of_v0.11.2_vs2017_release

2. Clone the repository in a folder (you can call it "3DTI_AudioToolkit_Example3") inside the openFramework folder.

3. Clone the submodules ("3dti_AudioToolkit" and third_party_libraries/portaudio) inside the openFramework folder .

4. Open the solution `example_3_basic_spatialisation_OF.sln` located at 
`localPath\of_v0.11.2_vs2017_release\3DTI_AudioToolkit_Example3\example_3_basic_spatialisation_OF` 
This has been tested with Visual Studio 2017 (v141) and Windows SDK 10.0.17763.0. To be able to build the 'libsofa' project, add (using VS Installer) the Visual C++ build tool called "VC++ 2015.3 v140 toolset".

5. Compile the project for the first time. 

6. Run the project

**Note 1**: To run the project from VisualStudio, copy all the files from the folder 
`localPath\3dti_AudioToolkit_Examples\example_2_portAudio\resources`
into the same folder as the project solution or the folder containing the exe file if you are going to run it directly.

**Note 2:** The use of the third party library Libsofa may require the user to add to the environment variable PATH the **absolute** path of the folder containing the libsofa libs. For example, in a 64-bit Microsoft Windows, you can find that folder in `3dti_AudioToolkit\3dti_ResourceManager\third_party_libraries\sofacoustics\libsofa\dependencies\lib\win\x64`





