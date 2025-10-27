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
#define OUT_HEIGHT_5 15
#define OUT_WIDTH_5 15
#define N_FILT_5 16
#define OUT_HEIGHT_6 13
#define OUT_WIDTH_6 13
#define N_FILT_6 16
#define OUT_HEIGHT_6 13
#define OUT_WIDTH_6 13
#define N_FILT_6 16
#define OUT_HEIGHT_9 6
#define OUT_WIDTH_9 6
#define N_FILT_9 16
#define OUT_HEIGHT_10 4
#define OUT_WIDTH_10 4
#define N_FILT_10 24
#define OUT_HEIGHT_10 4
#define OUT_WIDTH_10 4
#define N_FILT_10 24
#define OUT_HEIGHT_13 2
#define OUT_WIDTH_13 2
#define N_FILT_13 24
#define N_SIZE_0_14 96
#define N_LAYER_15 42
#define N_LAYER_15 42
#define N_LAYER_15 42
#define N_LAYER_19 64
#define N_LAYER_19 64
#define N_LAYER_19 64
#define N_LAYER_23 10
#define N_LAYER_23 10


// hls-fpga-machine-learning insert layer-precision
typedef nnet::array<ap_fixed<16,6>, 3*1> input_t;
typedef ap_fixed<28,13> fused_convbn_0_accum_t;
typedef nnet::array<ap_fixed<28,13>, 16*1> fused_convbn_0_result_t;
typedef ap_fixed<6,1> weight2_t;
typedef ap_fixed<6,1> bias2_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 16*1> layer4_t;
typedef ap_fixed<18,8> conv_act_0_table_t;
typedef ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0> pool_0_accum_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 16*1> layer5_t;
typedef ap_fixed<21,10> fused_convbn_1_accum_t;
typedef nnet::array<ap_fixed<21,10>, 16*1> fused_convbn_1_result_t;
typedef ap_fixed<6,1> weight6_t;
typedef ap_fixed<6,1> bias6_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 16*1> layer8_t;
typedef ap_fixed<18,8> conv_act_1_table_t;
typedef ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0> pool_1_accum_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 16*1> layer9_t;
typedef ap_fixed<21,10> fused_convbn_2_accum_t;
typedef nnet::array<ap_fixed<21,10>, 24*1> fused_convbn_2_result_t;
typedef ap_fixed<6,1> weight10_t;
typedef ap_fixed<6,1> bias10_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 24*1> layer12_t;
typedef ap_fixed<18,8> conv_act_2_table_t;
typedef ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0> pool_2_accum_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 24*1> layer13_t;
typedef ap_fixed<20,9> dense_0_accum_t;
typedef nnet::array<ap_fixed<20,9>, 42*1> dense_0_result_t;
typedef ap_fixed<6,1> weight15_t;
typedef ap_uint<1> bias15_t;
typedef ap_uint<1> layer15_index;
typedef nnet::array<ap_fixed<37,16>, 42*1> bn_dense_0_result_t;
typedef ap_fixed<16,6> bn_dense_0_scale_t;
typedef ap_fixed<16,6> bn_dense_0_bias_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 42*1> layer18_t;
typedef ap_fixed<18,8> dense_act_0_table_t;
typedef ap_fixed<19,8> dense_1_accum_t;
typedef nnet::array<ap_fixed<19,8>, 64*1> dense_1_result_t;
typedef ap_fixed<6,1> weight19_t;
typedef ap_uint<1> bias19_t;
typedef ap_uint<1> layer19_index;
typedef nnet::array<ap_fixed<36,15>, 64*1> bn_dense_1_result_t;
typedef ap_fixed<16,6> bn_dense_1_scale_t;
typedef ap_fixed<16,6> bn_dense_1_bias_t;
typedef nnet::array<ap_ufixed<6,0,AP_RND_CONV,AP_SAT,0>, 64*1> layer22_t;
typedef ap_fixed<18,8> dense_act_1_table_t;
typedef ap_fixed<29,13> output_dense_accum_t;
typedef nnet::array<ap_fixed<29,13>, 10*1> output_dense_result_t;
typedef ap_fixed<16,6> output_dense_weight_t;
typedef ap_fixed<16,6> output_dense_bias_t;
typedef ap_uint<1> layer23_index;
typedef nnet::array<ap_fixed<16,6>, 10*1> result_t;
typedef ap_fixed<18,8> output_softmax_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT,0> output_softmax_exp_table_t;
typedef ap_fixed<18,8,AP_RND,AP_SAT,0> output_softmax_inv_table_t;


#endif
