# Joker

Joker can turn binary program into daemon, such as c, golang, rust and other languages program.

### Install via [nami](https://github.com/txthinking/nami)

```
$ nami install github.com/txthinking/joker
```

or build from Source

```
$ make
```

### Usage

    joker: run command in background daemon

    	<command>   run your command
    	list [-a]   show running commands
    	stop <pid>  stop a command
    	log <pid>   view log of command
    	clean       clean stopped commands
    	help        show help
    	version     show version

### Example

    $ joker brook server -l :9999 -p password

### Why

There are many tools, such as systemd, supervisord, etc.
But I need a simple, small, clean, no configuration tool. Joker does **not** depend on systemd.

## License

Licensed under The GPLv3 License
