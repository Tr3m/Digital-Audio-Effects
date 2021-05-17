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
    setSize (400, 360);

    length.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    length.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    length.setRange(0.001f, 0.1f, 0.001);
    addAndMakeVisible(&length);
    length.addListener(this);
    length.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::length));
    //==
    lengthLabel.setText("Length", juce::dontSendNotification);
    lengthLabel.setJustificationType(juce::Justification::topLeft);
    lengthLabel.attachToComponent(&length, false);

    feedback.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    feedback.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    feedback.setRange(0, 1, 0.001);
    addAndMakeVisible(&feedback);
    feedback.addListener(this);
    feedback.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::feedback));
    //==
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::topLeft);
    feedbackLabel.attachToComponent(&feedback, false);

    wet.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wet.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    wet.setRange(0, 1, 0.01);
    addAndMakeVisible(&wet);
    wet.addListener(this);
    wet.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::wetMix));
    //==
    wetLabel.setText("Wet", juce::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::topLeft);
    wetLabel.attachToComponent(&wet, false);

    dry.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    dry.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    dry.setRange(0, 1, 0.01);
    addAndMakeVisible(&dry);
    dry.addListener(this);
    dry.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::dryMix));
    //==
    dryLabel.setText("Dry", juce::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::topLeft);
    dryLabel.attachToComponent(&dry, false);

    filter.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    filter.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    filter.setRange(500.0f, 20000.0f, 10);
    addAndMakeVisible(&filter);
    filter.addListener(this);
    filter.setValue(audioProcessor.rev1.getParameter(Reverb::Parameters::Filter));
    //==
    filterLabel.setText("Filter", juce::dontSendNotification);
    filterLabel.setJustificationType(juce::Justification::topLeft);
    filterLabel.attachToComponent(&filter, false);
}

ReverbPluginAudioProcessorEditor::~ReverbPluginAudioProcessorEditor()
{
}

//==============================================================================
void ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (25.0f);
    g.drawFittedText("Reverb Plug-In", 5, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void ReverbPluginAudioProcessorEditor::resized()
{
    length.setBounds(10, 80, getWidth(), 30);
    feedback.setBounds(10, 140, getWidth(), 30);
    wet.setBounds(10, 200, getWidth(), 30);
    dry.setBounds(10, 260, getWidth(), 30);
    filter.setBounds(10, 320, getWidth(), 30);
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