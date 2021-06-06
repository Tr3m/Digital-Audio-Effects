/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (370, 470);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setRange(-10.0f, 20.0f);
    gainSlider.setValue(audioProcessor.distortion.getParameter(Distortion::Parameters::gainParam));
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainSlider.setLookAndFeel(&graphics);
    

    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setRange(-70.0f, 9.0f);
    levelSlider.setValue(audioProcessor.distortion.getParameter(Distortion::Parameters::levelParam));
    levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&levelSlider);
    levelSlider.addListener(this);
    levelSlider.setLookAndFeel(&graphics);

    filterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    filterSlider.setRange(500.0f, 20000.0f, 10);
    addAndMakeVisible(&filterSlider);
    filterSlider.addListener(this);
    filterSlider.setValue(audioProcessor.distortion.getParameter(Distortion::Parameters::filterParam));
    filterSlider.setLookAndFeel(&graphics);
    

    startTimer(50);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DistortionPluginAudioProcessorEditor::resized()
{
    gainSlider.setBounds(44, 91, 124, 124);
    levelSlider.setBounds(198, 91, 124, 124);
    filterSlider.setBounds(44, 252, 124, 124);
}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.distortion.setParameter(Distortion::Parameters::gainParam, slider->getValue());
    }
    else if (slider == &levelSlider)
    {
        audioProcessor.distortion.setParameter(Distortion::Parameters::levelParam, slider->getValue());
    }
    else if (slider == &filterSlider)
    {
        audioProcessor.distortion.setParameter(Distortion::Parameters::filterParam, slider->getValue());
    }
           
}

void DistortionPluginAudioProcessorEditor::timerCallback()
{
   
}