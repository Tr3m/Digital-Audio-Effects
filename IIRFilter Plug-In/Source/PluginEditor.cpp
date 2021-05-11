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

    freqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    freqSlider.setRange(20.0, 20000.0, 10);
    freqSlider.setTextValueSuffix(" Hz");
    freqSlider.setValue(audioProcessor.leftFilter.getCutoff());
    addAndMakeVisible(&freqSlider);
    freqSlider.addListener(this);
    freqLabel.setText("Frequency", juce::dontSendNotification);
    freqLabel.setJustificationType(juce::Justification::topLeft);
    freqLabel.attachToComponent(&freqSlider, false);


    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setRange(-12.0, 12.0, 1);
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::topLeft);
    gainLabel.attachToComponent(&gainSlider, false);

    qSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    qSlider.setRange(0.2, 10.0, .001);
    //addAndMakeVisible(&qSlider);
    qSlider.addListener(this);
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::topLeft);
    qLabel.attachToComponent(&qSlider, false);

    filterSelect.setJustificationType(juce::Justification::centred);
    //filterSelect.setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkgrey);
    //filterSelect.setColour(juce::ComboBox::outlineColourId, juce::Colours::grey.withAlpha(1.0f));
    filterSelect.setAlpha(0.9f);
    filterSelect.addItem("Low-Pass Filter", 1);
    filterSelect.addItem("High-Pass Filter", 2);
    filterSelect.addItem("Parametric EQ", 3);
    addAndMakeVisible(&filterSelect);
    filterSelect.addListener(this);
    filterSelect.setSelectedId(audioProcessor.leftFilter.getFilterType() + 1);

    startTimer(50);
}

IirfilterPluginAudioProcessorEditor::~IirfilterPluginAudioProcessorEditor()
{
}

//==============================================================================
void IirfilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (25.0f);
    g.drawFittedText ("IIR Filters", 5, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void IirfilterPluginAudioProcessorEditor::resized()
{
    freqSlider.setBounds(10, 120, getWidth(), 30);
    gainSlider.setBounds(10, 180, getWidth(), 30);
    qSlider.setBounds(10, 240, getWidth(), 30);
    filterSelect.setBounds(145, 60, getWidth() / 3, 30);
}

void IirfilterPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &freqSlider)
    {
        audioProcessor.leftFilter.setCutoff(slider->getValue());
        audioProcessor.rightFilter.setCutoff(slider->getValue());        
    }
    else if (slider == &gainSlider)
    {
        audioProcessor.leftFilter.setGain(slider->getValue());
        audioProcessor.rightFilter.setGain(slider->getValue());
    }
    else if (slider == &qSlider)
    {
        audioProcessor.leftFilter.setQ(slider->getValue());
        audioProcessor.rightFilter.setQ(slider->getValue());
    }
}

void IirfilterPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    audioProcessor.leftFilter.setFilterType(comboBoxThatHasChanged->getSelectedId() - 1);
    audioProcessor.rightFilter.setFilterType(comboBoxThatHasChanged->getSelectedId() - 1);
}

void IirfilterPluginAudioProcessorEditor::timerCallback()
{
   freqSlider.setValue(audioProcessor.leftFilter.getCutoff());
   gainSlider.setValue(audioProcessor.leftFilter.getGain());
   qSlider.setValue(audioProcessor.leftFilter.getQ());

   if (filterSelect.getSelectedId() == 3)
   {
       gainSlider.setVisible(true);
       //qSlider.setVisible(true);
   }
   else
   {
       gainSlider.setVisible(false);
       //qSlider.setVisible(false);
   }
}