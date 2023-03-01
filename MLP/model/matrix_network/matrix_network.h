#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>
# include <cmath>

# include "../acivate_funcs/activate_func.h"


# define S_NEURONS_COUNT 10
# define A_NEURONS_COUNT 4
# define R_NEURONS_COUNT 26
// # define A_LAYERS_COUNT 5
// # define WEIGHTS_COUNT 6


namespace s21
{

	class MatrixNetwork {
	private:
		std::vector< float > SLayer;
		std::vector< std::vector< float > > ALayers;
		std::vector< float > RLayer;
		std::vector< std::vector< std::vector< float > > > Weights;
		std::vector< float > biases;


        void fillSLayer( int );
		// void fillALayers( int, int );
		void fillWeights( int, int );

	public:
		MatrixNetwork( int , std::vector<float> & );



        std::vector<float> solve_errors( int );
        std::vector< float > ComputeDelta( int );
        void CorrectRWeights( void );

		std::vector< float > getSLayer( void ) const;
		void setSLayer( const std::vector< float >& );

		std::vector< float > getRLayer( void ) const;
		void setRLayer( const std::vector< float >& );

		std::vector< std::vector< float > > getALayers( void ) const;
		void setALayers( const std::vector< std::vector< float > >& );

		std::vector< std::vector< std::vector< float > > > getWeights( void ) const;
		void setWeights( std::vector< std::vector< std::vector< float > > >& );

		void MultiplyWeights( const std::vector< float >&, int );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

	float genRandomFloat( void );
	
} // namespace s21



#endif