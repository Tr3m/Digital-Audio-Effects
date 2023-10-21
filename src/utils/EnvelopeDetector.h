#pragma once
#include <cmath>

/**
 * Envelope Detector Class
 */
template <typename SampleType>
class EnvelopeDetector
{
public:

    /**
     * @brief Constructor
     * 
     */
    EnvelopeDetector();
    
    /**
     * @brief Prepares object for processing
     * 
     * @param sampleRate Current sampling rate
     */
    void prepare(SampleType sampleRate);

    /**
     * @brief Processes a single sample
     * 
     * @param input Input sample
     */
    SampleType processSample(SampleType input);

    /**
     * @brief Sets the attack time of the Envelope Detector object
     * 
     * @param newValue New attack time in milliseconds
     */
    void setAttackTime(SampleType newValue);

    /**
     * @brief Returns the attack time parameter value of the Envelope Detector object
     */
    SampleType getAttackTime();

    /**
     * @brief Sets the release time of the Envelope Detector object
     * 
     * @param newValue New Release time in milliseconds
     */
    void setReleaseTime(SampleType newValue);

    /**
     * @brief Returns the release time parameter value of the Envelope Detector object
     * 
     * @return SampleType 
     */
    SampleType getReleaseTime();
    
    /**
     * @brief Sets the detection mode of the Envelope Detector object
     * 
     * @param index Detection mode index
     */
    void setDetectionMode(int index);

    /**
     * @brief Returns the detection mode index of the Envelope Detector object
     */
    int getDetectionMode();

    /**
     * @brief Sets the envelope detector in dB or linear output mode
     * 
     * @param outputIndB Should output be in dB boolean. 
     * True = db Output, False = Linear Output
     */
    void setOutputIndB(bool outputIndB);

    /**
     * @brief Returns Envelope Detector detection mode
     * 
     * @return true dB output
     * @return false Linear output
     */
    bool isOutputIndB();

    enum DetectionModes
    {
        Peak = 0,
        MS,		//Mean Square
        RMS		//Root Mean Square
    };


private:    

    SampleType sampleRate{ 44100.0 };

    //User Parameters
    SampleType attackTime{ 0.0 };   //In ms
    SampleType releaseTime{ 0.0 };  //In ms
    int detectionMode{DetectionModes::Peak};


    SampleType attackTimeCoeff{ 0.0 };
    SampleType releaseTimeCoeff{ 0.0 };
    bool output_In_dB{false};

    const double rc_atc = -0.99967234081320612357829304641019; //RC filter analog time constant

    SampleType previousValue{0.0}; //Envelope value for the previous sample

    void setSampleRate(SampleType sampleRate);
};