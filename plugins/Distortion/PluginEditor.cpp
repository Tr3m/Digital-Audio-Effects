#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{    
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));
    graphics.setColour(juce::PopupMenu::backgroundColourId, juce::Colours::grey.withAlpha(0.6f));
    graphics.setColour(juce::TextEditor::textColourId, juce::Colours::aqua);
    graphics.setColour(juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.withAlpha(0.7f));

    setMeters();

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider.get());
    gainSlider->setLookAndFeel(&graphics);

    gainSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "GAIN_ID", *gainSlider);
    
    levelSlider.reset(new juce::Slider("LevelSlider"));
    levelSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    levelSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(levelSlider.get());
    levelSlider->setLookAndFeel(&graphics);

    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);

    filterSlider.reset(new juce::Slider("FilterSlider"));
    filterSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    filterSlider->setTextValueSuffix(" Hz");
    addAndMakeVisible(filterSlider.get());
    filterSlider->setLookAndFeel(&graphics);

    filterSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FILTER_FREQ_ID", *filterSlider);

    int knobSize = 133;
    gainSlider->setBounds(40, 107, knobSize, knobSize);
    filterSlider->setBounds(198, 63, knobSize, knobSize);
    levelSlider->setBounds(40, 283, knobSize, knobSize);  

    algorithmSelect.reset(new juce::ComboBox("AlgorithmSelector"));
    algorithmSelect->clear(juce::dontSendNotification);
    addAndMakeVisible (algorithmSelect.get());
    algorithmSelect->setEditableText (false);
    algorithmSelect->setJustificationType (juce::Justification::centredLeft);
    algorithmSelect->addListener(this);

    algorithmSelect->setLookAndFeel(&graphics);
    algorithmSelect->setColour(juce::ComboBox::backgroundColourId, juce::Colours::transparentBlack.withAlpha(0.0f));
    algorithmSelect->setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack.withAlpha(0.0f));
    algorithmSelect->setAlpha(0.9f);
    algorithmSelect->setBounds(205, 277, 120, 30);

    for(int sat = 1; sat <= NUM_MODULES; ++sat)
        algorithmSelect->addItem(algorithmLabels[sat - 1], sat);

    comboBoxAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.apvts, "ALGORITHM_ID", *algorithmSelect));
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
    gainSliderAtt = nullptr;
    levelSliderAtt = nullptr;
    filterSliderAtt = nullptr;
    comboBoxAttachment = nullptr;
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void DistortionPluginAudioProcessorEditor::resized()
{
    
}

void DistortionPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    audioProcessor.setAlgorithm(comboBoxThatHasChanged->getSelectedItemIndex());
}

void DistortionPluginAudioProcessorEditor::setMeters()
{
    addAndMakeVisible(&inputMeter);
    addAndMakeVisible(&outputMeter);

    inputMeter.setMeterColour(juce::Colours::ivory);
    outputMeter.setMeterColour(juce::Colours::ivory);
    inputMeter.setBackgroundColour(juce::Colours::transparentBlack);
    outputMeter.setBackgroundColour(juce::Colours::transparentBlack);

    inputMeter.setBounds(13, getHeight() / 2 + 13, 6, 195);
    outputMeter.setBounds(getWidth() - 17, 24, 6, 195);
}