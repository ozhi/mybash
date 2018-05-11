# mybash

A basic command interpreter that executes bash commands.
Written in C, using OS primitive calls like `read`, `fork` and `exec`.

Reads commands from stdin, parses them and their arguments and executes them in a new OS process.

Also has support for background mode.
`sleep 2 &` sleeps for two seconds but lets you enter a new command immediately.

# Try it out

```sh
./compile-run
Compilation successful.
Running...

mybash> ls
mybash mybash.c README.md

mybash> echo some string arguments
some string arguments

mybash> cat no-such-file
cat: no-such-file: No such file or directory

mybash> hfgh
Command hfgh not found

mybash> sleep 2 &

mybash>bye
bye
```
