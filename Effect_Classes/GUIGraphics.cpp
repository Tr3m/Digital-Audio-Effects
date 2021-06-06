#include "GUIGraphics.h"

GUIGraphics::GUIGraphics(int effectType)
{
    reloadImage(effectType);
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
  
    }

    return backgroundImage;
}

juce::Image GUIGraphics::getFilterBackground(int filterState)
{
    switch (filterState)
    {
    case FilterStates::HighPass:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::filter_highpass_png, BinaryData::filter_highpass_pngSize);
        break;
    case FilterStates::LowPass:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::filter_lowpass_png, BinaryData::filter_lowpass_pngSize);
        break;
    case FilterStates::Parametric:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::filter_parametric_png, BinaryData::filter_parametric_pngSize);
    }

    return backgroundImage;
}

juce::Image GUIGraphics::getVibradoBackground(int vibradoState)
{
    switch (vibradoState)
    {
    case VibradoStates::Sine:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_sine_png, BinaryData::vibrado_sine_pngSize);
        break;
    case VibradoStates::Triangle:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_triangle_png, BinaryData::vibrado_triangle_pngSize);
        break;
    case VibradoStates::Saw:
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_saw_png, BinaryData::vibrado_saw_pngSize);
        break;
    }
    
    return backgroundImage;
}

juce::Image GUIGraphics::getCompressorBackground(int compressorState)
{
    if (compressorState == CompressorStates::SoftKnee)
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::compressor_soft_png, BinaryData::compressor_soft_pngSize);
    else if (compressorState == CompressorStates::HardKnee)
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::compressor_hard_png, BinaryData::compressor_hard_pngSize);

    return backgroundImage;
}

juce::Image GUIGraphics::getLimiterBackground(int limiterState)
{
    if (limiterState == LimiterStates::SoftKneeLimiter)
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::limiter_soft_png, BinaryData::compressor_soft_pngSize);
    else if (limiterState == LimiterStates::HardKneeLimiter)
        backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::limiter_hard_png, BinaryData::compressor_hard_pngSize);

    return backgroundImage;
}