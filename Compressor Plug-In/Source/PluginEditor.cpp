/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorPluginAudioProcessorEditor::CompressorPluginAudioProcessorEditor (CompressorPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (370, 470);

    thresholdSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider.setRange(-80.0, 0.0, 0.01);
    thresholdSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&thresholdSlider);
    thresholdSlider.addListener(this);
    thresholdSlider.setValue(audioProcessor.compL.getParameter(Compressor::Parameters::Threshold));
    thresholdSlider.setLookAndFeel(&graphics);


    ratioSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    ratioSlider.setRange(1.0, 100.0, 0.01);
    addAndMakeVisible(&ratioSlider);
    ratioSlider.addListener(this);
    ratioSlider.setValue(audioProcessor.compL.getParameter(Compressor::Parameters::Ratio));
    ratioSlider.setLookAndFeel(&graphics);


    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    attackSlider.setRange(1.0, 100.0, 0.01);
    attackSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&attackSlider);
    attackSlider.addListener(this);
    attackSlider.setValue(audioProcessor.compL.getParameter(Compressor::Parameters::Attack));
    attackSlider.setLookAndFeel(&graphics);

    releaseSilder.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSilder.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    releaseSilder.setRange(10.0, 1000.0, 0.01);
    releaseSilder.setTextValueSuffix(" ms");
    addAndMakeVisible(&releaseSilder);
    releaseSilder.addListener(this);
    releaseSilder.setValue(audioProcessor.compL.getParameter(Compressor::Parameters::Release));
    releaseSilder.setLookAndFeel(&graphics);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setRange(-20.0, 20.0, 0.01);
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainSlider.setValue(audioProcessor.compL.getParameter(Compressor::Parameters::MakeupGain));
    gainSlider.setLookAndFeel(&graphics);

    addAndMakeVisible(&hardKnee);
    hardKnee.setBounds(267, 140, 50, 30);
    hardKnee.setAlpha(0);
    hardKnee.onClick = [this] {
        audioProcessor.compL.setKneeType(Compressor::KneeTypes::Hard);
        audioProcessor.compR.setKneeType(Compressor::KneeTypes::Hard);
        repaint();
    };

    addAndMakeVisible(&softKnee);
    softKnee.setBounds(267, 106, 50, 30);
    softKnee.setAlpha(0);
    softKnee.onClick = [this] {
        audioProcessor.compL.setKneeType(Compressor::KneeTypes::Soft);
        audioProcessor.compR.setKneeType(Compressor::KneeTypes::Soft);
        repaint();
    };

  


}

CompressorPluginAudioProcessorEditor::~CompressorPluginAudioProcessorEditor()
{
}

//==============================================================================
void CompressorPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getCompressorBackground(audioProcessor.compL.getKneeType()), 0, 0);
}

void CompressorPluginAudioProcessorEditor::resized()
{
    thresholdSlider.setBounds(20, 100, 100, 100);
    ratioSlider.setBounds(132, 100, 100, 100);

    attackSlider.setBounds(20, 266, 100, 100);
    releaseSilder.setBounds(132, 266, 100, 100);
    gainSlider.setBounds(243, 266, 100, 100);
}

void CompressorPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &thresholdSlider)
    {
        audioProcessor.compL.setParameter(Compressor::Parameters::Threshold, slider->getValue());
        audioProcessor.compR.setParameter(Compressor::Parameters::Threshold, slider->getValue());
    }
    else if (slider == &ratioSlider)
    {
        audioProcessor.compL.setParameter(Compressor::Parameters::Ratio, slider->getValue());
        audioProcessor.compR.setParameter(Compressor::Parameters::Ratio, slider->getValue());
    }
    else if (slider == &attackSlider)
    {
        audioProcessor.compL.setParameter(Compressor::Parameters::Attack, slider->getValue());
        audioProcessor.compR.setParameter(Compressor::Parameters::Attack, slider->getValue());
    }
    else if (slider == &releaseSilder)
    {
        audioProcessor.compL.setParameter(Compressor::Parameters::Release, slider->getValue());
        audioProcessor.compR.setParameter(Compressor::Parameters::Release, slider->getValue());
    }
    else if (slider == &gainSlider)
    {
        audioProcessor.compL.setParameter(Compressor::Parameters::MakeupGain, slider->getValue());
        audioProcessor.compR.setParameter(Compressor::Parameters::MakeupGain, slider->getValue());
    }
}

void CompressorPluginAudioProcessorEditor::initializeSlider(juce::Slider& s)
{

}