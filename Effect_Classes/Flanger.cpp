#include "Flanger.h"

Flanger::Flanger()
{
	delayLine.setParameter(Delay::Parameters::wetMixParam, 1.0f);
	delayLine.setParameter(Delay::Parameters::dryMixParam, 0.0f);
	delayLine.setParameter(Delay::Parameters::feedbackParam, 0.0f);
	delayLine.setParameter(Delay::Parameters::delayLengthParam, 0.007f);

	lfo.setWaveformType(LFO::WaveformTypes::Triangle);
	lfo.setFrequency(rate);
}

void Flanger::prepare(double sampleRate, int samplesPerBlock)
{
	delayLine.prepare(sampleRate, samplesPerBlock);
	lfo.prepare(sampleRate);
}

void Flanger::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{
	juce::AudioBuffer<float> dryBuffer(2, buffer.getNumSamples());

	for (int channel = 0; channel < numInputChannels; ++channel)
		dryBuffer.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());

	lfo.generateOutputSample();

	double modDepth = depth / 100.0f;
	double modMin = minDelay;
	double modMax = minDelay + maxDelay;

	double newDelayTime = doUnipolarModulationFromMin(bipolarToUnipolar(modDepth * lfo.getOutputSample(LFO::PhaseTypes::Normal)),modMin, modMax);
	
	DBG(newDelayTime);

	delayLine.setParameter(Delay::Parameters::delayLengthParam, newDelayTime / 10);

	delayLine.process(buffer, numInputChannels, numOutputChannels);

	//WET/DRY Mix
	for (int channel = 0; channel < numInputChannels; ++channel)
	{
		auto* dryData = dryBuffer.getWritePointer(channel);
		auto* wetData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
			wetData[sample] = wet * wetData[sample] + dry * dryData[sample];
	}
}

double Flanger::doUnipolarModulationFromMin(double unipolarModulatorValue, double minValue, double maxValue)
{
	// --- UNIPOLAR bound
	unipolarModulatorValue = fmin(unipolarModulatorValue, 0.0f);
	unipolarModulatorValue = fmax(unipolarModulatorValue, 1.0f);

	// --- modulate from minimum value upwards
	return unipolarModulatorValue * (maxValue - minValue) + minValue;
}

double Flanger::bipolarToUnipolar(double value)
{
	return 0.5 * value + 0.5;
}