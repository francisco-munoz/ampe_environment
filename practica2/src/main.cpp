#include <iostream>
#include <chrono>
#include <assert.h>
#include <string>
#include <math.h>
#include "../include/practica2.h"

using namespace std;
using namespace std::chrono;



void configLinearParameters(int argc, char *argv[], unsigned int &M, unsigned int &K, unsigned int &N);

bool runLinearCommand(int argc, char *argv[]);
bool runHelpCommand();


int main(int argc, char *argv[]) {
    if(argc > 1) { //IF there is at least one parameter, -h is checked
        string arg = argv[1];
        if(arg=="-h") {
            runHelpCommand();
        }
      
        else if(arg=="-LINEAR") {
            runLinearCommand(argc, argv);
        }


	else {
	    std::cout << "How to use PRACTICA2 User Interface: ./" << argv[0] << " -h" << std::endl;
	}
    }

    else {
        std::cout << "How to use PRACTICA2 User Interface: ./" << argv[0] << " -h" << std::endl;
    }
}

bool runLinearCommand(int argc, char *argv[]) {
    float EPSILON=0.05;
    unsigned int MAX_RANDOM=10; //Variable used to generate the random values
    /** Generating the inputs and outputs **/

    unsigned int M=1;                                  // M
    unsigned int K=3;                                  // K
    unsigned int N=1;                                  // N

    configLinearParameters(argc, argv, M, K, N); 



    //Creating arrays to store the matrices
    unsigned int MK_size=M*K;
    unsigned int KN_size=N*K;
    unsigned int output_size=M*N;
    float* MK_matrix = (float*)aligned_alloc(32, MK_size * sizeof(float));
    float* KN_matrix = (float*)aligned_alloc(32, KN_size * sizeof(float));
    float* output = (float*)aligned_alloc(32, output_size * sizeof(float));;
    float* output_seq = (float*)aligned_alloc(32, output_size * sizeof(float));; //Used to store the CPU computed values to compare with the simulator version

    //Filling the arrays with random values
    for(int i=0; i<MK_size; i++) {
        MK_matrix[i]=rand()%MAX_RANDOM;
    }

    for(int i=0;i<KN_size; i++) {
        KN_matrix[i]=rand()%MAX_RANDOM;
    }

    //Computing the original version
    auto start_seq = high_resolution_clock::now(); 
    practica2LinearSeq(MK_matrix, KN_matrix, output_seq, M, K, N);
    auto stop_seq = high_resolution_clock::now(); 
    auto duration_seq = duration_cast<milliseconds>(stop_seq - start_seq); 

    //Computing the optimized version
    auto start_opt = high_resolution_clock::now();
    practica2Linear(MK_matrix, KN_matrix, output, M, K, N);
    auto stop_opt = high_resolution_clock::now();
    auto duration_opt = duration_cast<milliseconds>(stop_opt - start_opt);

    /** CHECKING the results to make sure that the output is correct  **/

    //Comparing the results
    for(int i=0;i<output_size; i++) {
        float difference=fabs(output[i]-output_seq[i]);
        if(difference > EPSILON) {
            std::cout << "ERROR position " << i <<  ": Value optimized: " << output[i] << ". Value sequential CPU: " << output_seq[i] << std::endl;
            std::cout << "\033[1;31mT test not passed\033[0m" << std::endl;
            free(MK_matrix);
            free(KN_matrix);
            free(output);
            free(output_seq);
            assert(false); //Always false
            
        }
    }


    //If the code does not stop then the TEST is correct
    std::cout << "\033[1;32mTest passed correctly \033[0m" << std::endl << std::endl;
    //Printing durations
    std::cout << "Time to compute sequential (original) version: " << duration_seq.count() << " milliseconds" << std::endl;
    std::cout << "Time to compute optimized version: " << duration_opt.count() <<  " milliseconds" << std::endl;
    std::cout << "Speedup optimized version: " << (float)((float)duration_seq.count() / (float)duration_opt.count()) << std::endl;

    free(MK_matrix);
    free(KN_matrix);
    free(output);
    free(output_seq);
    return true;
}

bool runHelpCommand() {
    std::cout << "Welcome to the PRACTICA2 User Interface Version 1.0: " << std::endl;
    std::cout << "***********************************************************************************************************" << std::endl;
    std::cout << "***********************************************************************************************************" << std::endl << std::endl;
    std::cout << "Usage: ./practica2_interface [-h | -LINEAR] [Dimensions]"  << std::endl;
    std::cout  << std::endl;
    std::cout << "[Dimensions]" << std::endl;
    std::cout << "-M=Number of rows MK matrix" << std::endl;
    std::cout << "-N=Number of columns KN matrix" << std::endl;
    std::cout << "-K=Number of columns MK and rows KN matrix (cluster size)" << std::endl;
    exit(0);
    return true; //Never executed
}

void configLinearParameters(int argc, char *argv[], unsigned int &M, unsigned int &K, unsigned int &N) {
  //Parsing
    for(int i=2; i<argc; i++) { //0 is the name of the program and 1 is the execution command ty
        string arg = argv[i];
        //Spliting using = character
        string::size_type pos = arg.find('=');
        if(arg.npos != pos) {
            string value_str=arg.substr(pos+1);
            string name=arg.substr(0, pos);
            unsigned int value;
            value=stoi(value_str);

	   if(name=="-M") {
                std::cout << "Changing M to " << value << std::endl;
                M=value;
           }

           else if(name=="-N") {
                std::cout << "Changing N to " << value << std::endl;
                N=value;
           }

           else if(name=="-K") {
                std::cout << "Changing K to " << value << std::endl;
                K=value;
           } 
        


           //Parameter is not recognized
           else {
                std::cout << "Error: parameter " << name << " does not exist" << std::endl;
                exit(1);
            }

 
    
           

        }
        else {

            std::cout << "Error: parameter " << arg << " does not exist" << std::endl;
            exit(1);

        }
    }  

}




