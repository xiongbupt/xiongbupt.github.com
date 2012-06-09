---
layout: post
title: "Octopress尝试记录"
category: Octopress
comments: true
tags: [Octopress, Github, Learning]
---
本文主要是参考Octopress的[官方网址][lab1]进行操作，之前使用了[google][lab2]搜索了若干参考，但是操作之后出现了错误，推翻重来之后，写下这篇记录，方便自己以后使用。  
首先介绍下自己的环境Arch，由于之前已经使用了github的个人博客，但是之前使用的是jekyll的方式，自己不会调整那些主题，感觉有些不方便，上网找了下，发现似乎Octopress相对来说比较简单，于是在这种情况下尝试使用Octopress。至于在github上创建个人博客主页，在这里不做说明，在Octopress环境下，自己相当不清楚。
<!--more-->
由于Arch已经安装了ruby，且版本是1.9.3高于octopress要求的1.9.2，使用`pacman`的方式安装了ruby之后便没有必要再安装ruby了。按照`arch wiki`中所说的方式安装rvm即可。在这些基本工作完成之后，开始安装Octopress。

##Octopress环境配置
git clone git://github.com/imathis/octopress.git octopress  
cd octopress    # If you use RVM, You'll be asked if you trust the .rvmrc file (say yes).  
gem install bundler  
bundle install  
rake install  

##Github用户页面设置
参照Octopress上的将页面部署到github的[手册][lab3]。  
Github Pages服务要求用户使用master分支作为Web服务器上的公共目录，当直接输入用户的web网址时，重定向的是master分支的目录。因此，可以创建一个source分支来工作，然后将生成的内容推送到master分支。Octopress可以通过使用下面的命令完成上面的任务：  
`rake setup_github_pages`  
上面的操作将会完成下面的操作：

* 请求用户输入个人的Github可读可写地址，使用ssh的目录，如git@github.com:xiongbupt/xiongbupt.github.com.git这样的地址，在输入上面的命令之后，要求输入地址时输入这样一个地址即可。  
* 将本来octopress分支的远端分支有origin重命名为octopress，相当于工作目录内有两个远端分支。  
* 将个人的Github Pages作为默认的远程origin分支。  
* 将当前分支由master转换为source分支。  
* 根据之前自身输入的地址来配置个人博客的地址。  
* 在_deploy目录下创建一个master分支用于来布置。  
接下来使用  
rake generate  
rake deploy  
这两个操作将会完成下面的任务：生成网页内容，将将生成的网页内容拷贝到`_deploy/`文件夹内，将这些文件添加到git跟踪目录下，提交然后将这些文件推送到master分支。因此在完成内容编辑之后，简单使用上面的两个命令就将会本地完成的编辑内容推送到远程的服务器端。

**不要忘记**将源文件推送到自己的远程分支。使用下面的操作即可完成操作：  
git add .
git commit -m '提交说明'
git push origin source

**注意：**目前Github网站设置的默认分支是最新提交的分支，因此如果在网页显示有问题时，可以登录到Github网站上查看是否自己的版本库的默认分支是否为master分支，将默认分支调整为master即可在网页上显示内容。

##Github工程页面设置
Github允许对于已存在的开源工程添加一个网页说明。Github会搜索工程目录下的gh-pages分支，然后将这些内容置于可以访问的类似于`http://username.github.com/project`。

可以通过下面的方式来公布自己的工程`gh-pages`。  
rake setup_github_pages 

这个操作将会：
* 请求工程目录库的网址url
* 将当前的origin本来指向的远程仓库imathis/octopress重命名为octopress
* 确定博客将被配置为一个子目录
* 在工程下新建_deploy文件夹，在该文件夹下建立gh-pages分支，准备配置该分支

接下来运行：    
rake generate
rake deploy
这将会生成博客内容，将生成的文件拷贝到`_deploy/`文件夹内，将它们加入到git同步库中，提交并将这些文件推送到master分支。

现在已经对网站的内容进行了一次提交，但是同样也应该对网站的博客的源代码进行提交。在添加了自己工程的网址作为远端仓库之后，可以进行提交，如下所示：        
git remote add origin (your repo url)
\#set your new origin as the default branch
git config.branch.master.remote origin

在完成上述设置之后便可以使用`git push`进行推送了。

##自定义域名
首先需要在`source`文件夹下创建一个名字为`CNAME`的文件，然后将自己的域名输入到该文件中，如下所示：   
echo 'your-domain.com' >> source/CNAME

接下来在域名的注册处添加域名记录。具体介绍参考[octopress][lab3]的介绍，此处不做详细描述。





[lab1]:http://octopress.org/ "OCTOPRESS 手册"
[lab2]:http://www.google.com/ "GOOGLE"
[lab3]:http://octopress.org/docs/deploying/github/ "OCTOPRESS Github介绍"
sed -n 's/\(category:\ \)\(\[\)\(\w*\)\(\]\)/\1\3/p' *.md
