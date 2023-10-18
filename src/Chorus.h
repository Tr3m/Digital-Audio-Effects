#pragma once
#include <utils/LinearInterpolationCircularBuffer.h>
#include <utils/LFO.h>

/**
 * Basic Chorus Effect
 * 
 */
template <typename SampleType>
class Chorus
{
public:

	/**
	 * @brief Constructor
	 * 
	 */
	Chorus();

	/**
	 * @brief Destructor
	 * 
	 */
	~Chorus();

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
	 * @brief Sets chorus wet/dry mix
	 * 
	 * @param newMix New wet/dry mix value
	 */
	void setMix(SampleType newMix);

private:

	SampleType doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue);
	SampleType bipolarToUnipolar(SampleType value);

private:

	SampleType sampleRate;

	LinearInterpolationCircularBuffer<SampleType> delayLine;
	LFO lfo;

	// Min and Max delay times in ms
	SampleType minDelay {1.0};
	SampleType maxDelay {7.0};

	SampleType rate{0.33}, depth{0.15}, mix{0.5}; 
};