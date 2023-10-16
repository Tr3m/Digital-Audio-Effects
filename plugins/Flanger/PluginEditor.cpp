/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerPluginAudioProcessorEditor::FlangerPluginAudioProcessorEditor (FlangerPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (370, 470);

    //Rate Slider
    rateSlider.setSliderStyle(juce::Slider::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(&rateSlider);
    rateSlider.addListener(this);
    rateSlider.setValue(audioProcessor.flanger.getParameter(Flanger::Parameters::Rate));
    rateSlider.setLookAndFeel(&graphics);    

    //Depth Slider
    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider.setTextValueSuffix(" %");
    depthSlider.setRange(0.1f, 100.0f, 0.1f);
    addAndMakeVisible(&depthSlider);
    depthSlider.addListener(this);
    depthSlider.setValue(audioProcessor.flanger.getParameter(Flanger::Parameters::Depth));
    depthSlider.setLookAndFeel(&graphics);

    //Wet Slider
    wetSlider.setSliderStyle(juce::Slider::Rotary);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    wetSlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&wetSlider);
    wetSlider.addListener(this);
    wetSlider.setValue(audioProcessor.flanger.getParameter(Flanger::Parameters::WetMix));
    wetSlider.setLookAndFeel(&graphics);

    //Dry Slider
    drySlider.setSliderStyle(juce::Slider::Rotary);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    drySlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&drySlider);
    drySlider.addListener(this);
    drySlider.setValue(audioProcessor.flanger.getParameter(Flanger::Parameters::DryMix));
    drySlider.setLookAndFeel(&graphics);

}

FlangerPluginAudioProcessorEditor::~FlangerPluginAudioProcessorEditor()
{
}

//==============================================================================
void FlangerPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void FlangerPluginAudioProcessorEditor::resized()
{
    rateSlider.setBounds(44, 91, 124, 124);
    depthSlider.setBounds(198, 91, 124, 124);
    wetSlider.setBounds(44, 252, 124, 124);
    drySlider.setBounds(198, 252, 124, 124);
}

void FlangerPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &rateSlider)
        audioProcessor.flanger.setParameter(Flanger::Parameters::Rate, slider->getValue());
    else if (slider == &depthSlider)
        audioProcessor.flanger.setParameter(Flanger::Parameters::Depth, slider->getValue());
    else if (slider == &wetSlider)
        audioProcessor.flanger.setParameter(Flanger::Parameters::WetMix, slider->getValue());
    else if (slider == &drySlider)
        audioProcessor.flanger.setParameter(Flanger::Parameters::DryMix, slider->getValue());
}
