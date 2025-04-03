
#include "calibration.hpp"

#include <iostream>
#include <string>

#include "bindings.hpp"
#include "network_cfg.hpp"
#include "projects/ANN-E/Bringup/Calibration/bindings.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/periph/analog_input.hpp"

namespace calibration {

float middleLayerWeights[bindings::kNumNeuronsPerLayer]
                        [bindings::kNumWeightsPerNeuron] = {
                            {
                                2.1664881706237793,
                                0.9372791647911072,
                                -1.6557891368865967,
                                -0.39831608533859253,
                                -0.7288235425949097,
                                -2.659982919692993,
                                3.738539457321167,
                                -1.2489608526229858,
                                -0.15284639596939087,
                                0.23639816045761108,
                                -0.09863411635160446,
                                2.052107095718384,
                            },
                            {
                                0.861344039440155,
                                0.4367678463459015,
                                0.024722453206777573,
                                -0.3973162770271301,
                                -0.04097411036491394,
                                1.742340326309204,
                                -0.15817666053771973,
                                0.5503004789352417,
                                3.2650976181030273,
                                0.19410957396030426,
                                0.2979756295681,
                                0.2610832452774048,
                            },
                            {
                                -0.09453188627958298,
                                -2.151118040084839,
                                0.5984936952590942,
                                0.4060435891151428,
                                -1.447737216949463,
                                1.529990315437317,
                                1.0888794660568237,
                                -1.5530439615249634,
                                -0.5233402252197266,
                                -0.2529886066913605,
                                0.2227957397699356,
                                -1.1084250211715698,
                            },
                            {
                                -0.22656171023845673,
                                1.4010077714920044,
                                1.3721469640731812,
                                -1.7507436275482178,
                                -1.3073136806488037,
                                -2.4992125034332275,
                                -0.1718052625656128,
                                -0.03928307443857193,
                                2.8354294300079346,
                                0.5743553042411804,
                                1.1909494400024414,
                                0.5331371426582336,
                            },
                            {
                                -1.095634937286377,
                                -1.4108448028564453,
                                0.3386712968349457,
                                0.7944347262382507,
                                -0.06140437722206116,
                                -1.1084022521972656,
                                1.3995968103408813,
                                -0.2709285318851471,
                                -1.33951997756958,
                                1.9189960956573486,
                                0.8912521600723267,
                                0.4078693389892578,
                            },
                            {
                                -0.16980841755867004,
                                -1.2021005153656006,
                                -0.9040570259094238,
                                2.073380947113037,
                                -0.6065662503242493,
                                -0.03839730843901634,
                                0.44058725237846375,
                                2.1213624477386475,
                                0.7585901618003845,
                                -0.14492329955101013,
                                -0.09358915686607361,
                                -0.08071891963481903,
                            },
                            {
                                2.516228199005127,
                                -1.6530191898345947,
                                2.682981014251709,
                                -3.3654582500457764,
                                -0.570246696472168,
                                0.5571966171264648,
                                -0.6976050138473511,
                                2.565195322036743,
                                1.6904131174087524,
                                0.970526933670044,
                                -1.1454570293426514,
                                -0.02566969394683838,
                            },
                            {
                                -1.1272757053375244,
                                0.8473675847053528,
                                -1.3313223123550415,
                                1.7831940650939941,
                                0.4354119896888733,
                                0.47938790917396545,
                                -1.2470331192016602,
                                1.3566983938217163,
                                1.078291654586792,
                                1.2641518115997314,
                                -0.9285987615585327,
                                0.866907000541687,
                            },
                            {
                                1.5423318147659302,
                                -1.7051502466201782,
                                0.6824184060096741,
                                -0.09413398802280426,
                                1.0926275253295898,
                                0.4855763018131256,
                                2.1061861515045166,
                                -0.5139979124069214,
                                -0.6344808340072632,
                                -0.829096257686615,
                                0.8203657269477844,
                                -0.5188748240470886,
                            },
                            {
                                -0.09978385269641876,
                                1.820223093032837,
                                -0.25765281915664673,
                                -0.7172019481658936,
                                0.7066702842712402,
                                0.9749800562858582,
                                1.0288337469100952,
                                0.2740044593811035,
                                0.23595580458641052,
                                -0.5686906576156616,
                                1.5532160997390747,
                                -0.5819675922393799,
                            },
                            {
                                1.149558663368225,
                                2.531559944152832,
                                -0.8278670310974121,
                                -1.058824896812439,
                                0.8433778285980225,
                                -2.5452523231506348,
                                0.43578478693962097,
                                2.6980905532836914,
                                0.31516388058662415,
                                -0.7472075819969177,
                                0.7776203155517578,
                                0.10773593187332153,
                            },
                            {
                                0.5048266053199768,
                                0.509644091129303,
                                0.23911897838115692,
                                -0.08840923756361008,
                                -1.8235231637954712,
                                0.8144299387931824,
                                0.8495240807533264,
                                -0.9075841307640076,
                                0.963322103023529,
                                0.29980143904685974,
                                -0.10682054609060287,
                                -0.06014372035861015,
                            },
};

float outputLayerWeights[bindings::kNumNeuronsPerLayerOutput]
                        [bindings::kNumWeightsPerNeuron] = {
                            {
                                -0.8819023370742798,
                                -0.15631727874279022,
                                -4.376169681549072,
                                -4.252255916595459,
                                -0.7921686768531799,
                                -0.21434924006462097,
                                -1.333181381225586,
                                -1.2962489128112793,
                                0.9313572645187378,
                                -2.160261631011963,
                                3.085545539855957,
                                5.554571151733398,
                            },
                            {
                                -1.063110113143921,
                                -5.625367641448975,
                                -9.299798011779785,
                                1.1397618055343628,
                                -0.7784349918365479,
                                2.0840232372283936,
                                2.897073984146118,
                                -0.5353513956069946,
                                0.7295053601264954,
                                3.562222719192505,
                                -4.141565322875977,
                                1.7511404752731323,
                            },
                            {
                                0.668320894241333,
                                -1.2429702281951904,
                                -0.403512179851532,
                                1.5209084749221802,
                                2.3129305839538574,
                                1.5912421941757202,
                                0.09969965368509293,
                                -3.0897953510284424,
                                -3.9316494464874268,
                                1.2759222984313965,
                                2.2762725353240967,
                                -0.9862318634986877,
                            },
                            {
                                -0.35978204011917114,
                                0.5537784695625305,
                                0.6871258616447449,
                                0.3644278049468994,
                                -1.100541591644287,
                                2.0885512828826904,
                                -1.373673439025879,
                                -3.5445940494537354,
                                -4.34380578994751,
                                -4.486298561096191,
                                -0.21857208013534546,
                                3.0547070503234863,
                            },
                            {
                                -1.7677899599075317,
                                0.2206321656703949,
                                2.3783438205718994,
                                -3.3436450958251953,
                                -2.0526208877563477,
                                -2.149763822555542,
                                3.9037013053894043,
                                3.0913498401641846,
                                -0.6231128573417664,
                                -0.17507034540176392,
                                -0.056310128420591354,
                                -5.400580406188965,
                            },
                            {
                                1.181901454925537,
                                2.2587082386016846,
                                -1.036136507987976,
                                -0.13973182439804077,
                                -0.1736425906419754,
                                -7.001873970031738,
                                -2.5665550231933594,
                                1.5330560207366943,
                                3.1637966632843018,
                                -3.07556414604187,
                                -1.434465765953064,
                                0.3893529176712036,
                            },
                            {
                                0.04850901663303375,
                                0.5749634504318237,
                                -1.9759901762008667,
                                1.5512311458587646,
                                -2.791264772415161,
                                -2.663017988204956,
                                -0.6625383496284485,
                                2.164886951446533,
                                2.483591079711914,
                                0.7625842094421387,
                                1.913898229598999,
                                -1.7403799295425415,
                            },
                            {
                                1.8656213283538818,
                                -4.975520610809326,
                                1.2118297815322876,
                                -1.145028829574585,
                                1.925515055656433,
                                1.9708654880523682,
                                1.99514901638031,
                                -1.561336636543274,
                                -4.261951923370361,
                                1.3680371046066284,
                                -3.4375057220458984,
                                -2.9644157886505127,
                            },
                            {
                                -2.871274948120117,
                                1.2351500988006592,
                                -2.2708992958068848,
                                0.5317742824554443,
                                1.927245855331421,
                                0.3564252555370331,
                                -1.5132920742034912,
                                -1.9214497804641724,
                                1.2405303716659546,
                                1.3607051372528076,
                                -1.0480979681015015,
                                1.7330294847488403,
                            },
                            {
                                -3.048651695251465,
                                0.6164897680282593,
                                -0.6908940672874451,
                                -4.1850738525390625,
                                2.9009196758270264,
                                0.2307450920343399,
                                -0.08044712990522385,
                                -1.6405360698699951,
                                -0.1206585168838501,
                                -3.299180507659912,
                                0.7400902509689331,
                                2.293893814086914,
                            },
};

void OpenAllTerminals() {
    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[0][i][j].SetPosition(neurons_pot_positions[i][j]);
            bindings::DelayMs(10);
            bindings::pots[0][i][j].SetTerminalConnections(false, false, false);
        }
        bindings::bias_pots[0][i].SetPosition(bias_pot_positions[i]);
        bindings::bias_pots[0][i].SetTerminalConnections(false, false, false);
        bindings::fb_pots[0][i].SetPosition(feedback_pot_positions[i]);
        bindings::fb_pots[0][i].SetTerminalConnections(false, false, false);
    }

    // condition second layer for pass through
    for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[1][i][j].SetPosition(neurons_pot_positions_2[i][j]);
            bindings::DelayMs(10);
            bindings::pots[1][i][j].SetTerminalConnections(false, false, false);
        }
        bindings::bias_pots[1][i].SetPosition(bias_pot_positions_2[i]);
        bindings::bias_pots[1][i].SetTerminalConnections(false, false, false);
        bindings::fb_pots[1][i].SetPosition(feedback_pot_positions_2[i]);
        bindings::fb_pots[1][i].SetTerminalConnections(false, false, false);
    }
}

