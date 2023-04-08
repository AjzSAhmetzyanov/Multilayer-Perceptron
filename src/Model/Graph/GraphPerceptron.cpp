//
// Created by Luigi Ketter on 3/22/23.
//

#include "GraphPerceptron.h"
using namespace s21;
void GraphPerceptron::init(int data) {
  actFunc.set();
  L = data;
  size.resize(data);
  size[0] = 784;
  for (int i = 1; i < L - 1; i++) size[i] = 140;
  size[L - 1] = 26;
  weights.resize(L - 1);
  for (int i = 0; i < L - 1; i++) {
    weights[i].init(size[i + 1], size[i]);
    weights[i].rand_();
  }
  neurons_val.resize(L);
  delta.resize(L);
  for (int i = 0; i < L; i++) {
    neurons_val[i].resize(size[i]);
    delta[i].resize(size[i]);
  }
}

std::vector<std::vector<std::string>> GraphPerceptron::read_file(
    std::string &fname) {
  std::vector<std::vector<std::string>> content;
  std::vector<std::string> row;
  std::string line, word;
  std::fstream file(fname, std::ios::in);
  if (file.is_open()) {
    std::cout << "reading file" << fname << std::endl;
    while (getline(file, line)) {
      row.clear();
      std::stringstream str(line);
      while (getline(str, word, ',')) row.push_back(word);
      content.push_back(row);
    }
  } else
    std::cout << "Could not open the file\n";
  file.close();
  return content;
}

void GraphPerceptron::print_config() {
  std::cout << "***********************************************************\n";
  for (int i = 0; i < L; i++) {
    std::cout << size[i] << " ";
  }
  std::cout
      << "\n***********************************************************\n\n";
}
void GraphPerceptron::set_input(std::vector<double> &values) {
  for (int i = 0; i < size[0]; i++) {
    neurons_val[0][i] = values[i];
  }
}

int GraphPerceptron::forward_feed() {
  for (int k = 1; k < L; ++k) {
    GraphNeuron::multi(weights[k - 1], neurons_val[k - 1], size[k - 1],
                       neurons_val[k]);
    actFunc.use(neurons_val[k], size[k]);
  }
  int pred = search_max_index(neurons_val[L - 1]);
  return pred;
}
int GraphPerceptron::search_max_index(std::vector<double> &value) {
  return std::distance(value.begin(),
                       std::max_element(value.begin(), value.end()));
}
void GraphPerceptron::print_values(int &L) {
  for (int j = 0; j < size[L]; j++) {
    std::cout << j << " " << neurons_val[L][j] << std::endl;
  }
}

void GraphPerceptron::back_propogation(double &expect) {
  for (int i = 0; i < size[L - 1]; i++) {
    if (i != int(expect))  //-1*
      delta[L - 1][i] =
          (-neurons_val[L - 1][i]) *
          actFunc.useDer(neurons_val[L - 1][i]);  // value*(1-value)
    else
      delta[L - 1][i] =
          (1.0 - neurons_val[L - 1][i]) *
          actFunc.useDer(neurons_val[L - 1][i]);  // value*(1-value)
  }
  for (int k = L - 2; k > 0; k--) {
    GraphNeuron::multi_t(weights[k], delta[k + 1], size[k + 1], delta[k]);
    for (int j = 0; j < size[k]; j++)
      delta[k][j] *= actFunc.useDer(neurons_val[k][j]);
  }
}

void GraphPerceptron::weights_updater(double &lr) {  // lr 0.08 or 0.3
  for (int i = 0; i < L - 1; ++i) {
    for (int j = 0; j < size[i + 1]; ++j) {
      for (int k = 0; k < size[i]; ++k) {
        weights[i](j, k) -= neurons_val[i][k] * delta[i + 1][j] * lr;
      }
    }
  }
}

void GraphPerceptron::save_weights(std::string &file) {
  std::ofstream fout;
  fout.open(file, std::ios::trunc);
  if (!fout.is_open()) {
    std::cout << "Error reading the file";
  }

  for (int i = 0; i < L - 1; ++i) {
    fout << weights[i] << " ";
  }
  std::cout << "Weights saved \n";
  fout.close();
}

void GraphPerceptron::read_weights(std::string &file) {
  std::ifstream fin;
  fin.open(file, std::ios::in);
  if (!fin.is_open()) {
    std::cout << "Error reading the file";
  }
  for (int i = 0; i < L - 1; ++i) {
    fin >> weights[i];
  }
  std::cout << "Weights readed \n";
  fin.close();
}

void GraphPerceptron::error_test(int &y_test) {
  double error_ = 0, mse_o_t = 0;
  for (int i = 0; i < neurons_val[L - 1].size(); i++) {
    error_ = (i == y_test) ? (std::pow(1 - neurons_val[L - 1][i], 2))
                           : (std::pow(0 - neurons_val[L - 1][i], 2));
    mse_o_t += error_;
  }
  MSE_.push_back(mse_o_t / 26.);
}

double GraphPerceptron::MSE(int &size_) {
  double temp = 0;
  for (auto &i : MSE_) {
    temp += i;
  }
  MSE_.clear();
  return temp / size_;
}

