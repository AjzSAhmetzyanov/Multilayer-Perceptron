#include "matrix_network.h"

namespace s21
{
	
	MatrixNetwork::MatrixNetwork( void ) {
		fillSLayer();
		fillALayers(A_LAYERS_COUNT);
	}

	std::vector< std::vector< float > > MatrixNetwork::getSLayer( void ) const {
		return SLayer;
	}

	void MatrixNetwork::setSLayer( const std::vector< std::vector< float > >& newSLayer ) {
		SLayer = newSLayer;
	}

	std::vector< std::vector< float > > MatrixNetwork::getALayers( void ) const {
		return ALayers;
	}
		
	void MatrixNetwork::setALayers( const std::vector< std::vector< float > >& newALayers) {
		ALayers = newALayers;
	}

	void MatrixNetwork::fillSLayer( void ) {
		SLayer.reserve(S_NEURONS_COUNT);
		for (int i = 0; i < S_NEURONS_COUNT; ++i) {
			std::vector<float> vec;
			vec.reserve(S_NEURONS_COUNT);

			for (int j = 0; j < S_NEURONS_COUNT; ++j) {
				vec.push_back(genRandomFloat());
			}
			
			SLayer.push_back(vec);
		}
	}

	void MatrixNetwork::fillALayers( int layersCount ) {
		ALayers.reserve(A_LAYERS_COUNT);
		for (int l_i = 0; l_i < A_LAYERS_COUNT; ++l_i) {
			std::vector<float> vec;
			vec.reserve(A_NEURONS_COUNT);

			for (int j = 0; j < A_NEURONS_COUNT; ++j) {
				vec.push_back(genRandomFloat());
			}
			
			ALayers.push_back(vec);
		}
	}

	std::ostream& operator<<( std::ostream &out, const MatrixNetwork &obj ) {
		out << "---------------- S-Layer ----------------" << std::endl;
		for (const auto& row : obj.getSLayer()) {
			for (float value : row) {
				out << value << ' ';
			}
			out << std::endl;
		}

		int i = 1;
		for (const auto& layer : obj.getALayers()) {
			out << "---------------- A-Layer-" << i << " ----------------" << std::endl;

			for (float value : layer) {
				out << value << ' ';
			}
			out << std::endl;

			++i;
		}

		return out;
	}

	float genRandomFloat( void ) {
		float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
		return (int)(100 * r) / 100.0;
	}

} // namespace s21
