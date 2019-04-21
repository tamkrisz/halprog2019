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
	Matrix( Matrix && m) : data{std::move(m.data)}, N{std::move(N)}
	{
		m.N = 0;
	}

	//Function call operator for reading and writing:
	T&       operator[]( int i )       { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }
	T& operator()(int i, int j) { return data[N*i + j]; };
	T const& operator()(int i, int j) const { return data[N*i+j]; };
	//Copy and Move assignment operators implemented by the compiler:
	Matrix<T>& operator=(Matrix const& m)
	{
		if(this != &m)
		{
			N = m.N;
			data = m.data;
		}
		return *this;
	}

	Matrix<T>& operator=(Matrix && m)
	{
		if(this != &m)
		{
			N = m.N;
			data = std::move(m.data);
			m.N = 0;
		}
		return *this;
	}


	//Dimension of the matrix
	int dim() const
	{
		return N;
	}
	
	//Number of elements of the Matrix:
	int size() const
	{
		return static_cast<unsigned int>(data.size());
	}


	//Function initialization
	template<typename F>
	Matrix(F f, int M) : N{M}
	{
		data.resize(N*N);
		for(int i=0; i<N; ++i){ data[i] = f(i); }
	}

	//Size initializationW
	Matrix( unsigned int M ) : N{M}
	{
		data.resize(N*N);
	}

	void resize(int M)
	{
		N = M;
		data.resize(N*N);
	}
	//List initialization
	Matrix( unsigned int M, std::initializer_list<T> const& il ) : N{M}, data{il}
	{
		if(data.size() < N*N) { std::cout << "Error: less values than expected!" << std::endl; std::exit(-1); }
		if(data.size() > N*N) { std::cout << "Error: more values than expected!" << std::endl; std::exit(-1); }
	}


	//scalar mul
	Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
	}
	//scalar div
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}

	//matrix mul
	Matrix<T>& operator*= (Matrix<T> const& cpy)
	{
		
		std::vector<T> res(cpy.dim());
		for(int i=0; i<cpy.dim();i++)
		{
			for(int j=0; j<cpy.dim();j++)
			{
				T temp = 0;
				for(int k=0; k<cpy.dim();k++)
				{
					temp += (*this)(i,k) * cpy(k,j);
				}
				res[j] = temp;
				temp = 0;
			}
			for(int l=0; l<cpy.dim();l++)
			{
				(*this)(i,l) = res[l];
			}
		}
		return *this;
	}
	//matrix add
	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, add);
		return *this;
	}
	//matrix sub
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, sub);
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
T norm_of_elements( Matrix<T>const& v )
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
			T temp = 0;
			for(int k=0; k<N;k++)
			{
				temp += v1(i,k) * v2(k,j);
			}
			result(i,j) = temp;
			temp = 0;
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
			T temp = 0;
			for(int k=0; k<N;k++)
			{
				temp += v1(i,k) * v2(k,j);
			}
			res[j] = temp;
			temp = 0;
		}
		for(int l=0; l<N;l++)
		{
			v1(i,l) = res[l];
		}
	}
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator*( Matrix<T> const& v1, Matrix<T> && v2 )
{
	std::vector<T> res(v1.dim());
	int N = v1.dim();
	for(int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			T temp = 0;
			for(int k=0; k<N;k++)
			{
				temp += v1(i,k) * v2(k,j);
			}
			res[j] = temp;
			temp = 0;
		}
		for(int l=0; l<N;l++)
		{
			v2(i,l) = res[l];
		}
	}
	return std::move(v2);
}


template<typename T>
Matrix<T>&& operator*( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	std::vector<T> res(v1.dim());
	int N = v1.dim();
	for(int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			T temp = 0;
			for(int k=0; k<N;k++)
			{
				temp += v1(i,k) * v2(k,j);
			}
			res[j] = temp;
			temp = 0;
		}
		for(int l=0; l<N;l++)
		{
			v2(i,l) = res[l];
		}
	}
	return std::move(v1);
}

//scalar mult right
template<typename T>
Matrix<T> operator*(Matrix<T> const& v, T const& scl)
{
	Matrix<T> result(v.dim());
	detail::transform_Matrix1(v, result, [=](T const& x){ return x * scl; });
	return result;
}

template<typename T>
Matrix<T>&& operator*(Matrix<T>&& v, T const& scl)
{
	detail::transform_Matrix1(v, v, [=](T const& x){ return x * scl; });
	return std::move(v);
}

//scalar mult left
template<typename T>
Matrix<T> operator*(T const& scl, Matrix<T> const& v)
{
	Matrix<T> result(v.dim());
	detail::transform_Matrix1(v, result, [=](T const& x){ return scl * x; });
	return result;
}

template<typename T>
Matrix<T>&& operator*(T const& scl, Matrix<T>&& v)
{
	detail::transform_Matrix1(v, v, [=](T const& x){ return scl * x; });
	return std::move(v);
}
// div scalar
template<typename T>
Matrix<T> operator/(Matrix<T> const& v, T const& scl)
{
	Matrix<T> result(v.dim());
	detail::transform_Matrix1(v, result, [=](T const& x){ return x / scl; });
	return result;
}

template<typename T>
Matrix<T>&& operator/(Matrix<T>&& v, T const& scl)
{
	detail::transform_Matrix1(v, v, [=](T const& x){ return x / scl; });
	return std::move(v);
}

//ostream
template<typename T>
std::ostream& operator<< (std::ostream& o, const Matrix<T>& m)
{	
	int N = m.dim();
	o << N << std::endl;
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


//istream
template<typename T>
std::istream& operator>>( std::istream& s, Matrix<T>& m )
{	
	auto restore_stream = [state = s.rdstate(), pos = s.tellg(), &s](){ s.seekg(pos); s.setstate(state); };
	std::string temp;
	std::vector<T> temp_vec;

	std::getline(s, temp, '\n');
	if(temp.size() == 0){ restore_stream(); return s; }	

	int N = std::stoi(temp);
	
	while(std::getline(s, temp, ' '))
	{
		if(temp.size() == 0){ restore_stream(); return s; }	
		temp_vec.push_back(static_cast<T>(std::stod(temp)));
	}

	if(temp_vec.size() > N*N) { std::cout << "Error: more input values than expected!" << std::endl; std::exit(-1); }
	if(temp_vec.size() < N*N) { std::cout << "Error: less input values than expected!" << std::endl; std::exit(-1); }

	m.resize(N);
	for(int i=0;i<N*N;i++)
	{
		m[i] = temp_vec[i];
	}
	
return s;
}
