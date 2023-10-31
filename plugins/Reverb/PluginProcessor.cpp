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
                       ), apvts(*this, nullptr, "Params", createParameters())
#endif
{
    
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
    reverb.prepare(sampleRate);
    meterSource.prepare(sampleRate);
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
    updateParameters();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    meterSource.updateInputLevel(buffer);

    auto* channelDataLeft = buffer.getWritePointer (0);
    auto* channelDataRight = buffer.getWritePointer (1);

    reverb.process(channelDataLeft, 0, buffer.getNumSamples());
    buffer.applyGain(GainUtilities<float>::decibelsToGain(*apvts.getRawParameterValue("LEVEL_ID")));

    meterSource.updateOutputLevel(buffer);

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());  
}

void ReverbPluginAudioProcessor::updateParameters()
{
  reverb.setRoomSize(*apvts.getRawParameterValue("ROOM_SIZE_ID"));
  reverb.setDecay(*apvts.getRawParameterValue("DECAY_ID") / 100.0);
  reverb.setCutoff(*apvts.getRawParameterValue("FILTER_ID"));
  reverb.setMix(*apvts.getRawParameterValue("MIX_ID") / 100.0);
}

juce::AudioProcessorValueTreeState::ParameterLayout ReverbPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ROOM_SIZE_ID", "ROOM_SIZE", 1.0f, 5.0, 1.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY_ID", "DECAY", 0.0f, 100.0, 50.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_ID", "FILTER", 500.0, 20000.0, 20000.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX_ID", "MIX", 0.0f, 100.0, 40.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL_ID", "LEVEL", -12.0f, 12.0, 0.0));


  return { parameters.begin(), parameters.end() };
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
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void ReverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbPluginAudioProcessor();
}
