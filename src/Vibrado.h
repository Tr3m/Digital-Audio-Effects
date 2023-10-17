#pragma once
#include "Delay.h"
#include <utils/LFO.h>

class Vibrado
{
public:

    Vibrado();

    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

    //Setters and Getters
    void setParameter(int index, float newValue);
    float getParameter(int index);

    void setLFOType(int type);
    int getLFOType();

    enum Parameters
    {
        Rate = 0,
        Depth,
        Level,
        LFO_Type
    };

    enum LFO_Types
    {
        Triangle = 0,
        Sine,
        Saw
    };

private:

    double doUnipolarModulationFromMin(double unipolarModulatorValue, double minValue, double maxValue);
    double bipolarToUnipolar(double value);
    float decibelToLinear(float dbValue);

    Delay delayLine_L, delayLine_R;
    LFO lfo;

    //Min and max delay times (in seconds)
    double minDelay{ 0.0001 }; 
    double maxDelay{ 0.007 }; 

    //User Parameters
    float rate{ 2.0 }; //Hz
    float depth{ 70.0 }; //%
    float level_dB{ 0.0 };
    int lfoType{ LFO_Types::Sine };
};