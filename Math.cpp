#include "Math.h"
#include "Novice.h"
#include <assert.h>
#include <cmath>
Math::Math() {}

Matrix4x4 Math::Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];

	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[1][3] = m1.m[1][3] + m2.m[1][3];

	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];
	result.m[2][3] = m1.m[2][3] + m2.m[2][3];

	result.m[3][0] = m1.m[3][0] + m2.m[3][0];
	result.m[3][1] = m1.m[3][1] + m2.m[3][1];
	result.m[3][2] = m1.m[3][2] + m2.m[3][2];
	result.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return result;
}

Matrix4x4 Math::Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	result.m[0][0] = m1.m[0][0] - m2.m[0][0];
	result.m[0][1] = m1.m[0][1] - m2.m[0][1];
	result.m[0][2] = m1.m[0][2] - m2.m[0][2];
	result.m[0][3] = m1.m[0][3] - m2.m[0][3];

	result.m[1][0] = m1.m[1][0] - m2.m[1][0];
	result.m[1][1] = m1.m[1][1] - m2.m[1][1];
	result.m[1][2] = m1.m[1][2] - m2.m[1][2];
	result.m[1][3] = m1.m[1][3] - m2.m[1][3];

	result.m[2][0] = m1.m[2][0] - m2.m[2][0];
	result.m[2][1] = m1.m[2][1] - m2.m[2][1];
	result.m[2][2] = m1.m[2][2] - m2.m[2][2];
	result.m[2][3] = m1.m[2][3] - m2.m[2][3];

	result.m[3][0] = m1.m[3][0] - m2.m[3][0];
	result.m[3][1] = m1.m[3][1] - m2.m[3][1];
	result.m[3][2] = m1.m[3][2] - m2.m[3][2];
	result.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return result;
}

Matrix4x4 Math::Transpose(const Matrix4x4& m) {
	Matrix4x4 result = {};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m.m[column][row];
		}
	}
	return result;
}

Matrix4x4 Math::MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; ++i) {
		result.m[i][i] = 1;
	}
	return result;
}

void Math::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 Math::Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 Math::Inverse(const Matrix4x4& matrix) {
	float a = {
	    1 / ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
	         (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])

	         - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
	         (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])

	         - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) -
	         (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2])

	         + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) +
	         (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])

	         + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) +
	         (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2])

	         - (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) -
	         (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])

	         - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) -
	         (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0])

	         + (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) +
	         (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]))};

	Matrix4x4 inverseMatrix = {};
	inverseMatrix.m[0][0] =
	    ((matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) + (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]) -
	     (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]));
	inverseMatrix.m[0][1] =
	    (-(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1]) - (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2]) +
	     (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]));
	inverseMatrix.m[0][2] =
	    ((matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1]) + (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2]) -
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]));

	inverseMatrix.m[0][3] =
	    (-(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1]) - (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2]) +
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]));

	inverseMatrix.m[1][0] =
	    (-(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]) +
	     (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]));

	inverseMatrix.m[1][1] =
	    ((matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2]) -
	     (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]));

	inverseMatrix.m[1][2] =
	    (-(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2]) +
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]));

	inverseMatrix.m[1][3] =
	    ((matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2]) -
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]));

	inverseMatrix.m[2][0] =
	    ((matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) -
	     (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]));

	inverseMatrix.m[2][1] =
	    (-(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1]) +
	     (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]));

	inverseMatrix.m[2][2] =
	    ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1]) -
	     (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]));

	inverseMatrix.m[2][3] =
	    (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1]) +
	     (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]));

	inverseMatrix.m[3][0] =
	    (-(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) +
	     (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) + (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]));

	inverseMatrix.m[3][1] =
	    ((matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2]) + (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1]) -
	     (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]));

	inverseMatrix.m[3][2] =
	    (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2]) - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1]) +
	     (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]));

	inverseMatrix.m[3][3] =
	    ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
	     (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a * inverseMatrix.m[i][j];
		}
	}

	return result;
}
