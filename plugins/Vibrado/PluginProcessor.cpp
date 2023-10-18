#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessor::VibradoPluginAudioProcessor()
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
    vibrado.prepare(sampleRate);
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
    updateParameters();

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* channelDataLeft = buffer.getWritePointer (0);
    auto* channelDataRight = buffer.getWritePointer (1);

    vibrado.process(channelDataLeft, 0, buffer.getNumSamples());

    // Do dual mono
    AudioChannelUtilities<float>::doDualMono(channelDataLeft, channelDataRight, 0, buffer.getNumSamples());
}

void VibradoPluginAudioProcessor::updateParameters()
{
  vibrado.setRate(*apvts.getRawParameterValue("RATE_ID"));
  vibrado.setDepth((*apvts.getRawParameterValue("DEPTH_ID")) / 100.0);
  vibrado.setLevel(*apvts.getRawParameterValue("LEVEL_ID"));
}

void VibradoPluginAudioProcessor::setLfoType(int lfoTypeIndex)
{
    vibrado.setLFOType(lfoTypeIndex);
}

int VibradoPluginAudioProcessor::getLfoType()
{
    return vibrado.getLFOType();
}

juce::AudioProcessorValueTreeState::ParameterLayout VibradoPluginAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RATE_ID", "RATE", 0.0f, 10.0, 0.3));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH_ID", "DEPTH", 0.0f, 100.0, 50.0));
  parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL_ID", "LEVEL", -20.0f, 20.0, 0.0));

  return { parameters.begin(), parameters.end() };
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
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void VibradoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new VibradoPluginAudioProcessor();
}
