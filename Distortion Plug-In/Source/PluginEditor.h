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
class DistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener,
                                             public juce::Timer
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);
    void timerCallback();

private:
    
    juce::Slider gainSlider, levelSlider, filterSlider;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Distortion };

    DistortionPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
