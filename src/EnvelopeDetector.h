#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class EnvelopeDetector
{
public:

    EnvelopeDetector();
        
    void prepare(double _sampleRate);
    double processSample(double input);

    //Setters and Getters

    void setAttackTime(double newValue);
    double getAttackTime();

    void setReleaseTime(double newValue);
    double getReleaseTime();

    void setDetectionMode(int index);
    int getDetectionMode();

    void setOutputIndB(bool _output_In_dB);
    bool isOutputIndB();

    enum DetectionModes
    {
        Peak = 0,
        MS,		//Mean Square
        RMS		//Root Mean Square
    };


private:    

    double sampleRate{ 44100.0 };

    //User Parameters
    double attackTime{ 0.0 };   //In ms
    double releaseTime{ 0.0 };  //In ms
    int detectionMode{DetectionModes::Peak};


    double attackTimeCoeff{ 0.0 };
    double releaseTimeCoeff{ 0.0 };
    bool output_In_dB{false};

    const double rc_atc = -0.99967234081320612357829304641019; //RC filter analog time constant

    double previousValue{0.0}; //Envelope value for the previous sample

    void setSampleRate(double m_SampleRate);
};