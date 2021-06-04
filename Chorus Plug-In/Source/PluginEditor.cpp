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
    
    setSize(370, 470);

    //Rate Slider
    rateSlider.setSliderStyle(juce::Slider::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(&rateSlider);
    rateSlider.addListener(this);
    rateSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::Rate));
    rateSlider.setLookAndFeel(&graphics);
   

    //Depth Slider
    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    depthSlider.setTextValueSuffix(" %");
    depthSlider.setRange(0.1f, 100.0f, 0.1f);
    addAndMakeVisible(&depthSlider);
    depthSlider.addListener(this);
    depthSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::Depth));
    depthSlider.setLookAndFeel(&graphics);
    

    //Wet Slider
    wetSlider.setSliderStyle(juce::Slider::Rotary);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    wetSlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&wetSlider);
    wetSlider.addListener(this);
    wetSlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::WetMix));
    wetSlider.setLookAndFeel(&graphics);
 

    //Dry Slider
    drySlider.setSliderStyle(juce::Slider::Rotary);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    drySlider.setRange(0.0f, 1.0f, 0.1f);
    addAndMakeVisible(&drySlider);
    drySlider.addListener(this);
    drySlider.setValue(audioProcessor.chorus.getParameter(Chorus::Parameters::DryMix));
    drySlider.setLookAndFeel(&graphics);
    

}

ChorusPluginAudioProcessorEditor::~ChorusPluginAudioProcessorEditor()
{
}

//==============================================================================
void ChorusPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
  
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void ChorusPluginAudioProcessorEditor::resized()
{
    rateSlider.setBounds(44, 91, 124, 124);
    depthSlider.setBounds(198, 91, 124, 124);
    wetSlider.setBounds(44, 252, 124, 124);
    drySlider.setBounds(198, 252, 124, 124);
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

