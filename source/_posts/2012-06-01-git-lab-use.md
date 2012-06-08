---
layout: post
title: "Git小项目基本操作"
category: Git
tags: [Linux, Git]
---
##Git个人电脑操作
Git版本控制有三个区域，分别是工作目录、暂存区和git目录。
![Git的本地操作][1]

平时的工作都在工作目录中完成，在修改完代码之后，需要将修改的代码加入到暂存区，这个通过`git add`操作完成。当需要将暂存区域里的代码提交进入git工作目录时，需要使用`git commit`来完成。

上面描述的两个命令`git add`和`git commit`是在本地目录工作中用到的主要命令。当需要删除文件时，使用的是`git rm`命令。

在使用`git commit`将本地工作的内容提交到git工作目录之后，本地代码的修改工作便已经完成。
<!--more-->
##Git获取服务器端代码
使用git从服务器端下载最新的代码，目前服务器端的ip地址为10.117.6.138。使用
    git clone git@10.117.6.138:/home/git/path_to_work
下载源代码之后，接下来便可以对代码进行修改了。每次修改之后，均使用`git add`和`git commit`在本地完成提交操作。这些操作与前面提到的在个人电脑上的操作类似。

##在个人电脑上创建新分支
git创建分支的操作非常简单，而且代价也很小。
    `git branch new_branch_name`
通过这样一条指令便可以创建一个名字为`new_branch_name`的分支。接下来，便可以切换到该分支上进行开发了，具体操作如下：
    git checkout new_branch_name
完成上述操作之后，便已经将当前的代码分支移动到了`new_branch_name`这个分支。使用`git branch`指令可以查看当前一共有多少分支，以及当前处于哪个分支。  
上面的两条指令可以用一条指令代替
    git checkout -b new_branch_name
这条命令即相当于连续执行了
    git branch new_branch_name
    git checkout new_branch_name

##查看服务器端的分支
如果想要查看服务器端都有什么分支，可以使用如下：
    git remote show origin
上面这条指令将会输出远端服务器端的分支，以及个人的电脑是否已经和这些分支同步。

##推送代码至Git服务器端
当自己需要将代码推送到Git服务器端时，需要确保服务器端的代码与自己下载的代码是一致的，因此推荐每次在向服务器端推送代码之前，先使用`git pull`操作将服务器端的代码与本地的代码进行合并，完成合并之后再进行提交。若未进行此操作，将代码推送至服务器端将会失败，服务器端将会给出提示。  
从Git服务器端下载代码有两种方式，一种是`git pull`，另外一种是`git fetch`。其中`git pull`操作不仅仅执行了`git fetch`，同时，它还将远端仓库的版本与当前的版本进行了合并即`merge`操作。如果可以直接合并，将不需要在本地端手工合并，Git将会自动合并。  
因此，在需要将代码提交至远端的Git服务器之前，需要先将服务器端的最新代码下载下来，然后在本地合并之后，再提交到服务器端。  
具体操作如下：
    git pull
    git mergetool
    git push origin branch_name
上面这三个操作是整个向服务器端推送的大致操作。其中最后一步`git push origin branch_name`将会把本地分支`branch_name`推送到服务器端，并且服务器端的分支的名字也为`branch_name`。若想在服务器端命名为不同的名字，则可以使用下面的指令
    git push origin local_branch:remote_branch
其中`local_branch`是本地分支的名字，而`remote_branch`则为远端服务器的分支名字。

##切换到远端Git服务器上分支
从服务器上使用`git fetch`下载代码之后，个人PC上的代码库便和服务端的代码库的版本是一致的。此时，如果个人PC希望切换到远端服务器的某个分支，必须在自己的代码库中再创建一个分支，建议将该分支的名字命名为与远端服务器的分支名字相同，这样在推送到服务器端时可以较为方便，防止再在远端服务器上创建一个新的分支。具体操作可以如下所示：
    git pull
    git remote show origin
    git checkout -b branch_name origin/branch_name
上面的操作即在本地创建了一个分支名为branch_name，该分支与服务器端的分支是一样的名字。如果在该分支上进行修改之后，接下来使用推送命令将修改的分支推送到远端服务器即可。
    git push origin branch_name
##开发流程简介
在创建项目之前，需要在服务器端创建一个版本库。这个操作需要有远端服务器的登录权限，可以在相应的目录下创建目录及文件，目前对服务器的登录为ssh的远程登录方式。在登录到服务器端后，使用*`git init --bare`* 创建一个空的仓库即可。也可以在本地创建仓库之后，使用如下命令将仓库拷贝到远端服务器。
    scp -r local_folder name@remote_server:/path/to/work
这一步可以由管理人员完成。当将git的项目在远端服务器端生成之后接下来便是`git`的发挥作用了。

假设现在项目组有三个人分别为A，B，C。他们共同从服务器下载了一份代码，并且开始开发。B下载代码之后，觉得自己有个新想法，于是使用
    git branch branch_B_1
创建了一个新的分支，分支名为branch_B_1。然后B使用
    git checkout branch_B_1
在这个分支上进行开发。同样，A也进行了类似的操作，不过他创建的分支版本为branch_A_1。在完成各自的想法之后，他们需要将自己的工作推送到服务器端。

>在推送到服务器端时，需要记住git的一个原则，除非指定需要提交的本地分支，否则，git是不会将本地生成的分支提交到远端的服务器端的。因此，在创建分支进行开发后，当需要提交分支时，需要按照上面提到的**推送代码到Git服务器端**的说明将代码推送到服务器端。

现在，A和B都完成了各自的修改，需要按照下面的步骤将修改后的分支推送到服务器端。假设A先推送，其首先使用
    git pull