// sets neuron voltage multiplier to 1
void EnablePassThrough(uint8_t layer, uint8_t neuron, uint8_t weight) {
    bindings::pots[layer][neuron][weight].SetPosition(255);
    bindings::pots[layer][neuron][weight].SetTerminalConnections(true, false,
                                                                 true);

    bindings::fb_pots[layer][neuron].SetPosition(255);
    bindings::fb_pots[layer][neuron].SetTerminalConnections(true, false, true);
}

// reset positions, but disconnect wipers
void DisablePassThrough(uint8_t layer, uint8_t neuron, uint8_t weight) {
    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        input_values[i / 4][i % 4] = 0;
    }
    bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
    bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
    bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);

    uint8_t position = layer == 0 ? neurons_pot_positions[neuron][weight]
                                  : neurons_pot_positions_2[neuron][weight];
    uint8_t fb_position = layer == 0 ? feedback_pot_positions[neuron]
                                     : feedback_pot_positions_2[neuron];

    bindings::pots[layer][neuron][weight].SetPosition(position);
    bindings::pots[layer][neuron][weight].SetTerminalConnections(false, false,
                                                                 false);

    bindings::fb_pots[layer][neuron].SetPosition(fb_position);
    bindings::fb_pots[layer][neuron].SetTerminalConnections(false, false,
                                                            false);
}

