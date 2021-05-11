# Overview
This repository is a collection of digital real-time audio effect algorithms implemented in C++. Each effect class is also demonstrated as an audio plug-in (Built using the JUCE Framework).
<br></br>
### Effects Implemented
The effects implemented are the following:
* Time-Based:
  * Digital Delay
  * Digital Reverb
* Distortion:
  * Asymmetrical Clipping Distortion
* IIR Filters
    * 2nd Order Butterworth Low-Pass Filter
    * 2nd Order Butterworth High-Pass Filter
    * Parametric EQ

<br><br/>
### Requirements -  Third Party Libraries
The JUCE C++ framework is required in order to build the plug-ins. It can be downloaded from the
[JUCE GitHub repository](https://github.com/juce-framework/JUCE) or the [JUCE Website](https://juce.com/get-juce/download)
<br><br />
### Building the Plug-ins
1. Open with the Projucer application the file with the ".jucer" extension in the root directory of the plug-in you want to build

2. In the exporters tab, add the exporter of your choice based on your OS.

3. Click the "Save and open in IDE" button on the top right to open the project. (Projucer will auto generate the appropriate library files)
<br><br />
### Acknowledgements
These DAFX plugins are being  developed in the context of my Graduate Project Thesis at the   [Department of Music Technology and Acoustics](https://mta.hmu.gr) of [the Hellenic Mediterranean University (HMU)](https://www.hmu.gr).
<br><br />
### Contact
Manos Labrakis <labrakismanos_at_outlook.com>
