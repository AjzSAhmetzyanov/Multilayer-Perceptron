#include "matrix_network.h"

namespace s21 {
	
	MatrixNetwork::MatrixNetwork( int weightsCount, std::vector<double>& Slayer_input) {
        srand((unsigned)time(NULL));

		SLayer = Slayer_input;

		Weights.reserve(weightsCount);

		// Fill first weight level
		std::vector< std::vector< double > > first;
		for (int i = 0; i < A_NEURONS_COUNT; ++i) {
			std::vector< double > line;
			for (int j = 0; j != S_NEURONS_COUNT; ++j) {
				line.push_back(genRandomFloat(-1.0, 1.0));
			}
			first.push_back(line);
		}
		Weights.push_back(first);

		for (int weight_i = 0; weight_i != weightsCount-2; ++weight_i) {
			std::vector< std::vector< double > > hiddens;
			for (int i = 0; i < A_NEURONS_COUNT; ++i) {
				std::vector< double > line;
				for (int j = 0; j != A_NEURONS_COUNT; ++j) {
					line.push_back(genRandomFloat(-1.0, 1.0));
				}
				hiddens.push_back(line);
			}
			Weights.push_back(hiddens);
		}

		std::vector< std::vector< double > > last;
		for (int i = 0; i < R_NEURONS_COUNT; ++i) {
			std::vector< double > line;
			for (int j = 0; j != A_NEURONS_COUNT; ++j) {
				line.push_back(genRandomFloat(-1.0, 1.0));
			}
			last.push_back(line);
		}
		Weights.push_back(last);
	}

	void MatrixNetwork::MultiplyWeights( const std::vector< double >& prevLayer, int weightInd ) {
		std::vector< double > tmp;
		for (int j = 0; j != Weights[weightInd].size(); ++j) {
            double sum = 1;
			for (int i = 0; i != prevLayer.size(); ++i) {
				sum += Weights[weightInd][j][i] * prevLayer[i];
			}
//            std::cout << ' ' << std::endl;
			tmp.push_back(ActivateFunction::use(sum, 1));
		}
		if (weightInd < Weights.size()-1) {
			ALayers.push_back(tmp);
		} else {
            RLayer = tmp;
        }
	}

    std::vector<double> MatrixNetwork::solve_errors(int prediction) {
        std::vector<double> errors;
        double system_errors = 0;
        for (int i = 0; i < R_NEURONS_COUNT; i++) {
            if (prediction-1 == i) {
                errors.push_back(1 - RLayer[i]);
            } else {
                errors.push_back(0 - RLayer[i]);
            }
        }

        for (int i = 0; i < R_NEURONS_COUNT; i++) {
            system_errors += (errors[i] * errors[i]);
        }
        std::cout << system_errors << std::endl;
            return errors;
    }

    std::vector< double > MatrixNetwork::ComputeDelta(int prediction) {
        std::vector< double > delta_r;
        std::vector< double > delta_l_last;
        std::vector< double > delta_h_last;
        auto errorsLast = solve_errors(prediction);

        for (int i = 0; i != errorsLast.size(); ++i) {
            delta_r.push_back(ActivateFunction::useDer(RLayer[i], 1) * errorsLast[i]);
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            double sum = 0;
            for (int j = 0; j != R_NEURONS_COUNT; ++j) {
                    sum += delta_r[j] * Weights[Weights.size() - 1][j][i];
                    }
                delta_l_last.push_back(sum);
            }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
                delta_h_last.push_back(delta_l_last[i]*ActivateFunction::useDer(ALayers[ALayers.size()-1][i], 1));
        }

        float learningRate = 0.15;
        for (int i = 0; i != R_NEURONS_COUNT; ++i) {
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                Weights[Weights.size()-1][i][j] =
                Weights[Weights.size()-1][i][j] - ALayers[ALayers.size()-1][i] * delta_h_last[i] * learningRate;
            }
        } //ok

        std::vector< double > delta_h_c_p;
        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            double sum = 0;
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                sum += delta_h_last[j] * Weights[Weights.size() - 2][j][i];
            }
            delta_h_c_p.push_back(sum);
        }

        std::vector< double > delta_h_p;
        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            delta_h_p.push_back(delta_l_last[i]*ActivateFunction::useDer(ALayers[ALayers.size()-2][i], 1));
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                Weights[Weights.size()-2][i][j] =
                        Weights[Weights.size()-2][i][j] - ALayers[ALayers.size()-2][i] * delta_h_p[i] * learningRate;
            }
        } //ok

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            double sum = 0;
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                sum += delta_h_p[j] * Weights[Weights.size() - 3][j][i];
            }
            delta_h_c_p.push_back(sum);
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            delta_h_p.push_back(delta_h_c_p[i]*ActivateFunction::useDer(ALayers[ALayers.size()-3][i], 1));
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                Weights[Weights.size()-3][i][j] =
                        Weights[Weights.size()-3][i][j] - ALayers[ALayers.size()-3][i] * delta_h_p[i] * learningRate;
            }
        } //ok

        for (int i = 0; i != S_NEURONS_COUNT; ++i) {
            double sum = 0;
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                sum += delta_h_p[j] * Weights[Weights.size() - 4][j][i];
            }
            delta_h_c_p.push_back(sum);
        }

        for (int i = 0; i != S_NEURONS_COUNT; ++i) {
            delta_h_p.push_back(delta_h_c_p[i]*ActivateFunction::useDer(SLayer[i], 1));
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            for (int j = 0; j != S_NEURONS_COUNT; ++j) {
                Weights[Weights.size()-4][i][j] =
                        Weights[Weights.size()-4][i][j] - SLayer[i] * delta_h_p[i] * learningRate;
            }
        } //ok
        return delta_r;
	}

    std::vector< double > MatrixNetwork::getSLayer( void ) const {
        return SLayer;
    }

	void MatrixNetwork::setSLayer( const std::vector< double >& newSLayer ) {
		SLayer = newSLayer;
	}

	std::vector< double > MatrixNetwork::getRLayer( void ) const {
		return RLayer;
	}

	void MatrixNetwork::setRLayer( const std::vector< double >& newRLayer ) {
		RLayer = newRLayer;
	}

	std::vector< std::vector< double > > MatrixNetwork::getALayers( void ) const {
		return ALayers;
	}
		
	void MatrixNetwork::setALayers( const std::vector< std::vector< double > >& newALayers) {
		ALayers = newALayers;
	}

	 std::vector< std::vector< std::vector< double > > > MatrixNetwork::getWeights( void ) const {
	 	return Weights;
	 }
	
	 void MatrixNetwork::setWeights( std::vector< std::vector< std::vector< double > > >&  newWeights) {
	 	Weights = newWeights;
	 }

	void MatrixNetwork::fillSLayer( int neuronsCount ) {
		SLayer.reserve(neuronsCount);
		for (int i = 0; i < neuronsCount; ++i) {	
			SLayer.push_back(genRandomFloat(-1,1));
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

    double genRandomFloat( double min, double max ) {
//        double r = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX));
        double value;
        value = rand() % (int)pow(10, 3);

        // получить вещественное число
        value = min + (value / pow(10, 3)) * (max - min);
        return value;
    }

} // namespace s21

