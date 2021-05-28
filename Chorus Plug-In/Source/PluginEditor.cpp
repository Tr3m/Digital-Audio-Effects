/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusPluginAudioProcessorEditor::ChorusPluginAudioProcessorEditor (ChorusPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(400, 340);

    //Rate Slider
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(&rateSlider);
    rateSlider.addListener(this);
    rateSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::Rate));
    //==
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::topLeft);
    rateLabel.attachToComponent(&rateSlider, false);

    //Depth Slider
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    depthSlider.setTextValueSuffix(" %");
    depthSlider.setRange(0.1f, 100.0f, 0.1f);
    addAndMakeVisible(&depthSlider);
    depthSlider.addListener(this);
    depthSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::Depth));
    //==
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::topLeft);
    depthLabel.attachToComponent(&depthSlider, false);

    //Wet Slider
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetSlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&wetSlider);
    wetSlider.addListener(this);
    wetSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::WetMix));
    //==
    wetLabel.setText("Wet", juce::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::topLeft);
    wetLabel.attachToComponent(&wetSlider, false);

    //Dry Slider
    drySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    drySlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&drySlider);
    drySlider.addListener(this);
    drySlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::DryMix));
    //==
    dryLabel.setText("Dry", juce::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::topLeft);
    dryLabel.attachToComponent(&drySlider, false);


}

ChorusPluginAudioProcessorEditor::~ChorusPluginAudioProcessorEditor()
{
}

//==============================================================================
void ChorusPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
  
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(25.0f);
    g.drawFittedText("Chorus Plug-In", 5, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void ChorusPluginAudioProcessorEditor::resized()
{
    rateSlider.setBounds(10, 80, getWidth() - 5, 30);
    depthSlider.setBounds(10, 140, getWidth() - 5, 30);
    wetSlider.setBounds(10, 200, getWidth() - 5, 30);
    drySlider.setBounds(10, 260, getWidth() - 5, 30);
}

void ChorusPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &rateSlider)
        audioProcessor.chorus.setParameter(Chorus::Parameters::Rate, slider->getValue());
    else if (slider == &depthSlider)
        audioProcessor.chorus.setParameter(Chorus::Parameters::Depth, slider->getValue());
    else if (slider == &wetSlider)
        audioProcessor.chorus.setParameter(Chorus::Parameters::WetMix, slider->getValue());
    else if (slider == &drySlider)
        audioProcessor.chorus.setParameter(Chorus::Parameters::DryMix, slider->getValue());
}

