# ifndef PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_

# include "netxpto.h"

# include "optical_hybrid.h"
# include "photodiode.h"
# include "subtractor.h"
# include "ti_amplifier.h"
# include "decoder.h"
# include "local_oscillator.h"
# include "sampler.h"
# include "super_block_interface.h"
# include "electrical_filter.h"
# include "clock.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class HomodyneReceiver : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	//OpticalSignal HMD00{ "HMD00.sgn" }; // Input Signal

	OpticalSignal HMD01{ "HMD01.sgn" }; // Local Oscillator

	OpticalSignal HMD02{ "HMD02.sgn" }; // S+L

	OpticalSignal HMD03{ "HMD03.sgn" }; // S-L

	OpticalSignal HMD04{ "HMD04.sgn" }; // S+iL

	OpticalSignal HMD05{ "HMD05.sgn" }; // S-ilL

	TimeContinuousAmplitudeContinuousReal HMD06{ "HMD06.sgn" }; // Subtracted

	TimeContinuousAmplitudeContinuousReal HMD07{ "HMD07.sgn" }; // Substracted

	TimeContinuousAmplitudeContinuousReal HMD08{ "HMD08.sgn" }; // Amplified

	TimeContinuousAmplitudeContinuousReal HMD09{ "HMD09.sgn" }; // Amplified

	//TimeContinuousAmplitudeContinuousReal HMD10{ "HMD10.sgn" }; //Filtered

	//TimeContinuousAmplitudeContinuousReal HMD11{ "HMD11.sgn" }; //Filtered

	TimeContinuousAmplitudeContinuousReal HMD11{ "HMD11.sgn" }; //Clock

	TimeDiscreteAmplitudeContinuousReal HMD12{ "HMD12.sgn" }; // Sampled 

	TimeDiscreteAmplitudeContinuousReal HMD13{ "HMD13.sgn" }; // Sampled 

	Binary HMD14{ "HMD14.sgn" }; // recovery Sequence


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1;

	OpticalHybrid B2;

	Photodiode B3;

	Photodiode B4;

	TIAmplifier B5;

	TIAmplifier B6;

	//ElectricalFilter B7;

	//ElectricalFilter B8;

	Clock B8;

	Sampler B9;

	Sampler B10;
	
	Decoder B11;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

	double localOscillatorOpticalPower{ 1e-3 };
	double localOscillatorPhase{ 0 };
	double localOscillatorWavelength{ 1550e-9 };

	//int samplesToSkip{ 0 };

	double outputOpticalFrequency{ SPEED_OF_LIGHT / localOscillatorWavelength };

public:

	/* Methods */

	HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) { B11.setIqAmplitudes(iqAmplitudesValues); };
	vector<t_iqValues> const getIqAmplitudes(void) { return B11.getIqAmplitudes(); };

	void setLocalOscillatorSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };
	void setLocalOscillatorOpticalPower(double opticalPower) { B1.setOpticalPower(opticalPower); };
	void setLocalOscillatorOpticalPower_dBm(double opticalPower_dBm) { B1.setOpticalPower_dBm(opticalPower_dBm); };
	void setLocalOscillatorPhase(double lOscillatorPhase) { B1.setPhase(lOscillatorPhase); };
	void setLocalOscillatorOpticalWavelength(double lOscillatorWavelength) { B1.setWavelength(lOscillatorWavelength); };

	void setSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); B8.setSamplingPeriod(sPeriod); };

	void  setResponsivity(t_real Responsivity) { B3.responsivity = Responsivity; B4.responsivity = Responsivity; };

	void setAmplification(t_real Amplification) { B5.amplification = Amplification; B6.amplification = Amplification; };
	void setNoiseAmplitude(t_real NoiseAmplitude) { B5.noiseamp = NoiseAmplitude; B6.noiseamp = NoiseAmplitude;};

	/*void setImpulseResponseTimeLength(int impResponseTimeLength) { B7.setImpulseResponseTimeLength(impResponseTimeLength); B8.setImpulseResponseTimeLength(impResponseTimeLength); };
	void setCutoffFrequency(double cOffFrequency) { B7.setCutoffFrequency(cOffFrequency); B8.setCutoffFrequency(cOffFrequency); };
	void setFilterType(Filter fType) { B7.setFilterType(fType); B8.setFilterType(fType); };*/

	void setClockSamplingPeriod(double sPeriod) { B8.setSamplingPeriod(sPeriod); };

	void setSamplesToSkip(int sToSkip) { B9.setSamplesToSkip(sToSkip); B10.setSamplesToSkip(sToSkip); };

};

#endif
