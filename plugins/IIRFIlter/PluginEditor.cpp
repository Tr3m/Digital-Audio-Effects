#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterPluginAudioProcessorEditor::IirfilterPluginAudioProcessorEditor (IirfilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    setMeters();

    freqSlider.reset(new juce::Slider("FrequencySlider"));
    freqSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    freqSlider->setTextValueSuffix(" Hz");
    addAndMakeVisible(freqSlider.get());
    freqSlider->setLookAndFeel(&graphics);

    freqSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FREQUENCY_ID", *freqSlider);

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
    levelSlider->setLookAndFeel(&graphics);
    addAndMakeVisible(levelSlider.get()); 
    
    levelSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "LEVEL_ID", *levelSlider);

    filterTypeSlider.reset(new juce::Slider("filterTypeSlider"));
    filterTypeSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "FILTER_TYPE_ID", *filterTypeSlider);

    int knobSize = 133;
    freqSlider->setBounds(40, 107, knobSize, knobSize);
    gainSlider->setBounds(198, 63, knobSize, knobSize);
    levelSlider->setBounds(198, 234, knobSize, knobSize);        

    hpButton.reset(new juce::ImageButton("HipassButton"));
    addAndMakeVisible(hpButton.get());
    hpButton->setBounds(71, 283, 70, 40);
    hpButton->setTooltip("High-Pass");
    hpButton->onClick = [this] {
        filterTypeSlider->setValue(FilterTypes::HPF, juce::NotificationType::sendNotificationSync);
        audioProcessor.setFilterType(FilterTypes::HPF);
        setGainKnob();
        updateButtons();
    };

    lpButton.reset(new juce::ImageButton("LowassButton"));
    addAndMakeVisible(lpButton.get());
    lpButton->setBounds(71, 323, 70, 40);
    lpButton->setTooltip("Low-Pass");
    lpButton->onClick = [this] {
        filterTypeSlider->setValue(FilterTypes::LPF, juce::NotificationType::sendNotificationSync);
        audioProcessor.setFilterType(FilterTypes::LPF);
        setGainKnob();
        updateButtons();
    };

    parButton.reset(new juce::ImageButton("PeakButton"));
    addAndMakeVisible(parButton.get());
    parButton->setBounds(71, 363, 70, 40);
    parButton->setTooltip("Peaking");
    parButton->onClick = [this] {
        filterTypeSlider->setValue(FilterTypes::Parametric, juce::NotificationType::sendNotificationSync);
        audioProcessor.setFilterType(FilterTypes::Parametric);
        setGainKnob();
        updateButtons();
    };

    setGainKnob();
    updateButtons();
}

IirfilterPluginAudioProcessorEditor::~IirfilterPluginAudioProcessorEditor()
{
    freqSliderAtt = nullptr;
    gainSliderAtt = nullptr;
    levelSliderAtt = nullptr;
    filterTypeSliderAtt = nullptr;
}

//==============================================================================
void IirfilterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void IirfilterPluginAudioProcessorEditor::resized()
{
    
}

void IirfilterPluginAudioProcessorEditor::setMeters()
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

void IirfilterPluginAudioProcessorEditor::updateButtons()
{
    assetManager.setFilterButton(hpButton, audioProcessor.getFilterType(), FilterTypes::HPF);
    assetManager.setFilterButton(lpButton, audioProcessor.getFilterType(), FilterTypes::LPF);
    assetManager.setFilterButton(parButton, audioProcessor.getFilterType(), FilterTypes::Parametric);
}

void IirfilterPluginAudioProcessorEditor::setGainKnob()
{
    if(audioProcessor.getFilterType() == FilterTypes::Parametric)
    {
        gainSlider->setEnabled(true);
        gainSlider->setAlpha(1.0);
    }
    else
    {
        gainSlider->setEnabled(false);
        gainSlider->setAlpha(0.5);
    }
}