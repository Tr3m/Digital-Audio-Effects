#pragma once
#include <utils/LinearInterpolationCircularBuffer.h>
#include <utils/LFO.h>
#include <utils/extras/GainUtilities.h>

/**
 * Basic Vibrado Effect
 * 
 */
template <typename SampleType>
class Vibrado
{
public:
    
	/**
	 * @brief Constructor
	 * 
	 */
    Vibrado();

	/**
	 * @brief Destructor
	 * 
	 */
    ~Vibrado();

	/**
	 * @brief Prepares object for playback
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
	 * @brief Processes a memory block that holds audio samples
	 * 
	 * @param data Memory block start pointer 
	 * @param startSample Sample index to start processing from
	 * @param endSample Number of samples to process
	 */
	void process(SampleType* data, int startSample, int endSample);
	/**
	 * @brief Sets chorus modulation rate
	 * 
	 * @param newRate New rate value
	 */
	void setRate(SampleType newRate);

	/**
	 * @brief Sets chorus modulation depth
	 * 
	 * @param newDepth New depth value
	 */
	void setDepth(SampleType newDepth);

	/**
	 * @brief Sets output level
	 * 
	 * @param level_dB New level value in decibels 
	 */
	void setLevel(SampleType level_dB);

    /**
     * @brief Sets LFO wave shape
     * 
     * @param type LFO type index
     */
    void setLFOType(int type);

    /**
     * @brief Returns LFO type index
     */
    int getLFOType();

    enum LFO_Types
    {
        Triangle = 0,
        Sine,
        Saw
    };

private:

	SampleType doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue);
	SampleType bipolarToUnipolar(SampleType value);

private:

    SampleType sampleRate;

	LinearInterpolationCircularBuffer<SampleType> delayLine;
	LFO lfo;

	// Min and Max delay times in ms
	SampleType minDelay {0.1};
	SampleType maxDelay {7.0};

	SampleType rate {2.0}, depth {0.5}, level {0.0};
    int lfoType {LFO_Types::Sine};
};