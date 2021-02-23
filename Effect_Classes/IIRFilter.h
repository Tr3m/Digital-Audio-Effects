#pragma once
#include "../IIRFilter Plug-In/JuceLibraryCode/JuceHeader.h"

class iirFilter
{

public:

	iirFilter(double sampleRate);
	iirFilter(double sampleRate, int type);


	void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels, double sampleRate);

    //void setParameter(int index, float newValue);
    //float getPameter(int index);

	void setCutoff(float newValue);
	void setFilterType(int filterType);
	void setQ(float newValue);

	float getCutoff();
	float getQ();

    
	enum FilterTypes
	{
		LPF = 0,	//Low Pass Fitler
		HPF,		//High Pass Filter
		BPF,		//Band Pass Fitler
		BSF			//Band Stop Filter
	};


private:

	void calculateCoeffs(float freq, double sampleRate);


	float a0, a1, a2, b1, b2, c0, d0, r, C;

	double last_SampleRate;

	float m_pi = 3.14159265358979323846;

	float xn_1 = 0, xn_2 = 0, yn_1 = 0, yn_2 = 0;

	//User Variables
	float fc, Q;
	int filterType;

};