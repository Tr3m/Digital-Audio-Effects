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
    
    setSize (400, 300);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setRange(-10.0f, 20.0f);
    gainSlider.setValue(0.0f);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkorchid);
    gainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::black);
    gainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blanchedalmond);
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);

    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setRange(-70.0f, 9.0f);
    levelSlider.setValue(-20.0f);
    levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    levelSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkorchid);
    levelSlider.setColour(juce::Slider::thumbColourId, juce::Colours::black);
    levelSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blanchedalmond);
    addAndMakeVisible(&levelSlider);
    levelSlider.addListener(this);
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.setJustificationType(juce::Justification::centred);
    levelLabel.attachToComponent(&levelSlider, false);

    startTimer(50);

}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (35.0f);
    g.drawFittedText ("Distortion Plug-In", 5, 10, getWidth(), 40, juce::Justification::centred, 1);
}

void DistortionPluginAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getWidth()/2 - 160, 120, 120, 120);
    levelSlider.setBounds(getWidth()/2 + 20 , 120, 120, 120);
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
           
}

void DistortionPluginAudioProcessorEditor::timerCallback()
{
    gainSlider.setValue(audioProcessor.distortion.getParameter(Distortion::Parameters::gainParam));
    levelSlider.setValue(audioProcessor.distortion.getParameter(Distortion::Parameters::levelParam));
}