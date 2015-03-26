#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm> 
#include "gausselimination.h"

// instances and their corresponding correct results
static const std::string testMatrices[] = {"[4,5]((2,-3,-1,2,3),(4,-4,-1,4,11),(2,-5,-2,2,-1),(0,2,1,0,4))\0",
										   "[3,3]((0,1,2),(1,-2,-3),(-1,1,2))\0",
												};
static const std::string correctOutput[] = {"[4,5]((4,-4,-1,4,11),(0,-3,-1.5,0,-6.5),(0,0,1,0,4),(0,0,0,0,-0.33))\0",
										    "[3,3]((1,-2,-3),(0,1,2),(0,0,1))\0",
											};

bool isrowechelonform(){
	using namespace boost::numeric::ublas;
	int num = 2;
	bool res;
	matrix<float> mat;
	matrix<float> outp;
  matrix<float> diff;
	
	for (int i=0; i<num; i++) {
		{
		std::istringstream is(testMatrices[i]);
		is >> mat;} 
		{
		std::istringstream is(correctOutput[i]);
		is >> outp;} 
    
    // apply the Gaussian Elimination function to change the matrix
		applygauselimination(mat);
		
		// compute the difference between the expected output and the modified matrix
		diff = outp-mat;
		bool f = false;
		for (int k=0; k<diff.size1() && !f; k++){
			for (int j=0; j<diff.size2(); j++) {
				if (diff(k,j) != 0 ) {
					std::cout<< "Error! The output is not correct!"<<std::endl;
					std::cout<<i;
					res = false;
					f = true;
					break;
				}
				else 
					res = true;
			}
		}

	} 
	return res;

	
	
}
