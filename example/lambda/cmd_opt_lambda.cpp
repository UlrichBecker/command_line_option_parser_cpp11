/*****************************************************************************/
/*                                                                           */
/*   Demonstration for using the command line option parser for C++11.       */
/*                                                                           */
/*   Usage of initializer-list with lambda-functions and function-pointers.  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*! @file    cmd_opt_lambda.cpp                                              */
/*! @author  Ulrich Becker                                                   */
/*! @date    31.12.2016                                                      */
/*! @see     parse_opts.hpp                                                  */
/*****************************************************************************/

/*
 * NOTE:
 * If you have been made and installed the shared-library via the makefile in
 * /src/makefile just compile this example by the following line:
 *
 * g++ -std=c++11 -o e2 -lParseOptsCpp11 cmd_opt_lambda.cpp
 *
 * otherwise invoke the makefile in this directory.
 */

#include <cstdlib>
#include <parse_opts.hpp>

using namespace std;
using namespace CLOP; // Namespace for Command-Line-Option-Parser

///////////////////////////////////////////////////////////////////////////////
class MY_PARSER: public PARSER
{
   unsigned int m_flags;
   string       m_sOptional;
   int          m_integer;
   bool         m_intSet;

public:
   MY_PARSER( int argc,
              char** ppArgv,
              vector<OPTION>& optList
            ):
            PARSER( argc, ppArgv, optList ),
            m_flags( 0 ),
            m_integer( 0 ),
            m_intSet( false )
   {
   }

   void setFlag( unsigned int n )
   {
      assert( n < (sizeof(m_flags) * 8) );
      m_flags |= (1 << n);
   }

   bool getFlag( unsigned int n )
   {
      assert( n < (sizeof(m_flags) * 8) );
      return ((m_flags & (1 << n)) != 0);
   }

   void setOptionalArg( string s ) { m_sOptional = s; }
   string& getOptionalArg( void )  { return m_sOptional; }
   void setInteger( int i ) { m_intSet = true; m_integer = i; }
   int getInteger( void ) const { return m_integer; }
   bool isIntSet( void ) const { return m_intSet; }
};

///////////////////////////////////////////////////////////////////////////////
// The following function is to large to implement it as lambda-function,
// therefore its used as classical function-pointer.
int readInteger( PARSER* poParser )
{
   #define IS_DIGIT( d ) (((d) >= '0') && ((d) <= '9'))
   assert( poParser->isOptArgPersent() );

   const char* str = poParser->getOptArg().c_str();

   if( (*str != '-' && *str != '+'  && !IS_DIGIT( *str )) ||
      ((*str == '-' || *str == '+') && !IS_DIGIT( str[1] ))
     )
   {
      cerr << poParser->getProgramName() << ": Argument no: " << poParser->getArgIndex()
           << " option: ";
      poParser->getCurrentOption()->print( cerr );
      cerr << " is not a integer number: " << poParser->getOptArg() << endl;
      return -1;
   }

   char* strEnd;
   int i = strtol( str, &strEnd, 10 );

   if( *strEnd != '\0' )
   {
      cerr << poParser->getProgramName() << ": Argument no: " << poParser->getArgIndex()
           << " option: ";
      poParser->getCurrentOption()->print( cerr );
      cerr << " has a invalid format: " << poParser->getOptArg() << endl;
      return -1;
   }

   static_cast<MY_PARSER*>(poParser)->setInteger(i);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** ppArgv )
{
   // Initializer-list 
   vector<OPTION> optList = 
   {
      {
         OPT_LAMBDA( parser,
         {
            assert( !parser->isOptArgPersent() );
            cout << "Usage: " << parser->getProgramName() << " [options,...]\n";
            parser->list( cout );
            cout << endl;
            exit( EXIT_SUCCESS );
            return 0;
         }),
         .m_hasArg   = OPTION::NO_ARG,
         .m_id       = 0,
         .m_shortOpt = 0,
         .m_longOpt  = "help",
         .m_helpText = "Print this help\nand exit"
      },
      {
         OPT_LAMBDA( poMyParser,
         {
            assert( !poMyParser->isOptArgPersent() );
            static_cast<MY_PARSER*>(poMyParser)->setFlag( 0 );
            return 0;
         }),
         .m_hasArg   = OPTION::NO_ARG,
         .m_id       = 0,
         .m_shortOpt = 'a',
         .m_longOpt  = "",
         .m_helpText = "Set flag \"a\"."
      },
      {
         OPT_LAMBDA( poMyParser,
         {
            assert( !poMyParser->isOptArgPersent() );
            static_cast<MY_PARSER*>(poMyParser)->setFlag( 1 );
            return 0;
         }),
         .m_hasArg   = OPTION::NO_ARG,
         .m_id       = 0,
         .m_shortOpt = 'b',
         .m_longOpt  = "",
         .m_helpText = "Set flag \"b\"."
      },
      {
         OPT_LAMBDA( poMyParser,
         {
            assert( !poMyParser->isOptArgPersent() );
            static_cast<MY_PARSER*>(poMyParser)->setFlag( 2 );
            return 0;
         }),
         .m_hasArg   = OPTION::NO_ARG,
         .m_id       = 0,
         .m_shortOpt = 'c',
         .m_longOpt  = "",
         .m_helpText = "Set flag \"c\"."
      },
      {
         OPT_LAMBDA( poMyParser,
         {
            if( poMyParser->isOptArgPersent() )
               static_cast<MY_PARSER*>(poMyParser)->setOptionalArg( poMyParser->getOptArg() );
            else
               static_cast<MY_PARSER*>(poMyParser)->setOptionalArg( "Default" );
            return 0;
         }),
         .m_hasArg   = OPTION::OPTIONAL_ARG,
         .m_id       = 0,
         .m_shortOpt = 'o',
         .m_longOpt  = "optional",
         .m_helpText = "Test for optional argument."
      },
      {
         .m_func     = readInteger, // Classical function-pointer.
         .m_hasArg   = OPTION::REQUIRED_ARG,
         .m_id       = 0,
         .m_shortOpt = 'i',
         .m_longOpt  = "integer",
         .m_helpText = "Test for mandatory integer argument."
      }
   };

   MY_PARSER parser( argc, ppArgv, optList );

   for( int i = 1; i < argc; i++ )
   {
      i = parser( i );
      if( i < 0 )
         return EXIT_FAILURE;
      if( i < argc )
         cout << "Non option argument on index " << i << ": " << ppArgv[i] << endl;
   }

   cout << "Flags:\n";
   for( int i = 0; i < 3; i++ )
      cout << static_cast<char>('a' + i) << ": "
           << (parser.getFlag( i )? "set" : "not set") << endl;

   if( !parser.getOptionalArg().empty() )
      cout << "Option with optional argument: " << parser.getOptionalArg() << endl;

   if( parser.isIntSet() )
      cout << "Integer-value: " << parser.getInteger() << endl;

   return EXIT_SUCCESS;
}
//================================== EOF=======================================
