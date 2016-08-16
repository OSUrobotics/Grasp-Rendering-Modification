#OpenRAVE Tips:

##Installation
To install openrave, download openrave_0.9-1_amd64.deb and run. To install the Collada support debians, run the file openrave_install_script.sh.

##Modifications to source code
The qtcoinrave folder contains a modified version of the qtcoinrave plugin. To add these changes to your installation of OpenRAVE, simply replace your qtcoinrave folder with the one here.

##Debugging
To compile a debug version of the OpenRAVE source, cd to the top level OpenRAVE folder and run the set of commands:

`cmake -DCMAKE_INSTALL_PREFIX=/my/new/install/dir -DCMAKE_BUILD_TYPE=Debug ..`


Note, `/my/new/install/dir` will most likely be `usr/local`.


OpenRAVE uses a Python frontend to run a C++ backend. Because of this, it is necessary to launch the program using Python, then find OpenRAVE's program ID and attatch it to gdb after it is already running. First, launch OpenRAVE as you normally would: 
`openrave.py --example hanoi`

Then, in a new terminal window, use the htop program manager to locate OpenRAVE and find its program ID. In the command line, simply type `htop` to start the program manager.

Once the program ID has been located, run gdb as root and then attach the program to the debugger.

```sudo gdb
  (gdb) attach 123456```
  
proceed to use gdb as normally.

