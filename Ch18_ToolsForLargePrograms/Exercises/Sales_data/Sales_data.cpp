#include "Sales_data.h"
#include <string>
using std::istream; using std::ostream;


Sales_data& Sales_data::operator=(const std::string& s)
{
	bookNo = s;
	return *this;
}

Sales_data::Sales_data(istream& is) 
{
	is >> *this; // read a transaction from is into this object
}

// double Sales_data::avg_price() const
// {
// 	if (units_sold)
// 		return revenue/units_sold;
// 	else
// 		return 0;
// }

// member binary operator: left-hand operand is bound to the implicit this pointer
/* ------------------------------------------------------------------------- */
// assumes that both objects refer to the same book
// Sales_data& Sales_data::operator+=(const Sales_data& rhs)
// {
// 	units_sold += rhs.units_sold;
// 	revenue += rhs.revenue;
// 	return *this;
// }

// // assumes that both objects refer to the same book
// Sales_data 
// operator+(const Sales_data& lhs, const Sales_data& rhs)
// {
// 	Sales_data sum = lhs;  // copy data members from lhs into sum
// 	sum += rhs;            // add rhs into sum
// 	return sum;
// }
/* ------------------------------------------------------------------------- */

/* Alternative implementation for + and += operators 						 */
/* ------------------------------------------------------------------------- */
// assumes both object refer to the same book
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs)
{
	if(lhs.isbn() != rhs.isbn())
		throw isbn_mismatch("<Sales_data::operator+> ISBN's don't match",
			lhs.isbn(), rhs.isbn());
	return Sales_data(lhs.bookNo
					 ,lhs.units_sold + rhs.units_sold
					 ,lhs.avg_price() + rhs.avg_price());
}

// assumes both object refer to the same book
Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
	*this = *this + rhs;
	return *this;
}
/* ------------------------------------------------------------------------- */

istream& operator>>(istream& is, Sales_data& item)
{
	double price;  // no need to initialize; we'll read into price before we use it
	is >> item.bookNo >> item.units_sold >> price;
	if (is)        // check that the inputs succeeded
    	item.revenue = item.units_sold * price;
	else
    	item = Sales_data(); // input failed: give the object the default state
	return is;
}

ostream& operator<<(ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.units_sold << " " 
	   << item.revenue << " " << item.avg_price();
	return os;
}

// operators replace these original named functions
istream& read(istream& is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}
ostream& print(ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.units_sold << " " 
	   << item.revenue << " " << item.avg_price();
	return os;
}
	
Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;  // copy data members from lhs into sum
	sum += rhs;            // add rhs into sum
	return sum;
}

