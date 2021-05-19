#pragma once
#include <JuceHeader.h>
#include "Delay.h"
#include "LFO.h"

class Flanger
{
public:
	
	Flanger();

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
	double doUnipolarModulationFromMin(double unipolarModulatorValue, double minValue, double maxValue);
	double bipolarToUnipolar(double value);

	Delay delayLine;
	LFO lfo;

	double minDelay = 0.01;
	double maxDelay = 0.07;

	//User Parameters
	double rate{0.7}; //In Hz
	double depth{50.0}; //Depth %
	double wet{0.5}, dry{0.5};

};