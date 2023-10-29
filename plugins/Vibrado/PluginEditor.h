#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>
#include <utils/custom_juce_classes/AssetManager.h>

//==============================================================================
/**
*/

class VibradoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor                                      
{
public:
    VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor&);
    ~VibradoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;    

    void setMeters();
    void updateButtons();

private:
   
    std::unique_ptr<juce::Slider> rateSlider, depthSlider, levelSlider, lfoTypeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAtt, depthSliderAtt, levelSliderAtt, lfoTypeSliderAtt;

    std::unique_ptr<juce::ImageButton> sineButton, triangleButton, sawButton;

    VibradoPluginAudioProcessor& audioProcessor;

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Vibrado };
    AssetManager assetManager;

    LevelMeter inputMeter, outputMeter;

    juce::TooltipWindow tooltipWindow{ this, 200 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibradoPluginAudioProcessorEditor)
};

