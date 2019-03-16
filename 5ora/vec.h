#include <math.h>


template<typename T>
struct Vector2
{
    T x, y;
    Vector2<T>& operator+=( Vector2<T> const& v )
    {
        x += v.x; y += v.y;
        return *this;
    };
};

template<typename T>
Vector2<T> operator+( Vector2<T> const& a, Vector2<T> const& b )
{
    return Vector2<T>{ a.x + b.x, a.y + b.y };
};

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2<T> const& v )
{
    o << v.x << " " << v.y;
    return o;
};

template<typename T>
T dot(Vector2<T> a, Vector2<T> b)
{
    return a.x * b.x + a.y * b.y;
};

template<typename T>
T sqlength(Vector2<T> a)
{
    return (a.x*a.x + a.y*a.y);
};

template<typename T>
T length(Vector2<T> a)
{
    T result = sqrt(a.x*a.x + a.y*a.y);
    return result;
};

