#include "matrix_network.h"

namespace s21 {
	
	MatrixNetwork::MatrixNetwork( int weightsCount, std::vector<float>& Slayer_input) {
        srand((unsigned)time(NULL));

		SLayer = Slayer_input;

		biases.assign(weightsCount, 1);

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
		} else {
            RLayer = tmp;
        }
	}

    std::vector<float> MatrixNetwork::solve_errors(int prediction) {
        std::vector<float> errors;
        for (int i = 0; i < R_NEURONS_COUNT; i++) {
            if (prediction-1 == i) {
                errors.push_back(1 - RLayer[i]);
            } else {
                errors.push_back(0 - RLayer[i]);
            }
        }
        return errors;
    }

    std::vector< float > MatrixNetwork::ComputeDelta(int prediction) {
        std::vector< float > delta;
        auto errorsLast = solve_errors(prediction);

        for (int i = 0; i != errorsLast.size(); ++i) {
            delta.push_back(abs(ActivateFunction::useDer(RLayer[i], 1) * errorsLast[i]));
        }

        float learningRate = 0.1;
        for (int i = 0; i != Weights[Weights.size()-1].size(); ++i) {
            for (int j = 0; j != Weights[Weights.size()-1][i].size(); ++j) {
                Weights[Weights.size()-1][i][j] =
                abs(Weights[Weights.size()-1][i][j] - ALayers[ALayers.size()-1][j] * delta[i] * learningRate);
            }
        }

//        std::vector< float > errors;
//        for


        return delta;
	}

//    void MatrixNetwork::CorrectRWeights( void ) {
//    }

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
