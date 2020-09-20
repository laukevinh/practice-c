# practice-c
data structures implemented in C

## Compiling C in Linux
Use `gcc` to compile your source code
```
gcc -o <output_file_name> <source_code.c>
```
Compile with -g3 option to show debugging info. This allows gdb to translate machine addresses back into identifiers and line numbers in the original program.
```
gcc -g3 -o <output_file_name> <source_code.c>
```

## Running your file
Simply execute using 
```
./<output_file_name>
```

## Debugging
```
$ gdb ./<output_file_name>
(gdb) break main
(gdb) run
```
Use `n` for next, `s` to step, `p <var>` to print a variable once, and `display <var>` to print every iteration.