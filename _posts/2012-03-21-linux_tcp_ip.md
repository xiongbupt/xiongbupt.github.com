---
layout: post
title: "linux_tcp_ip"
category: 
tags: []
---
{% include JB/setup %}
内核其他模块和用户空间应用程序可能都想知道网络设备注册、注销、打开、关闭的时间，因此提供了两个产生事件通知的途径，即netdev_chain通知链和netlink的RTMGRP_LINK组播组。
