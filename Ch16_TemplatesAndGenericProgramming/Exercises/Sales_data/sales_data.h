#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>

template <class T> class std::hash;

// template<typename T> class std::hash;


class Sales_data {
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend std::istream& operator>>(std::istream&, Sales_data&);
friend bool operator==(const Sales_data&, const Sales_data&);

friend std::ostream& print(std::ostream&, const Sales_data&);
friend std::istream& read(std::istream&, Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);

friend class std::hash<Sales_data>;

public:
	// constructors
	Sales_data() = default;
	Sales_data(const std::string& s): bookNo(s) { }
	Sales_data(const std::string& s, unsigned n, double p):
	           bookNo(s), units_sold(n), revenue(p*n) { }
	Sales_data(std::istream&);
	Sales_data& operator=(const std::string&);

	std::string isbn() const { return bookNo; }
	Sales_data& operator+=(const Sales_data&);
	operator std::string() const { return bookNo; }
	explicit operator double() const { return revenue; }
private:
	double avg_price() const;  
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

// non-member Sales_data operations
inline
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{ return lhs.isbn() < rhs.isbn(); }

inline
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() == rhs.isbn() && 
	       lhs.units_sold == rhs.units_sold && 
	       lhs.revenue == rhs.revenue;
}

inline
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
	return !(lhs == rhs);
}

// old versions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);

// new operator functions
Sales_data operator+(const Sales_data&, const Sales_data&);
std::ostream& operator<<(std::ostream&, const Sales_data&);
std::istream& operator>>(std::istream&, Sales_data&);


namespace std
{
	template<>
	struct hash<Sales_data>
	{
	public:
		// the type used to hash an unordered container must define these types
		typedef size_t result_type;
		typedef Sales_data argument_type;	// by default, this type need ==
		size_t operator()(const Sales_data& s) const;
		// uses synthesized copy control and constructors
	};

	size_t
	hash<Sales_data>::operator()(const Sales_data& s) const
	{
		return hash<std::string>()(s.bookNo) ^
			   hash<unsigned>()(s.units_sold) ^
			   hash<double>()(s.revenue);
	}
}


#endif
