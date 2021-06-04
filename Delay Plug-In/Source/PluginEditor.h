/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../../Effect_Classes//GUIGraphics.h"


//==============================================================================
/**
*/
class DelayPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public juce::Slider::Listener,
                                         public juce::Timer
{
public:
    DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor&);
    ~DelayPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);
    void timerCallback();

private:

    juce::Slider delayLengthSlider, feedbackSlider, dryMixSlider, wetMixSlider;
    
    GUIGraphics graphics{ GUIGraphics::EffectTypes::Delay };

    DelayPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessorEditor)
};
