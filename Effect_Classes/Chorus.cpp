#include "Chorus.h"

Chorus::Chorus()
{
	delayLine_L.setParameter(Delay::Parameters::wetMixParam, wet);
	delayLine_L.setParameter(Delay::Parameters::dryMixParam, dry);
	delayLine_L.setParameter(Delay::Parameters::feedbackParam, 0.0f);
	delayLine_L.setParameter(Delay::Parameters::delayLengthParam, 0.01);

	delayLine_R.setParameter(Delay::Parameters::wetMixParam, wet);
	delayLine_R.setParameter(Delay::Parameters::dryMixParam, dry);
	delayLine_R.setParameter(Delay::Parameters::feedbackParam, 0.0f);
	delayLine_R.setParameter(Delay::Parameters::delayLengthParam, 0.01);

	lfo.setWaveformType(LFO::WaveformTypes::Sine);
	lfo.setFrequency(rate);
}

void Chorus::prepare(double sampleRate, int samplesPerBlock)
{
	delayLine_L.prepare(sampleRate, samplesPerBlock);
	delayLine_R.prepare(sampleRate, samplesPerBlock);
	lfo.prepare(sampleRate);
}

void Chorus::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	double modDepth = depth / 100.0f;
	double modMin = minDelay;
	double modMax = minDelay + maxDelay;



	auto* channelDataLeft = buffer.getWritePointer(0);
	auto* channelDataRight = buffer.getWritePointer(1);

	for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
	{
		lfo.generateOutputSample();
		
		float newDelayTime = doBipolarModulation(depth * lfo.getOutputSample(LFO::PhaseTypes::Normal), modMin, modMax);

		channelDataLeft[sample] = delayLine_L.processSample(channelDataLeft[sample], 0);
		delayLine_L.setParameter(Delay::Parameters::delayLengthParam, newDelayTime);

		channelDataRight[sample] = delayLine_R.processSample(channelDataRight[sample], 0);
		delayLine_R.setParameter(Delay::Parameters::delayLengthParam, newDelayTime);
	}
}

void Chorus::setParameter(int index, float newValue)
{
	switch (index)
	{
	case Parameters::Rate:
		rate = newValue;

		//Bounds Check
		if (rate < 0.1)
			rate = 0.1;
		if (rate > 10.0)
			rate = 10.0;

		lfo.setFrequency(rate);

		break;

	case Parameters::Depth:
		depth = newValue;

		//Bounds Check
		if (depth < 0.0)
			depth = 0.0;
		if (depth > 100.0)
			depth = 100;

		break;

	case Parameters::WetMix:
		wet = newValue;

		//Bounds Check
		if (wet > 1.0)
			wet = 1.0;
		if (wet < 0.0)
			wet = 0.0;

		delayLine_L.setParameter(Delay::Parameters::wetMixParam, wet);
		delayLine_R.setParameter(Delay::Parameters::wetMixParam, wet);

		break;

	case Parameters::DryMix:
		dry = newValue;

		//Bounds Check
		if (dry > 1.0)
			dry = 1.0;
		if (dry < 0.0)
			dry = 0.0;

		delayLine_L.setParameter(Delay::Parameters::dryMixParam, dry);
		delayLine_R.setParameter(Delay::Parameters::dryMixParam, dry);

		break;
	}
}

float Chorus::getParameter(int index)
{
	switch (index)
	{
	case Parameters::Rate:
		return rate;
		break;
	case Parameters::Depth:
		return depth;
		break;
	case Parameters::WetMix:
		return wet;
		break;
	case Parameters::DryMix:
		return dry;
		break;
	}
}

double Chorus::doBipolarModulation(double bipolarModulatorValue, double minValue, double maxValue)
{
	// BIPOLAR bound
	bipolarModulatorValue = fmin(bipolarModulatorValue, -1.0f);
	bipolarModulatorValue = fmax(bipolarModulatorValue, 1.0f);

	// Calculate range and midpoint
	double halfRange = (maxValue - minValue) / 2.0;
	double midpoint = halfRange + minValue;

	return bipolarModulatorValue * (halfRange)+midpoint;
}