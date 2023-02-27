#include "s21_matrix_oop.h"

#include <iostream>

S21Matrix::S21Matrix() { this->zerro_padding(); }
// Default constructor
S21Matrix::~S21Matrix() { this->clear_matrix(); }
// Destructor
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 && cols <= 0) {
    throw std::out_of_range("Invalid size of rows or columns");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  this->create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) { *this = other; }

void S21Matrix::create_matrix() {
  if (!this->rows_ || !this->cols_)
    throw std::length_error("Rows is less or equal 0");
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::get_rows() { return this->rows_; }
int S21Matrix::get_columns() { return this->cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(rows, this->cols_);
  int min_rows = (rows < this->rows_) ? rows : this->rows_;

  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  this->clear_matrix();
  *this = temp;
}

void S21Matrix::set_columns(int columns) {
  if (columns <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(this->rows_, columns);
  if (columns < this->cols_) {
    this->cols_ = columns;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::zerro_padding() {
  this->rows_ = this->cols_ = 0;
  this->matrix_ = nullptr;
}

void S21Matrix::clear_matrix() {
  if (this->matrix_) {
    if (this->rows_ && this->cols_) {
      for (int i = 0; i < this->rows_; i++) {
        // for (int j = 0; j < this->cols_; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }
  }
}

// void S21Matrix::print_matrix() {
//   if (this->matrix_ != nullptr) {
//     for (int i = 0; i < this->rows_; i++) {
//       for (int j = 0; j < this->cols_; j++) {
//         std::cout << matrix_[i][j] << " ";
//       }
//       std::cout << std::endl;
//     }
//   } else {
//     std::cout << "Matrix is empty" << std::endl;
//   }
// }

void S21Matrix::number_padding(double x) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = x;
    }
  }
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }
  /* standard cpp function: copies memory of o.rows_ * o.cols_ * sizeof(double)
  from o.p pointer to _p pointer */
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

void S21Matrix::sum_matrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::sub_matrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}
bool S21Matrix::eq_matrix(const S21Matrix &other) {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if ((this->rows_ < 0 || this->cols_ < 0) &&
             (other.rows_ < 0 || other.cols_ < 0)) {
    result = false;
    throw std::out_of_range("Incorrect input, size cannot be less than zero");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-07)
          result = false;
      }
    }
  }
  return result;
}

void S21Matrix::mul_number(const double num) {
  if (this->matrix_ == nullptr) {
    throw std::out_of_range("Empty matrix");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix &other) {
  if (this->rows_ != other.cols_) {
    throw std::out_of_range(
        "the number of rows of the first matrix must be equal to the number of "
        "columns of the second matrix");
  } else if (!this->matrix_ || !other.matrix_) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    S21Matrix result(other.cols_, this->rows_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < this->cols_; k++) {
          result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        this->matrix_[i][j] = result.matrix_[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::transpose() {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::determinant_rec(double **matrix, int dim) {
  if (dim == 1) {
    return matrix[0][0];
  }
  int code = 0;
  double det = 0.0;
  double sign = 1.0;
  for (int i = 0; i < dim; i++) {
    if (dim < 1) {
      code = 1;
    }
    S21Matrix tmp(dim - 1, dim - 1);
    if (code == 1) {
      throw std::out_of_range("Incorrect input, matrix empty");
    }
    for (int m = 1; m < dim; m++) {
      int p = 0;
      for (int n = 0; n < dim; n++) {
        if (n == i) {
          continue;
        }
        tmp.matrix_[m - 1][p] = matrix[m][n];
        p++;
      }
    }

    det += sign * matrix[0][i] * determinant_rec(tmp.matrix_, dim - 1);
    sign = -sign;
  }
  return det;
}

void S21Matrix::fill_minor(S21Matrix &minor, int i, int j) {
  int minor_row_index = 0;
  int minor_column_index = 0;
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      if (m != i && n != j) {
        minor.matrix_[minor_row_index][minor_column_index] = matrix_[m][n];

        if (minor_column_index + 1 != minor.cols_) {
          minor_column_index++;
        } else {
          minor_row_index++;
          minor_column_index = 0;
        }
      }
    }
  }
}

double S21Matrix::determinant() {
  int code = 0;
  double result = 0;
  if ((cols_ < 1 || rows_ < 1) || (rows_ != cols_)) {
    code = 1;
  }
  if (code == 1) {
    throw std::out_of_range("Incorrect input");
  }
  if (code == 0 && cols_ == 1) {
    result = matrix_[0][0];
  } else if (code == 0 && cols_ > 1) {
    result = determinant_rec(matrix_, rows_);
  }
  return result;
}

S21Matrix S21Matrix::calc_complements() {
  S21Matrix result(rows_, cols_);
  if ((rows_ != cols_) || rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Incorrect input");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double determinant = 0.0;
      S21Matrix minor(rows_ - 1, cols_ - 1);
      this->fill_minor(minor, i, j);
      determinant = minor.determinant();
      result.matrix_[i][j] = pow(-1, i + j) * determinant;
    }
  }
  return result;
}

S21Matrix S21Matrix::inverse_matrix() {
  if (rows_ != cols_) {
    throw std::logic_error("\nRows and columns must match\n");
  } else if (determinant() == 0.0) {
    throw std::logic_error("\ndeterminant value can't be equal to 0\n");
  }
  const double determinant = 1 / this->determinant();
  S21Matrix tmpMatrix(calc_complements());
  S21Matrix resultMatrix(tmpMatrix.transpose());
  resultMatrix.mul_number(determinant);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < resultMatrix.cols_; j++) {
      this->matrix_[i][j] = resultMatrix.matrix_[i][j];
    }
  }
  return resultMatrix;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = new double *[other.rows_];
    for (int i = 0; i < other.rows_; i++) {
      matrix_[i] = new double[other.cols_];
    }
    /* standard cpp function: copies memory of o.rows_ * o.cols_ *
    sizeof(double) from o.p pointer to _p pointer */
    std::memcpy(matrix_, other.matrix_,
                other.rows_ * other.cols_ * sizeof(double));
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->eq_matrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  sum_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  sub_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  mul_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.sum_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.sub_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.mul_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(rows_, cols_);
  res.mul_number(num);
  return res;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_) {
    throw std::logic_error("\nIndex out of range\n");
  }
  return matrix_[i][j];
}