/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../../Effect_Classes/GUIGraphics.h"

//==============================================================================
/**
*/
class ChorusPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                          public juce::Slider::Listener
{
public:
    ChorusPluginAudioProcessorEditor (ChorusPluginAudioProcessor&);
    ~ChorusPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);

private:

    juce::Slider rateSlider, depthSlider, wetSlider, drySlider;
    

    ChorusPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Chorus };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPluginAudioProcessorEditor)
};
