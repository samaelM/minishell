# Minishell

## About the project

Minishell is a project from the 42School cursus, it aims to replicate the fundamentals features of the bash shell
such as executing commands/programs from an absolute or relative path, expanding environment variable, having a working
command history system etc.

## How to use it

You, of course, need to download the project then you can simply compile the code with the makefile provided using the command make on your shell.

```bash
git clone https://github.com/samaelM/minishell.git
cd minishell
make
```

## Features

The following features have been implemented:

- A working command history
- Launch the right executable (based on the PATH variable or using a relative or an absolute path)
- Redirections
  - "<" The command takes an infile
  - ">" The command takes an outfile, truncating the file if it exist
  - "<<" The command takes a here document as infile
  - ">>" The comman takes an outfile, not truncating it if it exist
- Piping commands
- Handle environment variables and $?
- Handle signals
  - "ctrl + C" Display an new line in interactive mode
  - "ctrl + \" Does nothing in interactive mode
  - "ctrl + D" Exit the shell
- Builtins
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
 
## Limitations

The following bash features have not been implemented:

- Unclosed quote handling
- Specials characters such as semicolons or backslashs
- Local variables
- Aliases
- Wildcards
- Comparators such as `&&` or `||`
- Parenthesis
- some more...

## About the name

This shell name is "poivre et shell", it's a pun with "poivre et sel" (pepper and salt in french) and shell

## Thanks

Special thanks to [@Anaelle42](https://github.com/Anaelle42), collaborator in this project
and a precious friend of mine, the project would not have been possible without her.

## Contacts

if you encounter any bugs or if you have some questions, please contact me at maemaldo@student.42.fr
