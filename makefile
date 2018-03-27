# this makefile replaces: g++ main.cpp -o gnh -std=c++11

gnh: main.cpp
	g++ main.cpp -o gnh -std=c++11

# reference: https://web.archive.org/web/20171220210007/http://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html
#
# <target>: [<dependency>]
# <TAB> <command>
