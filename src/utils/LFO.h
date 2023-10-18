#pragma once 
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

/**
 * Low Frequency Oscillator Class
 * 
 */
class LFO
{
public:

	/**
	 * @brief Contructor
	 * 
	 */
	LFO();
	
	/**
	 * @brief Constructor
	 * 
	 * Sets waveform type during object declaration
	 * 
	 * @param waveformType Waveform type index
	 */
	LFO(int waveformType);

	/**
	 * @brief Prepares object for processing
	 * 
	 * @param sampleRate Current sample rate
	 */
	void prepare(double sampleRate);

	/**
	 * @brief Generates and returns the next oscillator sample
	 * 
	 * @param phaseType Oscillator phase
	 */
	double getNextOutputSample(int phaseType);

	/**
	 * @brief Sets oscillator waveform type
	 * 
	 * @param waveformType Waveform type index
	 */
	void setWaveformType(int waveformType);

	/**
	 * @brief Returns waveform type index
	 */
	int getWaveformType();

	/**
	 * @brief Sets oscillation rate
	 * 
	 * @param freq New Rate
	 */
	void setFrequency(double freq);

	/**
	 * @brief Returns oscillation rate
	 */
	double getFrequency();

	/**
	 * @brief Sets the Sample Rate
	 * 
	 * @param sampleRate New sample rate
	 */
	void setSampleRate(double sampleRate);

	/**
	 * @brief Returns the current sample rate the object is operating on
	 */
	double getSampleRate();

	/**
	 * @brief Converts unipolar oscilation type to bipolar
	 * 
	 * @param value Value to convert
	 */
	double unipolarToBipolar(double value);

	enum Waveforms
	{
		Triangle = 0,
		Sine,
		Saw
	};

	enum LFOPhase
	{
		Normal = 0,
		Inverted,
		QuadPhase,
		QuadPhaseInverted
	};


private:
    void generateNextOutputSample();

	// Advabce the mod counter
	void moduloAdvance(double& modCounter, double phaceInc);

	// Check the mod counter and wrap
	void moduloWrap(double& modCounter, double phaceInc);
	// Advance the mod counter and wrap
	void moduloAdvanceAndWrap(double& modCounter, double phaceInc);

	// Parabolic Sine Calculation Function (Angle ragnes from -pi to pi)
	double parabolicSine(double angle);

	// Oscillator Parameters
	double modCounter, modCounter90, phaseInc;


	double frequency {1.0}, sampleRate;
	int waveformType {Waveforms::Sine};

	// Output Values
	double outNormal, outInverted, outQuadPhase, outQuadPhaseInverted;
};