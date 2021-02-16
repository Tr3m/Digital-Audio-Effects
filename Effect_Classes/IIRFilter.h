#pragma once
#include "../IIRFilter Plug-In/JuceLibraryCode/JuceHeader.h"

class IIRFilter
{

public:

	IIRFilter();


	void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels);

    void setParameter(int index, float newValue);
    float getPameter(int index);

    void calculateCoeffs(float fc);


private:

	float thetac, gamma, a0, a1, a2, b1, b2, c0, d0, m_SampleRate, fc;

	float m_pi{3.14159265358979323846};

	float xn_1 = 0, xn_2 = 0, yn_1 = 0, yn_2 = 0;

};