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

    };

    ~AssetManager()
    {

    };
    
    void setButtonAsset(std::unique_ptr<juce::ImageButton>& button, int activeButton, int buttonIndex)
    {
        if(int(activeButton) == int(buttonIndex))
        {
            button->setImages(false, false, false, toggleButtonAssets[buttonIndex][2], 1.0f, juce::Colours::transparentWhite,
                toggleButtonAssets[buttonIndex][2], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex][3], 1.0f, juce::Colours::transparentWhite, 0);
        }
        else
            resetButtonAssets(button, buttonIndex);
    };

    enum Buttons
    {
        Vibrado_Triagle = 0,
        Vibrado_Sine,
        Vibrado_Saw
    };

private:

    void resetButtonAssets(std::unique_ptr<juce::ImageButton>& button, int buttonIndex)
    {
        button->setImages(false, false, false, toggleButtonAssets[buttonIndex][0], 1.0f, juce::Colours::transparentWhite,
            toggleButtonAssets[buttonIndex][0], 1.0f, juce::Colours::transparentWhite, toggleButtonAssets[buttonIndex][1], 1.0f, juce::Colours::transparentWhite, 0);
    };

private:

    juce::Image toggleButtonAssets[3][4];    
     
};