# Evaluation notes (Minitalk)

The purpose of this project is to code a small data exchange program using UNIX signals.

A signal is an event generated by the UNIX and LINUX systems in response to some condition. When a process receive a signal, the process will take action to response to the signal. For example, let's say your program accidentally causes infinite loop. So what we normally do is to press CTRL + C at the terminal and then the program will stop. CTRL + C is actually a signal, called SIGINT, which is an interrupt signal. The default behaviour to terminate the process.

Each of the signal has its own default behaviour also known as dispositions, which is to determines how the process should behaves when it received the signal.

> Can ask to check man 7 signal

The usage of `signal()` is actually the same as `sigaction()` but `sigaction()` is more preferred. According to `man 2 signal`, `signal()` varies accross UNIX versions, and has also varied historically across different versions of Linux. So, for portability purpose, use `sigaction()` instead.

 The sigaction structure is defined as something like:

```c
           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
```

On some architectures, sa_handler and sa_sigaction is a union. So, only can use one. In order to use sa_sigaction, need to set sa_flags to SA_SIGINFO, which will provide extra info for the second parameter of sa_sigaction.

sa_mask: use to block signals

sa_flag: modify the behavior of the signal. Optional.

sigaction - used to hook the new action for a signal. new action is defined by `act`, `oldact` to save the previous action.

Usleep - Allow the program to pause for a period of time. In microsecond. In million microseconds is one second.

exit - Terminate the execution of a function anytime we want.

kill - not actually used to kill a process but to send a signal to a process.

getpid - get the current process id. But what's `PID` anyway? Every process on the system has a unique process ID number, known as the `PID`. This is simply an integer.

In bit manipulation, a mask defines which bits you want to keep, and which bits you want to clear. So here, I'm using it to check whether at n bit, is there a one or not. Start from 128, to 0, so use right-shifting.
