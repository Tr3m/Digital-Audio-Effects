#include "LFO.h"
#include <JuceHeader.h>

LFO::LFO()
{	
	
	setWaveformType(WaveformTypes::Triangle);
}

LFO::LFO(int _WaveformType)
{
	
	setWaveformType(_WaveformType);
}

void LFO::prepare(double _SampleRate)
{
	setSampleRate(_SampleRate);
	
	modCounter = 0.0;
	modCounter90 = 0.25;
}

void LFO::generateOutputSample()
{
	moduloWrap(modCounter, phaseInc);

	modCounter90 = modCounter;

	moduloAdvanceAndWrap(modCounter, 0.25);

	outNormal = 0.0;
	outInverted = 0.0;
	outQuadPhase = 0.0;
	outQuadPhaseInverted = 0.0;

	switch(waveformType)
	{
		case WaveformTypes::Triangle:
			//Normal Output
			outNormal = unipolarToBipolar(modCounter);
			outNormal = 2.0*fabs(outNormal) - 1.0;			

			//90 Degree phase shift
			outQuadPhase = unipolarToBipolar(modCounter90);
			outQuadPhase = 2.0*fabs(outQuadPhase) - 1.0;			

			break;

		case WaveformTypes::Sine:
			double angle;

			//Angle Calculation
			angle = modCounter*2.0*m_pi - m_pi;

			//Normal Output
			outNormal = parabolicSine(-angle);

			//90 Degree shift angle calculation
			angle = modCounter90*2.0*m_pi - m_pi;

			//90 Degree phase shift
			outQuadPhase = parabolicSine(-angle);

			break;

		case WaveformTypes::Saw:
			//Normal Output
			outNormal = unipolarToBipolar(modCounter);

			//90 Degree Shift
			outQuadPhase = unipolarToBipolar(modCounter90);

			break;

	}

	//Inverted Outputs

	//Inverted Normal Output
	outInverted = -outNormal;

	//Inverted 90 Degree
	outQuadPhaseInverted = -outQuadPhase;

	moduloAdvance(modCounter, phaseInc);
}

double LFO::getOutputSample(int phaseType)
{
	switch(phaseType)
	{
		case PhaseTypes::Normal:
			return outNormal;
			break;
		case PhaseTypes::Inverted:
			return outInverted;
			break;
		case PhaseTypes::QuadPhase:
			return outQuadPhase;
			break;
		case PhaseTypes::QuadPhase_Inverted:
			return outQuadPhaseInverted;
			break;
		default:
			return outNormal;
			break;
	}
}

void LFO::setWaveformType(int _WaveformType)
{
	switch(_WaveformType)
	{
		case WaveformTypes::Triangle:
			waveformType = WaveformTypes::Triangle;
			break;
		case WaveformTypes::Sine:
			waveformType = WaveformTypes::Sine;
			break;
		case WaveformTypes::Saw:
			waveformType = WaveformTypes::Saw;
			break;
	}
}

int LFO::getWaveformType()
{
	return waveformType;
}

void LFO::setFrequency(double _Frequency)
{
	frequency = _Frequency;
	phaseInc = frequency / sampleRate;
}

double LFO::getFrequency()
{
	return frequency;
}

void LFO::setSampleRate(double _SampleRate)
{
	sampleRate = _SampleRate;
}

double LFO::getSampleRate()
{
	return sampleRate;
}

double LFO::unipolarToBipolar(double value)
{
	return 2.0*value - 1.0;
}

void LFO::moduloAdvance(double& _ModCounter, double _PhaseInc)
{
	_ModCounter += _PhaseInc;
}

void LFO::moduloWrap(double& _ModCounter, double _PhaseInc)
{
	//Positive Frequencies
	if(_PhaseInc > 0 && _ModCounter >= 1.0)
		_ModCounter -= 1.0;

	//Negative Frequencies
	if(_PhaseInc < 0 && _ModCounter <= 0.0)
		_ModCounter += 1.0;
}

void LFO::moduloAdvanceAndWrap(double& _ModCounter, double _PhaseInc)
{
	//Advance
	_ModCounter += _PhaseInc;

	//Check if Wrap is needed

	//Positive Frequencies 
	if(_PhaseInc > 0 && _ModCounter >= 1.0)
		_ModCounter -= 1.0;

	//Negative Frequencies
	if(_PhaseInc < 0 && _ModCounter <= 0.0)
		_ModCounter += 1.0;
}

double LFO::parabolicSine(double angle)
{
	const double B = 4.0 / m_pi;
	const double C = -4.0 / (m_pi* m_pi);
	const double P = 0.225;

	double y = B * angle + C * angle * fabs(angle);
	y = P * (y * fabs(y) - y) + y;
	return y;
}