#include "IIRFilter.h"


IIRFilter::IIRFilter()
{
	fc = 400.0f;

		
}

void IIRFilter::calculateCoeffs(float fc)
{
	thetac = (2 * m_pi * fc) / m_SampleRate;

	gamma = cos(thetac) / (1 + sin(thetac));

	a0 = (1 + gamma) / 2;

	a1 = - ((1 + gamma) / 2);

	a2 = 0.0f;

	b1 = -gamma;

	b2 = 0.0f;

	c0 = 1.0f;

	d0 = 0.0;
}

void IIRFilter::prepare(double sampleRate, int samplesPerBlock)
{
	m_SampleRate = (float)sampleRate;
	calculateCoeffs(fc);

	std::string log = "a0 = " + std::to_string(a0) + "\na1 = " + std::to_string(a1) + "\na1 = " + std::to_string(a2) + "\na2 = " + std::to_string(a2)
		+ "\nb1 = " + std::to_string(b1) + "\nb2 = " + std::to_string(b2) + "\nSample Rate = " + std::to_string(m_SampleRate);
	DBG(log);
}

void IIRFilter::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	

	for(int channel = 0; channel < numOutputChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);

		float xn, yn;

		for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			xn = channelData[sample];
			
			yn = d0 * xn + c0 * (a0 * xn + a1 * xn_1 + a2 * xn_2 - b1 * yn_1 - b2 * yn_2);

			channelData[sample] = yn;

			xn_2 = xn_1;
			xn_1 = xn;

			yn_2 = yn_1;
			yn_1 = yn;

			
		}
	}
}