# 3dti_AudioToolkit_Examples
This is a repository containing examples to show how to use the 3D Tune-In Toolkit library, which is located here: https://github.com/3DTune-In/3dti_AudioToolkit. This examples include as a submodule the 3D Tune-In Toolkit as well as some 3rd party libraries which are listed below.

Technical details about the 3D Tune-In Toolkit spatialiser are described in:

Cuevas-Rodríguez M, Picinali L, González-Toledo D, Garre C, de la Rubia-Cuestas E, Molina-Tanco L and Reyes-Lecuona A. (2019) 3D Tune-In Toolkit: An open-source library for real-time binaural spatialisation. PLOS ONE 14(3): e0211899. https://doi.org/10.1371/journal.pone.0211899

**The structure of the repository is as follows:**
```
3dti_AudioToolkit_Examples
├── 3dti_AudioToolkit
├── third_party_libraries
|   ├── portaudio
|   └── rtaudio
├── example_1_basic_spatialisation_rtaudio
└── example_2_basic_spatialisation_portAudio
```

## List of included examples

**Note:** For more information about each example, please go to README files in the example folder.
### Example 1. Basic spatialisation using RTAudio
This example spatialize two static sources using RTAudio as the audio library. HRTF and BRIR for the spatialisation as well as sample clips are provided in the resource folder.
### Example 2. Basic spatialisation using PortAudio
This example spatialize two static sources using PortAudio as the audio library. HRTF and BRIR for the spatialisation as well as sample clips are provided in the resource folder.

## External content distributed together with this software 

*	HRTF file extracted from the LISTEN database and processed to extract ITD.

*	Audio clip “speech” is extracted from Music from Archimedes, Bang&Olufsen, 1992. 

## Credits

This software is being developed by a team coordinated by 
-	[Arcadio Reyes-Lecuona](https://github.com/areyesl) ([University of Malaga](https://www.uma.es/)). Contact: areyes@uma.es  

The current members of the development team are (in alphabetical order):
- [Maria Cuevas-Rodriguez](https://github.com/mariacuevas)
- [Daniel Gonzalez-Toledo](https://github.com/dgonzalezt) 
- [Luis Molina-Tanco](https://github.com/lmtanco) 

Former members of the development team are (in alphabetical order):
- [Gonzalo Bueno Santana](https://github.com/gonzupi) (Joinined the team Feb 2020, to Jul 2020)
- [Carlos Garre](https://github.com/carlosgarre) (Left the team Jan 2018)
- [Angel Rodriguez-Rivero](https://github.com/ardgzrivero) (Joined the team Feb 2018 to Jul 2019)
- [Ernesto de la Rubia](https://github.com/ernestodelarubia) (Left the team Apr 2018)


## Acknowledgements 

![European Union](EU_flag.png "European Union") This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No 644051. 

We would like to acknowledge Dr. Brian FG Katz and his team for their contributions in the field of sound spatialization, which were used as the basis for part of this software.
