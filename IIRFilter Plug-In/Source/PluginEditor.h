/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class IirfilterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener,
                                             public juce::ComboBox::Listener,
                                             public juce::Timer
{
public:
    IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor&);
    ~IirfilterPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);
    void timerCallback();
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    juce::Slider freqSlider, qSlider, gainSlider;
    juce::Label freqLabel, qLabel, gainLabel;
    juce::ComboBox filterSelect;

    IirfilterPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IirfilterPluginAudioProcessorEditor)
};
