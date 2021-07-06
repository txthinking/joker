# Joker

[中文](readme_zh.md)

[![Donate](https://img.shields.io/badge/Support-Donate-ff69b4.svg)](https://www.txthinking.com/opensource-support.html)
[![Slack](https://img.shields.io/badge/Join-Slack-ff69b4.svg)](https://docs.google.com/forms/d/e/1FAIpQLSdzMwPtDue3QoezXSKfhW88BXp57wkbDXnLaqokJqLeSWP9vQ/viewform)

Joker can turn process into daemon.

❤️ A project by [txthinking.com](https://www.txthinking.com)

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
    	stop <pid>  stop a command by SIGTERM
    	log <pid>   view log of command
    	last        view pid of last command

    	help        show help
    	version     show version

### Example

    $ joker brook server -l :9999 -p password

### Where are log files?

All log files are stored in $HOME/.joker based on PID

### Why

There are many tools, such as systemd, supervisord, etc.
But I need a simple, small, clean, no configuration tool. Joker does **not** depend on systemd.

### Auto start command at boot

You may like [txthinking/jinbe](https://github.com/txthinking/jinbe) or [brook-community/jinbe](https://github.com/brook-community/jinbe)

## License

Licensed under The GPLv3 License
