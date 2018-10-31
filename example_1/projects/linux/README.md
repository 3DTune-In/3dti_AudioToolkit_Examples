Before building the example project in linux, the following packages must be installed: zlib1g-dev, curl, libhdf5-10, libhdf5-dev, libnetcdf-c++4, libnetcdf-c++4-dev, libnetcdf11, libnetcdf-dev, m4, pulseaudio, libpulse-dev, osspd

For a quick install of all needed packages just execute the following command in the terminal (in a Debian-based distro):

sudo apt-get install zlib1g-dev curl, libhdf5-10 libhdf5-dev libnetcdf-c++4 libnetcdf-c++4-dev libnetcdf11 libnetcdf-dev m4 pulseaudio libpulse-dev osspd -y

In this example, PulseAudio is used for realtime audio output, but OSS and ALSA are also available by changing Makefile according to https://www.music.mcgill.ca/~gary/rtaudio/compiling.html

To build the example project, just execute make in this directory.