/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessor::IirfilterPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), leftFilter(getSampleRate(), iirFilter::FilterTypes::HPF),
                          rightFilter(getSampleRate(), iirFilter::FilterTypes::HPF)
#endif
{
}

IirfilterPluginAudioProcessor::~IirfilterPluginAudioProcessor()
{
}

//==============================================================================
const juce::String IirfilterPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IirfilterPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IirfilterPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IirfilterPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IirfilterPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IirfilterPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IirfilterPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IirfilterPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String IirfilterPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void IirfilterPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void IirfilterPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    leftFilter.prepare(sampleRate, samplesPerBlock);
    rightFilter.prepare(sampleRate, samplesPerBlock);
}

void IirfilterPluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IirfilterPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
   
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;


   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void IirfilterPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    //Process Left Channel
    leftFilter.process(buffer, 0, getSampleRate());

    //Process Right Channel
   rightFilter.process(buffer, 1, getSampleRate());
    

}

//==============================================================================
bool IirfilterPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* IirfilterPluginAudioProcessor::createEditor()
{
    return new IirfilterPluginAudioProcessorEditor (*this);
}

//==============================================================================
void IirfilterPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void IirfilterPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  
}

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IirfilterPluginAudioProcessor();
}
