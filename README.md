### Overview
This repository is a collection of real-time audio effect algorithms implemented in C++. Each effect class is also demonstrated as an audio plug-in (Built using the JUCE Framework).

### Effects Implemented
The effects implemented are the following:
* Time-Based:
  * Digital Delay
  * Reverb
* Modulation Effects:
  * Flanger
  * Chorus
  * Vibrado
* Distortion:
  * Vaccum Tube
  * Diode
  * Soft Clipper
  * Hard Clipper
  * Asymmetrical Clipping Distortion
* IIR Filters
    * 2nd Order Butterworth Low-Pass Filter
    * 2nd Order Butterworth High-Pass Filter
    * Peaking Filter
* Dynamic Effects:
  * Compressor
  * Limiter
* Utility Classes:
  * Comb Filter
  * Comb Filter (w/ Linear Interpolation)
  * Modulated Comb Filter
  * All-Pass Filter
  * All-Pass Filter (w/ Linear Interpolation)
  * Modulated All-Pass Filter
  * LFO (Low Frequency Oscillator)
  * Envelope Detector


<img src="https://github.com/Tr3m/Digital-Audio-Effects/assets/58518865/adb171de-abee-460c-be5b-b2ed823de1fc" width="100%" />
<br/>

### Building

### Prerequisites

Before building the plugins, the JUCE submodule included in this repo must be initialized by running:

```bash
git submodule update --init --recursive
```

### Building the Plug-ins

The source code and `CMakeLists.txt` files for building each plugin can be found in the ```plugins``` directory.

### Building on Windows

```bash
cmake -B build
cmake --build build --config Release
```

### Building on MacOS/Linux

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The resulting binaries can be found under the path:

```
build/<PLUGIN_NAME>_artefacts/Release/
```

### Documentation
 Documentation can be found [here](https://thesisdocs.loudsample.com).

### Acknowledgements
These Digital Audio Effects are being developed in the context of my Graduate Project Thesis at the [Department of Music Technology and Acoustics](https://mta.hmu.gr) of [the Hellenic Mediterranean University (HMU)](https://www.hmu.gr).