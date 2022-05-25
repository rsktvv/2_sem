#include <iostream>
#include <cassert>


template<typename T, int N, int M>
struct MasWrapper
{
	T mas[N][M];
};

template<typename T, int N, int M>
class Matrix
{
public:
	int getN() const { return m_n; }
	int getM() const { return m_m; }
	T get(int i, int j) const { return m_mat[i][j]; }
	void set(int i, int j, T data) { m_mat[i][j] = data; }

	Matrix()
	{
		m_n = N;
		m_m = M;
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = 0;
			}
		}
	}

	Matrix(const T mas[N][M])
	{
		m_n = N;
		m_m = M;
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mas[i][j];
	}


	Matrix(const MasWrapper<T, N, M>& mas)
	{

		m_n = N;
		m_m = M;
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mas.mas[i][j];
	}


	template<typename T, int N, int M>
	Matrix(const Matrix<T, N, M>& mat)
	{

		m_n = mat.getN();
		m_m = mat.getM();

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = mat.get(i, j);
			}
		}
	}


	template<typename T, int N, int M>
	Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
	{

		m_n = mat.getN();
		m_m = mat.getM();

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = mat.get(i, j);
			}
		}
		return *this;
	}

	template<typename T, int N, int M>
	Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
	{

		Matrix<T, N, M> tmp;
		if ((N != mat.getN()) && (M != mat.getM()))
		{
			std::cout << "the matrices are not the same " << std::endl;
		}

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.set(i, j, (m_mat[i][j] + mat.get(i, j)));
			}
		}
		return tmp;
	}

	template<typename T, int N, int M>
	Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
	{

		Matrix<T, N, M> tmp;
		if ((N != mat.getN()) && (M != mat.getM()))
		{
			std::cout << "the matrices are not the same " << std::endl;
		}
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.set(i, j, (m_mat[i][j] - mat.get(i, j)));
			}
		}
		return tmp;
	}

	template<typename T, int N, int M>
	Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
	{

		Matrix<T, N, M> tmp;

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < mat.getM(); j++)
			{
				T sum = 0;
				for (int k = 0; k < m_m; k++)
					sum += m_mat[i][k] * mat.get(k, j);
				tmp.set(i, j, sum);
			}
		}
		return tmp;
	}



	~Matrix()
	{

	}

	T DET()
	{

		if ((m_n != m_m) || ((m_n != 2) && (m_m != 3)))
			std::cout << "matrix isnt 2x2 or 3x3 " << std::endl;
		if (m_n == 2)
		{
			return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
		}
		else if (m_n == 3)
		{
			return m_mat[0][0] * m_mat[1][1] * m_mat[2][2]
				+ m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
				+ m_mat[1][0] * m_mat[2][1] * m_mat[0][2]
				- m_mat[0][2] * m_mat[1][1] * m_mat[2][0]
				- m_mat[0][0] * m_mat[1][2] * m_mat[2][1]
				- m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
		}
	}


	Matrix<T, N, M> reverse()
	{

		Matrix<double, N, M> tmp;
		if ((N != M) || ((N != 2) && (N != 3)))
		{
			std::cout << "the matrices are not the same " << std::endl;
			return tmp;
		}

		double Det = DET();
		if (Det == 0)
		{
			std::cout << "DET = 0 " << std::endl;
			return tmp;
		}
		if ((m_n == m_m && m_n == 2) || (m_n == m_m && m_n == 3))
		{
			if (N == 2)
			{
				tmp.set(0, 0, m_mat[1][1] / Det);
				tmp.set(0, 1, -m_mat[0][1] / Det);
				tmp.set(1, 0, -m_mat[1][0] / Det);
				tmp.set(1, 1, m_mat[1][1] / Det);
				return tmp;
			}
			else if (N == 3)
			{
				tmp.set(0, 0, ((m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / Det));
				tmp.set(1, 0, (-(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / Det));
				tmp.set(2, 0, ((m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / Det));
				tmp.set(0, 1, (-(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / Det));
				tmp.set(1, 1, ((m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / Det));
				tmp.set(2, 1, (-(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / Det));
				tmp.set(0, 2, ((m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / Det));
				tmp.set(1, 2, (-(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / Det));
				tmp.set(2, 2, ((m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / Det));
				return tmp;
			}

		}
	}

	
	Matrix<T, N, M> transposition()
	{
		Matrix<T, M, N> tmp;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tmp.set(i, j, m_mat[j][i]);
			}
		}
		return tmp;
	}

	template<typename T, int N, int M>
	friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat);

	template<typename T, int N, int M>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat);
private:
	int m_n, m_m;
	T m_mat[N][M];
};

template<typename T, int N, int M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
{
	for (int i = 0; i < mat.m_n; i++)
	{
		for (int j = 0; j < mat.m_m; j++)
		{
			in >> mat.m_mat[i][j];
		}
	}
	return in;
}

template<typename T, int N, int M>
std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
{
	for (int i = 0; i < mat.m_n; i++)
	{
		for (int j = 0; j < mat.m_m; j++)
		{
			out << mat.m_mat[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}

using Vec2i  = Matrix <int, 2, 1>;
using Vec2d  = Matrix <double, 2, 1>;
using Mat22i = Matrix <int, 2, 2>;
using Mat22d = Matrix <double, 2, 2>;
using Mat33i = Matrix <int, 3, 3>;
using Mat33d = Matrix <double, 3, 3>;
using Mat23i = Matrix <int, 2, 3>;
using Mat32i = Matrix <int, 3, 2>;

int main()
{

	std::cout << " Test '*' " << std::endl;
	{
		Mat22d A({ {{1,2},{3,4}} });

		Vec2d X({ {{1},{1}} });

		Vec2d B = A * X;

		assert(B.get(0, 0) == 3);
		assert(B.get(1, 0) == 7);
	}
	std::cout << "good" << std::endl;

	std::cout << "Test '-' " << std::endl;
	{
		Mat22d A({ {{1,2},{3,4}} });

		Mat22d X({ {{1,2},{3,4}} });
		Mat22d B = A - X;

		assert(B.get(0, 0) == 0);
		assert(B.get(0, 1) == 0);
		assert(B.get(1, 0) == 0);
		assert(B.get(1, 1) == 0);
	}
	std::cout << "good" << std::endl;

	std::cout << "Test '+' " << std::endl;
	{
		Mat22d A({ {{1,2},{3,4}} });

		Mat22d X({ {{1,2},{3,4}} });

		Mat22d B = A + X;

		assert(B.get(0, 0) == 2);
		assert(B.get(0, 1) == 4);
		assert(B.get(1, 0) == 6);
		assert(B.get(1, 1) == 8);
	}
	std::cout << "good" << std::endl;

	std::cout << "Test Det" << std::endl;
	{
		Mat22d A({ {{1,2},{3,4}} });

		Mat33d X({ {{1,2,3},{4,5,6},{7,8,9}} });

		assert(A.DET() == -2);
		assert(X.DET() == 0);
	}
	std::cout << "good" << std::endl;

	std::cout << "Test Reverese" << std::endl;
	{
		Mat22d X({ {{1,2},{3,4}} });
		Mat33d A({ {{2,5,7},{6,3,4},{5,-2,-3},} });

		Mat22d B = X.reverse();
		Mat33d C = A.reverse();
		assert(B.get(0, 0) == -2);
		assert(B.get(0, 1) == 1);
		assert(B.get(1, 0) == 1.5);
		assert(B.get(1, 1) == -2);

		assert(C.get(0, 0) == 1);
		assert(C.get(0, 1) == -1);
		assert(C.get(0, 2) == 1);
		assert(C.get(1, 0) == -38);
		assert(C.get(1, 1) == 41);
		assert(C.get(1, 2) == -34);
		assert(C.get(2, 0) == 27);
		assert(C.get(2, 1) == -29);
		assert(C.get(2, 2) == 24);
	}
	std::cout << "good" << std::endl;
	
	std::cout << "Test Transposition" << std::endl;
	{
		Mat23i X({ {{1,2,3},{4,5,6}} });
		Mat32i B = X.transposition();
		assert(B.get(0, 0) == 1);
		assert(B.get(1, 0) == 2);
		assert(B.get(2, 0) == 3);
		assert(B.get(0, 1) == 4);
		assert(B.get(1, 1) == 5);
		assert(B.get(2, 1) == 6);
	}
	std::cout << "good" << std::endl;


	return 0;
}
