/*****************************************************************************/
/*                                                                           */
/*      Test program for using the command line option parser for C++11.     */
/*                                                                           */
/* Demonstration for using initializer-lists with callback lambda-functions  */
/* and the overwritten callback function CLOP::OPTION_V::onGiven.            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*! @file    cmd_opt_test.cpp                                                */
/*! @author  Ulrich Becker                                                   */
/*! @date    17.12.2016                                                      */
/*! @see     parse_opts.hpp                                                  */
/*****************************************************************************/
#include <parse_opts.hpp>

using namespace std;
using namespace CLOP; // Namespace for Command-Line-Option-Parser

///////////////////////////////////////////////////////////////////////////////
// Initializer-list of options.
static vector<OPTION> optList =
{
   {
      OPT_LAMBDA( parser,
      {
         assert( !parser->isOptArgPersent() );
         cout << "Usage: " << parser->getProgramName() << " [options,...]\n";
         parser->list( cout );
         cout << endl;
         return 0;
      }),
      .m_hasArg   = OPTION::NO_ARG,
      .m_id       = 0,
      .m_shortOpt = 'h',
      .m_longOpt  = "help",
      .m_helpText = "Print this help\nand exit"
   },
   {
      OPT_LAMBDA( parser,
      {
         assert( parser->isOptArgPersent() );
         cout << "Option: ";
         parser->getCurrentOption()->print( cout );
         cout << "\nArgument: " << parser->getOptArg() << endl;
         return 0;
      }),
      .m_hasArg   = OPTION::REQUIRED_ARG,
      .m_id       = 0,
      .m_shortOpt = 'r',
      .m_longOpt  = "required",
      .m_helpText = "Test for required argument."
   },
   {
      // We do not necessarily need the macro OPT_LAMBDA
      .m_func = [] (PARSER* parser) -> int
      {
         cout << "Option: ";
         parser->getCurrentOption()->print( cout );
         cout << '\n';
         if( parser->isOptArgPersent() )
            cout << "Argument: " << parser->getOptArg() << endl;
         else
            cout << "No argument" << endl;
         return 0;
      },
      .m_hasArg   = OPTION::OPTIONAL_ARG,
      .m_id       = 0,
      .m_shortOpt = 'o',
      .m_longOpt  = "optional",
      .m_helpText = "Test for optional argument."
   }
};

///////////////////////////////////////////////////////////////////////////////
// Class to overwrite the callback-function CLOP::OPTION_V::onGiven
class MY_OPTION_V: public OPTION_V
{
public:
   MY_OPTION_V( void )
   {
      m_hasArg   = NO_ARG;
      m_shortOpt = 'v';
      m_longOpt  = "virtual";
      m_helpText = "Test for virtual callback function.";
   }
   virtual ~MY_OPTION_V( void ) {}
   virtual int onGiven( PARSER* poParser )
   {
      cout << "Virtual function" << endl;
      return 0;
   }
};

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** ppArgv )
{
   MY_OPTION_V optVirtual;
   PARSER parser( argc, ppArgv, optList );

   parser( optVirtual );

   parser.sortLong();

   for( int i = 1; i < argc; i++ )
   {
      i = parser( i );
      if( i < 0 )
         return EXIT_FAILURE;
      if( i < argc )
         cout << "Non option argument on index " << i << ": " << ppArgv[i] << endl;
   }
   return EXIT_SUCCESS;
}

//================================== EOF=======================================
