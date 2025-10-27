#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

// hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 32
#define N_INPUT_2_1 32
#define N_INPUT_3_1 3
#define OUT_HEIGHT_2 30
#define OUT_WIDTH_2 30
#define N_FILT_2 16
#define OUT_HEIGHT_2 30
#define OUT_WIDTH_2 30
#define N_FILT_2 16
#define OUT_HEIGHT_6 15
#define OUT_WIDTH_6 15
#define N_FILT_6 16
#define OUT_HEIGHT_7 13
#define OUT_WIDTH_7 13
#define N_FILT_7 16
#define OUT_HEIGHT_7 13
#define OUT_WIDTH_7 13
#define N_FILT_7 16
#define OUT_HEIGHT_11 6
#define OUT_WIDTH_11 6
#define N_FILT_11 16
#define OUT_HEIGHT_12 4
#define OUT_WIDTH_12 4
#define N_FILT_12 24
#define OUT_HEIGHT_12 4
#define OUT_WIDTH_12 4
#define N_FILT_12 24
#define OUT_HEIGHT_16 2
#define OUT_WIDTH_16 2
#define N_FILT_16 24
#define N_SIZE_0_17 96
#define N_LAYER_18 42
#define N_LAYER_18 42
#define N_LAYER_22 64
#define N_LAYER_22 64
#define N_LAYER_26 10
#define N_LAYER_26 10


// hls-fpga-machine-learning insert layer-precision
typedef nnet::array<ap_fixed<16,6>, 3*1> input_t;
typedef ap_fixed<38,18> conv_0_accum_t;
typedef nnet::array<ap_fixed<38,18>, 16*1> conv_0_result_t;
typedef ap_fixed<16,6> conv_0_weight_t;
typedef ap_fixed<16,6> conv_0_bias_t;
typedef nnet::array<ap_fixed<16,6>, 16*1> layer5_t;
typedef ap_fixed<18,8> conv_act_0_table_t;
typedef ap_fixed<16,6> pool_0_accum_t;
typedef nnet::array<ap_fixed<16,6>, 16*1> layer6_t;
typedef ap_fixed<41,21> conv_1_accum_t;
typedef nnet::array<ap_fixed<41,21>, 16*1> conv_1_result_t;
typedef ap_fixed<16,6> conv_1_weight_t;
typedef ap_fixed<16,6> conv_1_bias_t;
typedef nnet::array<ap_fixed<16,6>, 16*1> layer10_t;
typedef ap_fixed<18,8> conv_act_1_table_t;
typedef ap_fixed<16,6> pool_1_accum_t;
typedef nnet::array<ap_fixed<16,6>, 16*1> layer11_t;
typedef ap_fixed<41,21> conv_2_accum_t;
typedef nnet::array<ap_fixed<41,21>, 24*1> conv_2_result_t;
typedef ap_fixed<16,6> conv_2_weight_t;
typedef ap_fixed<16,6> conv_2_bias_t;
typedef nnet::array<ap_fixed<16,6>, 24*1> layer15_t;
typedef ap_fixed<18,8> conv_act_2_table_t;
typedef ap_fixed<16,6> pool_2_accum_t;
typedef nnet::array<ap_fixed<16,6>, 24*1> layer16_t;
typedef ap_fixed<40,20> dense_0_accum_t;
typedef nnet::array<ap_fixed<40,20>, 42*1> dense_0_result_t;
typedef ap_fixed<16,6> dense_0_weight_t;
typedef ap_fixed<16,6> dense_0_bias_t;
typedef ap_uint<1> layer18_index;
typedef nnet::array<ap_fixed<16,6>, 42*1> layer21_t;
typedef ap_fixed<18,8> dense_act_0_table_t;
typedef ap_fixed<39,19> dense_1_accum_t;
typedef nnet::array<ap_fixed<39,19>, 64*1> dense_1_result_t;
typedef ap_fixed<16,6> dense_1_weight_t;
typedef ap_fixed<16,6> dense_1_bias_t;
typedef ap_uint<1> layer22_index;
typedef nnet::array<ap_fixed<16,6>, 64*1> layer25_t;
typedef ap_fixed<18,8> dense_act_1_table_t;
typedef ap_fixed<39,19> output_dense_accum_t;
typedef nnet::array<ap_fixed<39,19>, 10*1> output_dense_result_t;
typedef ap_fixed<16,6> output_dense_weight_t;
typedef ap_fixed<16,6> output_dense_bias_t;
typedef ap_uint<1> layer26_index;
typedef nnet::array<ap_fixed<16,6>, 10*1> result_t;
typedef ap_fixed<18,8> output_softmax_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT,0> output_softmax_exp_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT,0> output_softmax_inv_table_t;


#endif
