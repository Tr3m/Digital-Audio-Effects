#include "Distortion.h"

Distortion::Distortion()
{
	m_Gain = 0.0f;
	m_Level = 0.0f;
	

	preGain.setGainDecibels(m_Gain);
	clipGain.setGainDecibels(40.0f);
	level.setGainDecibels(m_Level);

}


void Distortion::prepare(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
	juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = numOutputChannels;

	preGain.reset();
	preGain.prepare(spec);

	clipGain.reset();
	clipGain.prepare(spec);

	level.reset();
	level.prepare(spec);

}

void Distortion::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	juce::dsp::AudioBlock<float> block(buffer);

	//Set Values
	preGain.setGainDecibels(m_Gain);
	level.setGainDecibels(m_Level);

	//Gain Control
	preGain.process(juce::dsp::ProcessContextReplacing<float>(block));
	
	//Clipping
	clipGain.process(juce::dsp::ProcessContextReplacing<float>(block));

	//Distortion Transfer Function (Waveshaping)
	for (int channel = 0; channel < numOutputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			if (channelData[sample] >= 0) {

				channelData[sample] = (float)(atan(k * channelData[sample]) / atan(k));
			}
			else {

				channelData[sample] = (float)(0.5 * (atan((k / g) * channelData[sample]) / atan(k / g)));

			}
		}

	}

	//Level Control
	level.process(juce::dsp::ProcessContextReplacing<float>(block));


}

void Distortion::setParameter(int index, float newValue)
{
	switch(index)
	{
		case gainParam:
			m_Gain = newValue;
			break;
		case levelParam:
			m_Level = newValue;
			break;
	}
}

float Distortion::getParameter(int index)
{
	switch(index)
	{
		case gainParam:
			return m_Gain;
			break;
		case levelParam:
			return m_Level;
			break;
	}
}