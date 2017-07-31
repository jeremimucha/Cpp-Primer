#ifndef SALES_DATA_EXCEPTIONS_H_
#define SALES_DATA_EXCEPTIONS_H_

#include <stdexcept>

/* Execeptions */
/* ------------------------------------------------------------------------- */
class out_of_stock : public std::runtime_error
{
public:
	explicit out_of_stock(const std::string& s)
		: std::runtime_error(s)
		{ }
};

class isbn_mismatch : public std::logic_error
{
public:
	explicit isbn_mismatch(const std::string& s)
		: std::logic_error(s)
		{ }
	isbn_mismatch(const std::string& s,
				  const std::string& lhs, const std::string& rhs)
		: std::logic_error(s), left(lhs), right(rhs)
		{ }
// --- member variables
const std::string left, right;
};
/* ------------------------------------------------------------------------- */


#endif /* SALES_DATA_EXCEPTIONS_H_ */
