#ifndef MATRIX_NETWORK_H
# define MATRIX_NETWORK_H

# include <vector>
# include <iostream>
# include <random>
#include "../S21_Matrix/s21_matrix_oop.h"


enum layers{S_NEURONS_COUNT = 512, A_NEURONS_COUNT = 140, \
R_NEURONS_COUNT = 26, A_LAYERS_COUNT = 5, WEIGHTS_COUNT = 6};

namespace s21 {

	class MatrixNetwork {
	public:
        using s21_matrix = std::vector<S21Matrix>;
        using vector_double = std::vector<double>;
        void feed_init_value(const vector_double &values);

		MatrixNetwork( void );

		std::vector< float > getSLayer( void ) const;
		void setSLayer( const std::vector< float >& );

		std::vector< std::vector< float > > getALayers( void ) const;
		void setALayers( const std::vector< std::vector< float > >& );

		std::vector< std::vector< std::vector< float > > > getWeights( void ) const;
		void setWeights( std::vector< std::vector< std::vector< float > > >& );
    private:
        s21_matrix m_neurons_;
        s21_matrix m_weights_;
        vector_double m_biases_;
        static constexpr double step_ = 0.08;

        std::vector< float > SLayer;
        std::vector< std::vector< float > > ALayers;
        std::vector< std::vector< std::vector< float > > > Weights;

        void fillSLayer( int );
        void fillALayers( int, int );
        void fillWeights( int, int );
	};

	std::ostream& operator<<(std::ostream &out, const MatrixNetwork &obj);

	float genRandomFloat( void );
	
} // namespace s21



#endif