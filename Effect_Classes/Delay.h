#pragma once
//#include "../Delay Plug-In/JuceLibraryCode/JuceHeader.h"
#include <JuceHeader.h>

class Delay
{
public:

	Delay();
    Delay(float _delayLength, float _feedback, float _wet, float _dry);

	
    float getParameter(int index);
    void setParameter(int index, float newValue);
   

    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

    //=======================================================================


    enum Parameters
    {
        delayLengthParam = 0,
        dryMixParam,
        wetMixParam,
        feedbackParam,
        numParameters
    };

    

private:

    
    double m_SampleRate;
    float delayLength, feedback, dryMix, wetMix;

    //bool isBypassed;

	// Circular Buffer Variables
    juce::AudioSampleBuffer delayBuffer;
   
    int delayBufferLength;
    int delayReadPosition;
    int delayWritePosition;

};