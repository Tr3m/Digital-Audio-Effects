/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessor::VibradoPluginAudioProcessor()
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
    vibrado.setLFOType(Vibrado::LFO_Types::Triangle);
}

VibradoPluginAudioProcessor::~VibradoPluginAudioProcessor()
{
}

//==============================================================================
const juce::String VibradoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibradoPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibradoPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibradoPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibradoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibradoPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibradoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibradoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VibradoPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibradoPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VibradoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    vibrado.prepare(sampleRate, samplesPerBlock);
}

void VibradoPluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibradoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VibradoPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    vibrado.process(buffer, totalNumInputChannels, totalNumOutputChannels);

}

//==============================================================================
bool VibradoPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VibradoPluginAudioProcessor::createEditor()
{
    return new VibradoPluginAudioProcessorEditor (*this);
}

//==============================================================================
void VibradoPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VibradoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibradoPluginAudioProcessor();
}
