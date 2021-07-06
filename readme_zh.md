# Joker

[English](readme.md)

[![捐赠](https://img.shields.io/badge/%E6%94%AF%E6%8C%81-%E6%8D%90%E8%B5%A0-ff69b4.svg)](https://www.txthinking.com/opensource-support.html)
[![交流群](https://img.shields.io/badge/%E7%94%B3%E8%AF%B7%E5%8A%A0%E5%85%A5-%E4%BA%A4%E6%B5%81%E7%BE%A4-ff69b4.svg)](https://docs.google.com/forms/d/e/1FAIpQLSdzMwPtDue3QoezXSKfhW88BXp57wkbDXnLaqokJqLeSWP9vQ/viewform)

Joker可以将进程变成守护进程.

❤️ A project by [txthinking.com](https://www.txthinking.com)

### 用 [nami](https://github.com/txthinking/nami) 安装

```
$ nami install github.com/txthinking/joker
```

或者从源码编译

```
$ make
```

### 使用

    joker: run command as daemon

    	<command>   run your command
    	list        show running commands
    	stop <pid>  stop a command by SIGTERM
    	log <pid>   view log of command
    	last        view pid of last command

    	help        show help
    	version     show version

### 举例

    $ joker brook server -l :9999 -p password

### 日志文件在哪里?

所有的进程日志文件基于PID命名被存储在$HOME/.joker下

### 为什么

已经有几个类似软件, 比如 systemd, supervisord, 等.
但是我需要一个简单, 小巧, 干净, 无需配置的软件. 所以写了joker. joker不依赖systemd.

### 开机自动启动

你可能喜欢 [txthinking/jinbe](https://github.com/txthinking/jinbe) 或 [brook-community/jinbe](https://github.com/brook-community/jinbe)

## 开源协议

基于 GPLv3 协议开源