// change inputs to match current weight
void configureInputLayer(uint8_t layer, uint8_t neuron, uint8_t weight) {
    float ideal_weight = getIdealWeight(layer, neuron, weight);
    float input_value = layer == 1 ? 0.5f : ideal_weight < 0 ? -.5f : .5f;
    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        input_values[i / 4][i % 4] = 0;
    }
    if (layer == 1) {
        input_values[0][0] = input_value;
    }
    if (layer == 0) {
        input_values[weight / 4][weight % 4] = input_value;
    }

    bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
    bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
    bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);
}

shared::periph::AnalogInput* get_measuring_channel(uint8_t layer,
                                                   uint8_t neuron,
                                                   uint8_t weight) {
    if (layer == 0) {
        return bindings::adc_channels[0];
    }
    if (layer == 1) {
        return bindings::adc_channels[neuron];
    }
    return nullptr;
}

float getIdealWeight(uint8_t layer, uint8_t neuron, uint8_t weight) {
    if (layer == 0) {
        return middleLayerWeights[neuron][weight];
    }
    if (layer == 1) {
        return outputLayerWeights[neuron][weight];
    }
    return 0;
}

void calibrateWeight(uint8_t layer, uint8_t neuron, uint8_t weight) {
    auto pot = bindings::pots[layer][neuron][weight];
    auto fb_pot = bindings::fb_pots[layer][neuron];

    // setup cal config
    if (layer == 0) {
        EnablePassThrough(1, 0, neuron);
        fb_pot.SetPosition(feedback_pot_positions[neuron]);
        fb_pot.SetTerminalConnections(feedback_tcona_settings[neuron],
                                      feedback_tconb_settings[neuron],
                                      feedback_tconw_settings[neuron]);
        // pot.SetPosition(neurons_pot_positions[neuron][weight]);
        pot.SetTerminalConnections(neuron_tcona_settings[neuron][weight],
                                   neuron_tconb_settings[neuron][weight],
                                   neuron_tconw_settings[neuron][weight]);
    }
    if (layer == 1) {
        EnablePassThrough(0, weight, 0);
        fb_pot.SetPosition(feedback_pot_positions_2[neuron]);
        fb_pot.SetTerminalConnections(feedback_tcona_settings_2[neuron],
                                      feedback_tconb_settings_2[neuron],
                                      feedback_tconw_settings_2[neuron]);
        pot.SetPosition(neurons_pot_positions_2[neuron][weight]);
        pot.SetTerminalConnections(neuron_tcona_settings_2[neuron][weight],
                                   neuron_tconb_settings_2[neuron][weight],
                                   neuron_tconw_settings_2[neuron][weight]);
    }
    bindings::DelayMs(10);
    // std::cout << std::to_string(pot.GetPosition()) << std::endl;
    // std::cout << std::to_string(fb_pot.GetPosition()) << std::endl;
    configureInputLayer(layer, neuron, weight);

    shared::periph::AnalogInput* measuring_channel =
        get_measuring_channel(layer, neuron, weight);
    float ideal_weight = getIdealWeight(layer, neuron, weight) * 0.5f;

    // std::cout << "Ideal weight: " << ideal_weight << "   ";
    // std::cout << "Measuring channel: "
    //           << StmAdcToANNVoltage(measuring_channel->ReadVoltage())
    //           << std::endl;

    if(layer == 1){
        pot.SetPosition(0);
        float min_weight_error = std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - ideal_weight);
        uint8_t min_position = 0;
        for(int i = 0; i < 255; i++, pot++){
            if (std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - ideal_weight) < min_weight_error){
                min_weight_error = std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - ideal_weight);
                min_position = pot.GetPosition();
            }
        }
        neurons_pot_positions_2[neuron][weight] = min_position;
        std::cout << "set " << std::to_string(layer) << " "
              << std::to_string(neuron) << " " << std::to_string(weight)
              << " to " << std::to_string(min_position) << std::endl;
        
    }
    if(layer == 0){
        pot.SetPosition(0);
        float min_weight_error = std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - std::abs(ideal_weight));
        uint8_t min_position = 0;
        for(int i = 0; i < 255; i++, pot++){
            if (std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - std::abs(ideal_weight)) < min_weight_error){
                min_weight_error = std::abs(StmAdcToANNVoltage(measuring_channel->ReadVoltage()) - std::abs(ideal_weight));
                min_position = pot.GetPosition();
            }
        }
        neurons_pot_positions[neuron][weight] = min_position;
        std::cout << "set " << std::to_string(layer) << " "
              << std::to_string(neuron) << " " << std::to_string(weight)
              << " to " << std::to_string(min_position) << std::endl;
        
    }

    // std::cout << "Ideal weight: " << ideal_weight << "   ";
    // std::cout << "Measuring channel: "
    //           << StmAdcToANNVoltage(measuring_channel->ReadVoltage())
    //           << std::endl;
    std::cout << "set " << std::to_string(layer) << " "
              << std::to_string(neuron) << " " << std::to_string(weight)
              << " to " << std::to_string(pot.GetPosition()) << std::endl;

    // reset cal config
    if (layer == 0) {
        DisablePassThrough(1, 0, neuron);
    }
    if (layer == 1) {
        DisablePassThrough(0, weight, 0);
    }
    pot.SetTerminalConnections(false, false, false);
    fb_pot.SetTerminalConnections(false, false, false);
}

float StmAdcToANNVoltage(float adc_reading) {
    return adc_reading * 5.5f / 3.3f - 2.75f;
}

}  // namespace calibration