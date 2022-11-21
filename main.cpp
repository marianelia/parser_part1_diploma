#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/foreach.hpp>

#include <boost/phoenix/stl.hpp>
#include <string>
#include <iostream>
#include <fstream>

namespace client
{
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
typedef std::vector<std::string> vec_str;

//struct func_args
//{
//	//std::string type_out;
//	//std::vector<std::string> namespaces;
//	//std::string name;
//	std::vector<std::pair<std::string, std::string>> args_in;
//};


	template <typename Iterator>
	struct parser_struct : qi::grammar<Iterator, vec_str()>
	{
		parser_struct() : parser_struct::base_type(start)
		{
			using ascii::space;
			using ascii::char_;
			string = qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9");
			name_space = string >> *qi::space >> qi::lit(":") >> qi::lit(":");

			start %= string >> +qi::space >> *name_space >> *qi::space >> string >> *qi::space
						   >> '(' >> *qi::space
						   >> *(string >> +qi::space >> string >> *qi::space
								>> *(qi::lit(',') >> *qi::space >> string >> +qi::space >> string >> *qi::space))
						   >> ')' >> *qi::space
						   >> qi::lit(';');
		}
		qi::rule<Iterator, vec_str()> start;
		qi::rule<Iterator, std::string()> string, name_space;
	};
}

namespace qi = boost::spirit::qi;

int main()
{
	typedef std::string::const_iterator iterator_type;
	client::vec_str vec_parsed_param_of_func;
	client::parser_struct<iterator_type> p;

	std::string str("int n1::n2::func ( int name1,int2 name2) ;");

	//std::ifstream file_input;
	//file_input.open("/home/maria/diploma/v1/main/alsapi.h");


	//while (getline(file_input, str))
	//{
		std::string::const_iterator begin = str.begin();
		std::string::const_iterator end = str.end();
		if(qi::parse(begin, end, p, vec_parsed_param_of_func))
		{
			std::cout << "New line\nSize: " << vec_parsed_param_of_func.size() << '\n';
			for(int i = 0; i<vec_parsed_param_of_func.size(); i++)
			{
				std::cout << vec_parsed_param_of_func[i] << '\n';
			}
		}
		vec_parsed_param_of_func.clear();
	//}
	return 0;
}
