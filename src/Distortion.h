#pragma once
#include <cmath>
#include <stdexcept>
#include <IIRFilter.h>
#include <utils/extras/GainUtilities.h>

#include <utils/saturators/Diode.h>
#include <utils/saturators/HardClipper.h>
#include <utils/saturators/SoftClipper.h>
#include <utils/saturators/VaccumTube.h>
#include <utils/saturators/AsymetricClipper.h>

#define NUM_ALGORITHMS 5

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
	 * @brief Sets saturation algorithm
	 * 
	 * @param algorithmIndex Algorithm Index
	 */
	void setAlgorithm(int algorithmIndex);

	/**
	 * @brief Returns the algorithm index
	 * 
	 */
  	int getAlgorithm();
	
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

	enum Algorithms
	{
		Tube = 0,
		Shockley_Diode,
		Soft,
		Hard,
		Asymetric
	};

private:

	SampleType sampleRate;

	IIRFilter<SampleType> filter;

	int algorithm {1};
	SampleType gain {0.0}, level {0.0}, filterCutoff {20000.0};

};