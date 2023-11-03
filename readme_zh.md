# Joker

[English](readme.md)

Joker可以将进程变成守护进程.

❤️ A project by [txthinking.com](https://www.txthinking.com)

### 用 [nami](https://github.com/txthinking/nami) 安装

```
nami install joker
```

或者从源码编译

```
make
```

### 使用

    joker: run command as daemon

        <command>     run your command
        last          view pid of last command
        list          show running commands
        log <pid>     view log of command
        stop <pid>    stop a command by SIGTERM
        restart <pid> stop and run again
        help          show help
        version       show version

### 举例

    joker brook server -l :9999 -p password

### 日志文件在哪里?

所有的进程日志文件基于PID命名被存储在$HOME/.joker下

### 为什么

已经有几个类似软件, 比如 systemd, supervisord, 等.
但是我需要一个简单, 小巧, 干净, 无需配置的软件. 所以写了joker. joker不依赖systemd.

### 开机自动启动

你可能喜欢 [txthinking/jinbe](https://github.com/txthinking/jinbe)

## 开源协议

基于 GPLv3 协议开源
