---
layout: post
title: "VIM使用正则表达式改变大小写"
category: VIM
tags: [Regex]
---
##VIM使用正则表达式改变字符大小写
转载自[vim_wiki][label1]  
在VIM中使用正则表达式来改变单词的大小写是已经很简单的事情。  
只需要简单的将\U或者\L放在想要更改的回溯引用的前面，将\E放置在回溯引用的后面，VIM就会将回溯应用中的大小写进行相应的转换。使用\u和\l（这时不需要在最后使用\E）将会仅仅改变回溯引用中的第一个字符。  
    回溯引用是正则表达式中的一部分，用来表明匹配前面的一个部分。最常用的回溯表达式有&,\1,\2,\3,...,\9。  
<!--more-->
##示例
* 将整篇文档内容全部小写
{% codeblock lang:bash %}
:%s/.*/\L&/g
{% endcodeblock %}
    &是一个用来表明匹配前面全部的回溯引用的记录符号。
* 将紧跟着<后面的字符全部大写，比如在HTML标签中使用。
{% codeblock lang:bash %}
:%s/<\(\w*\)/<\U\1/g
{% endcodeblock %}

##注释
注意使用`gu`和`gU`命令加上移动操作也可以实现大小写的转换。  
比如`ggguG`可以实现将全文全部小写，其中，`gg`代表到达文章的首部，`gu`代表将文字转换为小写，`G`代表到达文章末尾（EOF）。

使用\0作为参考引用，而不是使用每个单独命名，比如（\1，\2等），下面的例子演示了\0的使用。
>This regex upper cases an explicit set of words to uppercase in a file.  

>`:%s/\(select\)\|\(order)\|\(by\)\|\(from\)\|\(where\)/\U\0/g`

>Not rocket science, but otherwise you'd have to do this:  

>`:%s/\(select\)\|\(order)\|\(by\)\|\(from\)\|\(where\)/\U\1\U\2\U\3\U\4\U\5/g`

>[edit:  Much easier to just use this, where either 0 or 1 will work:]  

>`:%s/\(select\|order\|by\|from\|where\)/\U\1/g`

上面的三个操作均是将一文中的几个关键词转换为大写操作，显然方法2显得很不合适，方法1和方法3要高明许多。


将HTML标签全部大写  
>:%s/<\/\=\(\w\+\)\>/\U&/g

将HTML标签全部小写  
>:%s/<\/\=\(\w\+\)\>/\L&/g

上面的例子中的`\=`可以替换成为`\?`，两个符号的意思都是匹配0个或者1个。
[label1]:http://vim.wikia.com/wiki/Changing_case_with_regular_expressions "VIM中使用正则表达式"
