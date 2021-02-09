# Overview
This repository is a collection of digital real-time audio effect algorithms implemented in C++. Each effect class is also demonstrated as an audio plug-in (Built using the JUCE Framework).

### Effects Implemented
The effects implemented are the following:
* Time-Based:
  * Digital Delay
* Distortion:
  * Asymmetrical Clipping Distortion

### Requirements -  Third Party Libraries
The JUCE C++ framework is required in order to build the plug-ins. It can be downloaded from the
[JUCE GitHub repository](https://github.com/juce-framework/JUCE)

### Building the Plug-ins
1. Open with the Projucer application the file with the ".jucer" extension in the root directory of the plug-in you want to build

2. In the exporters tab, add the exporter of your choice based on your OS.

3. Click the "Save and open in IDE" button on the top right to open the project. (Projucer will auto generate the appropriate library files)

### Acknowledgements
These DAFX plugins are being  developed in the context of my Graduate Project Thesis at the   Department of Music Technology and Acoustics of the Hellenic Mediterranean University (HMU).

### Contact
Manos Labrakis <labrakismanos@outlook.com>
