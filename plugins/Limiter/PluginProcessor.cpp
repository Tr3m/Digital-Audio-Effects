#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LimiterPluginAudioProcessor::LimiterPluginAudioProcessor()
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

LimiterPluginAudioProcessor::~LimiterPluginAudioProcessor()
{
}

//==============================================================================
const juce::String LimiterPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LimiterPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LimiterPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LimiterPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LimiterPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LimiterPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LimiterPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LimiterPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LimiterPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void LimiterPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LimiterPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    limiter.prepare(sampleRate);
}

void LimiterPluginAudioProcessor::releaseResources()
{
  
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LimiterPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void LimiterPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* channelDataLeft = buffer.getWritePointer (0);
    auto* channelDataRight = buffer.getWritePointer (1);

    limiter.process(channelDataLeft, 0, buffer.getNumSamples());

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
}

void LimiterPluginAudioProcessor::updateParameters()
{
    limiter.setParameter(Limiter<float>::Parameters::Threshold, *apvts.getRawParameterValue("THRESHOLD_ID"));
    limiter.setParameter(Limiter<float>::Parameters::Attack, *apvts.getRawParameterValue("ATTACK_ID"));
    limiter.setParameter(Limiter<float>::Parameters::Release, *apvts.getRawParameterValue("RELEASE_ID"));
    limiter.setParameter(Limiter<float>::Parameters::MakeupGain, *apvts.getRawParameterValue("GAIN_ID"));
}

void LimiterPluginAudioProcessor::setKneeType(int kneeTypeIndex)
{
    limiter.setKneeType(kneeTypeIndex);
}

int LimiterPluginAudioProcessor::getKneeType()
{
    return limiter.getKneeType();
}

juce::AudioProcessorValueTreeState::ParameterLayout LimiterPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("THRESHOLD_ID", "THRESHOLD", -80.0f, 0.0, -20.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK_ID", "ATTACK", 1.0f, 100.0, 35.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE_ID", "RELEASE", 10.0f, 100.0, 35.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN_ID", "GAIN", -20.0f, 20.0, 0.0));

  return { parameters.begin(), parameters.end() };
}

//==============================================================================
bool LimiterPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LimiterPluginAudioProcessor::createEditor()
{
    return new LimiterPluginAudioProcessorEditor (*this);
}

//==============================================================================
void LimiterPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LimiterPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new LimiterPluginAudioProcessor();
}