void GraphPerceptron::training_(std::string &train_file_, double &lr,
                                int &epoch) {
  std::vector<std::vector<std::string>> content_train;
  std::vector<double> train_ = {};
  content_train = s21::GraphPerceptron::read_file(train_file_);
  std::chrono::duration<double> time{};
  int right_train = 0, pred_train = 0, train_ex = content_train.size(),
      epoch_ = 0;
  double mse_ = 0.0, temp_mse_ = 0.0;
  while (epoch_ < epoch) {
    epoch_++;
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < train_ex; i++) {
      for (int j = 1; j < content_train[i].size(); j++) {
        train_.push_back(stod(content_train[i][j]) / 255);
      }
      set_input(train_);
      right_train = stoi(content_train[i][0]) - 1;
      pred_train = forward_feed();
      if (pred_train != right_train) {
        back_propogation(reinterpret_cast<double &>(right_train));
        weights_updater(lr);
      }
      forward_feed();
      error_test(right_train);
      train_.clear();
    }
    mse_ = MSE(train_ex);
    if (temp_mse_ <= mse_ && temp_mse_ != 0) {
      lr += 0.1;
    }
    temp_mse_ = mse_;
    auto t2 = std::chrono::steady_clock::now();
    time = t2 - t1;
    std::cout << epoch_ << " "
              << "train_comlete "
              << "lr: " << lr << " mse: " << mse_
              << " time: " << time.count() / 60. << std::endl;
  }
}

void GraphPerceptron::testing_(std::string &test_file_,
                               std::string &save_file) {
  std::vector<std::vector<std::string>> content_test;
  std::vector<double> test_ = {};
  content_test = s21::GraphPerceptron::read_file(test_file_);
  std::chrono::duration<double> time{};
  int right_test = 0, pred_test = 0, test_ex = content_test.size();
  double accur_ = 0.0, ra_test = 0.0;
  auto begin = std::chrono::steady_clock::now();
  for (int k = 0; k < test_ex; k++) {
    for (int j = 1; j < content_test[k].size(); j++) {
      test_.push_back(stod(content_test[k][j]) / 255);
    }
    set_input(test_);
    right_test = stoi(content_test[k][0]) - 1;
    pred_test = forward_feed();
    if (pred_test == right_test) {
      ra_test++;
    }
    test_.clear();
  }
  accur_ = ra_test / test_ex;
  save_weights(save_file);
  auto end = std::chrono::steady_clock::now();
  time = end - begin;
  std::cout << " accurracy: " << accur_ * 100 << "% "
            << "time: " << time.count() / 60. << " min" << std::endl;
}

std::pair<double, double> GraphPerceptron::cross_validation(const int &L,
                                                            std::string &file,
                                                            const int &k,
                                                            const int &epoch,
                                                            const double &lr) {
  std::vector<std::vector<std::string>> vec;
  s21::GraphPerceptron netw;
  netw.init(L);
  vec = s21::GraphPerceptron::read_file(file);
  double fraction = 0.8;
  std::vector<double> accuracies(k);
  std::pair<double, double> res;

  for (int i = 0; i < k; ++i) {
    std::cout << "Fold " << i << std::endl;

    // Разбиваем данные на обучающие и тестовые подмножества
    std::pair<std::vector<std::vector<std::string>>,
              std::vector<std::vector<std::string>>>
        split = split_data(vec, fraction);

    std::vector<std::vector<std::string>> train_data = split.first;
    std::vector<std::vector<std::string>> test_data = split.second;

    // Тренируем модель на обучающих данных
    std::chrono::duration<double> time{};
    std::vector<double> train_ = {};
    double lr_ = 0.08;
    int right_train = 0, pred_train = 0, train_ex = train_data.size(),
        epoch_ = 0;
    double mse_ = 0.0, temp_mse_ = 0.0, time_ = 0.0;
    while (epoch_ < epoch) {
      epoch_++;
      auto t1 = std::chrono::steady_clock::now();
      for (int i = 0; i < train_ex; i++) {
        for (int j = 1; j < train_data[i].size(); j++) {
          train_.push_back(stod(train_data[i][j]) / 255);
        }
        netw.set_input(train_);
        right_train = stoi(train_data[i][0]) - 1;
        pred_train = netw.forward_feed();
        if (pred_train != right_train) {
          netw.back_propogation(reinterpret_cast<double &>(right_train));
          netw.weights_updater(lr_);
        }
        netw.forward_feed();
        netw.error_test(right_train);
        train_.clear();
      }
      mse_ = MSE(train_ex);
      if (temp_mse_ <= mse_ && temp_mse_ != 0) {
      }
      temp_mse_ = mse_;
      auto t2 = std::chrono::steady_clock::now();
      time = t2 - t1;
      time_ = time.count() / 60.;
      std::cout << epoch_ << " "
                << "train_comlete "
                << "lr: " << lr << " mse: " << mse_
                << " time: " << time.count() / 60. << std::endl;
    }
    res.first = mse_;
    res.second = time_;
  }
  return res;
}

std::pair<std::vector<std::vector<std::string>>,
          std::vector<std::vector<std::string>>>
GraphPerceptron::split_data(const std::vector<std::vector<std::string>> &data,
                            double fraction, bool shuffle) {
  std::vector<int> indices(data.size());
  std::iota(indices.begin(), indices.end(), 0);

  if (shuffle) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(indices.begin(), indices.end(), gen);
  }

  int split_idx = static_cast<int>(data.size() * fraction);
  std::vector<std::vector<std::string>> train_data, test_data;
  train_data.reserve(split_idx);
  test_data.reserve(data.size() - split_idx);

  for (int i = 0; i < data.size(); ++i) {
    if (i < split_idx) {
      train_data.push_back(data[indices[i]]);
    } else {
      test_data.push_back(data[indices[i]]);
    }
  }

  return std::make_pair(train_data, test_data);
}
