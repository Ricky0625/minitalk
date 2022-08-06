# Minitalk

The purpose of this project is to code a small data exchange program using UNIX signals.

> Works on UNIX / LINUX environment only. WSL maybe also can?

## How to use?

1. Clone the repo

    ```shell
    git clone https://github.com/Ricky0625/minitalk.git minitalk && cd minitalk
    ```

2. Make the server & client

    ```shell
    make all
    ```

You should be able to see something like this on your terminal.

![Make all](https://i.ibb.co/Bqs8zF3/Screenshot-2022-08-06-at-18-44-36.png)

3. Run server. `./server`
4. Run client. `./client [pid] [msg in string format]`
