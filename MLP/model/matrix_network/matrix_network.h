#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>


# define S_NEURONS_COUNT 10
# define A_NEURONS_COUNT 4
// # define R_NEURONS_COUNT 26
// # define A_LAYERS_COUNT 5
# define WEIGHTS_COUNT 6

namespace s21
{

	class MatrixNetwork {
	private:
		std::vector< float > SLayer;
		std::vector< float > ALayer1;
		std::vector< std::vector< std::vector< float > > > Weights;
		std::vector< float > biases;

		void fillSLayer( int );
		// void fillALayers( int, int );
		void fillWeights( int, int );

	public:
		MatrixNetwork( void );

		std::vector< float > getSLayer( void ) const;
		void setSLayer( const std::vector< float >& );

		// std::vector< std::vector< float > > getALayers( void ) const;
		// void setALayers( const std::vector< std::vector< float > >& );

		std::vector< std::vector< float > > getWeights1( void ) const;
		void setWeights( std::vector< std::vector< std::vector< float > > >& );

		void MultiplyWeights( const std::vector< float >&, int );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

	float genRandomFloat( void );
	
} // namespace s21



#endif