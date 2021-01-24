#pragma once
#include "../Distortion Plug-In/JuceLibraryCode/JuceHeader.h"

class Distortion
{

public:


	Distortion();

	
	void setParameter(int index, float newValue);
	float getParameter(int index);

	void prepare(double sampleRate, int samplesPerBlock, int numOutputChannels);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

    static enum Parameters
    {
    	gainParam = 0,
    	levelParam
    };


private:

	float m_Gain, m_Level;


	juce::dsp::Gain <float> preGain, clipGain, level;


	float k{ 1.5 }; //input gain
	float g{ 0.7 }; //saturation limit

};