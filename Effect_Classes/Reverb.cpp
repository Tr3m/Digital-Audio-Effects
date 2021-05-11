#include "Reverb.h"

Reverb::Reverb()
{
	//Comb filter Feedback and Time initialization. This needs some work...

    float len = 0.073;
    float g = 0.4;

    comb1.setParameter(Delay::Parameters::feedbackParam, g);
    comb2.setParameter(Delay::Parameters::feedbackParam, g - 0.0131);
    comb3.setParameter(Delay::Parameters::feedbackParam, g - 0.0274);
    comb4.setParameter(Delay::Parameters::feedbackParam, g - 0.031);

    comb1.setParameter(Delay::Parameters::delayLengthParam, len);
    comb2.setParameter(Delay::Parameters::delayLengthParam, len - 0.0011);
    comb3.setParameter(Delay::Parameters::delayLengthParam, len + 0.0019);
    comb4.setParameter(Delay::Parameters::delayLengthParam, len - 0.0007);

    comb1.setParameter(Delay::Parameters::dryMixParam, 0.0);
    comb1.setParameter(Delay::Parameters::wetMixParam, 1.0);

    comb2.setParameter(Delay::Parameters::dryMixParam, 0.0);
    comb2.setParameter(Delay::Parameters::wetMixParam, 1.0);

    comb3.setParameter(Delay::Parameters::dryMixParam, 0.0);
    comb3.setParameter(Delay::Parameters::wetMixParam, 1.0);

    comb4.setParameter(Delay::Parameters::dryMixParam, 0.0);
    comb4.setParameter(Delay::Parameters::wetMixParam, 1.0);
}

void Reverb::setParameter(int index, float newValue)
{

}

float Reverb::getParameter(int index)
{
	return 0.0f; //Placeholder...
}

void Reverb::prepare(double sampleRate, int samplesPerBlock)
{
	comb1.prepare(sampleRate, samplesPerBlock);
    comb2.prepare(sampleRate, samplesPerBlock);
    comb3.prepare(sampleRate, samplesPerBlock);
    comb4.prepare(sampleRate, samplesPerBlock);
}

void Reverb::process(juce::AudioBuffer<float>& buffer, int numInputChannels, int numOutputChannels)
{

    juce::AudioBuffer<float> buff_1(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_2(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_3(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_4(2, buffer.getNumSamples());

	//Fill the Comb Filter buffers with the input samples

	for (int channel = 0; channel < numInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        buff_1.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_2.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_3.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_4.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        
    }
   
    
  
    //Comb filter parallel processing

    comb1.process(buff_1, numInputChannels, numOutputChannels);
    comb2.process(buff_2, numInputChannels, numOutputChannels);
    comb3.process(buff_3, numInputChannels, numOutputChannels);
    comb4.process(buff_4, numInputChannels, numOutputChannels);
   

   
    
    //Sum the filter outputs
    //TODO:: Need to add WET/DRY controls...

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        buffer.copyFrom(channel, 0, buff_1.getWritePointer(channel), buffer.getNumSamples());
        //buffer.applyGain(0.5f);

        buffer.addFrom(channel, 0, buff_2.getWritePointer(channel), buffer.getNumSamples());
        buffer.applyGain(0.5f);
        
        buffer.addFrom(channel, 0, buff_3.getWritePointer(channel), buffer.getNumSamples());
        buffer.applyGain(0.5f);

        buffer.addFrom(channel, 0, buff_4.getWritePointer(channel), buffer.getNumSamples());
        buffer.applyGain(0.5f);
    }
}