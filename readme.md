# Joker

Joker can turn binary program into daemon, such as golang program.

### Download Binary

-   [joker](https://github.com/txthinking/joker/releases/download/v20190818/joker) for linux
-   [joker_darwin](https://github.com/txthinking/joker/releases/download/v20190818/joker_darwin) for macOS

### Build from Source

    $ make
    $ make install

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
But I need a simple, small, clean tool. Joker does **not** depend on systemd.

## License

Licensed under The GPLv3 License
