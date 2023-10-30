#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorPluginAudioProcessorEditor::CompressorPluginAudioProcessorEditor (CompressorPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    inputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextInput();}),
    outputMeter(LevelMeter::Orientations::Vertical, [&]() {return audioProcessor.meterSource.getNextOutput();})
{
    setSize (370, 470);

    graphics.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphics.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));
    graphicsSmalll.setColour (Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    graphicsSmalll.setColour (Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    graphicsSmalll.setColour (Slider::textBoxTextColourId, juce::Colours::ivory.withAlpha(0.85f));

    setMeters();

    thresholdSlider.reset(new juce::Slider("ThresholdSlider"));
    thresholdSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(thresholdSlider.get());
    thresholdSlider->setLookAndFeel(&graphics);

    thresholdSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "THRESHOLD_ID", *thresholdSlider);

    ratioSlider.reset(new juce::Slider("RatioSlider"));
    ratioSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(ratioSlider.get());
    ratioSlider->setLookAndFeel(&graphics);

    ratioSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RATIO_ID", *ratioSlider);

    attackSlider.reset(new juce::Slider("AttackSlider"));
    attackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 17);
    attackSlider->setTextValueSuffix(" ms");
    addAndMakeVisible(attackSlider.get());
    attackSlider->setLookAndFeel(&graphicsSmalll);

    attackSliderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "ATTACK_ID", *attackSlider);

    releaseSilder.reset(new juce::Slider("ReleaseSlider"));
    releaseSilder->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSilder->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 17);
    releaseSilder->setTextValueSuffix(" ms");
    addAndMakeVisible(releaseSilder.get());
    releaseSilder->setLookAndFeel(&graphicsSmalll);

    releaseSilderAtt = std::make_unique<juce::AudioProcessorValueTreeState::
        SliderAttachment>(audioProcessor.apvts, "RELEASE_ID", *releaseSilder);

    gainSlider.reset(new juce::Slider("GainSlider"));
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 17);
    gainSlider->setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider.get());
    gainSlider->setLookAndFeel(&graphicsSmalll);

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
        kneeSlider->setValue(Compressor<float>::KneeTypes::Soft, juce::NotificationType::sendNotificationSync);
        audioProcessor.setKneeType(Compressor<float>::KneeTypes::Soft);
        updateButtons();
    }; 

    hardKnee.reset(new juce::ImageButton("HardKneeButtton"));
    addAndMakeVisible(hardKnee.get());
    hardKnee->setBounds(softKnee->getX(), softKnee->getY() + 27, 25, 25);
    hardKnee->setTooltip("Hard");
    hardKnee->onClick = [this] {
        kneeSlider->setValue(Compressor<float>::KneeTypes::Hard, juce::NotificationType::sendNotificationSync);
        audioProcessor.setKneeType(Compressor<float>::KneeTypes::Hard);
        updateButtons();
    };

    updateButtons();

    int knobSize = 133;
    int knobSizeSmall = 111;

    thresholdSlider->setBounds(40, 107, knobSize, knobSize);
    ratioSlider->setBounds(198, 63, knobSize, knobSize);
    
    attackSlider->setBounds(19, 328, knobSizeSmall, knobSizeSmall);
    releaseSilder->setBounds(132, 291, knobSizeSmall, knobSizeSmall);
    gainSlider->setBounds(247, 250, knobSizeSmall, knobSizeSmall);

}

CompressorPluginAudioProcessorEditor::~CompressorPluginAudioProcessorEditor()
{
    thresholdSliderAtt = nullptr;
    ratioSliderAtt = nullptr;
    attackSliderAtt = nullptr;
    releaseSilderAtt = nullptr;
    gainSliderAtt = nullptr;
    kneeSliderAtt = nullptr;
}

//==============================================================================
void CompressorPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void CompressorPluginAudioProcessorEditor::resized()
{

}

void CompressorPluginAudioProcessorEditor::setMeters()
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

void CompressorPluginAudioProcessorEditor::updateButtons()
{
    assetManager.setCompressorButton(softKnee, audioProcessor.getKneeType(), Compressor<float>::KneeTypes::Soft);
    assetManager.setCompressorButton(hardKnee, audioProcessor.getKneeType(), Compressor<float>::KneeTypes::Hard);
}