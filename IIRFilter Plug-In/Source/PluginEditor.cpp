/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessorEditor::IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    cutoff.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    cutoff.setRange(20.0, 20000, 0);
    cutoff.setValue(audioProcessor.leftFilter.getCutoff());
    addAndMakeVisible(&cutoff);
    cutoff.addListener(this);

    startTimer(50);
}

IirfilterPluginAudioProcessorEditor::~IirfilterPluginAudioProcessorEditor()
{
}

//==============================================================================
void IirfilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("IIR High-Pass Test", getLocalBounds(), juce::Justification::centred, 1);
}

void IirfilterPluginAudioProcessorEditor::resized()
{
    cutoff.setBounds(getLocalBounds());
}

void IirfilterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &cutoff)
    {
        audioProcessor.leftFilter.setCutoff(slider->getValue());
        audioProcessor.rightFilter.setCutoff(slider->getValue());
        //DBG(audioProcessor.hp.getCutoff());
        
    }
}

void IirfilterPluginAudioProcessorEditor::timerCallback()
{
    cutoff.setValue(audioProcessor.leftFilter.getCutoff());
   
}