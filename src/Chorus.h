#pragma once
#include <base/ModulationProcessor.h>

/**
 * Basic Chorus Effect
 * 
 */
template <typename SampleType>
class Chorus : public ModulationProcessor<SampleType>
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
	void prepare(SampleType sampleRate) override;

	/**
	 * @brief Processes a single sample
	 * 
	 * @param input Input sample
	 */
	SampleType processSample(SampleType input) override;

	/**
	 * @brief Processes a memory block that holds audio samples
	 * 
	 * @param data Memory block start pointer 
	 * @param startSample Sample index to start processing from
	 * @param endSample Number of samples to process
	 */
	void process(SampleType* data, int startSample, int endSample) override;
	/**
	 * @brief Sets chorus modulation rate
	 * 
	 * @param newRate New rate value
	 */
	void setRate(SampleType newRate) override;

	/**
	 * @brief Sets chorus modulation depth
	 * 
	 * @param newDepth New depth value
	 */
	void setDepth(SampleType newDepth) override;

	/**
	 * @brief Sets chorus wet/dry mix
	 * 
	 * @param newMix New wet/dry mix value
	 */
	void setMix(SampleType newMix);

private:

	// Min and Max delay times in ms
	SampleType minDelay {1.0};
	SampleType maxDelay {7.0};

	SampleType rate{0.33}, depth{0.15}, mix{0.5}; 
};