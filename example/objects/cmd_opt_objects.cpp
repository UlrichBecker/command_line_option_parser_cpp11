/*****************************************************************************/
/*                                                                           */
/*       Demonstration of the usage of class CLOP::OPTION_V of the           */
/*       command-line-option-parser for C++11                                */
/*                                                                           */
/*  Overwriting of the callback function CLOP::OPTION_V::onGiven             */
/*  Overwriting of the callback function CLOP::PARSER::onArgument            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*! @file    cmd_opt_objects.cpp                                             */
/*! @author  Ulrich Becker                                                   */
/*! @date    01.01.2017                                                      */
/*! @see     parse_opts.hpp                                                  */
/*****************************************************************************/
#include <cstdlib>
#include <parse_opts.hpp>

using namespace std;
using namespace CLOP; // Namespace for Command-Line-Option-Parser

///////////////////////////////////////////////////////////////////////////////
class OPTION_FLAG: public OPTION_V
{
   bool m_flag;

public:
   OPTION_FLAG( char shortOpt )
   {
      m_flag     = false;
      m_shortOpt = shortOpt;
      m_hasArg   = NO_ARG;
      m_helpText = "Set flag: ";
      m_helpText.push_back( shortOpt );
   }

   bool get( void ) const { return m_flag; }

private:
   int onGiven( PARSER* poParser ) override
   {
      assert( !poParser->isOptArgPersent() );
      m_flag = true;
      return 0;
   }
};

///////////////////////////////////////////////////////////////////////////////
class OPTION_HELP: public OPTION_V
{
public:
   OPTION_HELP( void )
   {
      m_hasArg   = NO_ARG;
      m_shortOpt = 'h';
      m_longOpt  = "help";
      m_helpText = "Print this help\nand exit.";
   }

private:
   int onGiven( PARSER* poParser ) override
   {
      assert( !poParser->isOptArgPersent() );
      cout << "Usage: " << poParser->getProgramName() << " [options,...]\n";
      poParser->list( cout );
      cout << endl;
      exit( EXIT_SUCCESS );
      return 0;
   }
};

///////////////////////////////////////////////////////////////////////////////
class OPTION_OPTIONAL_ARG: public OPTION_V
{
   string  m_sOptional;

public:
   OPTION_OPTIONAL_ARG( void )
   {
      m_hasArg   = OPTIONAL_ARG;
      m_shortOpt = 'o';
      m_longOpt  = "optional";
      m_helpText = "Test for optional argument.";
   }

   bool    isSet( void ) const { return !m_sOptional.empty(); }
   string& get( void ) { return m_sOptional; }

private:
   int onGiven( PARSER* poParser ) override
   {
      if( poParser->isOptArgPersent() )
         m_sOptional = poParser->getOptArg();
      else
         m_sOptional = "Default";

      return 0;
   }
};

///////////////////////////////////////////////////////////////////////////////
class OPTION_REQUIRED_ARG: public OPTION_V
{
   int  m_value;
   bool m_isSet;

public:
   OPTION_REQUIRED_ARG( void )
   {
      m_hasArg   = REQUIRED_ARG;
      m_shortOpt = 'i';
      m_longOpt  = "integer";
      m_helpText = "Test for mandatory integer argument.";
   }

   bool isSet( void ) const { return m_isSet; }
   int  get( void ) const  { return m_value; }

private:
   virtual int onGiven( PARSER* poParser )
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
         print( cerr );
         cerr << " is not a integer number: " << poParser->getOptArg() << endl;
         return -1;
      }

      char* strEnd;
      int i = strtol( str, &strEnd, 10 );

      if( *strEnd != '\0' )
      {
         cerr << poParser->getProgramName() << ": Argument no: " << poParser->getArgIndex()
              << " option: ";
         print( cerr );
         cerr << " has a invalid format: " << poParser->getOptArg() << endl;
         return -1;
      }

      m_value = i;
      m_isSet = true;
      return 0;
   }
};

///////////////////////////////////////////////////////////////////////////////
class MY_PARSER: public PARSER
{
public:
   MY_PARSER( int argc, char** ppArgv ):
      PARSER( argc, ppArgv ) {}

   // The overwriting of the following callback-function makes it enable
   // to evaluate non-option arguments too.
   int onArgument( void ) override
   {
      cout << "Non option argument on index " << getArgIndex() << ": "
           << getArgVect()[getArgIndex()] << endl;
      return 1; // Continue parsing for mixed order.
   }
};

//=============================================================================
int main( int argc, char** ppArgv )
{
   MY_PARSER parser( argc, ppArgv );

   OPTION_FLAG         optA( 'a' );
   OPTION_FLAG         optB( 'b' );
   OPTION_FLAG         optC( 'c' );
   OPTION_HELP         optHelp;
   OPTION_OPTIONAL_ARG optOtionalArg;
   OPTION_REQUIRED_ARG optRequiredIntegerArg;

   // Yes, this following manner is possible, 
   // but I don't know exactly whether this is a real good idea.
   // But this is a demonstration only.
   if( parser( optA )( optB )( optC )( optHelp )( optOtionalArg )( optRequiredIntegerArg )() < 0 )
      return EXIT_FAILURE;

   cout << "Flag a is " << (optA.get()? "set" : "not set") << endl;
   cout << "Flag b is " << (optB.get()? "set" : "not set") << endl;
   cout << "Flag c is " << (optC.get()? "set" : "not set") << endl;

   if( optOtionalArg.isSet() )
      cout << "Option with optional argument: " << optOtionalArg.get() << endl;

   if( optRequiredIntegerArg.isSet() )
      cout << "Integer-value: " << optRequiredIntegerArg.get() << endl;

   return EXIT_SUCCESS;
}
//================================== EOF=======================================
