#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusPluginAudioProcessor::ChorusPluginAudioProcessor()
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

ChorusPluginAudioProcessor::~ChorusPluginAudioProcessor()
{
}

//==============================================================================
const juce::String ChorusPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChorusPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChorusPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChorusPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChorusPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChorusPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChorusPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChorusPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChorusPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChorusPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChorusPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    chorus.prepare(sampleRate);
}

void ChorusPluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChorusPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ChorusPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* channelDataLeft = buffer.getWritePointer (0);
    auto* channelDataRight = buffer.getWritePointer (1);

    chorus.process(channelDataLeft, 0, buffer.getNumSamples());

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
    
}

void ChorusPluginAudioProcessor::updateParameters()
{
  chorus.setRate(*apvts.getRawParameterValue("RATE_ID"));
  chorus.setDepth((*apvts.getRawParameterValue("DEPTH_ID")) / 100.0);
  chorus.setMix(*apvts.getRawParameterValue("WET_ID"));
}

juce::AudioProcessorValueTreeState::ParameterLayout ChorusPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RATE_ID", "RATE", 0.0f, 10.0, 0.3));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH_ID", "DEPTH", 0.0f, 100.0, 50.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WET_ID", "WET", 0.0f, 1.0, 0.4));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DRY_ID", "DRY", 0.0f, 1.0, 0.4));

  return { parameters.begin(), parameters.end() };
}

//==============================================================================
bool ChorusPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChorusPluginAudioProcessor::createEditor()
{
    return new ChorusPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ChorusPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ChorusPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new ChorusPluginAudioProcessor();
}
