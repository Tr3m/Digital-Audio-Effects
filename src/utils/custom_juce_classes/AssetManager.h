#pragma once
#include "BinaryData.h"

class AssetManager
{
public:

    AssetManager()
    {
        //TODO: Refactor this using getNamedResource()
        toggleButtonAssets[Buttons::Vibrado_Triagle][0] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_00_png, BinaryData::vibrado_00_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Triagle][1] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_01_png, BinaryData::vibrado_01_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Triagle][2] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_02_png, BinaryData::vibrado_02_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Triagle][3] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_03_png, BinaryData::vibrado_03_pngSize);

        toggleButtonAssets[Buttons::Vibrado_Sine][0] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_10_png, BinaryData::vibrado_10_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Sine][1] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_11_png, BinaryData::vibrado_11_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Sine][2] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_12_png, BinaryData::vibrado_12_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Sine][3] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_13_png, BinaryData::vibrado_13_pngSize);

        toggleButtonAssets[Buttons::Vibrado_Saw][0] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_20_png, BinaryData::vibrado_20_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Saw][1] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_21_png, BinaryData::vibrado_21_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Saw][2] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_22_png, BinaryData::vibrado_22_pngSize);
        toggleButtonAssets[Buttons::Vibrado_Saw][3] = juce::ImageFileFormat::loadFrom(BinaryData::vibrado_23_png, BinaryData::vibrado_23_pngSize);

        toggleButtonAssets[Buttons::Compressor_Soft_Knee][0] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_00_png, BinaryData::compressor_00_pngSize);
        toggleButtonAssets[Buttons::Compressor_Soft_Knee][1] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_01_png, BinaryData::compressor_01_pngSize);
        toggleButtonAssets[Buttons::Compressor_Soft_Knee][2] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_02_png, BinaryData::compressor_02_pngSize);
        toggleButtonAssets[Buttons::Compressor_Soft_Knee][3] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_03_png, BinaryData::compressor_03_pngSize);

        toggleButtonAssets[Buttons::Compressor_Hard_Knee][0] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_10_png, BinaryData::compressor_10_pngSize);
        toggleButtonAssets[Buttons::Compressor_Hard_Knee][1] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_11_png, BinaryData::compressor_11_pngSize);
        toggleButtonAssets[Buttons::Compressor_Hard_Knee][2] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_12_png, BinaryData::compressor_12_pngSize);
        toggleButtonAssets[Buttons::Compressor_Hard_Knee][3] = juce::ImageFileFormat::loadFrom(BinaryData::compressor_13_png, BinaryData::compressor_13_pngSize);

        toggleButtonAssets[Buttons::Filter_LOWPASS][0] = juce::ImageFileFormat::loadFrom(BinaryData::filter_00_png, BinaryData::filter_00_pngSize);
        toggleButtonAssets[Buttons::Filter_LOWPASS][1] = juce::ImageFileFormat::loadFrom(BinaryData::filter_01_png, BinaryData::filter_01_pngSize);
        toggleButtonAssets[Buttons::Filter_LOWPASS][2] = juce::ImageFileFormat::loadFrom(BinaryData::filter_02_png, BinaryData::filter_02_pngSize);
        toggleButtonAssets[Buttons::Filter_LOWPASS][3] = juce::ImageFileFormat::loadFrom(BinaryData::filter_03_png, BinaryData::filter_03_pngSize);

        toggleButtonAssets[Buttons::Filter_HIGHPASS][0] = juce::ImageFileFormat::loadFrom(BinaryData::filter_10_png, BinaryData::filter_10_pngSize);
        toggleButtonAssets[Buttons::Filter_HIGHPASS][1] = juce::ImageFileFormat::loadFrom(BinaryData::filter_11_png, BinaryData::filter_11_pngSize);
        toggleButtonAssets[Buttons::Filter_HIGHPASS][2] = juce::ImageFileFormat::loadFrom(BinaryData::filter_12_png, BinaryData::filter_12_pngSize);
        toggleButtonAssets[Buttons::Filter_HIGHPASS][3] = juce::ImageFileFormat::loadFrom(BinaryData::filter_13_png, BinaryData::filter_13_pngSize);

        toggleButtonAssets[Buttons::Filter_PEAKING][0] = juce::ImageFileFormat::loadFrom(BinaryData::filter_20_png, BinaryData::filter_20_pngSize);
        toggleButtonAssets[Buttons::Filter_PEAKING][1] = juce::ImageFileFormat::loadFrom(BinaryData::filter_21_png, BinaryData::filter_21_pngSize);
        toggleButtonAssets[Buttons::Filter_PEAKING][2] = juce::ImageFileFormat::loadFrom(BinaryData::filter_22_png, BinaryData::filter_22_pngSize);
        toggleButtonAssets[Buttons::Filter_PEAKING][3] = juce::ImageFileFormat::loadFrom(BinaryData::filter_23_png, BinaryData::filter_23_pngSize);

    };

    ~AssetManager()
    {

    };
    
    void setVibradoButton(std::unique_ptr<juce::ImageButton>& button, int activeButton, int buttonIndex)
    {
        if(int(activeButton) == int(buttonIndex))
        {
            button->setImages(false, false, false, toggleButtonAssets[buttonIndex][2], 1.0f, juce::Colours::transparentWhite,
                toggleButtonAssets[buttonIndex][2], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex][3], 1.0f, juce::Colours::transparentWhite, 0);
        }
        else
            resetButtonAssets(button, buttonIndex);
    };

    void setCompressorButton(std::unique_ptr<juce::ImageButton>& button, int activeButton, int buttonIndex)
    {
        if(int(activeButton) == int(buttonIndex))
        {
            button->setImages(false, false, false, toggleButtonAssets[buttonIndex + 3][2], 1.0f, juce::Colours::transparentWhite,
                toggleButtonAssets[buttonIndex + 3][2], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex + 3][3], 1.0f, juce::Colours::transparentWhite, 0);
        }
        else
            resetButtonAssets(button, buttonIndex + 3);
    };

    void setFilterButton(std::unique_ptr<juce::ImageButton>& button, int activeButton, int buttonIndex)
    {
        if(int(activeButton) == int(buttonIndex))
        {
            button->setImages(false, false, false, toggleButtonAssets[buttonIndex + 5][2], 1.0f, juce::Colours::transparentWhite,
                toggleButtonAssets[buttonIndex + 5][2], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex + 5][3], 1.0f, juce::Colours::transparentWhite, 0);
        }
        else
            resetButtonAssets(button, buttonIndex + 5);
    };    

    enum Buttons
    {
        Vibrado_Triagle = 0,
        Vibrado_Sine,
        Vibrado_Saw,
        Compressor_Soft_Knee,
        Compressor_Hard_Knee,
        Filter_LOWPASS,
        Filter_HIGHPASS,
        Filter_PEAKING
    };

private:

    void resetButtonAssets(std::unique_ptr<juce::ImageButton>& button, int buttonIndex)
    {
        button->setImages(false, false, false, toggleButtonAssets[buttonIndex][0], 1.0f, juce::Colours::transparentWhite,
            toggleButtonAssets[buttonIndex][0], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex][1], 1.0f, juce::Colours::transparentWhite, 0);
    };

private:

    juce::Image toggleButtonAssets[8][4];    
     
};
