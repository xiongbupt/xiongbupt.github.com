---
layout: post
title: "Linux内核TCP/IP笔记"
category: Notes
tags: [Linux, Learning]
---
内核其他模块和用户空间应用程序可能都想知道网络设备注册、注销、打开、关闭的时间，因此提供了两个产生事件通知的途径，即`netdev_chain`通知链和`netlink`的`RTMGRP_LINK`组播组。
