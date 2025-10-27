#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

// hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 16
#define N_INPUT_1_1 16
#define N_LAYER_3 64
#define N_LAYER_3 64
#define N_LAYER_3 64
#define N_LAYER_8 32
#define N_LAYER_8 32
#define N_LAYER_8 32
#define N_LAYER_13 32
#define N_LAYER_13 32
#define N_LAYER_13 32
#define N_LAYER_18 5
#define N_LAYER_18 5


// hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<13,5> input_1_t;
typedef ap_fixed<12,5> h_quantize_t;
typedef ap_fixed<20,7> h_dense_accum_t;
typedef ap_fixed<12,7> h_dense_t;
typedef ap_fixed<10,4> h_dense_weight_t;
typedef ap_fixed<20,7> h_dense_bias_t;
typedef ap_uint<1> layer3_index;
typedef ap_ufixed<11,6> re_lu_t;
typedef ap_fixed<18,8> re_lu_table_t;
typedef ap_ufixed<11,6> h_dense_relu_quantizer_t;
typedef ap_fixed<20,10> h_dense_1_accum_t;
typedef ap_fixed<12,10> h_dense_1_t;
typedef ap_fixed<9,4> h_dense_1_weight_t;
typedef ap_fixed<20,10> h_dense_1_bias_t;
typedef ap_uint<1> layer8_index;
typedef ap_ufixed<10,8> re_lu_1_t;
typedef ap_fixed<18,8> re_lu_1_table_t;
typedef ap_ufixed<10,8> h_dense_1_relu_quantizer_t;
typedef ap_fixed<17,11> h_dense_2_accum_t;
typedef ap_fixed<13,11> h_dense_2_t;
typedef ap_fixed<7,3> h_dense_2_weight_t;
typedef ap_fixed<17,11> h_dense_2_bias_t;
typedef ap_uint<1> layer13_index;
typedef ap_ufixed<8,6> re_lu_2_t;
typedef ap_fixed<18,8> re_lu_2_table_t;
typedef ap_ufixed<8,6> h_dense_2_relu_quantizer_t;
typedef ap_fixed<15,7> h_dense_3_accum_t;
typedef ap_fixed<13,7> h_dense_3_t;
typedef ap_fixed<8,2> h_dense_3_weight_t;
typedef ap_fixed<15,7> h_dense_3_bias_t;
typedef ap_uint<1> layer18_index;
typedef ap_fixed<13,7> result_t;


#endif
