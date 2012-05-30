---
layout: post
title: "vim cookbook"
category:
tags: []
---
{% include JB/setup %}
字符翻转
xp

可交换的替换单词
1G
/idiot<enter>
cwmanager
n
.

%s/\<idiot\>/manager/gc
/\<idiot\>/ 	This text specifies the text we are looking for wand want. The \< tells Vim to match a word start and the \> tells Vim to match the end of a word.


检查Makefile错误的好方法，由于命令是以tab开始的，若是空格将有错误
:set list
可以显示出空格和tab的区别，tab是^I


vim读取man文件
man subject|ul -i|vim -

vim移除行末的空格
:1,$s/[tab]*$//


将last, First改为First Last
:1,$s/\([^,]*\),\(.*$\)/\2\1/
. The \( ... \) delimiters are used to inform the editor that the text that matches the regular expression side is to be treated special.

Hello *world!
123+4*56/2
my $str = '*whee!'
if ( x>3 ) {
  "Hello *world!"           ds"         Hello world!
  [123+4*56]/2              cs])        (123+456)/2
  "Look ma, I'm *HTML!"     cs"<q>      <q>Look ma, I'm HTML!</q>
  if *x>3 {                 ysW(        if ( x>3 ) {
  my $str = *whee!;         vllllS'     my $str = 'whee!';


vim --startuptime timefile the_file_you_want_to_edit
      查看vim启动时间所占用的时间比

set list查看不可见字符
