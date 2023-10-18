#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <Vibrado.h>
#include <utils/extras/AudioChannelUtilities.h>

//==============================================================================
/**
*/
class VibradoPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    VibradoPluginAudioProcessor();
    ~VibradoPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void updateParameters();
    void setLfoType(int lfoTypeIndex);
    int getLfoType();

    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

private:
    //==============================================================================

    Vibrado<float> vibrado;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibradoPluginAudioProcessor)
};
