template<typename T>
struct Vector2d
{
    T x, y;
    Vector2d<T>& operator+=( Vector2d<T> const& v )
    {
        x += v.x; y += v.y;
        return *this;
    };
    Vector2d<T>& operator-=( Vector2d<T> const& v )
    {
        x -= v.x; y -= v.y;
        return *this;
    };
};

template<typename T>
Vector2d<T> operator-( Vector2d<T> const& a, Vector2d<T> const& b )
{
    return Vector2d<T>{ a.x + b.x, a.y + b.y };
};

template<typename T>
Vector2d<T> operator+( Vector2d<T> const& a, Vector2d<T> const& b )
{
    return Vector2d<T>{ a.x - b.x, a.y - b.y };
};

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& v )
{
    o << v.x << " " << v.y;
    return o;
};

template <typename T>
std::istream& operator>>( std::istream& i, Vector2d<T> & v )
{
    i >> v.x;
    i >> v.y;
    return i;
};

template<typename T>
T dot(Vector2d<T> const& a, Vector2d<T> const& b)
{
    return a.x * b.x + a.y * b.y;
};

template<typename T>
T sqlength(Vector2d<T> const& a)
{
    return a.x*a.x + a.y*a.y;
};

template<typename T>
T length(Vector2d<T> const& a)
{
    T result = sqrt(a.x*a.x + a.y*a.y);
    return result;
};

