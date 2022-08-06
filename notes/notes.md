# Minitalk Learning Notes

## Project instructions

- Can have one global variable per program (client and server)
- Allowed functions
    1. `write`
    2. `ft_printf` or any equivalent YOU coded
    3. `signal`
    4. `sigemptyset`
    5. `sigaddset`
    6. `sigaction`
    7. `kill`
    8. `getpid`
    9. `malloc`
    10. `free`
    11. `pause`
    12. `sleep`
    13. `usleep`
    14. `exit`
- Create a communication program in the form of a **client** and a **server**.
- Server must be started first. When launch, print its `PID`.
- Client takes two parameters:
    1. Server `PID`
    2. String to send
- Once server received the string, the server must print it.
- Server should be able to receive strings from several clients in a row without needing to restart.
- Communication between client and server has to be done **only** using UNIX signals.
- Allowed signals: `SIGUSR1` and `SIGUSR2`

## Research

The following section is just for me to understand the project better. DO NOT just read whatever I've written down here because there might be some misleading info. So, do your research instead! Hehe.

### What are Signals?

Resources:

- `man 7 signal`
- [What are Linux signals?](https://www.educative.io/answers/what-are-linux-signals)

A **signal** is an event generated by the UNIX and LINUX systems in response to some condition. Upon receipt of a signal, a process may take action to response the signal. A signal is just like an interrupt; when it is generated at the user level, a call is made to the kernel of the OS, which thenacts accordingly.

Two types of signals:

- **Maskable**: signals which can be changed or ignored by the user.
- **Non-maskable**: signals which cannot be changed or ignored by the user.

Check `man 7 signal` to view the list of the standard signals.

### `signal` *(the function)*

Resources:

- `man 2 signal`

The usage of `signal()` is actually the same as `sigaction()` but `sigaction()` is more preferred. According to `man 2 signal`, `signal()` varies accross UNIX versions, and has also varied historically across different versions of Linux. So, for portability purpose, use `sigaction()` instead! (RTFM!!!)

There's another benefit that we should use `sigaction()` instead of `signal()`. `sigaction()` can help in the restoration of the previous functionality of the signals handlers (3rd parameter).

```c
#include <signal.h>

sighandler_t signal(int signum, sighandler_t handler);
```

### `sigemptyset`

Resources:

- [sigemptyset](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sigemptyset.html)
- [sigset_t data type](https://www.gnu.org/software/libc/manual/html_node/Signal-Sets.html#:~:text=The%20sigset_t%20data%20type%20is,try%20to%20manipulate%20them%20directly.)

```c
#include <signal.h>

int sigemptyset(sigset_t *set);
```

Initializes the signal set pointed to by `set`, such that all signals defined in this document are excluded.

Upon successful completion, `sigemptyset()` returns 0. Else, returns -1.

#### sigset_t (data type)

Resources:

- [sigset_t](https://www.gnu.org/software/libc/manual/html_node/Signal-Sets.html#:~:text=The%20sigset_t%20data%20type%20is,try%20to%20manipulate%20them%20directly.)
- [sigset_t](https://youtu.be/_1TuZUbCnX0?t=140)

All of the signal blocking functions use a data structure called a `signal set` to specify what signals are affected. Thus, every activity involves two stages: creating the signal set, and then passing it as an argument to a library function.

It is used to represent a signal set. Internally, it may be implemented as either an integer or structure type.

It is an array of bits representing a set of signals. Each bits represents one signal type. Usually we initialized `sigset_t` by calling `sigemptyset(&s)`, which will clear all the bits.

Use `sigaddset(&s, SIGTERM)` to set the bit corresponsing to the signal.

![Visual representation](https://i.ibb.co/pKTLzXd/Screenshot-2022-08-01-at-17-31-34.png)

Use `sigdelset(&s, SIGTERM)` to remove a signal from the set.

Use `sigfillset(&s)` to set them all.

Use `sigismember(&s, SIGTERM)` to check whether a signal is the member of the signal set. Return 1 means true, 0 if not.

### `sigaddset`

```c
#include <signal.h>
int sigaddset(sigset_t *set, int signo);
```

Adds the individual signal specified by the `signo` to the **signal set** (sigset_t) pointed to by `set`.

Upon successful completion, `sigaddset()` returns 0. Otherwise, it returns -1 and set errno to indicate the error.

It may fail if the value of the `signo` is an invalud or unsupported signal number.

### `sigaction`

Resources:

- `man 2 sigaction`
- [Handling signals](https://youtu.be/jF-1eFhyz1U)

`sigaction` is used to **change the action** taken by a process on receipt of a specific signal. For example, when we run a program and we press `ctrl + z`, it will send signal to the operating system stop our program. What it we want to change the behavior of it? So that when we press `ctrl + z`, it won't stop our program but do something different. To do so, we can use `sigaction` to **change the action** to something we defined.

```c
int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);

// signum   : any valid signal (check standard signals) expect SIGKILL and SIGSTOP
// act      : new action for signal `signum` is installed from `act`
// oldact   : if it's non-NULL, the previous action is saved in `oldact` 
```

`sigaction` structure is defined as something like:

```c
struct sigaction {
    void        (*sa_handler)(int); // SIG_IGN (ignore) or SIG_DFL (default) or we can define our own handler function
    void        (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t    sa_mask; // set of signals to be blocked during execution of handler
    int         sa_flags; //optional flags. to control your operation in more detailed
    void        (*sa_restorer)(void);
};
```

`sigaction()` example:

```c
void    handler(int sigtype)
{ ... }

int main()
{
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);
}
```

`SA_RESTART` implies that if the signal comes when the process is blocked in a system call like `read()`, the call should be restarted after the signal handler returns. In short, let the system auto restart the interrupted system call.

System calls can be interrupted by **any signal**, this includes such signals as SIGINT (generated by CTRL-C), SIGHUP, etc.

> System calls can be interrupted. System calls such as read, wait, and accept that can potentially block the process for a long period of time are called **slow system calls**. On some older versions of Unix, slow system calls that are interrupted when a handler catches a signal do not resume when the signal handler returns but instead return immediately to the user with an error condition and errno set to EINTR. On these systems, programmers must include code that manually restarts interrupted system calls.

Signals are delivered **asynchronously**. It can occur at anytime. Perhaps we don't want to be interrupted went the signal is sent. So, we need to ensure that we can complete an update on some critical data structure. If that's the case, we can set the process's **signal masks**, which is basically a set of signals that are currently blocked from delivery. Blocked signals are held *pending* and will be *delivered when unblocked*. Need to know that the blocked signals are not queued up if several signals of the same type are delivered. When they are unblocked, only **one** will be delivered.

### `kill`

Resources:

- `man 2 kill`

```c
int kill(pid_t pid, int sig);
```

`kill()` can be used to send any signal to any process group or process.

if `pid` is:

1. positive, then signal `sig` is sent to the process with the ID specified by `pid`.
2. zero (0), then `sig` is sent to every process in the process group of the calling process.
3. -1, then `sig` is sent to every process that which the calling process has permission to send signals.

if `sig` is 0, no signal is sent.

On success, `kill()` return 0. Else, -1 is returned.

### `getpid`

Resource:

- `man 2 getpid`

`getpid` returns the process ID (PID) of the calling process.

But what's `PID` anyway? Every process on the system has a unique process ID number, known as the `PID`. This is simply an integer.

Usage:

```c
#include <unistd.h> // needed to define getpid()

int main()
{
    // so when we execute the program, getpid() will get the PID of this process and return it
    printf("PID: %d\n", getpid());
    return (0);
}
```

> Can use `top` command to check the list of running processes. The first field is PID.

### `pause`

### `sleep`

```c
#include <unistd.h>
unsigned sleep(unsigned seconds);
```

Allow the program to pause for a period of time.

### `usleep`

```c
#include <unistd.h>
int usleep(usecond_t useconds); // microseconds
```

### `exit`

```c
#include <stdlib.h>
void exit(int status);
```

Terminate the execution of a function anytime we want.

### Communicating between processes using signals

Resources:

[Communicating between processes using signals](https://youtu.be/PErrlOx3LYE)

```c
// shared variable between the parent and child process
int g_x = 0;

// communicating between processes using signals
void    handle_sigusr1(int sig)
{
    if (g_x == 0)
        printf("\n(HINT) Remember that multiplication is repetitive addtion :)");
}

int main(int ac, char **av)
{
    int pid = fork();
    // error handling
    if (pid == -1)
        return (1);
    // if we are in the child process
    if (pid == 0)
    {
        // Child process
        // do the hinting
        // while (g_x == 0)
        // {
            sleep(5);
        // SIGUSR1 is user defined signal
        // by default it only terminated the process
        // to avoid this, we can use sigaction to change the action
            kill(getppid(), SIGUSR1);
        // }
    }
    else
    {
        // initialize all member of sa to 0
        struct sigaction sa = { 0 };
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        // hook the action to SIGUSR1
        // so that when the process receive the signal
        // it will perform the action we defined
        sigaction(SIGUSR1, &sa, NULL);
        // Parent process
        printf("What is the result of 3 X 5: ");
        scanf("%d", &g_x);
        if (g_x == 15)
            printf("Right!\n");
        else
            printf("Wrong!\n");
        // wait for the child process to finish
        wait(NULL);
    }
}
```

## Ideas

Client -> Server:

1. Check argument (ac, av). If ac less than 3, terminate the process.
2. Parse the string into binary, char by char.
3. Send one bit at a time to the server using SIGUSR1 and SIGUSR2.
4. Server receive the bits, once it receive total of 8 bits, meaning 1 byte, print the char.
5. Once every character of the msg has been printed out, server side exit.
6. Inform client that server has received the msg. (Acknowledgment system)