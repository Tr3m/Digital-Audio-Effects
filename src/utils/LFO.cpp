#include "LFO.h"
#include <JuceHeader.h>

LFO::LFO()
{	
	
}

LFO::LFO(int waveformType)
{	
	setWaveformType(waveformType);
}

void LFO::prepare(double sampleRate)
{
	setSampleRate(sampleRate);	
	modCounter = 0.0;
	modCounter90 = 0.25;
	setFrequency(frequency);
}

double LFO::getNextOutputSample(int phaseType)
{
	generateNextOutputSample();

	switch(phaseType)
	{
		case LFOPhase::Normal:
			return outNormal;
			break;
		case LFOPhase::Inverted:
			return outInverted;
			break;
		case LFOPhase::QuadPhase:
			return outQuadPhase;
			break;
		case LFOPhase::QuadPhaseInverted:
			return outQuadPhaseInverted;
			break;
		default:
			return outNormal;
			break;
	}
}

void LFO::setWaveformType(int waveformType)
{
	switch(waveformType)
	{
		case Waveforms::Triangle:
			waveformType = Waveforms::Triangle;
			break;
		case Waveforms::Sine:
			waveformType = Waveforms::Sine;
			break;
		case Waveforms::Saw:
			waveformType = Waveforms::Saw;
			break;
	}
}

int LFO::getWaveformType()
{
	return waveformType;
}

void LFO::setFrequency(double freq)
{
	frequency = freq;
	phaseInc = frequency / sampleRate;
}

double LFO::getFrequency()
{
	return frequency;
}

void LFO::setSampleRate(double sampleRate)
{
	this->sampleRate = sampleRate;
}

double LFO::getSampleRate()
{
	return sampleRate;
}

double LFO::unipolarToBipolar(double value)
{
	return 2.0*value - 1.0;
}

void LFO::generateNextOutputSample()
{
	moduloWrap(modCounter, phaseInc);

	modCounter90 = modCounter;

	moduloAdvanceAndWrap(modCounter90, 0.25);

	outNormal = 0.0;
	outInverted = 0.0;
	outQuadPhase = 0.0;
	outQuadPhaseInverted = 0.0;

	switch(waveformType)
	{
		case Waveforms::Triangle:
			// Normal Output
			outNormal = unipolarToBipolar(modCounter);
			outNormal = 2.0*fabs(outNormal) - 1.0;			

			// 90 Degree phase shift
			outQuadPhase = unipolarToBipolar(modCounter90);
			outQuadPhase = 2.0*fabs(outQuadPhase) - 1.0;			

			break;

		case Waveforms::Sine:
			double angle;

			// Angle Calculation
			angle = modCounter*2.0*PI - PI;

			// Normal Output
			outNormal = parabolicSine(-angle);

			// 90 Degree shift angle calculation
			angle = modCounter90*2.0*PI - PI;

			// 90 Degree phase shift
			outQuadPhase = parabolicSine(-angle);

			break;

		case Waveforms::Saw:
			// Normal Output
			outNormal = unipolarToBipolar(modCounter);

			// 90 Degree Shift
			outQuadPhase = unipolarToBipolar(modCounter90);

			break;

	}

	// Inverted Outputs

	// Inverted Normal Output
	outInverted = -outNormal;

	// Inverted 90 Degree
	outQuadPhaseInverted = -outQuadPhase;

	moduloAdvance(modCounter, phaseInc);
}

void LFO::moduloAdvance(double& modCounter, double phaseInc)
{
	modCounter += phaseInc;
}

void LFO::moduloWrap(double& modCounter, double phaseInc)
{
	// Positive Frequencies
	if(phaseInc > 0 && modCounter >= 1.0)
		modCounter -= 1.0;

	// Negative Frequencies
	if(phaseInc < 0 && modCounter <= 0.0)
		modCounter += 1.0;
}

void LFO::moduloAdvanceAndWrap(double& modCounter, double phaseInc)
{
	// Advance
	modCounter += phaseInc;

	// Check if Wrap is needed

	// Positive Frequencies 
	if(phaseInc > 0 && modCounter >= 1.0)
		modCounter -= 1.0;

	// Negative Frequencies
	if(phaseInc < 0 && modCounter <= 0.0)
		modCounter += 1.0;
}

double LFO::parabolicSine(double angle)
{
	const double B = 4.0 / PI;
	const double C = -4.0 / (PI* PI);
	const double P = 0.225;

	double y = B * angle + C * angle * fabs(angle);
	
	return (P * (y * fabs(y) - y) + y);
}