#pragma once

#include "PluginProcessor.h"
#include <utils/custom_juce_classes/GUIGraphics.h>
#include <utils/custom_juce_classes/LevelMeter.h>

//==============================================================================
/**
*/
class DistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::ComboBox::Listener
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    void setMeters();

private:
    
    std::unique_ptr<juce::Slider> gainSlider, levelSlider, filterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAtt, levelSliderAtt, filterSliderAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxAttachment;

    std::unique_ptr<juce::ComboBox> algorithmSelect;
    juce::String algorithmLabels[NUM_MODULES]{"Tube", "Diode", "Soft", "Hard", "Asymetric"};

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Distortion };
    LevelMeter inputMeter, outputMeter;

    DistortionPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
