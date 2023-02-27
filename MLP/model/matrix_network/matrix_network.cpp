#include "matrix_network.h"

namespace s21
{
	
	MatrixNetwork::MatrixNetwork( void ) {
		fillSLayer(S_NEURONS_COUNT);
		fillALayers(A_LAYERS_COUNT, A_LAYERS_COUNT);
		Weights.reserve(WEIGHTS_COUNT);
		fillWeights(S_NEURONS_COUNT, A_NEURONS_COUNT);
		for (int i = 0; i < WEIGHTS_COUNT-2; ++i) {
			fillWeights(A_NEURONS_COUNT, A_NEURONS_COUNT);
		}
		fillWeights(A_NEURONS_COUNT, R_NEURONS_COUNT);
	}

	std::vector< float > MatrixNetwork::getSLayer( void ) const {
		return SLayer;
	}

	void MatrixNetwork::setSLayer( const std::vector< float >& newSLayer ) {
		SLayer = newSLayer;
	}

	std::vector< std::vector< float > > MatrixNetwork::getALayers( void ) const {
		return ALayers;
	}
		
	void MatrixNetwork::setALayers( const std::vector< std::vector< float > >& newALayers) {
		ALayers = newALayers;
	}

	std::vector< std::vector< std::vector< float > > > MatrixNetwork::getWeights( void ) const {
		return Weights;
	}	
	
	void MatrixNetwork::setWeights( std::vector< std::vector< std::vector< float > > >&  newWeights) {
		Weights = newWeights;
	}

	void MatrixNetwork::fillSLayer( int neuronsCount ) {
		SLayer.reserve(neuronsCount);
		for (int i = 0; i < neuronsCount; ++i) {	
			SLayer.push_back(genRandomFloat());
		}
	}

	void MatrixNetwork::fillALayers( int layersCount, int neuronsCount ) {
		ALayers.reserve(layersCount);
		for (int l_i = 0; l_i < layersCount; ++l_i) {
			std::vector<float> vec;
			vec.reserve(neuronsCount);

			for (int j = 0; j < neuronsCount; ++j) {
				vec.push_back(genRandomFloat());
			}
			
			ALayers.push_back(vec);
		}
	}

	void MatrixNetwork::fillWeights( int prevLayerNeuronsCount, int nextLayerNeuronsCount) {
		std::vector< std::vector< float > > weights;
		weights.reserve(prevLayerNeuronsCount);

		for (int j = 0; j < prevLayerNeuronsCount; ++j) {
			std::vector< float > weight;
			weight.reserve(nextLayerNeuronsCount);

			for (int k = 0; k < nextLayerNeuronsCount; ++k) {
				weight.push_back(genRandomFloat());
			}

			weights.push_back(weight);
		}

		Weights.push_back(weights);
	}

	std::ostream& operator<<( std::ostream &out, const MatrixNetwork &obj ) {
		out << "---------------- S-Layer ----------------" << std::endl;
		for (float value : obj.getSLayer()) {
			out << value << ' ';
		}
		out << std::endl;

		int i = 1;
		for (const auto& layer : obj.getALayers()) {
			out << "---------------- A-Layer-" << i << " ----------------" << std::endl;

			for (float value : layer) {
				out << value << ' ';
			}
			out << std::endl;

			++i;
		}

		i = 1;
		for (const auto& weight : obj.getWeights()) {
			out << "---------------- Weight-" << i << " ----------------" << std::endl;

			for (const auto& row : weight) {
				for (float value : row) {
					out << value << ' ';
				}
				out << std::endl;
			}

			++i;
		}

		return out;
	}

	float genRandomFloat( void ) {
		float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
		return (int)(100 * r) / 100.0;
	}

} // namespace s21
