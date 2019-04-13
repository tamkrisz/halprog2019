#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_Matrix1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_Matrix2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

//Common lambdas:
inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };
inline auto divide = [](auto const& x, auto const& y){ return x / y; };
inline auto mul = [](auto const& x, auto const& y){ return x * y; };

template<typename T>
class Matrix
{
	private:
	std::vector<T> data;
	unsigned int N;

	public:
	//<< és >> operatort külön tesztelni
	Matrix() = default;
	Matrix( Matrix const& ) = default;
	Matrix( Matrix && ) = default;

	//Function call operator for reading and writing:
	T&       operator[]( int i )       { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }
	T& operator()(int i, int j) { return data[N*i + j]; };
	T const& operator()(int i, int j) const { return data[N*i+j]; };
	//Copy and Move assignment operators implemented by the compiler:
	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix &&) = default;


	//Dimension of the matrix
	int dim() const
	{
		return static_cast<unsigned int>(sqrt(data.size()));
	}
	
	//Number of elements of the Matrix:
	int size() const
	{
		return static_cast<unsigned int>(data.size());
	}


	//Function initialization
/*
	template<typename F>
	Matrix(F f, int n)
	{
		data.resize(n);
		for(int i=0; i<n; ++i){ data[i] = f(i); }
	}
*/
	//Size initialization
	Matrix( unsigned int M ) : N{M}
	{
		for(unsigned int i=0; i<N*N; ++i){ data.push_back(0); }
	}

	//List initialization
	Matrix( unsigned int M, std::initializer_list<T> const& il ) : N{M}, data{il}
	{
		if(sqrt(data.size()) < N) { std::cout << "Error: less values than expected!" << std::endl; std::exit(-1); }
		if(sqrt(data.size()) > N) { std::cout << "Error: more values than expected!" << std::endl; std::exit(-1); }
	}

	//Add, sub, mult, div by scalar
	//mult
	Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
	}
	//add
	Matrix<T>& operator+= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x + scl;} );
		return *this;
	}
	//sub
	Matrix<T>& operator-= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x - scl;} );
		return *this;
	}
	//div
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}

	//Add, sub, mult, div with other matrix
	Matrix<T>& operator*= (Matrix<T> const& cpy)
	{
		std::vector<T> res(cpy.dim());
		for(int i=0; i<cpy.dim();i++)
		{
			for(int j=0; j<cpy.dim();j++)
			{
				for(int k=0; k<cpy.dim();k++)
				{
					res[j] += (*this)[N*i + k] * cpy[N*k + j];
				}
			}
			for(int l=0; l<cpy.dim();l++)
			{
				(*this)[N*i + l] = res[l];
				res[l] = 0;
			}
		}
		return *this;
	}

	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, add);
		return *this;
	}

	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, sub);
		return *this;
	}

	Matrix<T>& operator/= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, divide);
		return *this;
	}

	//begin and end for compatibility with STL:
	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}


};

template<typename T> 
T length( Matrix<T>const& v )
{
	return std::sqrt(std::accumulate(v.cbegin(), v.cend(), static_cast<T>(0), [](T const& acc, T const& x){ return acc + x*x; }));
}


//+MAtrix
template<typename T>
Matrix<T> operator+( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	Matrix<T> result(v1.dim());
	detail::transform_Matrix2(v1, v2, result, add);
	return result;
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, add );
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T> const& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v2, add );
	return std::move(v2);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, add );
	return std::move(v1);
}
//-MAtrix
template<typename T>
Matrix<T> operator-( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	Matrix<T> result(v1.dim());
	detail::transform_Matrix2(v1, v2, result, sub);
	return result;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, sub );
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T> const& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v2, sub );
	return std::move(v2);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, sub );
	return std::move(v1);
}
// /Matrix
template<typename T>
Matrix<T> operator/( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	Matrix<T> result(v1.dim());
	detail::transform_Matrix2(v1, v2, result, divide );
	return result;
}

template<typename T>
Matrix<T>&& operator/( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, divide);
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator/( Matrix<T> const& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v2, divide );
	return std::move(v2);
}

template<typename T>
Matrix<T>&& operator/( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	detail::transform_Matrix2(v1, v2, v1, divide );
	return std::move(v1);
}

//*Matrix
template<typename T>
Matrix<T> operator*( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	int N = v1.dim();
	Matrix<T> result(N);
	for(int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			for(int k=0; k<N;k++)
			{
				result[N*i + j] += v1[N*i + k] * v2[N*k + j];
			}
		}
	}
	return result;
}

template<typename T>
Matrix<T>&& operator*( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	std::vector<T> res(v2.dim());
	int N = v2.dim();
	for(int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			for(int k=0; k<N;k++)
			{
				res[j] += v1[N*i + k] * v2[N*k + j];
			}
		}
		for(int l=0; l<N;l++)
		{
			v1[N*i + l] = res[l];
			res[l] = 0;
		}
	}
	return std::move(v1);
}

template<typename T>
std::ostream& operator<< (std::ostream& o, const Matrix<T>& m)
{	
	int N = m.dim();
	for(int i=0; i<N;i++)
	{
		for(int j=0; j<N; j++)
		{
			o << m(i,j) << " ";
		}
		o << std::endl;
	}
return o;
}
