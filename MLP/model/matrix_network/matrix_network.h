#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>


# define S_NEURONS_COUNT 512
# define A_NEURONS_COUNT 140
# define R_NEURONS_COUNT 26
# define A_LAYERS_COUNT 5
# define WEIGHTS_COUNT 6

namespace s21
{

	class MatrixNetwork {
	private:
		std::vector< float > SLayer;
		std::vector< std::vector< float > > ALayers;
		std::vector< std::vector< std::vector< float > > > Weights;

		void fillSLayer( int );
		void fillALayers( int, int );
		void fillWeights( int, int );

	public:
		MatrixNetwork( void );

		std::vector< float > getSLayer( void ) const;
		void setSLayer( const std::vector< float >& );

		std::vector< std::vector< float > > getALayers( void ) const;
		void setALayers( const std::vector< std::vector< float > >& );

		std::vector< std::vector< std::vector< float > > > getWeights( void ) const;
		void setWeights( std::vector< std::vector< std::vector< float > > >& );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

	float genRandomFloat( void );
	
} // namespace s21



#endif