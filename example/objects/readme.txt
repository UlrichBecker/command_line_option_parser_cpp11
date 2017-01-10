
1)
Compile and link this example:

make all

2)
And then type for example this:

./e3 -ac Hello world --optional=MyLog -4711 "How are you?" -i42

You'll see the following output:

Non option argument on index 2: Hello
Non option argument on index 3: world
Non option argument on index 5: -4711
Non option argument on index 6: How are you?
Flag a is set
Flag b is not set
Flag c is set
Option with optional argument: MyLog
Integer-value: 42


3)
Have fun playing! :-)

