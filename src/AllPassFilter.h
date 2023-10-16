#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class AllPassFilter
{
public:

	AllPassFilter();
    AllPassFilter(float _delayLength, float _feedback);

	//Setters and Getters
    void setDelayLength(float newValue);
    float getDelayLength();

    void setFeedback(float newValue);
    float getFeedback();
   

    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);
    float processSample(float sample, int channel);

     

private:

    
    double m_SampleRate;
    float delayLength, feedback;

 
	// Circular Buffer Variables
    juce::AudioSampleBuffer delayBuffer;
   
    int delayBufferLength;
    int delayReadPosition;
    int delayWritePosition;

};