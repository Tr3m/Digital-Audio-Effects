#pragma once
#include "Delay.h"
#include "LFO.h"

class Chorus
{
public:

	Chorus();

	void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

    //Setters and Getters
    void setParameter(int index, float newValue);
    float getParameter(int index);

    enum Parameters
    {
    	Rate = 0,
    	Depth,
    	WetMix,
    	DryMix
    };

private:

	double doBipolarModulation(double bipolarModulatorValue, double minValue, double maxValue);

	Delay delayLine_L, delayLine_R;
	LFO lfo;

	float minDelay{0.01};
	float maxDelay{0.03};

	//User Parameters
	double rate{0.33}; //In Hz
	double depth{60.0}; //Depth %
	double wet{0.5}, dry{0.5};

};