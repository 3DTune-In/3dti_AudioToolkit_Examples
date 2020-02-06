
## Installation guide
Before building the example project in linux, some packages must be installed. 
#### Quick install of the packages(Debian/Ubuntu based)
For a quick install of all needed packages just execute the following command in the terminal (in a Debian-based distro):
~~~
sudo apt-get install zlib1g-dev curl libhdf5-10 libhdf5-dev libnetcdf-c++4 libnetcdf-c++4-dev libnetcdf11 libnetcdf-dev m4 pulseaudio libpulse-dev osspd -y
~~~
#### Slow install of the packages
The packages can be downloaded from here too (rpm or debian package):

+ [zlib1g-dev](https://pkgs.org/download/zlib1g-dev)
+ [curl](https://pkgs.org/download/curl)
+ [libhdf5-10](https://pkgs.org/download/libhdf5-10)
+ [libhdf5-dev](https://pkgs.org/download/libhdf5-dev)
+ [libnetcdf-c++4](https://pkgs.org/download/libnetcdf-c++4)
+ [libnetcdf-c++4-dev](https://pkgs.org/download/libnetcdf-c++4-dev)
+ [libnetcdf11](https://pkgs.org/download/libnetcdf11)
+ [libnetcdf-dev](https://pkgs.org/download/libnetcdf-dev)
+ [m4](https://pkgs.org/download/m4)
+ [pulseaudio](https://pkgs.org/download/pulseaudio)
+ [libpulse-dev](https://pkgs.org/download/libpulse-dev)
+ [osspd](https://pkgs.org/download/osspd)

## Notes
In this example, PulseAudio is used for realtime audio output, but OSS and ALSA are also available by changing Makefile according to [https://www.music.mcgill.ca/~gary/rtaudio/compiling.html](https://www.music.mcgill.ca/~gary/rtaudio/compiling.html)

The frame rate can be configurated modifying the constant _"BUFFERSIZE"_ in the file _"example.cpp"_. In linux, typically, it must have a value of _2048_.


### How to install


Open a terminal and go to your user folder and type this following commands:

~~~
git clone --recursive https://github.com/3DTune-In/3dti_AudioToolkit_Examples.git
cd 3dti_AudioToolkit_Examples/example_1/projects/linux/
sudo apt-get install cmake make
make
~~~

## Use guide
To build the example project just execute _make_ in this directory when all the "git clone" have been done (if the git clone is not made there will be a problem with libraries and header files). 
When the make is made go to the new location ./bin/release and paste the files inside of the _resources_ folder.
Then just execute the example and enjoy.
~~~
cd ./bin/release/
cp ../../../../resources/* ./
./example
~~~

If in your console appears that issue: 
~~~
_NOT_ running realtime scheduling
~~~
You can run it like admin to solve it using sudo writing: _sudo ./example_

