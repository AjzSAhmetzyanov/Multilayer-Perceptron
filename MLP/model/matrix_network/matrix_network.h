#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>
# include <cmath>
#include <time.h>
#include <algorithm>

# include "../acivate_funcs/activate_func.h"


# define S_NEURONS_COUNT 784
# define A_NEURONS_COUNT 140
# define R_NEURONS_COUNT 26
// # define A_LAYERS_COUNT 5
// # define WEIGHTS_COUNT 6


namespace s21 {

	class MatrixNetwork {
	private:
		std::vector< double > SLayer;
		std::vector< std::vector< double > > ALayers;
		std::vector< double > RLayer;
		std::vector< std::vector< std::vector< double > > > Weights;
		std::vector< double > biases;


        void fillSLayer( int );
		// void fillALayers( int, int );
		void fillWeights( int, int );

	public:
		MatrixNetwork( int , std::vector<double> & );



        std::vector<double> solve_errors( int );
        std::vector< double > ComputeDelta( int );
        void CorrectRWeights( void );

		std::vector< double > getSLayer( void ) const;
		void setSLayer( const std::vector< double >& );

		std::vector< double > getRLayer( void ) const;
		void setRLayer( const std::vector< double >& );

		std::vector< std::vector< double > > getALayers( void ) const;
		void setALayers( const std::vector< std::vector< double > >& );

		std::vector< std::vector< std::vector< double > > > getWeights( void ) const;
		void setWeights( std::vector< std::vector< std::vector< double > > >& );

		void MultiplyWeights( const std::vector< double >&, int );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

    double genRandomFloat( double, double );
	
} // namespace s21



#endif