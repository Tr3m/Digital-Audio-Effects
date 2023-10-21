#pragma once

#include "PluginProcessor.h"
#include <GUIGraphics.h>

//==============================================================================
/**
*/
class IirfilterPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener
{
public:
    IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor&);
    ~IirfilterPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);



private:
    
    std::unique_ptr<juce::Slider> freqSlider, qSlider, gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqSliderAtt, qSliderAtt, gainSliderAtt;

    juce::Label freqLabel, qLabel, gainLabel;
    juce::TextButton lpButton, hpButton, parButton;

    juce::TooltipWindow tooltipWindow{ this, 200 };

    GUIGraphics graphics{ GUIGraphics::EffectTypes::Filter };

    IirfilterPluginAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IirfilterPluginAudioProcessorEditor)
};
