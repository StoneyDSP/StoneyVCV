#include "plugin.hpp"

struct OscillatorEngine {
	float phase = 0.f;
};

struct MyModule : Module {
    OscillatorEngine engines[16];
	float blinkPhase = 0.f;
	enum ParamId {
		PITCH_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		PITCH_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SINE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		BLINK_LIGHT,
		LIGHTS_LEN
	};

	MyModule() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PITCH_PARAM, 0.f, 1.f, 0.f, "");
		configInput(PITCH_INPUT, "");
		configOutput(SINE_OUTPUT, "");
	}

	void process(const ProcessArgs &args) override {
        // Get desired number of channels from a "primary" input.
        // If this input is unpatched, getChannels() returns 0, but we should still generate 1 channel of output.
        int channels = std::max(1, inputs[PITCH_INPUT].getChannels());

        // Iterate through each active channel.
        for (int c = 0; c < channels; c++) {
            float pitch = params[PITCH_PARAM].getValue();
            // Use getPolyVoltage(c) so that monophonic inputs apply their modulation to all channels.
            pitch += inputs[PITCH_INPUT].getPolyVoltage(c);
            float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

            OscillatorEngine& engine = engines[c];

            engine.phase += freq * args.sampleTime;
            if (engine.phase >= 1.f)
                engine.phase -= 1.f;

            float sine = std::sin(2.f * M_PI * engine.phase);
            // Set the c'th channel by passing the second argument.
            outputs[SINE_OUTPUT].setVoltage(5.f * sine, c);
        }

        // Set the number of channels for each output.
        outputs[SINE_OUTPUT].setChannels(channels);
    }
};


struct MyModuleWidget : ModuleWidget {
	MyModuleWidget(MyModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/MyModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, MyModule::PITCH_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 77.478)), module, MyModule::PITCH_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, MyModule::SINE_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 25.81)), module, MyModule::BLINK_LIGHT));
	}
};


Model* modelMyModule = createModel<MyModule, MyModuleWidget>("MyModule");
