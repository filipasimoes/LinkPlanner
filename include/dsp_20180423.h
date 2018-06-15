# ifndef PROGRAM_INCLUDE_DSP_H_
# define PROGRAM_INCLUDE_DSP_H_

# include "netxpto_20180118.h"

# include "real_to_complex_20180221.h"
# include "cpe_20180423.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class DSP : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################


	BandpassSignal DSP01{ "DSP01.sgn" };  // real to complex
	BandpassSignal DSP02{ "DSP02.sgn" };  // cpe
	

 // #####################################################################################################
 // ########################### Blocks Declaration and Inicialization ###################################
 // #####################################################################################################

	RealToComplex2 B01;

	CPE B02;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

public:

	/* Methods */

	DSP(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */
	
	void setCPEnTaps(int nTaps) { B02.setnTaps(nTaps); }
	void setCPETestPhase(int TestPhase) { B02.setTestPhase(TestPhase); }
	void setCPESamplingPeriod(double sPeriod) { B02.setSamplingPeriod(sPeriod); }
	void setCPEmethodType(string mType) { B02.setmethodType(mType); }

	void setSamplingPeriod(double sPeriod) { B02.setSamplingPeriod(sPeriod); };
	
};

#endif