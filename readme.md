# Joker

Joker can turn process into daemon.

### Install via [nami](https://github.com/txthinking/nami)

```
$ nami install github.com/txthinking/joker
```

or build from Source

```
$ make
```

### Usage

    joker: run command as daemon

    	<command>   run your command
    	list        show running commands
    	stop <pid>  stop a command
    	log <pid>   view log of command

    	help        show help
    	version     show version

### Example

    $ joker brook server -l :9999 -p password

### Where are log files?

All log files are stored in $HOME/.joker based on PID

### Why

There are many tools, such as systemd, supervisord, etc.
But I need a simple, small, clean, no configuration tool. Joker does **not** depend on systemd.

## License

Licensed under The GPLv3 License
