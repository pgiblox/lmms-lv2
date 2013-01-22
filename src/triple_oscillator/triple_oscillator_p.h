#ifndef TRIPLE_OSCILLATOR_P_H__
#define TRIPLE_OSCILLATOR_P_H__

// max length of each envelope-segment (e.g. attack)
#define SECS_PER_ENV_SEGMENT 5.0f
// max length of LFO period
#define SECS_PER_LFO_OSCILLATION 20.0f
// Scale Cutoff frequency
#define CUT_FREQ_MULTIPLIER 6000.0f
// Scale Resonance value
#define RES_MULTIPLIER 2.0f

#define PAN_MAX 100.0f
#define VOL_MAX 100.0f

#define PITCH_BEND_LAG   0.3
#define PITCH_BEND_RANGE 2.0


// PORTS
enum {
	// Instrument
	TRIPOSC_CONTROL = 0,
	TRIPOSC_OUT_L = 1,
	TRIPOSC_OUT_R = 2,
	// Voice - Triple oscillator
	TRIPOSC_OSC1_VOL = 3,
	TRIPOSC_OSC1_PAN = 4,
	TRIPOSC_OSC1_DETUNE_COARSE = 5,
	TRIPOSC_OSC1_DETUNE_FINE_L = 6,
	TRIPOSC_OSC1_DETUNE_FINE_R = 7,
	TRIPOSC_OSC1_PHASE_OFFSET = 8,
	TRIPOSC_OSC1_PHASE_DETUNE = 9,
	TRIPOSC_OSC1_PHASE_RANDOM = 10,
	TRIPOSC_OSC1_WAVE_SHAPE = 11,
	TRIPOSC_OSC1_OSC2_MOD = 12,
	TRIPOSC_OSC2_VOL = 13,
	TRIPOSC_OSC2_PAN = 14,
	TRIPOSC_OSC2_DETUNE_COARSE = 15,
	TRIPOSC_OSC2_DETUNE_FINE_L = 16,
	TRIPOSC_OSC2_DETUNE_FINE_R = 17,
	TRIPOSC_OSC2_PHASE_OFFSET = 18,
	TRIPOSC_OSC2_PHASE_DETUNE = 19,
	TRIPOSC_OSC2_PHASE_RANDOM = 20,
	TRIPOSC_OSC2_WAVE_SHAPE = 21,
	TRIPOSC_OSC2_OSC3_MOD = 22,
	TRIPOSC_OSC3_VOL = 23,
	TRIPOSC_OSC3_PAN = 24,
	TRIPOSC_OSC3_DETUNE_COARSE = 25,
	TRIPOSC_OSC3_DETUNE_FINE_L = 26,
	TRIPOSC_OSC3_DETUNE_FINE_R = 27,
	TRIPOSC_OSC3_PHASE_OFFSET = 28,
	TRIPOSC_OSC3_PHASE_DETUNE = 29,
	TRIPOSC_OSC3_PHASE_RANDOM = 30,
	TRIPOSC_OSC3_WAVE_SHAPE = 31,
	// Voice - Standard instrument configuration
	TRIPOSC_ENV_VOL_DEL = 32,
	TRIPOSC_ENV_VOL_ATT = 33,
	TRIPOSC_ENV_VOL_HOLD = 34,
	TRIPOSC_ENV_VOL_DEC = 35,
	TRIPOSC_ENV_VOL_SUS = 36,
	TRIPOSC_ENV_VOL_REL = 37,
	TRIPOSC_ENV_VOL_MOD = 38,
	TRIPOSC_FILTER_ENABLED = 39,
	TRIPOSC_FILTER_TYPE = 40,
	TRIPOSC_FILTER_CUT = 41,
	TRIPOSC_FILTER_RES = 42,
	TRIPOSC_ENV_CUT_DEL = 43,
	TRIPOSC_ENV_CUT_ATT = 44,
	TRIPOSC_ENV_CUT_HOLD = 45,
	TRIPOSC_ENV_CUT_DEC = 46,
	TRIPOSC_ENV_CUT_SUS = 47,
	TRIPOSC_ENV_CUT_REL = 48,
	TRIPOSC_ENV_CUT_MOD = 49,
	TRIPOSC_ENV_RES_DEL = 50,
	TRIPOSC_ENV_RES_ATT = 51,
	TRIPOSC_ENV_RES_HOLD = 52,
	TRIPOSC_ENV_RES_DEC = 53,
	TRIPOSC_ENV_RES_SUS = 54,
	TRIPOSC_ENV_RES_REL = 55,
	TRIPOSC_ENV_RES_MOD = 56
};


// Per-oscillator ports and calculated coefficients
typedef struct {
	// Ports
	float *vol_port;
	float *pan_port;
	float *detune_coarse_port;
	float *detune_fine_l_port;
	float *detune_fine_r_port;
	float *phase_offset_port;
	float *phase_detune_port;
	float *phase_random_port;
	float *wave_shape_port;
	float *modulation_port;
	
	// Calculated values
	float m_volumeLeft;
	float m_volumeRight;
	// normalized detuning -> x/sampleRate
	float m_detuningLeft;
	float m_detuningRight;
	// normalized offset -> x/360
	float m_phaseOffsetLeft;
	float m_phaseOffsetRight;
} OscillatorUnit;


// Plugin voice state
typedef struct {
	Oscillator osc_l[3];
	Oscillator osc_r[3];
} TripOscGenerator;


// The entire instrument
typedef struct {
	/* Features */
	LV2_URID_Map *map;

	/* Instrument Ports */
	LV2_Atom_Sequence *event_port;
	float *out_l_port;
	float *out_r_port;

	float *filter_enabled_port;
	float *filter_type_port;
	float *filter_cut_port;
	float *filter_res_port;

	EnvelopeParams env_vol_params;
	EnvelopeParams env_cut_params;
	EnvelopeParams env_res_params;

	/* Generic instrument stuff */
	Voice *voices;
	int    victim_idx;

	float  pitch_bend;        // Pitchbend in-value
	float  pitch_bend_lagged; // Pitchbend out-value

	/* URIs TODO: Global*/
	struct {
		LV2_URID midi_event;
		LV2_URID atom_message;
	} uris;

	/* Generator Ports */
	OscillatorUnit units[3];

	/* Playback state */
	uint32_t frame; // TODO: frame_t
	float    srate;
} TripleOscillator;


#endif // TRIPLE_OSCILLATOR_P_H__