#include <iostream>

class Matrix
{
public:
	Matrix(int n, int m)
	{
		m_n = n;
		m_m = m;
		m_mat = new double* [m_n];
		for (int i = 0; i < m_n; i++)
		{
			m_mat[i] = new double[m_m];
		}
	}

	
	Matrix(const Matrix& mat)
	{
		m_n = mat.m_n;
		m_m = mat.m_m;
		m_mat = new double* [m_n];
		for (int i = 0; i < m_n; i++)
		{
			m_mat[i] = new double[m_m];
		}
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = mat.m_mat[i][j];
			}
		}
	}

	Matrix& operator=(const Matrix& mat)
	{
		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = mat.m_mat[i][j];
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& mat)
	{
		Matrix tmp(m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			}
		}
		return tmp;
	}

	Matrix operator-(const Matrix& mat)
	{
		Matrix tmp(m_n, mat.m_m);
		if (m_m != mat.m_m && m_n != mat.m_m)
		{
			std::cout << "matrici ne ravnbI" << std::endl;
		}
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
			}
		}
		return tmp;
	}
	
	Matrix operator*(const Matrix& mat)
	{
		Matrix tmp(m_n, mat.m_m);
		if (m_m != mat.m_n)
		{
			std::cout << "stroka ne ravno stolbcu"<<std::endl;
		}
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < mat.m_m; j++)
			{
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < mat.m_n; k++)
				{
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
				}
			}
		}
		return tmp;
	}

	~Matrix()
	{
		for (int i = 0; i < m_n; i++)
		{
			delete[] m_mat[i];
		}
		delete m_mat;
	}

	double Matrix::DET()
	{ 
		if ((m_n != m_m) && (m_n!=2) && (m_n!=3))
		{
			std::cout << "matrix is not 2x2 or 3x3 " << std::endl;
		}

		else if (m_n == 2)
		{
			double det = 0;
			det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
			return det;
		}

		else if (m_n == 3)
		{
			double det = 0;
			det = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
				+ m_mat[1][0] * m_mat[2][1] * m_mat[0][2] - m_mat[2][0] * m_mat[1][1] * m_mat[0][2] -
				m_mat[2][1] * m_mat[1][2] * m_mat[0][0] - m_mat[1][0] * m_mat[0][1] * m_mat[2][2];
			return  det;
		}
	}

	Matrix Matrix::reverse()
	{
		int Det = DET();
		Matrix tmp(m_n, m_m);
		if ((m_n == m_m && m_n== 2) || (m_n == m_m && m_n == 3))
		{
			if (Det == 0)
			{
				std::cout << "det = 0 " << std::endl;
			}
			else
			{
				if (m_n == 2)
				{
					tmp.m_mat[0][0] = m_mat[1][1] / Det;
					tmp.m_mat[0][1] = -m_mat[0][1] / Det;
					tmp.m_mat[1][0] = -m_mat[1][0] / Det;
					tmp.m_mat[1][1] = m_mat[0][0] / Det;
					return tmp;
				}
				else if (m_n == 3)
				{
					tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / Det;
					tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / Det;
					tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / Det;
					tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / Det;
					tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / Det;
					tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / Det;
					tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / Det;
					tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / Det;
					tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / Det;
					return tmp;
				}
			}
		}
		else
			std::cout << "matrix is not 2x2 or 3x3 " << std::endl;
	}

	Matrix Matrix::transposition()
	{
		std::swap(m_m, m_n);
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = m_mat[j][i];
			}
		}

		for (int i = 0; i < m_m; i++)
		{
			delete[] m_mat[i];
		}
		delete m_mat;

		m_mat = new double* [m_n];
		for (int i = 0; i < m_n; i++)
		{
			m_mat[i] = new double[m_m];
		}

		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				m_mat[i][j] = tmp.m_mat[i][j];
			}
		}
		return tmp;
	}

	friend std::istream& operator>>(std::istream& in, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);
private:
	int m_n, m_m;
	double** m_mat;
};

std::istream& operator>>(std::istream& in, Matrix& mat)
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

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
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

int main()
{
	int n = 0;
	int m = 0;

	std::cin >> n >> m;
	Matrix B(n, m);
	std::cin >> B;
	B.transposition();
	std::cout << "Transposition Matrix B: " << std::endl << B << std::endl;
	B.transposition();
	std::cout << "Transposition Matrix B: " << std::endl << B << std::endl;

	std::cin >> n >> m;
	Matrix A(n,m);
	std::cin >> A;

	std::cout << '\n';
	std::cout << A * B << std::endl;
	std::cout << A - B << std::endl;

	std::cout << "Det A: " << std::endl << A.DET() << std::endl;
	std::cout << "Reverse A: " << std::endl << A.reverse() << std::endl;

	return 0;
}
