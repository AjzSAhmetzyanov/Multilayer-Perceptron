#include <gtest/gtest.h>
#include "../Controller/controller.h"
#include "../Model/ActivateFunctions/ActivateFunction.h"
#include  "../Model/Graph/GraphNeuron.h"
#include  "../Model/Graph/GraphPerceptron.h"
#include 	"../Model/Matrix/Matrix.h"

/**
 *  MODEL UNIT_TESTS
 */

class ActivateFunctionTest : public ::testing::Test {
protected:
    s21::ActivateFunction actFunc;
    std::vector<double> values;

    void SetUp() override {
        values = { -1.0, 0.0, 1.0 };
    }
};

TEST_F(ActivateFunctionTest, test_1) {
    actFunc.set();
    EXPECT_EQ(actFunc.set(), activateFunc::sigmoid);
    actFunc.set();
    EXPECT_EQ(actFunc.set(), activateFunc::ReLU);
    actFunc.set();
    EXPECT_EQ(actFunc.set(), activateFunc::thx);
}

TEST_F(ActivateFunctionTest, test_2) {
    actFunc.set();
    actFunc.use(values, values.size());
    EXPECT_NEAR(values[0], 0.26894, 0.00001);
    EXPECT_EQ(values[1], 0.5);
    EXPECT_NEAR(values[2], 0.73105, 0.00001);
}

TEST_F(ActivateFunctionTest, test_3) {
    actFunc.set();
    double value = 0.5;
    double result = actFunc.useDer(value);
    EXPECT_NEAR(result, 0.25, 0.00001);
}

/**
 *  GRAPH_NEURON UNIT_TESTS
 */

TEST(GraphNeuronTest, test_1) {
    s21::GraphNeuron gn;
    int row = 2;
    int col = 3;
    gn.init(row, col);

    EXPECT_EQ(gn.matrix.size(), row);
    EXPECT_EQ(gn.matrix[0].size(), col);
    EXPECT_EQ(gn.row, row);
    EXPECT_EQ(gn.col, col);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            EXPECT_EQ(gn.matrix[i][j], 0);
        }
    }
}

TEST(GraphNeuronTest, test_2) {
    s21::GraphNeuron gn;
    int row = 2;
    int col = 3;
    gn.init(row, col);
    gn.rand_();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            EXPECT_GE(gn.matrix[i][j], 0);
            EXPECT_LE(gn.matrix[i][j], 1);
        }
    }
}

TEST(GraphNeuronTest, test_3) {
    s21::GraphNeuron gn;
    int row1 = 2;
    int col1 = 3;
    gn.init(row1, col1);
    gn.rand_();
    std::vector<double> neuron = {0.1, 0.2, 0.3};
    int n = 3;
    std::vector<double> c(row1, 0);
    gn.multi(gn, neuron, n, c);

    for (int i = 0; i < row1; ++i) {
        double tmp = 0;
        for (int j = 0; j < col1; ++j) {
            tmp += gn.matrix[i][j] * neuron[j];
        }
        EXPECT_EQ(c[i], tmp);
    }
}

TEST(GraphNeuronTest, test_4) {
    s21::GraphNeuron gn;
    int row1 = 2;
    int col1 = 3;
    gn.init(row1, col1);
    gn.rand_();
    std::vector<double> neuron = {0.1, 0.2};
    int n = 2;
    std::vector<double> c(col1, 0);
    gn.multi_t(gn, neuron, n, c);

    for (int i = 0; i < col1; ++i) {
        double tmp = 0;
        for (int j = 0; j < row1; ++j) {
            tmp += gn.matrix[j][i] * neuron[j];
        }
        EXPECT_EQ(c[i], tmp);
    }
}

TEST(GraphNeuronTest, test_5) {
    s21::GraphNeuron gn;
    int row = 2;
    int col = 3;
    gn.init(row, col);
    gn.rand_();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            gn(i, j) += 1.0;
            EXPECT_EQ(gn.matrix[i][j], gn(i, j));
        }
    }
}

/**
 *  GRAPH_PERCEPTRON UNIT_TESTS
 */

