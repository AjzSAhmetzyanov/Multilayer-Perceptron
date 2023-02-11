#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>


# define S_NEURONS_COUNT 512
# define A_NEURONS_COUNT 140
# define R_LAYERS_COUNT 26
# define A_LAYERS_COUNT 5

namespace s21
{

	class MatrixNetwork {
	private:
		std::vector< std::vector< float > > SLayer;
		std::vector< std::vector< float > > ALayers;

		void fillSLayer( void );
		void fillALayers( int layersCount );

	public:
		MatrixNetwork( void );

		std::vector< std::vector< float > > getSLayer( void ) const;
		void setSLayer( const std::vector< std::vector< float > >& );

		std::vector< std::vector< float> > getALayers( void ) const;
		void setALayers( const std::vector< std::vector<float> >& );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

	float genRandomFloat( void );
	
} // namespace s21



#endif