---
layout: post
title: "Arch指定DNS服务器"
date: 2012-06-14 07:55
comments: true
categories: Linux
tags: [Linux, Arch]
---
学校里提供了IPv6的接入，但是之前使用的一直是学校提供的DNS服务器，使用的是IPv4的方式。在google上的[IPv6的hosts文档][la1]上知道有IPv6的DNS服务器的地址，于是上网找了在Arch上设置DNS服务器的地址，简单记录如下。
##修改/etc/resolv.conf的可修改性
由于学校使用的是DHCP的方式获取IP地址，Arch上使用的DHCP的客户端是dhcpcd，在默认情况下该服务器将会将获取的DNS服务器的地址填入到/etc/resolv.conf文件中。因此如果指定DNS服务器的方式，可以将该文件的文件设置为不可写。通过使用<kbd>chattr +i /etc/resolv.conf</kbd>的方式可以将该文件设置为不可修改的。  
如果在网络的环境不变的情况下，使用该种方式便可以解决，但是由于在宿舍和在实验室的环境，这两个网络环境下学校指定的DNS服务器是不一样的，在使用校内提供的服务器时，还是用学校的DNS服务器便可以了，因此这种方法对自己而言还不是很合适。于是出现下面的方法。
<!--more-->
##增加/etc/resolv.conf.head文件
最想的还是根据适当的情况，将一个不变的DNS服务器增加到/etc/resolv.conf文件中，在打开/etc/resolv.conf文件时，可以看到这样一行：

```
# /etc/resolv.conf.head can replace this line
```
于是上网找了下这个文件的说明，似乎看到的是在/etc目录下新建一个名为resolv.conf.head的，dhcpcd客户端在将DNS服务器地址写入到resolv.conf文件时将会把resolv.conf.head文件的内容添加进入到resolv.conf文件中。因此可以通过在resolv.conf.head文件中添加内容来完成这个功能。  

目前在电脑上使用的是第二种方法，完成了指定DNS服务器的方式，目前首选的是Google的IPv6服务器。

###附录：目前可用IPv6的DNS服务器地址
根据Google上面提供的IPv6 DNS服务器的地址，目前摘抄如下： 	

* ordns.he.net （最优）  
        2001:470:20::2
        74.82.42.42 
* google-public-dns-a.google.com （推荐）   
        2001:4860:4860::8888
        8.8.8.8（不返回 Google 系列的 AAAA 记录）    
* google-public-dns-b.google.com （推荐）    
        2001:4860:4860::8844
        8.8.4.4（不返回 Google 系列的 AAAA 记录） 
* ns.ipv6.uni-leipzig.de （西欧地区适用）    	 
        2001:638:902:1::10
        139.18.25.34 

[la1]:https://code.google.com/p/ipv6-hosts/ "IPv6 Hosts"
