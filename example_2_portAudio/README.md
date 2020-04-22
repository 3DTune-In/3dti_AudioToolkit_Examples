This folder is structured as follows:

projects: This folder contains the project files for Windows' Visual Studio, Mac OS X's Xcode, and Linux's Makefile, each one in a different folder.

resources: This folder contains the files needed by the example program (HRTF, BRIR and audio files). Its contents must be copied to the same folder the executable file is located in order for it to work.

rtaudio: This folder contains RtAudio library, a cross-platform library with a common API for realtime audio output. By default it will use WASAPI in Windows, CoreAudio in OSX and PulseAudio in Linux.

src: This folder contains the source files of the example project (example.cpp and example.h).