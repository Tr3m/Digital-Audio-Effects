#include "Distortion.h"

Distortion::Distortion()
{
	m_Gain = 0.0f;
	m_Level = -20.0f;
	
	/*
	preGain.setGainDecibels(m_Gain);
	clipGain.setGainDecibels(40.0f);
	level.setGainDecibels(m_Level);
	*/

}


void Distortion::prepare(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
	/*
	juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = numOutputChannels;
	*/

	/*
	preGain.reset();
	preGain.prepare(spec);

	clipGain.reset();
	clipGain.prepare(spec);

	level.reset();
	level.prepare(spec);
	*/

	filterLeft.prepare(sampleRate, samplesPerBlock);
	filterRight.prepare(sampleRate, samplesPerBlock);

	m_SampleRate = sampleRate;

}

void Distortion::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	//juce::dsp::AudioBlock<float> block(buffer);

	//Set Values
	//preGain.setGainDecibels(m_Gain);
	//level.setGainDecibels(m_Level);

	//Gain Control
	//preGain.process(juce::dsp::ProcessContextReplacing<float>(block));

	buffer.applyGain(juce::Decibels::decibelsToGain(m_Gain));
	
	//Clipping
	//clipGain.process(juce::dsp::ProcessContextReplacing<float>(block));

	buffer.applyGain(juce::Decibels::decibelsToGain(40.0));

	//Distortion Transfer Function (Waveshaping)
	for (int channel = 0; channel < numOutputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			if (channelData[sample] >= 0) 
			{

				channelData[sample] = (float)(atan(k * channelData[sample]) / atan(k));
			}
			else 
			{

				channelData[sample] = (float)(0.5 * (atan((k / g) * channelData[sample]) / atan(k / g)));

			}
		}

	}

	//Filter Control
	filterLeft.process(buffer, 0, m_SampleRate);
	filterRight.process(buffer, 1, m_SampleRate);

	//Level Control
	//level.process(juce::dsp::ProcessContextReplacing<float>(block));
	buffer.applyGain(juce::Decibels::decibelsToGain(m_Level));

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
		case filterParam:
			filterLeft.setCutoff(newValue);
			filterRight.setCutoff(newValue);
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
		case filterParam:
			return m_FilterCutoff;
			break;
	}
}