---
layout: post
title: "VIM使用便签"
category: Linux
tags: [VIM, Linux]
---
转载自[vim_cook_book][1]

字符翻转
>xp

可交换的替换单词
{% codeblock lang:bash %}
1G              #到第一行
/idiot<enter>   #搜索单词idiot
cwmanager       #将idiot替换为manager
n               #搜索下一个idiot
.               #重复上面的替换操作
{% endcodeblock %}

{% codeblock lang:bash %}
%s/\<idiot\>/manager/gc #直接在命令行模式下进行输入，使用全局替换的方式
{% endcodeblock %}
/\<idiot\>/ 	
>This text specifies the text we are looking for wand want. The \< tells Vim to match a word start and the \> tells Vim to match the end of a word.  
>\<表明匹配的是一个单词的开始，\>表明匹配的是一个单词的结束。

<!--more-->
检查Makefile错误的好方法，由于命令是以tab开始的，若是空格将有错误
{% codeblock lang:bash %}
:set list
{% endcodeblock %}
可以显示出空格和tab的区别，tab是^I

vim读取man文件
{% codeblock lang:bash %}
man subject|ul -i|vim -
{% endcodeblock %}

vim移除行末的空格
{% codeblock lang:bash %}
:1,$s/[tab]*$//
{% endcodeblock %}

将Last, First改为First Last
{% codeblock lang:bash %}
:1,$s/\([^,]*\),\(.*$\)/\2\1/
{% endcodeblock %}
>The \( ... \) delimiters are used to inform the editor that the text that matches the regular expression side is to be treated special.  
>\(...\)分隔符告知编辑器将括号内的内容应该被当做正则表达式来对待（？？？）

操作示例
    if ( x>3 ) {
      "Hello *world!"           ds"         Hello world!
      [123+4*56]/2              cs])        (123+456)/2
      "Look ma, I'm *HTML!"     cs"<q>      <q>Look ma, I'm HTML!</q>
      if *x>3 {                 ysW(        if ( x>3 ) {
      my $str = *whee!;         vllllS'     my $str = 'whee!';
上述操作中，\*代表的是光标所在位置，在普通模式下，输入中间的命令，将会得到后面的效果

{% codeblock lang:bash %}
vim --startuptime timefile the_file_you_want_to_edit
{% endcodeblock %}
查看vim启动时间所占用的时间比

set list查看不可见字符

[1]:http://www.oualline.com/vim-cook.html "vim_cook_book"
