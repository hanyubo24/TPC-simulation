#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ap_fixed.h"
#include "ap_int.h"

#include "nnet_utils/nnet_code_gen.h"
#include "nnet_utils/nnet_helpers.h"
// hls-fpga-machine-learning insert includes
#include "nnet_utils/nnet_activation.h"
#include "nnet_utils/nnet_activation_stream.h"
#include "nnet_utils/nnet_dense.h"
#include "nnet_utils/nnet_dense_compressed.h"
#include "nnet_utils/nnet_dense_stream.h"

// hls-fpga-machine-learning insert weights
#include "weights/w3.h"
#include "weights/b3.h"
#include "weights/w8.h"
#include "weights/b8.h"
#include "weights/w13.h"
#include "weights/b13.h"
#include "weights/w18.h"
#include "weights/b18.h"


// hls-fpga-machine-learning insert layer-config
// h_dense
struct config3 : nnet::dense_config {
    static const unsigned n_in = 16;
    static const unsigned n_out = 64;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 672;
    static const unsigned n_nonzeros = 352;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef h_dense_accum_t accum_t;
    typedef h_dense_bias_t bias_t;
    typedef h_dense_weight_t weight_t;
    typedef layer3_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseLatency<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// re_lu
struct ReLU_config6 : nnet::activ_config {
    static const unsigned n_in = 64;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef re_lu_table_t table_t;
};

// h_dense_1
struct config8 : nnet::dense_config {
    static const unsigned n_in = 64;
    static const unsigned n_out = 32;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 1765;
    static const unsigned n_nonzeros = 283;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef h_dense_1_accum_t accum_t;
    typedef h_dense_1_bias_t bias_t;
    typedef h_dense_1_weight_t weight_t;
    typedef layer8_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseLatency<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// re_lu_1
struct ReLU_config11 : nnet::activ_config {
    static const unsigned n_in = 32;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef re_lu_1_table_t table_t;
};

// h_dense_2
struct config13 : nnet::dense_config {
    static const unsigned n_in = 32;
    static const unsigned n_out = 32;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 876;
    static const unsigned n_nonzeros = 148;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef h_dense_2_accum_t accum_t;
    typedef h_dense_2_bias_t bias_t;
    typedef h_dense_2_weight_t weight_t;
    typedef layer13_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseLatency<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// re_lu_2
struct ReLU_config16 : nnet::activ_config {
    static const unsigned n_in = 32;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef re_lu_2_table_t table_t;
};

// h_dense_3
struct config18 : nnet::dense_config {
    static const unsigned n_in = 32;
    static const unsigned n_out = 5;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 97;
    static const unsigned n_nonzeros = 63;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef h_dense_3_accum_t accum_t;
    typedef h_dense_3_bias_t bias_t;
    typedef h_dense_3_weight_t weight_t;
    typedef layer18_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseLatency<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};



#endif
