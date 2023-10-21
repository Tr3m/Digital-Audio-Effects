#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (370, 470);

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(gainSlider.get());
    gainSlider->setLookAndFeel(&graphics);

    gainSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "GAIN_ID", *gainSlider);
    
    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(levelSlider.get());
    levelSlider->setLookAndFeel(&graphics);

    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);

    filterSlider.reset(new juce::Slider("FilterSlider"));
    filterSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(filterSlider.get());
    filterSlider->setLookAndFeel(&graphics);

    filterSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FILTER_FREQ_ID", *filterSlider);

    gainSlider->setBounds(44, 91, 124, 124);
    levelSlider->setBounds(198, 91, 124, 124);
    filterSlider->setBounds(44, 252, 124, 124);    
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
    gainSliderAtt = nullptr;
    levelSliderAtt = nullptr;
    filterSliderAtt = nullptr;
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DistortionPluginAudioProcessorEditor::resized()
{
    
}