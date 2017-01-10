
1)
Compile and link this example:

make all

2)
And then type for example this:

./e1 -vr¡Hola! --optional = "¿Cómo estás?" -h

You'll see the following output:

Virtual function
Option: -r <PARAM>, --required <PARAM>
Argument: ¡Hola!
Option: -o [=PARAM], --optional [=PARAM]
Argument: ¿Cómo estás?
Usage: ./e1 [options,...]

-h, --help
        Print this help
        and exit

-o [=PARAM], --optional [=PARAM]
        Test for optional argument.

-r <PARAM>, --required <PARAM>
        Test for required argument.

-v, --virtual
        Test for virtual callback function.


3)
Have fun playing! :-)

