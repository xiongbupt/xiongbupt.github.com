---
layout: post
title: "Markdown基本使用"
category: Notes
tags: [Learning, Markdown]
---
##链接
如果需要在页面插入链接，使用尖括号\<\>括起来便可以了。

如果需要为一段文字加上链接，使用如下方式
[文字,google](http://www.google.com) （ <a> href="http://" </a>

为链接加上标题可如下所示
[文字，google](http://www.google.com "对应的标题")

[链接][lable1]
按照上述方式，在文章中另起一行，通常是在文章的末尾，添加
    [lable1]:http://www.google.com
[lable1]:http://www.google.com
将对应的链接完成即可。注意使用的是中括号和一个冒号，后面添加对应的链接地址。
<!--more-->
同样也可以使用链接和标题的方式
[lable2]:http://www.google.com "对应的标题"

##图片
![插入图片](对应的图片的地址 "标签")
<img src="www.google.com" alt="" title="描述">

##标题格式
通过输入####来确定标题格式，一共有6级
或者是使用====和----来确定标题。后面这种只能提供两种级别的。
<h1> </h1>

##粗体和斜体
文字两边各加一个星号( * )或者下划线（ _ )表示斜体。
各加对应的两个符号表示粗体。
各加对应的三个符号表示粗斜体。
<strong> 粗体</strong>
<em>斜体</em>
<strong><em> 粗斜体</em></strong>

##引用内容
使用>（大于号）即可，相当于html中的blockquote
>引用
<blockquote>引用</blockquote>

##原文输出
    如果一段文字已经有序，或者包含有html中的语法，不想让其再进行解释，只需要将这些文字缩进至少四个空格或一个Tab宽度即可。它对应着html中的<pre>标签。
比如下面的例子
{% codeblock lang:c %}
  printf("hello world");
{% endcodeblock %}
<pre>
<code>
printf("hello world");
</code>
</pre>

##列表
html中的两种列表分别为无序列表和有序列表，分别使用  <ul></ul> 和<ol></ol>括起来。
在markdown中，对于无序列表，只需要在列表前面加上一个星号( * )、或加号( + )、或减号( - )即可。
* first
* second
- third
+ fourth


对应的html代码为

{% codeblock lang:html %}
<ul>
<li>first</li>
<li>second</li>
</ul>
{% endcodeblock %}

<ul>
<li>first</li>
<li>second</li>
</ul>


对于有序列表，只需要在第一条前添加一个数字，后跟一个英文句号，次好即可仍旧使用加或星或减。无论第一个条目前加的数字是什么，列表都会从1开始计数。

1. 第1条
2. 第2条
3. 第3条abc
4. 第4条
5. 第5条

对应的html代码
<ol>
<li>第一条</li>
<li>第2条</li>
</ol>

{% codeblock lang:html %}
<ol>
<li>第一条</li>
<li>第2条</li>
</ol>
{% endcodeblock %}

##转义符
在markdown中使用"\\"来实现转义。
比如
[链接](http://www.google.com)
在加上转义之后变为  
\[链接](http://www.google.com)

比如\*号的输出，为了输出三个星号
\*\*\*输出3个星号\*\*\*

##HTML实体
在HTML中有两个特殊含义的字符，分别是"< "和" & "

##换行符
在一行的末尾使用两个以上的空格表示HTML中的一个换行符“\<br/>"
    <br/>表示换行符

##段落
    在HTML中，使用”<p></p>“括起来的内容称为一个段落。在markdonw中，两段之间有一个空行就可以在翻译的时候翻译成一个段落。

##水平线
    HTML中，“<hr/>"标记可以在页面中输出一条横线，在Markdonw中，使用三个以上的星号”*“或减号"-"可以起到同样的作用。

星号和减号之间可以有空格；如果减号没有空格，必须在一个段落中，即在含有三个以上无空格分隔的减号的行的前后都要有一个空行。

比如下面的  
google
- - - - - - - -
google

与  

google
* * * * * * 
google

google
******
google

对应的HTML代码均为

{% codeblock lang:html %}
    <p>google</p>
    <hr/>
    <p>google</p>
{% endcodeblock %}

<p>google</p>
<hr/>
<p>google</p>


google

--------

google

##嵌套
在markdown中可以使用嵌套。
比如下面的代码
>google
>>google
对应的html标签为

<blockquote>
<p>google</p>

<blockquote>
<p>google</p>
</blockquote>

</blockquote>


{% codeblock lang:html %}
<blockquote>
<p>google</p>

<blockquote>
<p>google</p>
</blockquote>

</blockquote>
{% endcodeblock %}

表示HTML中的    `"<code>"`标记的\`同样可以嵌套。如果希望插入一个该符号而不愿意被翻译成为`"<code>"`，可以使用"`"  

`` ` ``
html代码为

<code>`</code>

{% codeblock lang:html %}
<code>'</code>
{% endcodeblock %}


##c语言测试
{% codeblock lang:c %}
#include <stdio.h>

int main(void) {
  int i = 9527;
  printf("Your ID: %d", i);
  return 0;
}
{% endcodeblock %}
##bash测试
{% codeblock lang:bash %}
cd ~
{% endcodeblock %}

##语法高亮简述
使用pygmentize生成对应的css文件，然后在default.html中修改文件，使用对应的css文件，即可开启语法高亮。

<pre>
<code>
    { % highlight bash linenos % }
    { % endhighlight % }
</code>
</pre>

