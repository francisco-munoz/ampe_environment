#include "../include/practica2.h"
#include <iostream>
#include <immintrin.h>

void practica2Linear(float* MK_matrix, float* KN_matrix, float* output_matrix, int M, int K, int N) {
     std::cout << "Running the code for optimized matrix multiplication" << std::endl;
     for(int i=0; i<M; i++) {
         for(int j=0; j<N; j++) {
	     float suma=0.0;
             for(int k=0; k<K; k++) {
	         suma+=MK_matrix[i*K+k]*KN_matrix[j*K+k];
	     }

	     output_matrix[i*N+j]=suma;
         }
     }
}

void practica2LinearSeq(float* MK_matrix, float* KN_matrix, float* output_matrix, int M, int K, int N) {
     std::cout << "Running the code for matrix multiplication" << std::endl;
     for(int i=0; i<M; i++) {
         for(int j=0; j<N; j++) {
             float suma=0.0;
             for(int k=0; k<K; k++) {
                 suma+=MK_matrix[i*K+k]*KN_matrix[j*K+k];
             }

             output_matrix[i*N+j]=suma;
         }
     }

}