的方式从服务器端下载最新的代码，然后按照
    git push origin branch_A_1
的方式将分支代码提交到了Git服务器端。接下来，B也想提交自身修改的分支代码，于是B也首先使用`git pull`的方式从服务器端下载最新的代码，然后使用
    git push origin branch_B_1
的方式提交分支代码。注意在B使用`git pull`的方式下载代码时，其将会下载服务器端由A提交的分支branch_A_1。如果B此时想查看A究竟做了什么工作时，可以使用
    git checkout -b branch_A_1 origin/branch_A_1
的方式，先在本地创建一个同样名字为branch_A_1的分支，然后再切换到该分支进行查看。

>git从服务器端下载的分支代码无法直接查看，必须在本地创建一个对应的分支，然后才可以查看该分支的代码。至于本地分支的名字则没有影响，但是为了与远端分支的一致性，推荐使用相同的分支名。

C使用`git pull`之后，在切换分支查看了A和B的想法之后，觉得A和B的想法都可以采纳，C想将A和B的想法合并到一起，于是便开始合并这两个分支。  
首先，C新创建了一个分支，名字为branch_C_1，接下来，C切换到该分支，然后使用
    git merge branch_A_1
将分支branch_A_1与自己创建的分支合并，接着使用
    git merge branch_B_1
将分支branch_B_1与自己创建的分支合并。这时，C创建的分支已经同时包含了A和B的想法。如果在合并的工程中出现了冲突，可以使用
    git mergetool
这个工具将会打开这些冲突，选择解决这些问题。

总之，git的提交分支的方式便是按照上面的一个简单的说明进行开发。

###git版本回退##
如果在开发过程中，发现出现了错误，想要将git的版本回退到某个时期，可以使用
    git checkout hash_number
的方式回退到hash_number所代表的版本。在这上面再创建分支
    git chekcout -b branch_test hash_number
这样可以以这个hash_number代表的历史版本。

###git版本合并##
从服务器端下载代码之后，如果出现了冲突，需要使用
    git mergetool
来对代码进行合并。  
在本地分支下，使用
    git pull
git将会尝试自动合并，如果合并失败，使用
    git mergetool
再来尝试手动合并即可。
##git基本命令介绍#
从服务器端下载代码
>git clone username@remote_server:/path/to/work

添加文件到暂存区
>git add filename

将已经在版本库中但是在工作目录下修改的文件添加到暂存区
>git add -u

从版本库中删除文件
>git rm filename

将文件重命名
>git mv oldname newname

将暂存区文件存储到版本库中
>git commit

直接添加注释，不再进入界面编辑提交日志
>git commit -m 'Description of the commit'

从已经克隆的版本库中下载服务器端的代码到本地版本库中
>git fetch

从已经克隆的版本库中下载服务器端的代码并合并分支
>git pull

在本地创建一个名字为branch_name的分支
>git branch branch_name

切换到本地名字为branch_name的分支
>git checkout branch_name

在本地创建一个分支名为branch_name的分支并切换到该分支
>git chekcout -b branch_name

将本地名字为branch_name的分支推送到服务器端，并且在服务器端的名字为branch_name
>git push origin branch_name

将本地名字为branch_name的分支推送到服务器端，并且在服务器端的名字为branch_server
>git push origin branch_name:branch_server

查看服务器端的分支状态
>git remote show origin

查看本地分支状态
>git branch

删除本地分支
>git branch -d branch_name

合并分支
>git merge

合并冲突解决
>git mergetool

查看简明历史
>git log

查看每次提交具体修改
>git log -p

查看提交某个文件的修改历史
>git log -p filename

显示文件的增减行数
>git log --stat

git个人邮件配置
>git config --global user.email username@web.com

git个人名字配置
>git config --global user.name username

git简称配置，如chekcout简称为co，commit为ci，branch为br，status为st
>git config --global alias.co checkout  
>git config --global alias.ci commit  
>git config --global alias.br branch  
>git config --global alias.st status  

git格式化与空格
    由于linux系统和windows系统对行尾结束符处理方式不一致，windows下使用回车和换行两个字符来结束一行，而Linux系统仅仅使用一个换行字符，当跨平台在linux系统和windows系统下开发时，会出现较麻烦的现象。Git可以在提交时自动将结束符CRLF转换成LF，而在签出代码时将LF转换成为CRLF。在windows系统下，将autocrlf选项设置为true，这样在签出代码时，LF将会被换成CRLF；在Linux系统下，将autocrlf设置为input仅仅在签入代码时将CRLF转换为LF，在签出代码时，不进行转换，LF还是LF。此选项对跨平台开发具有较大作用，推荐使用。
>git config --global core.autocrlf true*（windows下使用）*  
>git config --global core.autocrlf input*(Linux下使用）*   
#注意事项
* Git的每次提交到服务器端的操作必须先从服务器端下载最新的提交代码，在本地完成合并冲突之后才可以完成提交。
* Git对于文件的合并有自动合并的功能，当已修改的版本与未修改的版本只是删减操作时，Git将会自动合并。
* Git在本地的提交操作不需要连接到服务器端。
* 为了防止服务器版本库的差异过大，在每次完成一个完整的功能块时，建议将代码push推送到服务器端，不要多次未推送提交，一次改动过大。
* 使用`git checkout filename`操作时，将会从暂存区中获取文件，替代本地文件。注意这种情况下，本地的所有修改都会丢失。因此，在使用此命令之前，需要确认本地的修改已经无用或者已经保存。
* 尽量多使用`git status`查看当前状态，在这个命令的输出中可以获取很多帮助信息以及可以采取什么操作来实现哪些功能。








[1]:/images/fig0101-tn.png "Git 本地操作"
