# 3dti_AudioToolkit_Examples
3D Tune-In Toolkit repository that shows a practical example of how to use the 3DTune-In Toolkit library.

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

## External content distributed together with this software 

*	HRTF file extracted from the LISTEN database and processed to extract ITD.

*	Audio clip “speech” is extracted from Music from Archimedes, Bang&Olufsen, 1992. 

## Credits

This software was developed by a team coordinated by 
-	Arcadio Reyes-Lecuona ([University of Malaga](https://www.uma.es/)). Contact: areyes@uma.es  

The members of the development team are (in alphabetical order):
- [Maria Cuevas-Rodriguez](https://github.com/mariacuevas) (University of Malaga)
- [Carlos Garre](https://github.com/carlosgarre) (University of Malaga)
- [Daniel Gonzalez-Toledo](https://github.com/dgonzalezt) (University of Malaga)
- [Luis Molina-Tanco](https://github.com/lmtanco) (University of Malaga)
- [Ernesto de la Rubia](https://github.com/ernestodelarubia) (University of Malaga)
- [Angel Rodríguez-Rivero] (https://github.com/ardgzrivero) (University of Malaga)

## Acknowledgements 

![European Union](3dti_AudioToolkit/docs/images/EU_flag.png "European Union") This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No 644051. 

We would like to acknowledge Dr. Brian FG Katz and his team for their contributions in the field of sound spatialization, which were used as the basis for part of this software.