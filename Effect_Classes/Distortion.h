#pragma once
#include <JuceHeader.h>
#include "iirFilter.h"

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
    	levelParam,
		filterParam
    };


private:

	float m_Gain, m_Level;
	float m_FilterCutoff = 20000.0;

	double m_SampleRate;

	juce::dsp::Gain <float> preGain, clipGain, level;
	IIRFilter filterLeft{44100, IIRFilter::FilterTypes::LPF, m_FilterCutoff };
	IIRFilter filterRight{44100, IIRFilter::FilterTypes::LPF, m_FilterCutoff };


	float k{ 1.5 }; //input gain
	float g{ 0.7 }; //saturation limit

};