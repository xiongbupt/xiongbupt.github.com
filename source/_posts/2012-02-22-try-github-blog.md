---
layout: post
title: "在github上使用blog"
category: Git
tags: [Linux, Git, jekyll]
---
#在Linux上使用git
git作为一款分布式版本控制软件，在Linux上的安装相当容易。各个不同的发行版使用源更新工具安装git即可。具体步骤可以使用google搜索对应版本的git的安装。
在git安装完成之后，对git全局用户进行初始化设置。
`git config --global user.name xxx`
`git config --global user.email xxx@xxx`
完成这些基本设置之后，在[github网址](https://github.com)上成功注册帐号，在登录后的界面上点击Create A repository，创建一个新的项目。项目名称命名为xxx.github.com，其中xxx为自身注册的用户名。
#github的ssh设置
在安装了git和ssh之后，使用ssh对github进行账户的关联控制，在以后就不用输入密码了。
