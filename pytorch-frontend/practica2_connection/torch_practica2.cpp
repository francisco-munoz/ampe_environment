#include <torch/extension.h>
#include "../../practica2/include/practica2.h"

#include <iostream>
#include <tuple>


torch::Tensor practica2_linear_forward(torch::Tensor input,  torch::Tensor weight) {
    //Here starts the function
    //Getting the data
    int input_n_dim = input.dim();
    int M = input.sizes()[input_n_dim-2]; // Batch size. The dimension previous to the last one
    int K = input.sizes()[input_n_dim-1]; //Number of input neurons. Last dimension
    int N = weight.sizes()[0]; //Number of output neurons 
    float* MK_input_raw = (float*) input.data_ptr();
    float* KN_weight_raw = (float*) weight.data_ptr();
	//Creating output tensor
    torch::Tensor output;
    if(input_n_dim == 2) {
        output = torch::rand({M, N}); //M is batch size and N is the number of output neurons
    }

    else {
        output = torch::rand({1, M, N});
    }

    float* output_raw = (float*) output.data_ptr();


    practica2Linear(MK_input_raw, KN_weight_raw, output_raw, M, K, N);
    return output;

   
}



PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("practica2_linear_forward", &practica2_linear_forward, "Linear forward implemented for practica 2");
}
