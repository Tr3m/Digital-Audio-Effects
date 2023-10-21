#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessor::DistortionPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Params", createParameters())
#endif
{
}

DistortionPluginAudioProcessor::~DistortionPluginAudioProcessor()
{
}

//==============================================================================
const juce::String DistortionPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionPluginAudioProcessor::getNumPrograms()
{
    return 1; 
}

int DistortionPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortionPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortionPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    distortion.prepare(sampleRate);
}

void DistortionPluginAudioProcessor::releaseResources()
{
   
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DistortionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
  updateParameters();

  for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

  auto* channelDataLeft = buffer.getWritePointer (0);
  auto* channelDataRight = buffer.getWritePointer (1);

  distortion.process(channelDataLeft, 0, buffer.getNumSamples());

  // Do dual mono
  AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
}

void DistortionPluginAudioProcessor::updateParameters()
{
  distortion.setGain(*apvts.getRawParameterValue("GAIN_ID"));
  distortion.setLevel(*apvts.getRawParameterValue("LEVEL_ID"));
  distortion.setFilterFreq(*apvts.getRawParameterValue("FILTER_FREQ_ID"));
}

juce::AudioProcessorValueTreeState::ParameterLayout DistortionPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN_ID", "GAIN", -10.0f, 20.0, 0.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL_ID", "LEVEL", -60.0, 20.0, -10.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER_FREQ_ID", "FILTER_FREQ", 500.0f, 20000.0, 20000.0));

  return { parameters.begin(), parameters.end() };
}

//==============================================================================
bool DistortionPluginAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DistortionPluginAudioProcessor::createEditor()
{
    return new DistortionPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void DistortionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new DistortionPluginAudioProcessor();
}
