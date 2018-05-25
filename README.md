# 3dti_AudioToolkit_Examples
This is a repository containing an example to show how to use the 3D Tune-In Toolkit library, which is located here: (enlace). This example includes as a submodule the 3D Tune-In Toolkit as well as some 3rd party libraries which are listed below.

**The structure of the repository is as follows:**
```
3dti_AudioToolkit_Examples
├── 3dti_AudioToolkit
└── example_1
    ├── rtaudio
    ├── src
    └── vstudio
```

## Third party libraries

* RtAudio - A set of C++ classes that provide a common API for realtime audio i/o (https://github.com/thestk/rtaudio)

The 3D Tune-In Toolkit has partially integrated the Takuya OOURA General purpose FFT library (http://www.kurims.kyoto-u.ac.jp/~ooura/fft.html)  

The 3D Tune-In Toolkit Resource Management Package uses: 
* Libsofa (Copyright (c) 2013-2014, UMR STMS 9912-Ircam-Centre Pompidou/CNRS/UPMC. https://github.com/sofacoustics/API_Cpp). 

* Cereal - A C11 library for serialization (Grant, W. Shane and Voorhies, Randolph (2017) http://uscilab.github.io/cereal).  

## Compilation issues
The use of the third party library Libsofa may require the user to add to the environment variable PATH the **absolute** path of the folder containing the required files. For example, in a 64-bit Microsoft Windows, you can find that folder in 3dti_AudioToolkit\3dti_ResourceManager\third_party_libraries\sofacoustics\libsofa\dependencies\lib\win\x64

## RtAudio configuration
Before using RtAudio, the developer needs to specify by the use of preprocessor definitions which APIs they want to use in order to RtAudio to compile them and be able to use them. By default, the Visual Studio solution provided compiles WASAPI by defining ____WINDOWS_WASAPI____. Depending on the audio output device and the OS used, this may be subject to change by the user. Further information can be found in: https://www.music.mcgill.ca/~gary/rtaudio/compiling.html

## External content distributed together with this software 

*	HRTF file extracted from the LISTEN database and processed to extract ITD.

*	Audio clip “speech” is extracted from Music from Archimedes, Bang&Olufsen, 1992. 

## Credits

This software was developed by a team coordinated by 
-	[Arcadio Reyes-Lecuona](https://github.com/areyesl) ([University of Malaga](https://www.uma.es/)). Contact: areyes@uma.es  

The members of the development team are (in alphabetical order):
- [Maria Cuevas-Rodriguez](https://github.com/mariacuevas) (University of Malaga)
- [Carlos Garre](https://github.com/carlosgarre) (University of Malaga)
- [Daniel Gonzalez-Toledo](https://github.com/dgonzalezt) (University of Malaga)
- [Luis Molina-Tanco](https://github.com/lmtanco) (University of Malaga)
- [Ernesto de la Rubia](https://github.com/ernestodelarubia) (University of Malaga)
- [Angel Rodriguez-Rivero](https://github.com/ardgzrivero) (University of Malaga)

## Acknowledgements 

![European Union](EU_flag.png "European Union") This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No 644051. 

We would like to acknowledge Dr. Brian FG Katz and his team for their contributions in the field of sound spatialization, which were used as the basis for part of this software.
