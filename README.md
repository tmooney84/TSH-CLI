# Welcome to My Zsh
***

## Task
TSH Command Line Interpreter that executes commands binaries and lookup table-based built-in commands.

## Description
Within the TSH shell:

-Command binaries are accessible.

-Limited POSIX-like versions of cd, echo, export, unset, env, exit, pwd, which are accessible as well.

***I used the execvp() instead of the execve() in the main program on accident. If I was to use the execve(), I would pull the Environment Path string, and parse through it for each full binary path and would then use access(full_path, X_OK) to check if the desired binary exists as an executable within the given binary directory. Once found that binary would be executed or return an error that the given command does not exist on the PATH.

## Installation

Clone my_zsh repository using SSH
```
git clone git@git.us.qwasar.io:my_zsh_186296_gyspfr/my_zsh.git
```

Clone my_zsh repository using HTTPS
```
git clone https://git.us.qwasar.io/my_zsh_186296_gyspfr/my_zsh.git
```

Compile TSH shell:
```
make TSH
```

## Usage

Run TSH shell
```
./tsh
```

Run testing on TSH shell:
```
./tests.sh
```

***tests.sh may need to be run two consecutive times for the env command test to function correctly



### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
