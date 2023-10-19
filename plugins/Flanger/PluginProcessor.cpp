#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerPluginAudioProcessor::FlangerPluginAudioProcessor()
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

FlangerPluginAudioProcessor::~FlangerPluginAudioProcessor()
{
}

//==============================================================================
const juce::String FlangerPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlangerPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FlangerPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FlangerPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FlangerPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlangerPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlangerPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlangerPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FlangerPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void FlangerPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FlangerPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    flanger.prepare(sampleRate);
   
}

void FlangerPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FlangerPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FlangerPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* channelDataLeft = buffer.getWritePointer (0);
    auto* channelDataRight = buffer.getWritePointer (1);

    flanger.process(channelDataLeft, 0, buffer.getNumSamples());

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
    
}

void FlangerPluginAudioProcessor::updateParameters()
{
  flanger.setRate(*apvts.getRawParameterValue("RATE_ID"));
  flanger.setDepth((*apvts.getRawParameterValue("DEPTH_ID")) / 100.0);
  flanger.setMix(*apvts.getRawParameterValue("WET_ID"));
}

juce::AudioProcessorValueTreeState::ParameterLayout FlangerPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RATE_ID", "RATE", 0.0f, 10.0, 0.3));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH_ID", "DEPTH", 0.0f, 100.0, 50.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WET_ID", "WET", 0.0f, 1.0, 0.4));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DRY_ID", "DRY", 0.0f, 1.0, 0.4));

  return { parameters.begin(), parameters.end() };
}

//==============================================================================
bool FlangerPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FlangerPluginAudioProcessor::createEditor()
{
    return new FlangerPluginAudioProcessorEditor (*this);
}

//==============================================================================
void FlangerPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void FlangerPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new FlangerPluginAudioProcessor();
}
