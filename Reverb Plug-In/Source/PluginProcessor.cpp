/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessor::ReverbPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    /*float len = 0.073;
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
    comb4.setParameter(Delay::Parameters::wetMixParam, 1.0);*/
    

}

ReverbPluginAudioProcessor::~ReverbPluginAudioProcessor()
{
}

//==============================================================================
const juce::String ReverbPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReverbPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReverbPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    /*comb1.prepare(sampleRate, samplesPerBlock);
    comb2.prepare(sampleRate, samplesPerBlock);
    comb3.prepare(sampleRate, samplesPerBlock);
    comb4.prepare(sampleRate, samplesPerBlock);*/

    rev1.prepare(sampleRate, samplesPerBlock);
}

void ReverbPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReverbPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /*juce::AudioBuffer<float> buff_1(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_2(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_3(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_4(2, buffer.getNumSamples());*/

  
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    rev1.process(buffer, totalNumInputChannels, totalNumOutputChannels);

   /*
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        buff_1.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_2.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_3.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_4.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        
    }
   
    
  
    
    comb1.process(buff_1, totalNumInputChannels, totalNumOutputChannels);
    comb2.process(buff_2, totalNumInputChannels, totalNumOutputChannels);
    comb3.process(buff_3, totalNumInputChannels, totalNumOutputChannels);
    comb4.process(buff_4, totalNumInputChannels, totalNumOutputChannels);

   
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData1 = buff_2.getWritePointer(channel);
        auto* channelData2 = buff_4.getWritePointer(channel);
       

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData1[sample] = -1 * channelData1[sample];
            channelData2[sample] = -1 * channelData2[sample];
          
        }
    }

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        buffer.copyFrom(channel, 0, buff_1.getWritePointer(channel), buffer.getNumSamples());
        //buffer.applyGain(0.5f);

        buffer.addFrom(channel, 0, buff_2.getWritePointer(channel), buffer.getNumSamples());
        //buffer.applyGain(0.5f);
        
        buffer.addFrom(channel, 0, buff_3.getWritePointer(channel), buffer.getNumSamples());
        //buffer.applyGain(0.5f);

        buffer.addFrom(channel, 0, buff_4.getWritePointer(channel), buffer.getNumSamples());
        //buffer.applyGain(0.5f);
    }*/
}

//==============================================================================
bool ReverbPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReverbPluginAudioProcessor::createEditor()
{
    return new ReverbPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ReverbPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbPluginAudioProcessor();
}
