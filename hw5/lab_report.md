# Lab Report: Format String Attack Lab

Robert D. Hernandez <rherna70@uic.edu>

## Env Setup

Disable Address Space Layout Randomization

`sudo sysctl -w kernel.randomize_va_space=0`

## Task 1: Crashing the Program

Initial run with benign input
![alt text](./images/run-one-benign.png)

Create initial payload file:
![alt text](./images/initial-payload.png)

Injecting inital payload to format program
![alt text](./images/inject-initial-payload.png)

After changing the line `build_string.py` program line 

```c
# s = "%.8x"*1200 + "%n"
```
to 
```c
s = "%s"*12
```

`format` Program crashes as expected:

![alt text](./images/format_program_crash.png)

My solution for Task 1 is located at `./attack-code/task_1_crash_program.py`

Start the docker compose stack, and invoke it with

```sh
$ task run_task1
````
then Press Ctrl+C.

We use a format string with twelve (12) %s format string modifiers to encounter the first memory address that is invalid.


### Task 2: Printing out the Server Program's Memory

### Task 2.A: Stack Data

My solution for Task 2A is located at `./attack-code/task_2A_stack_data.py`


Start the docker compose stack, and invoke it with

`
$ task run_task2A
`

then Press Ctrl+C.

We use the python program to create an input buffer with a number at it's highest memory value and a sequence four dummy chars "abcd" (not important to the solution), followed by sixty-four (64) modified "%x" modifiers.  The literal string used was "%.8x. which serves to make the program output slightly more human readable by placing full stops between memory elements. 

The 64th index was found through trial and error by first printing quite a bit of the stack and experimenting with smaller values.

![alt text](./images/print_program_memory.png)

Importantly, we observe that the program prints the bytes as a string instead of as a number.

![alt text](./images/task_2A_complete.png)

This observation is significant because it here at the 64th index that we observe the alignment of the va_list pointer in printf with the data that we injected at runtime through user input "3735928559" as a hexademical number "0xdeadbeef".


### Task 2.B: Heap Data

My solution for Task 2A is located at `./attack-code/task_2A_stack_data.py`


Start the docker compose stack, and invoke it with

`
$ task run_task2B
`

then Press Ctrl+C.

With the va_list pointer aligned at the 64th element, we replace "%x" with "%s" and we replace the bytes for our number with the address on the heap of the char buffer of the string we want to print using the "%s" format modifier.

```c
s = "%.8x."* 63 + "%s"
```

When executing our attack with netcat, we cause the format program to print the buffer at the memory address we injected over the network via user input.

![alt text](./images/task_2B_complete.png)

## Task 3: Modifying the Server Program's Memory
## Task 4: Inject Malicious Code into the Server Program
## Task 5: Attacking the 64-bit Server Program
## Task 6: Fixing the Problem
