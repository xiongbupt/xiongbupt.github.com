---
layout: post
title: "Octopress添加标签"
category: Octopress
comments: true
tags: [Octopress, Learning, Github]
toc: true
---

##前因
由于之前参考中文的搜索，结果都不理想，推翻重来，直接使用[google][l1]使用`octopress tag`关键词搜索到的[第一个返回结果][l2]来修改，下面记录如下。
###显示所有的便签列表
修改`source/_layouts/post.html`文件，使它们include一个名字为`tags.html`的新文件。

<!--more-->

创建一个新文件`source/_includes/post/tags.html`，整个文件的内容如下所示：  
{% codeblock  source/_includes/post/tags.html lang:html %}
<div id="tag_list">
    Tags:
    <ul id="tags_ul">
{% for t in page.tags  %}
        <li><a href="/tags/{{t}}/">{{t}}</a></li>
{% endfor %}
    </ul>
</div>
{% endcodeblock %}

在`sass/custom/_styles.css`文件中添加如下内容：   

{% codeblock sass/custom/_styles.css lang:css %}
div#tag_list {
    font-size: 12pt;
}

#tags_ul {
    display: inline;
}

#tags_ul li:last-child:after {
  content: "";
}

#tags_ul li:after {
  content: ", ";
}

#tags_ul li {
    display: inline;
}
{% endcodeblock %}
###创建tag文件和tag云
使用作者提供的perl脚本文件，由于作者使用`Octopress`生成的文件是直接在public文件夹下面的，但是默认的`Octopress`生成的博客内容是在`/public/blog`文件夹下面的，因此作者的提供的perl文件需要进行一个小的改动，若没有改动将无法生成对应的tags，检查是否成功的办法是查看成功的生成了`source/_includes/custom/tag_cloud.html`文件，该文件的内容类似于下面的方式：

{% codeblock source/_includes/custom/tag_cloud.html  lang:html %}
<div id='tag_cloud'>
<a href="/blog/tags/6LoWPAN/" title="1 entry" class="tag_1">6LoWPAN</a>
<a href="/blog/tags/Arch/" title="1 entry" class="tag_1">Arch</a>
<a href="/blog/tags/AWK/" title="1 entry" class="tag_1">AWK</a>
</div>
{% endcodeblock %}
文章末尾附上修改后的`tagify.pl`文件。
在添加了该代码之后，整个生成tag的操作便是下面的步骤
{% codeblock 生成tags操作 lang:bash %}
rake generate
./tagify.pl
rake generate
{% endcodeblock %}
上面的代码只是需要在每次有新的tag加入的时候需要执行，如果新添加的博客文章没有使用新的tag，则不需要执行这个步骤，只需要按照正常的操作即可。  
上面的操作一共干了三件事：  

* 生成`source/_includes/custom/tag_cloud.html`文件，文件内容如上所述。
* 对于每个tag标签，在对应的目录下生成一个`index.markdown`文件，如对于`Linux`这个标签，将会创建`source/tags/Linux/index.markdown`这样一个文件。
* 同时创建了一个`source/tags/index.markdown`的文件，可以在主页面被引用。

###显示tag云标签
为了在右侧显示云标签，需要修改`_config.yaml`文件，将`tag_cloud.html`文件添加到`default_asides`中，目前的博客内容没有显示该分类，若想添加云标签显示可以通过修改`_config.yml`通过添加该侧边栏完成该功能。  
创建`source/_includes/asides/tag_cloud.html`文件，该文件包含了`soure/_includes/custom/tag_cloud.html`文件（该文件是由`tagify.pl`脚本文件生成的），文件的内容如下所示：
{% include_code source/_includes/asides/tag_cloud.html lang:html html/tag_cloud.html %}

接下来修改`sass/custom/_styles.css`文件，添加标签的`css`示例，该文件内容如下所示：

{% codeblock sass/custom/_styles.css lang:css %}
.tag_1 {
    font-weight: 200;
    font-size: 10pt;
}
.tag_2 {
    font-weight: 200;
    font-size: 12pt;
}
...
.tag_10 {
    font-weight: 900;
    font-size: 24pt;
}
{% endcodeblock %}

最后在导航控制文件`source/_includes/custom/navigation.html`中增加`Tags`标签，具体修改文件如下所示：

{% codeblock source/_includes/custom/navigation.html lang:html %}
<li><a href="/">Home</a></li>
<li><a href="/blog/archives">Archives</a></li>
+<li><a href="/tags/">Tags</a></li>
<li><a href="/about/">About Me</a></li>
{% endcodeblock %}

##总结
完成上述操作之后，便可以在主页的首部出现一个`Tags`的导航键，同时可以添加`Tags`分类标签到页面右侧的侧边栏，目前Tags标签功能似乎不支持中文页面的分类，待测试。

###代码附录
{% include_code 修改后的tagify.pl lang:perl perl/tagify.pl %}
[l1]:http://www.google.com/
[l2]:http://aijazansari.com/2012/01/07/tag-clouds-with-octopress/
