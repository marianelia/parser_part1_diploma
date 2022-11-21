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

	struct FuncArgs
	{
	//std::string type_out;
	//std::vector<std::string> namespaces;
	//std::string name;
	//std::vector<std::pair<std::string, std::string>> args_in;
		std::vector<std::string> arg_in_types;
		std::vector<std::string> arg_in_names;
	};


	template <typename Iterator>
	struct parser_struct : qi::grammar<Iterator, FuncArgs()>
	{
		parser_struct() : parser_struct::base_type(start)
		{
			using ascii::space;
			using ascii::char_;
			string = qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9");

			list_arg_in_types = string;
			//list_arg_in_names = string;

			start %= "(" >> *qi::space >> list_arg_in_types >> +qi::space >> list_arg_in_types >> *qi::space
						// >> *("," >> list_arg_in_types >> +qi::space >> list_arg_in_names >> *qi::space)
						 >> ")";
			//name_space = string >> *qi::space >> qi::lit(":") >> qi::lit(":");

//			start %= string >> +qi::space >> *name_space >> *qi::space >> string >> *qi::space
//						   >> '(' >> *qi::space
//						   >> *(string >> +qi::space >> string >> *qi::space
//								>> *(qi::lit(',') >> *qi::space >> string >> +qi::space >> string >> *qi::space))
//						   >> ')' >> *qi::space
//						   >> qi::lit(';');

			BOOST_SPIRIT_DEBUG_NODES( (start) (list_arg_in_types) )
		}
		private:

		qi::rule<Iterator, std::string()> string;
		qi::rule<Iterator, std::vector<std::string>()> list_arg_in_types;
		//qi::rule<Iterator, std::vector<std::string>()> list_arg_in_names;
		qi::rule<Iterator, FuncArgs()> start;
	};
}

BOOST_FUSION_ADAPT_STRUCT(client::FuncArgs,
		(std::vector<std::string>, arg_in_types)
		(std::vector<std::string>, arg_in_names)
						  )

namespace qi = boost::spirit::qi;

int main()
{
	typedef std::string::const_iterator iterator_type;
	//client::vec_str vec_parsed_param_of_func;
	client::parser_struct<iterator_type> p;

	client::FuncArgs func_args;

	//std::string str("int n1::n2::func ( int name1,int2 name2) ;");
	std::string str("( int name1 )");

	//std::ifstream file_input;
	//file_input.open("/home/maria/diploma/v1/main/alsapi.h");


	//while (getline(file_input, str))
	//{
		std::string::const_iterator begin = str.begin();
		std::string::const_iterator end = str.end();
		if(qi::parse(begin, end, p, func_args))
		{
			//std::cout << "\nSize: " << func_args.arg_in_types.size() << '\n';
			for(int i = 0; i<func_args.arg_in_types.size(); i++)
			{
				std::cout  << "arg_in_types: "<< func_args.arg_in_types[i] << '\n';
			}
			for(int i = 0; i<func_args.arg_in_names.size(); i++)
			{
				std::cout  << "arg_in_names: "<< func_args.arg_in_names[i] << '\n';
			}
		}
		//vec_parsed_param_of_func.clear();
	//}
	return 0;
}
