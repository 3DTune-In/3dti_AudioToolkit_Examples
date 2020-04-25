# 3dti_AudioToolkit_Examples
This is a repository containing examples to show how to use the 3D Tune-In Toolkit library, which is located here: https://github.com/3DTune-In/3dti_AudioToolkit. This examples include as a submodule the 3D Tune-In Toolkit as well as some 3rd party libraries which are listed below.

**The structure of the repository is as follows:**
```
3dti_AudioToolkit_Examples
├── 3dti_AudioToolkit
├── third_party_libraries
|   └── portaudio
├── example_1
|   ├── rtaudio
|   ├── src
|   ├── resources
|   └── projectsv
|       └── vstudio
|       └── linux
|       └── xcode
└── example_2_portaudio
    ├── src
    └── resources
    └── projects
        └── vstudio
```

## List of eincluded xamples
### Example 1. Basic spatialisation using RTAudio
This example spatialize two static sources using RTAudio as the audio library. HRTF and BRIR for the spatialisation as well as sample clips are provided in the resource folder.
### Example 2. Basic spatialisation using PortAudio
This example spatialize two static sources using PortAudio as the audio library. HRTF and BRIR for the spatialisation as well as sample clips are provided in the resource folder


## Compilation issues
The use of the third party library Libsofa may require the user to add to the environment variable PATH the **absolute** path of the folder containing the required files. For example, in a 64-bit Microsoft Windows, you can find that folder in 3dti_AudioToolkit\3dti_ResourceManager\third_party_libraries\sofacoustics\libsofa\dependencies\lib\win\x64

## RtAudio configuration
Before using RtAudio, the developer needs to specify by the use of preprocessor definitions which APIs they want to use in order to RtAudio to compile them and be able to use them. By default, the Visual Studio solution provided compiles WASAPI by defining ____WINDOWS_WASAPI____. Depending on the audio output device and the OS used, this may be subject to change by the user. Further information can be found in: https://www.music.mcgill.ca/~gary/rtaudio/compiling.html

## External content distributed together with this software 

*	HRTF file extracted from the LISTEN database and processed to extract ITD.

*	Audio clip “speech” is extracted from Music from Archimedes, Bang&Olufsen, 1992. 

## Credits

This software is being developed by a team coordinated by 
-	[Arcadio Reyes-Lecuona](https://github.com/areyesl) ([University of Malaga](https://www.uma.es/)). Contact: areyes@uma.es  

The current members of the development team are (in alphabetical order):
- [Gonzalo Bueno Santana](https://github.com/gonzupi)
- [Maria Cuevas-Rodriguez](https://github.com/mariacuevas)
- [Daniel Gonzalez-Toledo](https://github.com/dgonzalezt) 
- [Luis Molina-Tanco](https://github.com/lmtanco) 

Former members of the development team are (in alphabetical order):
- [Carlos Garre](https://github.com/carlosgarre) 
- [Ernesto de la Rubia](https://github.com/ernestodelarubia) 
- [Angel Rodriguez-Rivero](https://github.com/ardgzrivero)

## Acknowledgements 

![European Union](EU_flag.png "European Union") This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No 644051. 

We would like to acknowledge Dr. Brian FG Katz and his team for their contributions in the field of sound spatialization, which were used as the basis for part of this software.
