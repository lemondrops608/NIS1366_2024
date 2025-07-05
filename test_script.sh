#!/usr/bin/expect
    if {[llength $argv] < 1} {
        puts "Usage: $argv0 \[taskname\]"
        exit 1
    }

    # 第一个参数是任务名称
    set taskName [lindex $argv 0]
    cd ./bin
    spawn ./MyExecutable
    send "run\r"
    expect "Please enter the command."
    send "1\r"
    expect "Please enter a user name:"
    send "lcy\r"
    expect "Please enter your password:"
    send "123456\r"
    expect "Type \"deltask\" to delete a task."
    send "addtask\r"
    expect "task name:"
    send "$taskName\r"
    #send "test\r"
    expect "start time:(eg: 2024 7 18 04:00)"
    send "2024 7 18 21:00\r"
    expect "doesn't matter]"
    send "2\r"
    expect "doesn't matter]"
    send "1\r"
    expect "reminding time:(eg: 2024 7 18 03:00)"
    set nextDate [exec bash -c "date -d '+1 minute' +'%Y %m %d %H:%M'"]
    # 将获取的当前时间发送给 MyExecutable
    send "$nextDate\r"
    interact