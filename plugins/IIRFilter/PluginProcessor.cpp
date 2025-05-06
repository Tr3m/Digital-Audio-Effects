#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessor::IirfilterPluginAudioProcessor()
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
  iirFilter.prepare(sampleRate);
  meterSource.prepare(sampleRate);
  iirFilter.setFilterType(*apvts.getRawParameterValue("FILTER_TYPE_ID"));
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
  updateParameters();

  meterSource.updateInputLevel(buffer);

  for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

  auto* channelDataLeft = buffer.getWritePointer (0);
  auto* channelDataRight = buffer.getWritePointer (1);

  iirFilter.process(channelDataLeft, 0, buffer.getNumSamples());

  buffer.applyGain(GainUtilities<float>::decibelsToGain(*apvts.getRawParameterValue("LEVEL_ID")));

  meterSource.updateOutputLevel(buffer);

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
}

void IirfilterPluginAudioProcessor::updateParameters()
{
  iirFilter.setCutoff(*apvts.getRawParameterValue("FREQUENCY_ID"));
  iirFilter.setGain(*apvts.getRawParameterValue("GAIN_ID"));
}

void IirfilterPluginAudioProcessor::setFilterType(int filterTypeIndex)
{
  iirFilter.setFilterType(*apvts.getRawParameterValue("FILTER_TYPE_ID"));
}

int IirfilterPluginAudioProcessor::getFilterType()
{
  return iirFilter.getFilterType();
}

juce::AudioProcessorValueTreeState::ParameterLayout IirfilterPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FREQUENCY_ID", "FREQUENCY", 20.0f, 20000.0, 500.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN_ID", "GAIN", -20.0f, 20.0, 0.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL_ID", "LEVEL", -12.0f, 12.0, 0.0));
  parameters.push_back(std::make_unique<juce::AudioParameterInt>("FILTER_TYPE_ID", "FILTER_TYPE", 0, 2, 0));

  return { parameters.begin(), parameters.end() };
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
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);    
}

void IirfilterPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(apvts.state.getType()))
      apvts.replaceState(juce::ValueTree::fromXml(*xmlState)); 
}

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IirfilterPluginAudioProcessor();
}
