/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibradoPluginAudioProcessorEditor::VibradoPluginAudioProcessorEditor (VibradoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(400, 340);

    //Rate Slider
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    rateSlider.setTextValueSuffix(" Hz");
    rateSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(&rateSlider);
    rateSlider.addListener(this);
    rateSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Rate));
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
    depthSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Depth));
    //==
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::topLeft);
    depthLabel.attachToComponent(&depthSlider, false);

    //Level Slider
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    levelSlider.setRange(-12.0f, 12.0f, 0.1f);
    levelSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&levelSlider);
    levelSlider.addListener(this);
    levelSlider.setValue(audioProcessor.vibrado.getParameter(Vibrado::Parameters::Level));
    //==
    levelLabel.setText("Level", juce::dontSendNotification);
    levelLabel.setJustificationType(juce::Justification::topLeft);
    levelLabel.attachToComponent(&levelSlider, false);

    lfoType.setJustificationType(juce::Justification::centred);
    //lfoType.setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkgrey);
    //lfoType.setColour(juce::ComboBox::outlineColourId, juce::Colours::grey.withAlpha(1.0f));
    lfoType.setAlpha(0.9f);
    lfoType.addItem("Triangle", 1);
    lfoType.addItem("Sine", 2);
    lfoType.addItem("Saw", 3);
    addAndMakeVisible(&lfoType);
    lfoType.addListener(this);
    lfoType.setSelectedId(audioProcessor.vibrado.getLFOType()+1);
    //==
    lfoLabel.setText("LFO Type   ", juce::dontSendNotification);
    lfoLabel.setJustificationType(juce::Justification::centredLeft);
    lfoLabel.attachToComponent(&lfoType, true);
}

VibradoPluginAudioProcessorEditor::~VibradoPluginAudioProcessorEditor()
{
}

//==============================================================================
void VibradoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(25.0f);
    g.drawFittedText("Vibrado Plug-In", 5, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void VibradoPluginAudioProcessorEditor::resized()
{
    lfoType.setBounds((getWidth() / 2) - (getWidth() - 180) / 2, 90, getWidth() - 100,  25);
    rateSlider.setBounds(10, 160, getWidth() - 5, 30);
    depthSlider.setBounds(10, 220, getWidth() - 5, 30);
    levelSlider.setBounds(10, 280, getWidth() - 5, 30);
}

void VibradoPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &rateSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Rate, slider->getValue());
    else if (slider == &depthSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Depth, slider->getValue());
    else if (slider == &levelSlider)
        audioProcessor.vibrado.setParameter(Vibrado::Parameters::Level, slider->getValue());
}

void VibradoPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    audioProcessor.vibrado.setLFOType(comboBoxThatHasChanged->getSelectedId() - 1);
}