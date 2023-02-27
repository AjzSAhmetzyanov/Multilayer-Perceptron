#include "matrix_network.h"

namespace s21
{
	
	MatrixNetwork::MatrixNetwork( int weightsCount ) {
		srand((unsigned)time(NULL));

		fillSLayer(S_NEURONS_COUNT);

		biases.assign(weightsCount, 0.0);

		Weights.reserve(weightsCount);

		// Fill first weight level
		std::vector< std::vector< float > > first;
		for (int i = 0; i < A_NEURONS_COUNT; ++i) {
			std::vector< float > line;
			for (int j = 0; j != S_NEURONS_COUNT; ++j) {
				line.push_back(genRandomFloat());
			}
			first.push_back(line);
		}
		Weights.push_back(first);

		for (int weight_i = 0; weight_i != weightsCount-2; ++weight_i) {
			std::vector< std::vector< float > > hiddens;
			for (int i = 0; i < A_NEURONS_COUNT; ++i) {
				std::vector< float > line;
				for (int j = 0; j != A_NEURONS_COUNT; ++j) {
					line.push_back(genRandomFloat());
				}
				hiddens.push_back(line);
			}
			Weights.push_back(hiddens);
		}

		std::vector< std::vector< float > > last;
		for (int i = 0; i < R_NEURONS_COUNT; ++i) {
			std::vector< float > line;
			for (int j = 0; j != A_NEURONS_COUNT; ++j) {
				line.push_back(genRandomFloat());
			}
			last.push_back(line);
		}
		Weights.push_back(last);

		// std::cout << Weights.size();

		// for (int i = 0; i != Weights[0].size(); ++i) {
		// 	for (int j = 0; j != Weights[0][i].size(); ++j) {
		// 		std::cout << Weights[0][i][j] << " ";
		// 	}
		// 	std::cout << std::endl;
		// }

		// for (int w = 1; w != Weights.size()-1; ++w) {
		// 	std::cout << "ALayer-" << w << std::endl;
		// 	for (int i = 0; i != Weights[w].size(); ++i) {
		// 		for (int j = 0; j != Weights[w][i].size(); ++j) {
		// 			std::cout << Weights[0][i][j] << " ";
		// 		}
		// 		std::cout << std::endl;
		// 	}
		// 	std::cout << "-------------------------------------\n";
		// }

		// for (int i = 0; i != Weights[Weights.size()-1].size(); ++i) {
		// 	for (int j = 0; j != Weights[Weights.size()-1][i].size(); ++j) {
		// 		std::cout << Weights[Weights.size()-1][i][j] << " ";
		// 	}
		// 	std::cout << std::endl;
		// }
	}

	void MatrixNetwork::MultiplyWeights( const std::vector< float >& prevLayer, int weightInd ) {
		std::vector< float > tmp;
		for (int j = 0; j != Weights[weightInd].size(); ++j) {
			float sum = 0;
			for (int i = 0; i != prevLayer.size(); ++i) {
				sum += Weights[weightInd][j][i] * prevLayer[i] + biases[weightInd];
			}
			tmp.push_back(ActivateFunction::use(sum, 1));
		}
		if (weightInd < Weights.size()-1) {
			ALayers.push_back(tmp);
		}

		// for (int i = 0; i != prevLayer.size(); ++i) {
		// 	std::cout << prevLayer[i] << " ";
		// }
		// std::cout << std::endl;
		// std::cout << "--------------------------------------------\n";

		// for (const auto & weights : Weights[weightInd]) {
		// 	for (auto elem : weights) {
		// 		std::cout << elem << " ";
		// 	}
		// 	std::cout << std::endl;
		// }
		// std::cout << "--------------------------------------------\n";

		// for (int i = 0; i != tmp.size(); ++i) {
		// 	std::cout << tmp[i] << " ";
		// }
		// std::cout << std::endl;

		// std::cout << "___________________________________________________________________________\n";

	}

	std::vector< float > MatrixNetwork::getSLayer( void ) const {
		return SLayer;
	}

	void MatrixNetwork::setSLayer( const std::vector< float >& newSLayer ) {
		SLayer = newSLayer;
	}

	std::vector< float > MatrixNetwork::getRLayer( void ) const {
		return RLayer;
	}

	void MatrixNetwork::setRLayer( const std::vector< float >& newRLayer ) {
		RLayer = newRLayer;
	}

	std::vector< std::vector< float > > MatrixNetwork::getALayers( void ) const {
		return ALayers;
	}
		
	void MatrixNetwork::setALayers( const std::vector< std::vector< float > >& newALayers) {
		ALayers = newALayers;
	}

	// std::vector< std::vector< float > > MatrixNetwork::getWeights1( void ) const {
	// 	return Weights1;
	// }	
	
	// void MatrixNetwork::setWeights1( std::vector< std::vector< float > >&  newWeights) {
	// 	Weights1 = newWeights;
	// }

	void MatrixNetwork::fillSLayer( int neuronsCount ) {
		SLayer.reserve(neuronsCount);
		for (int i = 0; i < neuronsCount; ++i) {	
			SLayer.push_back(genRandomFloat());
		}
	}

	// void MatrixNetwork::fillALayers( int layersCount, int neuronsCount ) {
	// 	ALayers.reserve(layersCount);
	// 	for (int l_i = 0; l_i < layersCount; ++l_i) {
	// 		std::vector<float> vec;
	// 		vec.reserve(neuronsCount);

	// 		for (int j = 0; j < neuronsCount; ++j) {
	// 			vec.push_back(genRandomFloat());
	// 		}
			
	// 		ALayers.push_back(vec);
	// 	}
	// }

	// void MatrixNetwork::fillWeights1( int prevLayerNeuronsCount, int nextLayerNeuronsCount) {
	// 	std::vector< std::vector< float > > weights;
	// 	weights.reserve(prevLayerNeuronsCount);

	// 	for (int j = 0; j < prevLayerNeuronsCount; ++j) {
	// 		std::vector< float > weight;
	// 		weight.reserve(nextLayerNeuronsCount);

	// 		for (int k = 0; k < nextLayerNeuronsCount; ++k) {
	// 			weight.push_back(genRandomFloat());
	// 		}

	// 		weights.push_back(weight);
	// 	}

	// 	Weights1.push_back(weights);
	// }

	// std::ostream& operator<<( std::ostream &out, const MatrixNetwork &obj ) {
	// 	out << "---------------- S-Layer ----------------" << std::endl;
	// 	for (float value : obj.getSLayer()) {
	// 		out << value << ' ';
	// 	}
	// 	out << std::endl;

	// 	int i = 1;
	// 	for (const auto& layer : obj.getALayers()) {
	// 		out << "---------------- A-Layer-" << i << " ----------------" << std::endl;

	// 		for (float value : layer) {
	// 			out << value << ' ';
	// 		}
	// 		out << std::endl;

	// 		++i;
	// 	}

	// 	i = 1;
	// 	for (const auto& weight : obj.getWeights()) {
	// 		out << "---------------- Weight-" << i << " ----------------" << std::endl;

	// 		for (const auto& row : weight) {
	// 			for (float value : row) {
	// 				out << value << ' ';
	// 			}
	// 			out << std::endl;
	// 		}

	// 		++i;
	// 	}

	// 	return out;
	// }

	float genRandomFloat( void ) {
		float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
		return (int)(100 * r) / 100.0;
	}

} // namespace s21
