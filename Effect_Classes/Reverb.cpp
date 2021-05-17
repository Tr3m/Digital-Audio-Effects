#include "Reverb.h"

Reverb::Reverb()
{
    
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
    switch (index)
    {
    case Parameters::length:
        len = newValue;
        break;
    case Parameters::feedback:
        g = newValue;
        if (g > 1)
            g = 1;
        if (g < 0.1)
            g = 0.1;
        break;
    case Parameters::wetMix:
        wet = newValue;
        if (wet > 1.0f)
            wet = 1.0f;
        if (wet < 0)
            wet = 0;
        break;
    case Parameters::dryMix:
        dry = newValue;
        if (dry > 1.0f)
            dry = 1.0f;
        if (dry < 0)
            dry = 0;
        break;
    case Parameters::Filter:
        if (newValue > 20000.0)
            newValue = 20000.0;
        if (newValue < 500.0)
            newValue = 500.0;
        filterLeft.setCutoff(newValue);
        filterRight.setCutoff(newValue);
        break;
    }
    

    updateReverbParameters();
}

float Reverb::getParameter(int index)
{
    switch (index)
    {
    case Parameters::length:
        return len;
        break;
    case Parameters::feedback:
        return g;
        break;
    case Parameters::wetMix:
        return wet;
        break;
    case Parameters::dryMix:
        return dry;
        break;
    case Parameters::Filter:
        return filterValue;
        break;
    }
}

void Reverb::prepare(double sampleRate, int samplesPerBlock)
{
    m_SampleRate = sampleRate;

	comb1.prepare(sampleRate, samplesPerBlock);
    comb2.prepare(sampleRate, samplesPerBlock);
    comb3.prepare(sampleRate, samplesPerBlock);
    comb4.prepare(sampleRate, samplesPerBlock);

    filterLeft.prepare(sampleRate, samplesPerBlock);
    filterRight.prepare(sampleRate, samplesPerBlock);
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
   
       
  
    //Comb filter processing

    comb1.process(buff_1, numInputChannels, numOutputChannels);
    comb2.process(buff_2, numInputChannels, numOutputChannels);
    comb3.process(buff_3, numInputChannels, numOutputChannels);
    comb4.process(buff_4, numInputChannels, numOutputChannels);
   

    //Phase inverse for comb filters 2 and 4

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        auto* channelData1 = buff_2.getWritePointer(channel);
        auto* channelData2 = buff_4.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData1[sample] = -channelData1[sample];
            channelData2[sample] = -channelData2[sample];
        }
    }
    
    //Sum the comb filter outputs.

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        buff_1.addFrom(channel, 0, buff_1.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9f);

        buff_1.addFrom(channel, 0, buff_2.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.8f);
        
        buff_1.addFrom(channel, 0, buff_3.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.5f);

        buff_1.addFrom(channel, 0, buff_4.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.5f);
    }

    //Filter Process
    filterLeft.process(buff_1, 0, m_SampleRate);
    filterRight.process(buff_1, 1, m_SampleRate);

    //WET/DRY Control

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        auto* dryData = buffer.getWritePointer(channel);
        auto* WetData = buff_1.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            dryData[sample] = dry * dryData[sample] + wet * WetData[sample];
        }
    }
}

void Reverb::updateReverbParameters()
{
    comb1.setParameter(Delay::Parameters::feedbackParam, g);
    comb2.setParameter(Delay::Parameters::feedbackParam, g - 0.0131);
    comb3.setParameter(Delay::Parameters::feedbackParam, g - 0.0274);
    comb4.setParameter(Delay::Parameters::feedbackParam, g - 0.031);

    comb1.setParameter(Delay::Parameters::delayLengthParam, len);
    comb2.setParameter(Delay::Parameters::delayLengthParam, len - 0.0011);
    comb3.setParameter(Delay::Parameters::delayLengthParam, len + 0.0019);
    comb4.setParameter(Delay::Parameters::delayLengthParam, len - 0.0007);
}