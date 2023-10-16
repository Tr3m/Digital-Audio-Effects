#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "Delay.h"
#include "IIRFilter.h"
#include "AllPassFilter.h"
#include "CombFilter.h"


class Reverb
{
	public:

		Reverb();

		float getParameter(int index);
	    void setParameter(int index, float newValue);
   

	    void prepare(double sampleRate, int samplesPerBlock);
	    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

		enum Parameters
		{
			length = 0,
			feedback,
			wetMix,
			dryMix,
			Filter
		};

    //=======================================================================

	private:

		double m_SampleRate;

		void updateReverbParameters();

		float len = 0.09; //Length
		float g = 0.8;	//Feedback
		float dry = 0.5;
		float wet = 0.5;
		float filterValue = 20000.0;

		//TODO: Maybe do these in an array...

		CombFilter comb1, comb2, comb3, comb4; 
		IIRFilter filterLeft{ 44100, IIRFilter::FilterTypes::LPF, filterValue };
		IIRFilter filterRight{ 44100, IIRFilter::FilterTypes::LPF, filterValue };

		AllPassFilter allpass1{ 0.005, 0.7};
		AllPassFilter allpass2{ 0.00168, 0.7};
		AllPassFilter allpass3{ 0.00048, 0.7};
	    
};