TEST(GraphPerceptronTest, test_1) {
    s21::GraphPerceptron gp;
    gp.init(3);
    EXPECT_EQ(gp.L, 3);
    EXPECT_EQ(gp.size[0], 784);
    EXPECT_EQ(gp.size[1], 140);
    EXPECT_EQ(gp.size[2], 26);
    EXPECT_EQ(gp.weights.size(), 2);
    EXPECT_EQ(gp.neurons_val.size(), 3);
    EXPECT_EQ(gp.delta.size(), 3);
}

TEST(GraphPerceptronTest, test_2) {
    testing::internal::CaptureStdout();
    s21::GraphPerceptron gp;
    gp.init(3);
    gp.print_config();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "***********************************************************\n784 140 26 \n***********************************************************\n\n");
}

TEST(GraphPerceptronTest, test_3) {
    s21::GraphPerceptron gp;
    gp.init(3);
    std::vector<double> values(784, 0.5);
    gp.set_input(values);
    EXPECT_EQ(gp.neurons_val[0][0], 0.5);
    EXPECT_EQ(gp.neurons_val[0][783], 0.5);
}

TEST(GraphPerceptronTest, ForwardFeedTest) {
    s21::GraphPerceptron gp;
    gp.init(3);
    std::vector<double> values(784, 0.5);
    gp.set_input(values);
    int pred = gp.forward_feed();
    EXPECT_LE(pred, 25);
    EXPECT_GE(pred, 0);
}

TEST(GraphPerceptronTest, test_4) {
    s21::GraphPerceptron gp;
    std::vector<double> values = {1.0, 2.0, 3.0, 2.0, 1.0};
    int max_index = gp.search_max_index(values);
    EXPECT_EQ(max_index, 2);
}

TEST(GraphPerceptronTest, test_5) {
    s21::GraphPerceptron gp;
    gp.init(3);
    std::vector<double> values(784, 0.5);
    gp.set_input(values);
    int expect = 5;
    gp.forward_feed();
    gp.back_propogation(expect);
    EXPECT_EQ(gp.delta[2][expect], (1.0 - gp.neurons_val[2][expect]) * gp.actFunc.useDer(gp.neurons_val[2][expect]));
    for (int i = 0; i < gp.size[1]; i++) {
        double val = gp.neurons_val[1][i];
        EXPECT_EQ(gp.delta[1][i], gp.actFunc.useDer(val) * (gp.weights[1](expect, i) * gp.delta[2][expect]));
    }
}

/**
 *  MATRIX UNIT_TESTS
 */

TEST(MatrixTest, test_1) {
    s21::Matrix m;
    int row = 3;
    int col = 4;
    m.init(row, col);
    EXPECT_EQ(m.get_row(), row);
    EXPECT_EQ(m.get_col(), col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            EXPECT_EQ(m.get_matrix()[i][j], 0);
        }
    }
}

TEST(MatrixTest, test_2) {
    s21::Matrix m;
    int row = 3;
    int col = 4;
    m.init(row, col);
    m.rand_();
    EXPECT_EQ(m.get_row(), row);
    EXPECT_EQ(m.get_col(), col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            EXPECT_GE(m.get_matrix()[i][j], 0.0);
            EXPECT_LE(m.get_matrix()[i][j], 1.0);
        }
    }
}

TEST(MatrixTest, test_3) {
    s21::Matrix m1;
    int row1 = 2;
    int col1 = 3;
    m1.init(row1, col1);
    m1.set_matrix({{1, 2, 3}, {4, 5, 6}});
    std::vector<double> neuron = {2, 3, 4};
    int n = 3;
    std::vector<double> c(row1);
    m1.multi(m1, neuron, n, c);
    EXPECT_EQ(c.size(), row1);
    EXPECT_EQ(c[0], 20);
    EXPECT_EQ(c[1], 47);
}

TEST(MatrixTest, test_4) {
    s21::Matrix m1;
    int row1 = 2;
    int col1 = 3;
    m1.init(row1, col1);
    m1.set_matrix({{1, 2, 3}, {4, 5, 6}});
    std::vector<double> neuron = {2, 3};
    int n = 2;
    std::vector<double> c(col1);
    m1.multi_t(m1, neuron, n, c);
    EXPECT_EQ(c.size(), col1);
    EXPECT_EQ(c[0], 14);
    EXPECT_EQ(c[1], 19);
    EXPECT_EQ(c[2], 24);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
