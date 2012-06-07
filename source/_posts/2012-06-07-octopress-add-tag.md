---
layout: post
title: "Octopress添加标签"
category: Notes
tags: [VIM, Learning]
---

##前因
由于之前参考中文的搜索，结果都不理想，推翻重来，直接使用[google][l1]使用`octopress tag`关键词搜索到的[第一个返回结果][l2]来修改，下面记录如下。
###显示所有的便签列表
修改`source/_layouts/post.html`文件，使它们include一个名字为`tags.html`的新文件。

创建一个新文件`source/_includes/post/tags.html`，整个文件的内容如下所示：
    <div id="tag_list">
        Tags:
        <ul id="tags_ul">
    {% for t in page.tags  %}
            <li><a href="/tags/{{t}}/">{{t}}</a></li>
    {% endfor %}
        </ul>
    </div>

在sass/custom/_styles.css文件中添加如下内容：

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
###创建tag文件和tag云
使用作者提供的perl脚本文件。
###显示tag云标签
为了在右侧显示云标签，需要修改`_config.yaml`文件，添加

[l1]:http://www.google.com/
[l2]:http://aijazansari.com/2012/01/07/tag-clouds-with-octopress/
