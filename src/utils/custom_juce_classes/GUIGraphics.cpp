#include "GUIGraphics.h"

GUIGraphics::GUIGraphics(int effectType, bool isSmallSlider)
{
    reloadImage(effectType);
    this->isSmallSlider = isSmallSlider;
}

void GUIGraphics::reloadImage(int _effectType)
{
    switch (_effectType)
    {
    case EffectTypes::Distortion:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::distortion_Knob_png, BinaryData::distortion_Knob_pngSize);
        effectType = EffectTypes::Distortion;
        break;
    case EffectTypes::Delay:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::delay_Knob_png, BinaryData::delay_Knob_pngSize);
        effectType = EffectTypes::Delay;
        break;
    case EffectTypes::Reverb:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::reverb_Knob_png, BinaryData::reverb_Knob_pngSize);
        effectType = EffectTypes::Reverb;
        break;
    case EffectTypes::Flanger:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::flanger_Knob_png, BinaryData::flanger_Knob_pngSize);
        effectType = EffectTypes::Flanger;
        break;
    case EffectTypes::Chorus:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::chorus_Knob_png, BinaryData::chorus_Knob_pngSize);
        effectType = EffectTypes::Chorus;
        break;
    case EffectTypes::Vibrado:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_Knob_png, BinaryData::vibrado_Knob_pngSize);
        effectType = EffectTypes::Vibrado;
        break;
    case EffectTypes::Filter:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::filter_Knob_png, BinaryData::filter_Knob_pngSize);
        effectType = EffectTypes::Filter;
        break;
    case EffectTypes::Compressor:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::compressor_Knob_png, BinaryData::compressor_Knob_pngSize);
        effectType = EffectTypes::Compressor;
        break;
    case EffectTypes::Limiter:
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::limiter_Knob_png, BinaryData::limiter_Knob_pngSize);
        effectType = EffectTypes::Limiter;
        break;
    }
}

void GUIGraphics::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    if (knobImage.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = knobImage.getHeight() / knobImage.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = juce::jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(knobImage,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId * knobImage.getWidth(),
            knobImage.getWidth(),
            knobImage.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        juce::Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(juce::Colours::white);

        g.drawFittedText(juce::String("No Image"), text_bounds.getSmallestIntegerContainer(),
            juce::Justification::horizontallyCentred | juce::Justification::centred, 1);
    }
}

juce::Image GUIGraphics::getBackground()
{
    switch (effectType)
    {
    case EffectTypes::Distortion:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::distortion_background_png, BinaryData::distortion_background_pngSize);
        break;
    case EffectTypes::Delay:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::delay_background_png, BinaryData::delay_background_pngSize);
        break;
    case EffectTypes::Reverb:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::reverb_background_png, BinaryData::reverb_background_pngSize);
        break;
    case EffectTypes::Flanger:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::flanger_background_png, BinaryData::flanger_background_pngSize);
        break;
    case EffectTypes::Chorus:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::chorus_background_png, BinaryData::chorus_background_pngSize);
        break;
    case EffectTypes::Vibrado:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_background_png, BinaryData::vibrado_background_pngSize);
        break;
    case EffectTypes::Compressor:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::compressor_background_png, BinaryData::compressor_background_pngSize);
        break;
    case EffectTypes::Limiter:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::limiter_background_png, BinaryData::limiter_background_pngSize);
        break;
    case EffectTypes::Filter:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::filter_background_png, BinaryData::filter_background_pngSize);
        break;
  
    }

    return backgroundImage;
}