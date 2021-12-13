#pragma once
#include <iostream>

// a square matrix whose elements are either 1 or 0
struct bit_matrix {
	bit_matrix(uint32_t width) {
		mat = new bool[width*width];
		dim = width;
	}

	~bit_matrix() {
		delete[] mat;
	}

	bool get(uint32_t row, uint32_t col) const {
		return mat[row + col*dim];
	}

	void set(uint32_t row, uint32_t col) {
		mat[row+ col*dim] = true;
	}

	void clear(uint32_t row, uint32_t col) {
		mat[row + col*dim] = false;
	}

	void fold_x(uint32_t n) {
		// start at fold line, shift left
		for (size_t row = 0; row < dim; ++row) {
			int col_count = 0;
			for (size_t col = n; col < dim; ++col) {
				if (get(row, col)) {
					clear(row, col);
					set(row , col-col_count);
				}
				col_count +=2;
			}
		}
	}

	void fold_y(uint32_t n) {
		// start at fold line, shift up
		int row_count = 0;
		for (size_t row = n; row < dim; ++row) {
			for (size_t col = 0; col < dim; ++col) {
				if (get(row, col)) {
					clear(row, col);
					set(row-row_count, col);
				}
			}
			row_count += 2;
		}
	}

	int n_set() const {
		int count = 0;
		for (size_t r = 0; r < dim; ++r) {
			for (size_t c = 0; c < dim; ++c) {
				count += get(r, c) ? 1 : 0;
			}
		}
		return count;
	}

	friend std::ostream& operator<<(std::ostream &os, const bit_matrix &m) {
		for (size_t row = 0; row < 10; ++row) {
			for (size_t col = 0; col < 50; ++col) {
				os << (m.get(row, col) ? "X" : ".");
			}
			os << "\n";
		}
		return os;
	}
	
private:
	bool *mat;
	uint32_t dim;
};
