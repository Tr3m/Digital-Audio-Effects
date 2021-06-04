/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessorEditor::ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{    
    setSize (370, 470);

    length.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    length.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    length.setRange(0.001f, 0.1f, 0.001);
    addAndMakeVisible(&length);
    length.addListener(this);
    length.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::length));
    length.setLookAndFeel(&graphics);
  

    feedback.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedback.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    feedback.setRange(0, 1, 0.001);
    addAndMakeVisible(&feedback);
    feedback.addListener(this);
    feedback.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::feedback));
    feedback.setLookAndFeel(&graphics);



    wet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wet.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    wet.setRange(0, 1, 0.01);
    addAndMakeVisible(&wet);
    wet.addListener(this);
    wet.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::wetMix));
    wet.setLookAndFeel(&graphics);


    dry.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dry.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    dry.setRange(0, 1, 0.01);
    addAndMakeVisible(&dry);
    dry.addListener(this);
    dry.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::dryMix));
    dry.setLookAndFeel(&graphics);
  

    filter.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filter.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    filter.setRange(500.0f, 20000.0f, 10);
    addAndMakeVisible(&filter);
    filter.addListener(this);
    filter.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::Filter));
    filter.setLookAndFeel(&graphics);
   
}

ReverbPluginAudioProcessorEditor::~ReverbPluginAudioProcessorEditor()
{
}

//==============================================================================
void ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void ReverbPluginAudioProcessorEditor::resized()
{
    int smallSlider = 100;

    length.setBounds(44, 91, 124, 124);
    feedback.setBounds(198, 91, 124, 124);
    wet.setBounds(20, 266, smallSlider, smallSlider);
    dry.setBounds(132, 266, smallSlider, smallSlider);
    filter.setBounds(243, 266, smallSlider, smallSlider);
}

void ReverbPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &length)
        audioProcessor.rev1.setParameter(Reverb::Parameters::length, slider->getValue());
    else if (slider == &feedback)
        audioProcessor.rev1.setParameter(Reverb::Parameters::feedback, slider->getValue());
    else if (slider == &wet)
        audioProcessor.rev1.setParameter(Reverb::Parameters::wetMix, slider->getValue());
    else if (slider == &dry)
        audioProcessor.rev1.setParameter(Reverb::Parameters::dryMix, slider->getValue());
    else if (slider == &filter)
        audioProcessor.rev1.setParameter(Reverb::Parameters::Filter, slider->getValue());
}

void ReverbPluginAudioProcessorEditor::timerCallback()
{

}