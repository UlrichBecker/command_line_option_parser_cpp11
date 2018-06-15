#A commandline (option) parser for C++11 projects

An alternative to getopt() and getopt_long() (and boost::program_options) by using of callback functions for each
recognized option in the shape of:
- classical function-pointers
- anonymous "lambda" functions
- or virtual object-functions

# Advantages:

- Avoiding of global variables like "optind" or "optarg".
- Using of a callback function for each option instead of (confusing huge) switch-case- or if-statements. (Avoiding of spaghetti-code.)
- Use of anonymous callback functions (lambda functions) possible.
  That means implementation of the function body directly in the option-list initializer possible. (See code-example below.)
- Object oriented flavor: Short option-name (if given), long option-name (if given) and help-text (if given)
  are bound together in a single object by a corresponding callback function.
- Avoiding of redundance: If you'll change a option name, so you have to do this on one place in your source-code only.
- Commands by mixed order of options and non-options are possible.
- Specialized callback objects per single option and/or initializer-lists with callback lambda- functions and/or
  function-pointers are possible. (This is a matter of taste.)
- Scalable, if a serten kind of option-type won't used for your project just define the corresponding compiler-switch (CONFIG_CLOP_NO_...) in your Makefile respectively build-system to reduce memory, provided you'll link the sourc-ecode directly to your project rather than the shared-library.


If you intend to write a pure C-project or you are not allowed to write your program in C++ (not to mention in C++11), so you can take a look in the following link:

https://github.com/UlrichBecker/command_line_option_parser

A practical application using this module you can find in this repository:
https://github.com/UlrichBecker/DocFsm

Excuses my Eric Allman coding-style and my bad English ;-)

Code-example
------------
Example for using lambda callback function in a initializer-list:

See also ./example/lambda/cmd_opt_lambda.cpp
```c++
#include <parse_opts.hpp>

using namespace std;
using namespace CLOP; // Namespace for Command-Line-Option-Parser

int main( int argc, char** ppArgv )
{
   // Initializer-list 
   vector<OPTION> optList = 
   {
      {
         OPT_LAMBDA( parser,
         {
            cout << "Usage: " << parser->getProgramName() << " [options,...]\n";
            parser->list( cout );
            cout << endl;
            exit( EXIT_SUCCESS );
            return 0;
         }),
         .m_hasArg   = OPTION::NO_ARG,
         .m_id       = 0,
         .m_shortOpt = 'h',
         .m_longOpt  = "help",
         .m_helpText = "Print this help and exit"
      },
      {
         //... further options ...
      }
   };

   PARSER parser( argc, ppArgv, optList );

   for( int i = 1; i < argc; i++ )
   {
      i = parser( i );
      if( i < 0 )
         return EXIT_FAILURE;
      if( i < argc )
         cout << "Non option argument on index " << i << ": " << ppArgv[i] << endl;
   }
   // Do something others...
   return EXIT_SUCCESS;
}
```

Example for using virtual object-functions for each option:

See also ./example/objects/cmd_opt_objects.cpp
```c++
#include <parse_opts.hpp>

using namespace std;
using namespace CLOP; // Namespace for Command-Line-Option-Parser

class OPTION_HELP: public OPTION_V
{
public:
   OPTION_HELP( void )
   {
      m_hasArg   = NO_ARG;
      m_shortOpt = 'h';
      m_longOpt  = "help";
      m_helpText = "Print this help and exit.";
   }

private:
   // Function becomes immediately triggered if the parser recognized
   // the option "-h" or "--help" in the commend-line.
   int onGiven( PARSER* poParser ) override
   {
      cout << "Usage: " << poParser->getProgramName() << " [options,...]\n";
      poParser->list( cout );
      cout << endl;
      exit( EXIT_SUCCESS );
      return 0;
   }
};

// Further classes inherited of the base-class CLOP::OPTION_V ...

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

int main( int argc, char** ppArgv )
{
   MY_PARSER parser( argc, ppArgv );
   OPTION_HELP optHelp;
   // ... further objects of the base CLOP::OPTION_V
   if( parser( optHelp )() < 0 )
      return EXIT_FAILURE;
   // Do something others ...
   return EXIT_SUCCESS;
}

```
