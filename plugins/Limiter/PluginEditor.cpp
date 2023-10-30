#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LimiterPluginAudioProcessorEditor::LimiterPluginAudioProcessorEditor (LimiterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{
    setSize(370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    setMeters();

    thresholdSlider.reset(new juce::Slider("ThresholdSlider"));
    thresholdSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(thresholdSlider.get());
    thresholdSlider->setLookAndFeel(&graphics);

    thresholdSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "THRESHOLD_ID", *thresholdSlider);

    attackSlider.reset(new juce::Slider("AttackSlider"));
    attackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    attackSlider->setTextValueSuffix(" ms");
    addAndMakeVisible(attackSlider.get());
    attackSlider->setLookAndFeel(&graphics);

    attackSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "ATTACK_ID", *attackSlider);

    releaseSilder.reset(new juce::Slider("ReleaseSlider"));
    releaseSilder->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSilder->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    releaseSilder->setTextValueSuffix(" ms");
    addAndMakeVisible(releaseSilder.get());
    releaseSilder->setLookAndFeel(&graphics);

    releaseSilderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RELEASE_ID", *releaseSilder);

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider.get());
    gainSlider->setLookAndFeel(&graphics);

    gainSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "GAIN_ID", *gainSlider);

    kneeSlider.reset(new juce::Slider("KneeSlider"));
    kneeSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "KNEE_ID", *kneeSlider);

    softKnee.reset(new juce::ImageButton("SoftKneeButtton"));
    addAndMakeVisible(softKnee.get());
    softKnee->setBounds(4, inputMeter.getY() - 83, 25, 25);
    softKnee->setTooltip("Soft");
    softKnee->onClick = [this] {
        kneeSlider->setValue(Limiter<float>::KneeTypes::Soft, juce::NotificationType::sendNotificationSync);
        audioProcessor.setKneeType(Limiter<float>::KneeTypes::Soft);
        updateButtons();
    }; 

    hardKnee.reset(new juce::ImageButton("HardKneeButtton"));
    addAndMakeVisible(hardKnee.get());
    hardKnee->setBounds(softKnee->getX(), softKnee->getY() + 27, 25, 25);
    hardKnee->setTooltip("Hard");
    hardKnee->onClick = [this] {
        kneeSlider->setValue(Limiter<float>::KneeTypes::Hard, juce::NotificationType::sendNotificationSync);
        audioProcessor.setKneeType(Limiter<float>::KneeTypes::Hard);
        updateButtons();
    };

    updateButtons();

    int knobSize = 133;
    thresholdSlider->setBounds(40, 107, knobSize, knobSize);
    gainSlider->setBounds(198, 63, knobSize, knobSize);
    attackSlider->setBounds(40, 283, knobSize, knobSize);
    releaseSilder->setBounds(198, 234, knobSize, knobSize);
}

LimiterPluginAudioProcessorEditor::~LimiterPluginAudioProcessorEditor()
{
    thresholdSliderAtt = nullptr;
    attackSliderAtt = nullptr;
    releaseSilderAtt = nullptr;
    gainSliderAtt = nullptr;
    kneeSliderAtt = nullptr;
}

//==============================================================================
void LimiterPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void LimiterPluginAudioProcessorEditor::resized()
{

}

void LimiterPluginAudioProcessorEditor::setMeters()
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

void LimiterPluginAudioProcessorEditor::updateButtons()
{
    assetManager.setCompressorButton(softKnee, audioProcessor.getKneeType(), Limiter<float>::KneeTypes::Soft);
    assetManager.setCompressorButton(hardKnee, audioProcessor.getKneeType(), Limiter<float>::KneeTypes::Hard);
}