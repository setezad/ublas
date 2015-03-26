
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <algorithm> 


template <class T>
void applygauselimination (T &m) {
	/*
	The psuedocode in Wikipedia has been used:
	http://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode 
	*/
	using namespace boost::numeric::ublas;

	int row = m.size1();
	int col = m.size2();
	int min = std::min(row, col);

	float value;
    double alpha;
    int rmax;

	    for (int i=0; i<min; i++ ){
			value = 0;
			for (int h=i; h<min; h++){
				if (std::abs(m(h,i))>value) {
					value = std::abs(m(h,i));
					rmax = h;
				}
			}

			if (m(rmax,i) == 0) {
				std::cout<<"Error: Matrix is singular!"<<std::endl;
			}
			// swap rows using ublas embedded functions
			matrix_row<T> rmax_row (m, rmax);
			matrix_row<T> i_row (m, i);
			swap(i_row, rmax_row);

			for (int j=i+1; j<row; j++) {
				for (int d=i+1; d<col; d++) {
					alpha = m(j,i)/m(i,i);
					// prefered precision
					if (alpha <1e-5 ) {
						alpha = 0;
					}
					m(j,d) -= m(i,d)*alpha;
					
				}
				m(j,i) = 0;
			}

		}


}
