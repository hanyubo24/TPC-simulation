#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(
    hls::stream<input_t> &input_3,
    hls::stream<result_t> &layer28_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=input_3,layer28_out 
    #pragma HLS DATAFLOW

    // hls-fpga-machine-learning insert load weights
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        nnet::load_weights_from_txt<conv_0_weight_t, 432>(w2, "w2.txt");
        nnet::load_weights_from_txt<conv_0_bias_t, 16>(b2, "b2.txt");
        nnet::load_weights_from_txt<conv_1_weight_t, 2304>(w7, "w7.txt");
        nnet::load_weights_from_txt<conv_1_bias_t, 16>(b7, "b7.txt");
        nnet::load_weights_from_txt<conv_2_weight_t, 3456>(w12, "w12.txt");
        nnet::load_weights_from_txt<conv_2_bias_t, 24>(b12, "b12.txt");
        nnet::load_weights_from_txt<dense_0_weight_t, 4032>(w18, "w18.txt");
        nnet::load_weights_from_txt<dense_0_bias_t, 42>(b18, "b18.txt");
        nnet::load_weights_from_txt<dense_1_weight_t, 2688>(w22, "w22.txt");
        nnet::load_weights_from_txt<dense_1_bias_t, 64>(b22, "b22.txt");
        nnet::load_weights_from_txt<output_dense_weight_t, 640>(w26, "w26.txt");
        nnet::load_weights_from_txt<output_dense_bias_t, 10>(b26, "b26.txt");
        loaded_weights = true;    }
#endif
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<conv_0_result_t> layer2_out("layer2_out");
    #pragma HLS STREAM variable=layer2_out depth=900
    nnet::conv_2d_cl<input_t, conv_0_result_t, config2>(input_3, layer2_out, w2, b2); // conv_0

    hls::stream<layer5_t> layer5_out("layer5_out");
    #pragma HLS STREAM variable=layer5_out depth=900
    nnet::relu<conv_0_result_t, layer5_t, relu_config5>(layer2_out, layer5_out); // conv_act_0

    hls::stream<layer6_t> layer6_out("layer6_out");
    #pragma HLS STREAM variable=layer6_out depth=225
    nnet::pooling2d_cl<layer5_t, layer6_t, config6>(layer5_out, layer6_out); // pool_0

    hls::stream<conv_1_result_t> layer7_out("layer7_out");
    #pragma HLS STREAM variable=layer7_out depth=169
    nnet::conv_2d_cl<layer6_t, conv_1_result_t, config7>(layer6_out, layer7_out, w7, b7); // conv_1

    hls::stream<layer10_t> layer10_out("layer10_out");
    #pragma HLS STREAM variable=layer10_out depth=169
    nnet::relu<conv_1_result_t, layer10_t, relu_config10>(layer7_out, layer10_out); // conv_act_1

    hls::stream<layer11_t> layer11_out("layer11_out");
    #pragma HLS STREAM variable=layer11_out depth=36
    nnet::pooling2d_cl<layer10_t, layer11_t, config11>(layer10_out, layer11_out); // pool_1

    hls::stream<conv_2_result_t> layer12_out("layer12_out");
    #pragma HLS STREAM variable=layer12_out depth=16
    nnet::conv_2d_cl<layer11_t, conv_2_result_t, config12>(layer11_out, layer12_out, w12, b12); // conv_2

    hls::stream<layer15_t> layer15_out("layer15_out");
    #pragma HLS STREAM variable=layer15_out depth=16
    nnet::relu<conv_2_result_t, layer15_t, relu_config15>(layer12_out, layer15_out); // conv_act_2

    hls::stream<layer16_t> layer16_out("layer16_out");
    #pragma HLS STREAM variable=layer16_out depth=4
    nnet::pooling2d_cl<layer15_t, layer16_t, config16>(layer15_out, layer16_out); // pool_2

    auto& layer17_out = layer16_out;
    hls::stream<dense_0_result_t> layer18_out("layer18_out");
    #pragma HLS STREAM variable=layer18_out depth=1
    nnet::dense<layer16_t, dense_0_result_t, config18>(layer17_out, layer18_out, w18, b18); // dense_0

    hls::stream<layer21_t> layer21_out("layer21_out");
    #pragma HLS STREAM variable=layer21_out depth=1
    nnet::relu<dense_0_result_t, layer21_t, relu_config21>(layer18_out, layer21_out); // dense_act_0

    hls::stream<dense_1_result_t> layer22_out("layer22_out");
    #pragma HLS STREAM variable=layer22_out depth=1
    nnet::dense<layer21_t, dense_1_result_t, config22>(layer21_out, layer22_out, w22, b22); // dense_1

    hls::stream<layer25_t> layer25_out("layer25_out");
    #pragma HLS STREAM variable=layer25_out depth=1
    nnet::relu<dense_1_result_t, layer25_t, relu_config25>(layer22_out, layer25_out); // dense_act_1

    hls::stream<output_dense_result_t> layer26_out("layer26_out");
    #pragma HLS STREAM variable=layer26_out depth=1
    nnet::dense<layer25_t, output_dense_result_t, config26>(layer25_out, layer26_out, w26, b26); // output_dense

    nnet::softmax<output_dense_result_t, result_t, softmax_config28>(layer26_out, layer28_out); // output_softmax

}

