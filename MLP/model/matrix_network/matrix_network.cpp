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
        std::vector<double> system_errors;
        for (int i = 0; i < R_NEURONS_COUNT; i++) {
            if (prediction-1 == i) {
                errors.push_back((1 - RLayer[i])*(1 - RLayer[i]));
            } else {
                errors.push_back((0 - RLayer[i])*(0 - RLayer[i]));
            }
        }
        for (int i = 0; i < R_NEURONS_COUNT; i++) {
            system_errors.push_back(errors[i] * errors[i]);
        }
        for (auto & i : errors)
            std::cout << i << std::endl;
        std::cout << std::max_element(system_errors.begin(), system_errors.end()) - system_errors.begin();
        std::cout << "......................."<<std::endl;
            return errors;
    }

    std::vector< double > MatrixNetwork::ComputeDelta(int prediction) {
        std::vector< double > delta_r;
        std::vector< double > delta_l_last;
        std::vector< double > delta_h_last;
        std::vector< double > temp;
        auto errorsLast = solve_errors(prediction);

        for (int i = 0; i != errorsLast.size(); ++i) {
            temp.push_back(ActivateFunction::useDer(RLayer[i], 1) * errorsLast[i]);
        }
        delta_r = temp;
        temp.clear();

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            double sum = 0;
            for (int j = 0; j != R_NEURONS_COUNT; ++j) {
                    sum += delta_r[j] * Weights[Weights.size() - 1][j][i];
                    }
                temp.push_back(sum);
            }
        delta_l_last = temp;
        temp.clear();

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
                temp.push_back(delta_l_last[i]*ActivateFunction::useDer(ALayers[ALayers.size()-1][i], 1));
        }
        delta_h_last = temp;
        temp.clear();

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
            temp.push_back(sum);
        }
        delta_h_c_p = temp;
        temp.clear();

        std::vector< double > delta_h_p;
        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            temp.push_back(delta_l_last[i]*ActivateFunction::useDer(ALayers[ALayers.size()-2][i], 1));
        }
        delta_h_p = temp;
        temp.clear();

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
            temp.push_back(sum);
            delta_h_c_p = temp;
            temp.clear();
        }

        for (int i = 0; i != A_NEURONS_COUNT; ++i) {
            temp.push_back(delta_h_c_p[i]*ActivateFunction::useDer(ALayers[ALayers.size()-3][i], 1));
        }
        delta_h_p = temp;
        temp.clear();

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
            temp.push_back(sum);
            delta_h_c_p = temp;
            temp.clear();
        }

        for (int i = 0; i != S_NEURONS_COUNT; ++i) {
            temp.push_back(delta_h_c_p[i]*ActivateFunction::useDer(SLayer[i], 1));
        }
        delta_h_p = temp;
        temp.clear();

        for (int i = 0; i != S_NEURONS_COUNT; ++i) {
            for (int j = 0; j != A_NEURONS_COUNT; ++j) {
                Weights[Weights.size()-4][j][i] =
                        Weights[Weights.size()-4][j][i] - SLayer[i] * delta_h_p[i] * learningRate;
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

    double genRandomFloat( double min, double max ) {
        double value;
        value = rand() % (int)pow(10, 2);
        value = min + (value / pow(10, 2)) * (max - min);
        return value;
    }

} // namespace s21


