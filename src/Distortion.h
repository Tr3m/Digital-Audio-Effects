#pragma once
#include <IIRFilter.h>
#include <utils/extras/GainUtilities.h>

/**
 * Basic Distortion Effect
 */
template <typename SampleType>
class Distortion
{
public:

	/**
	 * @brief Constructor
	 */
	Distortion();

	/**
	 * @brief Destructor
	 */
	~Distortion();

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
	 * @brief Sets distortion input gain
	 * 
	 * @param newGain New gain value in decibels
	 */
	void setGain(SampleType newGain);

	/**
	 * @brief Sets distortion output level
	 * 
	 * @param newLevel New output level value in decibels
	 */
	void setLevel(SampleType newLevel);

	/**
	 * @brief Sets the filter frequency
	 * 
	 * @param newFilterFreq New filter frequency in Hz
	 */
	void setFilterFreq(SampleType newFilterFreq);

private:

	SampleType sampleRate;

	SampleType gain {0.0}, level {-20.0}; // In dB
	SampleType filterCutoff {20000.0};

	IIRFilter<SampleType> filter;

	SampleType k{ 1.5 }; //input gain
	SampleType g{ 0.7 }; //saturation limit

};