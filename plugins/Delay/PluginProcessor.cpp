#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessor::DelayPluginAudioProcessor()
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

DelayPluginAudioProcessor::~DelayPluginAudioProcessor()
{
}

//==============================================================================
const juce::String DelayPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayPluginAudioProcessor::getNumPrograms()
{
    return 1;  
}

int DelayPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DelayPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DelayPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  delay.prepare(sampleRate);
  meterSource.prepare(sampleRate);
}

void DelayPluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DelayPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
  updateParameters();

  for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

  auto* channelDataLeft = buffer.getWritePointer (0);
  auto* channelDataRight = buffer.getWritePointer (1);

  meterSource.updateInputLevel(buffer);
  
  delay.process(channelDataLeft, 0, buffer.getNumSamples());
  buffer.applyGain(GainUtilities<float>::decibelsToGain(*apvts.getRawParameterValue("LEVEL_ID")));

  meterSource.updateOutputLevel(buffer);

  // Do dual mono
  AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
}

void DelayPluginAudioProcessor::updateParameters()
{
  delay.setDelayTime(*apvts.getRawParameterValue("DELAY_TIME_ID"));
  delay.setFeedback(*apvts.getRawParameterValue("FEEDBACK_ID"));
  delay.setMix((*apvts.getRawParameterValue("MIX_ID") / 100.0));
}

juce::AudioProcessorValueTreeState::ParameterLayout DelayPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DELAY_TIME_ID", "DELAY_TIME", 95.0f, 1000.0, 500.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK_ID", "FEEDBACK", 0.0f, 0.95, 0.7));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX_ID", "MIX", 0.0f, 100.0, 50.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL_ID", "LEVEL", -12.0f, 12.0, 0.0));

  return { parameters.begin(), parameters.end() };
}

//==============================================================================
bool DelayPluginAudioProcessor::hasEditor() const
{
    return true; 
}

juce::AudioProcessorEditor* DelayPluginAudioProcessor::createEditor()
{
    return new DelayPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DelayPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);    
}

void DelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(apvts.state.getType()))
      apvts.replaceState(juce::ValueTree::fromXml(*xmlState));    
}

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayPluginAudioProcessor();
}
