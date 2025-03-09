# Pico Shell

Pico Shell is a minimalistic shell implementation that supports Four Built in commands: `echo` , `cd`,`pwd` and `exit`. If any other command is entered, it Then an external utilities is executed by fork a new process then uses system call called execp to run the needed utility.

---

## Features

- **`echo`**: Prints the provided input to the terminal.
- **`exit`**: Exits the shell.
- **`pwd`** : Prints The current Working Directory.
- **`cd`**  : Change The working Directory to another one.
- **Invalid Command Handling**: Displays "Invalid command" for any unsupported command.
- **`Static and Dynamic Allocation`** : Provides Both Static and Dynamic Allocation 
---

## Usage

- Clone the repository:
   ```bash
   git clone https://github.com/your-username/femto-shell.git
   cd Pico_Shell/"Pico_Shell Static Allocation"

- compile the Static allocation program
   ```bash
   gcc Pico_Shell.c -o Pico_Shell.exe
   
   ./Pico_Shell.exe
   ```
- compile the Dynamic allocation program 
   ```bash
   cd ../"Pico_Shell Dynamic Allocation"
   
   gcc Pico_Shell.c LinkedStackprogram.c -o Pico_Shell.exe

   ./Pico_Shell.exe
   ```


## Allocation

#### **`Dynamic Allocation`** : The Dynamic Allocation using a Stack Like Data Structure i built before in 2024 , But the order of storing the command arguments is not reversed like the stack it look like the linked list .

- **`Allocation Life Cycle`** : 
```
1. The user enters the command
2. The command is stored in a buffer using "fgets()" function
3. The command is parsed by white spaces using "strtok()" function
4. The parsed words is stored in the Dynamic list by "malloc()" function
5. The command is poped word by word to be executed
6. If the command is implemented internally it is executed & no need to fork a new process
7. If not Then the process forks and execute the new program using "fork() " , "execp()" system calls
8. At the end of the command execution The dynamic allocated memory id freed using "free()" function 

```

####  **`Static Allocation`** : The command is parsed and stored in an array with a fixed size.


## Example
```bash
./myFemtoShell.exe 
Yalla beina >>> 
Yalla beina >>> 
Yalla beina >>> 
Yalla beina >>> echo ana femto shell Ramadna kareem                 
ana femto shell Ramadna kareem
Yalla beina >>> 
Yalla beina >>> ls
Invalid command
Yalla beina >>> exit
Good Bye :)
```







