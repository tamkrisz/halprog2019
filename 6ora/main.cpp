#include "matrix.h"

int main()
{
	auto err = [](auto str){ std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

	//Test default constructor:
	{
		Matrix<double> u;
		if(u.size() != 0)         { err("default contructor test [size]");           }
		if(u.begin() != u.end())  { err("default contructor test [begin == end]");   }
		if(u.cbegin() != u.cend()){ err("default contructor test [cbegin == cend]"); }
	}

	//Test list initialization and indexing:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		if(a.size() != 4)                            { err("initializer list constructor test [size]");               }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 2.2){ err("initializer list constructor test [indexing with []]");   }
		if(a(0,0) != 3.1 || a(0,1) != 5.2 || a(1,0) != 9.3 || a(1,1) != 2.2){ err("initializer list constructor test [indexing with (i,j)]");   }
		if( ++ ++ ++ ++ (a.begin()) != a.end() )         { err("initializer list constructor test [begin + 3 == end]");   }
		if( ++ ++ ++ ++ (a.cbegin()) != a.cend() )       { err("initializer list constructor test [cbegin + 3 == cend]"); }
	}
	//Test copy constructor:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b{a};
		if(b.size() != 4)                            { err("copy constructor test [size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 2.2){ err("copy constructor test [elements]");           }
		if( ++ ++ ++ ++(b.begin()) != b.end() )         { err("copy constructor test [begin + 3 == end]");   }
		if( ++ ++ ++ ++(b.cbegin()) != b.cend() )       { err("copy constructor test [cbegin + 3 == cend]"); }
		if(a.size() != 4)                            { err("copy constructor test [src size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 2.2){ err("copy constructor test [src elements]");       }
	}

	//Test move constructor:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b{ std::move(a) };
		if(a.size() != 0)                            { err("move constructor test [src size]");             }
		if(a.begin() != a.end())                     { err("move constructor test [src begin == src end]"); }
		if(b.size() != 4)                            { err("move constructor test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 2.2){ err("move constructor test [elements]");             }
		if( ++ ++ ++ ++(b.begin()) != b.end() )         { err("move constructor test [begin + 3 == end]");     }
		if( ++ ++ ++ ++(b.cbegin()) != b.cend() )       { err("move constructor test [cbegin + 3 == cend]");   }
	}

	//Test assignment:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b;
		b = a;
		if(b.size() != 4)                            { err("assignment test [size]");         }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 2.2){ err("assignment test [elements]");     }
		if(a.size() != 4)                            { err("assignment test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 2.2){ err("assignment test [src elements]"); }
	}

	//Test self assignment:
	{
		Matrix<double> c = {2, {3.1, 5.2, 9.3, 2.2}};
		c = c;
		if(c.size() != 4)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3 || c[3] != 2.2){ err("self assignment test [elements]"); }
	}

	//Test move assignment:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b;
		b = std::move(a);
		if(a.begin() != a.end())                     { err("assignment test [src begin == src end]"); }
		if(a.size() != 0)                            { err("assignment test [src size]");             }
		if(b.size() != 4)                            { err("assignment test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 2.2){ err("assignment test [elements]");             }
	}

	//Test self move assignment:
	{
		Matrix<double> c = {2, {3.1, 5.2, 9.3, 2.2}};
		c = std::move(c);
		if(c.size() != 4)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3 || c[3] != 2.2){ err("self assignment test [elements]"); }
	}

	//Add, sub, mult, div by scalar
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> ref = {2, {5.1, 7.2, 11.3, 4.2}};
	    a += 2;
		if(a.size() != 4)                              { err("+= test [size]");         }
		a -= ref;
		if(length(a) > 1e-14)                    { err("+= test [value]");        }
	}
	//Test -=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> ref = {2, {1.1, 3.2, 7.3, 0.2}};
	    a -= 2;
		if(a.size() != 4)                              { err("-= test [size]");         }
		a -= ref;
		if(length(a) > 1e-14)                    { err("-= test [value]");        }
	}
	//Test *=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> ref = {2, {6.2, 10.4, 18.6, 4.4}};
		a *= 2.0;
		if(a.size() != 4)          { err("*= test [size]");  }
		a -= ref;
		if(length(a) > 1e-14)                    { err("*= test [value]");        }
	}
	//Test /=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> ref = {2, {1.55, 2.6,  4.65, 1.1}};
		a /= 2.0;
		if(a.size() != 4)          { err("/= test [size]");  }
		a -= ref;
		if(length(a) > 1e-14)                    { err("/= test [value]");        }
	}
	
	//Add, sub, mult, div by matrix
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b   = {2, {7.1, 15.2, 11.3, 1.0}};
		Matrix<double> ref = {2, {10.2, 20.4, 20.6, 3.2}};
	    a += b;
		if(a.size() != 4)                              { err("+= test [size]");         }
		if(b.size() != 4)                              { err("+= test [src size]");     }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("+= test [src elements]"); }
		a -= ref;
		if(length(a) > 1e-14)                    { err("+= test [value]");        }
	}
	//Test -=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b   = {2, {1.0, 2.0, 3.0, 1.2}};
		Matrix<double> ref = {2, {2.1, 3.2, 6.3, 1.0}};
		a -= b;
		if(a.size() != 4)                            { err("-= test [size]");         }
		if(b.size() != 4)                            { err("-= test [src size]");     }
		if(b[0] != 1.0 || b[1] != 2.0 || b[2] != 3.0 || b[3] != 1.2){ err("-= test [src elements]"); }
		a -= ref;
		if(length(a) > 1e-14)                    { err("-= test [value]");        }
	}

	//Test *=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 1.0, 2.2}};
		Matrix<double> b   = {2, {5.0, 2.0, 3.0, 4.0}};
		Matrix<double> ref = {2, {31.1, 27, 11.6, 10.8}};
		a *= b;
		if(a.size() != 4)                            { err("*= test [size]");         }
		if(b.size() != 4)                            { err("*= test [src size]");     }
		if(b[0] != 5.0 || b[1] != 2.0 || b[2] != 3.0 || b[3] != 4.0){ err("*= test [src elements]"); }
		a -= ref;
		if(length(a) > 1e-14)                    { err("*= test [value]");        }
	}

	//Test /=:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.0, 16.0}};
		Matrix<double> b   = {2, {1.0, 2.0, 3.0, 4.0}};
		Matrix<double> ref = {2, {3.1, 2.6, 3.0, 4.0}};
		a /= b;
		if(a.size() != 4)                            { err("/= test [size]");         }
		if(b.size() != 4)                            { err("/= test [src size]");     }
		if(b[0] != 1.0 || b[1] != 2.0 || b[2] != 3.0 || b[3] != 4.0){ err("/= test [src elements]"); }
		a -= ref;
		if(length(a) > 1e-14)                    { err("/= test [value]");        }
	}

	//Add, sub, mult, div by matrix #2
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b   = {2, {7.1, 15.2, 11.3, 1.0}};
		Matrix<double> ref = {2, {10.2, 20.4, 20.6, 3.2}};
		Matrix<double> c;
	    c = a + b;
		if(a.size() != 4)                              { err("+ test [size]");         }
		if(b.size() != 4)                              { err("+ test [src size]");     }
		if(c.size() != 4)                              { err("+ test [result size]");     }
		c -= ref;
		if(length(c) > 1e-14)                    { err("+ test [value]");        }
	}
	//Test -:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.3, 2.2}};
		Matrix<double> b   = {2, {1.0, 2.0, 3.0, 1.2}};
		Matrix<double> ref = {2, {2.1, 3.2, 6.3, 1.0}};
		Matrix<double> c;
	    c = a - b;
		if(a.size() != 4)                            { err("- test [size]");         }
		if(b.size() != 4)                            { err("- test [src size]");     }
		if(c.size() != 4)                            { err("- test [src size]");     }
		c -= ref;
		if(length(c) > 1e-14)                    { err("- test [value]");        }
	}

	//Test *:
	{
		Matrix<double> a = {2, {3.1, 5.2, 1.0, 2.2}};
		Matrix<double> b   = {2, {5.0, 2.0, 3.0, 4.0}};
		Matrix<double> ref = {2, {31.1, 27, 11.6, 10.8}};
		Matrix<double> c;
	    c = a * b;
		if(a.size() != 4)                            { err("* test [size]");         }
		if(b.size() != 4)                            { err("* test [src size]");     }
		if(c.size() != 4)                            { err("* test [src size]");     }
		c -= ref;
		if(length(c) > 1e-14)                    { err("* test [value]");        }
	}

	//Test /:
	{
		Matrix<double> a = {2, {3.1, 5.2, 9.0, 16.0}};
		Matrix<double> b   = {2, {1.0, 2.0, 3.0, 4.0}};
		Matrix<double> ref = {2, {3.1, 2.6, 3.0, 4.0}};
		Matrix<double> c;
	    c = a / b;
		if(a.size() != 4)                            { err("/ test [size]");         }
		if(b.size() != 4)                            { err("/ test [src size]");     }
		if(c.size() != 4)                            { err("/ test [src size]");     }
		c -= ref;
		if(length(c) > 1e-14)                    { err("/ test [value]");        }
	}
	
	return 0;
}
