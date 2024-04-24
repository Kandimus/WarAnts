del _moe.y.cpp
del _moe.l.cpp
cls
flex -o_moe.l.cpp -i -Pyy _moe.l 
bison --token-table --verbose --debug --no-lines -o _moe.y.cpp -p yy _moe.y
rem bison --token-table -o _ugol.y.cpp -p ul ugol.y
