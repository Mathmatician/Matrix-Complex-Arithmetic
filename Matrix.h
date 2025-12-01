#include <iostream>
#include <vector>
#include <thread>

template<typename T>
using VECTOR = std::vector<T>;

template<typename T>
using MATRIX = std::vector<std::vector<T>>;


template<typename T>
const int RowSize(const MATRIX<T>& mtx)
{
	return mtx.size();
}

template<typename T>
const int ColumnSize(const MATRIX<T>& mtx)
{
	if (mtx.size() > 0)
		return mtx[0].size();

	return 0;
}

template<typename T>
MATRIX<T> CreateMatrix(int rowSize, int colSize)
{
	return MATRIX<T>(rowSize, VECTOR<T>(colSize, 0));
}
	
template<typename T>
MATRIX<T> CreateMatrix(int rowSize, int colSize, T initVal)
{
	return MATRIX<T>(rowSize, VECTOR<T>(colSize, initVal));
}

template<typename T>
MATRIX<T> Multiply(const MATRIX<T>& A, const MATRIX<T>& B)
{
	const int a_rowSize = RowSize(A);
	const int a_colSize = ColumnSize(A);
	const int b_rowSize = RowSize(B);
	const int b_colSize = ColumnSize(B);
	std::vector<std::thread> thrds;
	const int num_of_threads = 1; //std::thread::hardware_concurrency();

	if (a_colSize == b_rowSize && b_rowSize != 0)
	{
		MATRIX<T> result = CreateMatrix<T>(a_rowSize, b_colSize);
		
		for (int i = 0; i < num_of_threads; i++)
		{
			thrds.emplace_back([i, A, B, a_rowSize, a_colSize, b_colSize, num_of_threads, &result] () {
				int a_row = 0;
				int b_col = i;
				T val;
				
				while (a_row < a_rowSize)
				{
					val = 0;
					if (b_col >= b_colSize)
					{
						int a_incrementor = b_col / b_colSize;
						b_col = b_col % b_colSize;
						a_row += a_incrementor;
					}

					if (a_row < a_rowSize && b_col < b_colSize)
					{
						for (int k = 0; k < a_colSize; k++)
						{
							T A_elm = A[a_row][k];
							T B_elm = B[k][b_col];
							val += A_elm * B_elm;
						}
						result[a_row][b_col] = val;
					}
					b_col += num_of_threads;
				}
			});
		}

		for (auto& th : thrds)
			th.join();

		return result;
	}

	return {};
}

template<typename T>
void MultiplyScalar(MATRIX<T>& A, const T scalar)
{
	std::vector<std::thread> thrds;
	const int num_of_threads = std::thread::hardware_concurrency();
	const int rowSize = RowSize(A);
	const int colSize = ColumnSize(A);

	for (int i = 0; i < num_of_threads; i++)
	{
		thrds.emplace_back([i, rowSize, colSize, num_of_threads, scalar, &A](){
			int r = 0;
			int c = i;

			while (r < rowSize)
			{
				if (c >= colSize)
				{
					int r_incrementor = c / colSize;
					r += r_incrementor;
					c = c % colSize;
				}
				
				if (r < rowSize && c < colSize)
					A[r][c] *= scalar;

				c += num_of_threads;
			}
		});
	}

	for (auto& th : thrds)
		th.join();
}

template<typename T>
MATRIX<T> Add(const MATRIX<T>& A, const MATRIX<T>& B)
{
	std::vector<std::thread> thrds;
	const int num_of_threads = std::thread::hardware_concurrency();
	const int a_rowSize = RowSize(A);
	const int a_colSize = ColumnSize(A);
	const int b_rowSize = RowSize(B);
	const int b_colSize = ColumnSize(B);

	if (a_rowSize > 0 && a_rowSize == b_rowSize && a_colSize == b_colSize)
	{
		MATRIX<T> result = CreateMatrix<T>(a_rowSize, b_colSize);

		for (int i = 0; i < num_of_threads; i++)
		{
			thrds.emplace_back([i, A, B, a_rowSize, a_colSize, num_of_threads, &result](){
				int r = 0;
				int c = i;
				

				while (r < a_rowSize)
				{
					if (c >= a_colSize)
					{
						int r_incrementor = c / a_colSize;
						r += r_incrementor;
						c = c % a_colSize;
					}
					
					if (r < a_rowSize && c < a_colSize)
					{
						T A_elm = A[r][c];
						T B_elm = B[r][c];
						result[r][c] = A_elm + B_elm;
					}

					c += num_of_threads;
				}
			});
		}

		for (auto& th : thrds)
			th.join();

		return result;
	}

	return {};
}

template<typename T>
MATRIX<T> Subtract(const MATRIX<T>& A, const MATRIX<T>& B)
{
	MATRIX<T> nB = B;
	T n_1 = T(-1.0);
	MultiplyScalar(nB, n_1);
	return Add(A, nB);
}

template<typename T>
void Display(VECTOR<T>& vec)
{
	for (auto& elm : vec)
		std::cout << elm << " ";

	std::cout << std::endl;
}

template<typename T>
void Display(MATRIX<T>& mtx)
{
	for (auto& row : mtx)
		Display(row);

	std::cout << std::endl;
}

