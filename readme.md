# joker

joker can turn process into daemon.

❤️ A project by [txthinking.com](https://www.txthinking.com)

### Install via [nami](https://github.com/txthinking/nami)

```
nami install joker
```

or build from Source

```
make
```

### Usage

    joker: run command as daemon

        <command>     run your command
        last          view pid of last command
        list          show running commands
        log <pid>     view log of command
        stop <pid>    stop a command by SIGTERM
        help          show help
        version       show version

### Example

    joker brook server -l :9999 -p password

### Where are log files?

All log files are stored in $HOME/.joker based on PID

### Why

There are many tools, such as systemd, supervisord, etc.
But I need a simple, small, clean, no configuration tool. joker does **not** depend on systemd.

### Auto start command at boot

You may like [txthinking/z](https://github.com/txthinking/z)

## License

Licensed under The GPLv3 License
