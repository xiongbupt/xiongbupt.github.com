---
layout: post
title: "Learning SQL(ch1-ch3)"
category: [Notes]
tags: [MySQL, Learning]
---
{% include JB/setup %}
##CH1 背景知识
###术语

|术  语  |   定义 |
|:------:|:-----------|
|实  体  |数据库用户所关注的对象，如顾客、部门、地理等。
|列      |存储在表中的独立数据片段。                    
|行      |所有列的一个集合，完整地描述了一个实体或实体上的某种行为，也称之为记录。
|表      |行的集合，既可以保存在内存中（未持久化），也可以保存在存储设备中（已持久化）。
|结果表  | 未持久化的表的另一个名字，一般为查询的结果。
|主 键   | 用于唯一标识表中每个行的一个或多个列。
|外 键   |一个或多个用于标识其他表中某一行的列。

###SQL语句分类
通过SQL方案语句所创建的所有数据库元素都被存储在一个特殊的表集合，即数据字典中。
SQL语句
{% highlight sql %}
>select / * 一个或多个事务 * / ...
>from  / * 一个或多个地点 * / ...
>where  / * 一个或多个条件 * / ...
>update
>delete
>insert
{% endhighlight %}

##CH2 创建和使用数据库
{% highlight sql %}
>mysql -u user -p passwd
{% endhighlight %}
进入用户名为user，密码为passwd的账户
在使用root用户登录之后可以创建其他的账户，允许其他账户进行登录
{% highlight sql %}
>create database bank;
{% endhighlight %}
创建一个bank数据库
{% highlight sql %}
>grant all privileges on bank.\* to 'someuser'@'localhost' identified by 'passwd'
{% endhighlight %}
创建一个用户名为someuser，密码为passwd的账户，可以使用bank数据库的所有表项，具有完全的权限。

{% highlight sql %}
>select now();
{% endhighlight %}
可以用来查询系统的时间，now()是MySQL内建的函数。
如果为了与oracle数据库兼容，可以使用
{% highlight sql %}
>select now() from dual;
{% endhighlight %}

###MySQL数据类型
仅仅讨论字符型、数值型和日期型
####字符类型
有两种，可变型和固定长度。固定长度的在长度不满足要求时使用空格向右填充，保证满足定长，而变长的不需要。
当定义一个字符列时**必须**指定字符串的最大长度。

1. char(20) 固定长度
2. varchar(20) 可变长度

char列可以设置的最大长度为*255*个字节，varchar列最多可以存储65535字节。

{% highlight sql %}
show character set;
{% endhighlight %}
显示mysql支持的字符集。
为数据列指定非默认的字符集只需要在类型定义后加上系统支持的字符集名称，比如
`varchar(20) character set utf8`

在mysql中修改整个数据库的默认字符集：
{% highlight sql %}
create database foreign_sales character set utf8;
{% endhighlight %}

#####文本数据
若超过了64KB则需要使用文本类型

|文本类型|最大值|
|:------|:----|
|tinytext|255
|text     |65 535
|mediumtext| 16 777 215
|longtext  | 4 294 967 295



注意：
若超长，则截短；
不会消除尾部的空格；
使用文本列排序时，只会使用前1024个字节，可以放宽；

####数值型数据
#####整数类型
|类型|最大值|
|:------|:----|
|tinyint| -128~127 0~255
|smallint| -32 768~32 767 0~65535
|mediumint| -8 388 608 ~ 8 388 607 0~16 777 215
|int      |-2 147 483 648 ~ 2 147 483 647 0 ~ 4 294 967 295
|bigint   |-9 223 372 036 854 775 808 ~ 9 223 372 036 854 775 807 (8字节)

#####浮点类型

1. float(p,s) 38次方
2. double(p,s) 308次方

p为小数点左边到右边所允许的数字总位数
s为小数点右边所允许的数字位数

####时间数据
|类型|格式|
|:------|:----|
|date |YYYY-MM-DD
|datetime| YYYY-MM-DD HH:MI:SS
|timestamp| YYYY-MM-DD HH:MI:SS
|year| YYYY
|time| HHH:MI:SS

####创建表
在定义表时，需要向数据库指明哪个列或者哪些列作为表的主键，通过为表建立一个约束(constraint)可以做到这一点。
MySQL提供了一种enum数据类型，与c语言的枚举是一个道理，仅仅允许从那几个字符里面选择一个。

{% highlight sql %}
>create table person (person_id smallint unsigned, fname varchar(20), lname varchar(20), gender enum('M','F'), birth_date date, street varchar(30), city varchar(20), state varchar(20), country varchar(20), postal_code varchar(20), constraint pk_person primary key (person_id) );
{% endhighlight %}

上述语句创建一个表。

{% highlight sql %}
>desc(describle) person;
{% endhighlight %}
查看表是否被创建

使用
{% highlight sql %}
>create table name (表所包含的数据);
{% endhighlight %}
来创建一个表。

使用desc查看表之后，在表中会出现NULL字段
对于NULL字段的出现，一共有三种情况：
业务上不可行
不知道应如何赋值
集合为空

{% highlight sql %}
>create table favorite_food (person_id smallint unsigned, food varchar(20), constraint pk_favorite_food primary key(person_id, food) , constraint fk_fav_food_person_id foreign key(person_id) references person(person_id) );
{% endhighlight %}
上述语句创建一个表，其中的`foreign key(key_name) references table_name(key_name)`是外键约束的创建，使得`key_name`仅仅只能是`table_name`这个表中的`key_name`。若在这个表里面没有对应的`key_name`时，创建条目将会是错误的。
如果在首次建表时忘记创建外键约束，可以在后面通过`alter table`语句添加。

####操作和修改表
#####插入数据insert
insert语句由3个部分构成
所要插入的数据的表的名称；
表中需要使用的列的名称；
需要插入到列的值。

{% highlight sql %}
>alter table talbe_name modify colum_name for_example smallint unsigned auto_increment;
{% endhighlight %}


{% highlight sql %}
>INSERT INTO table_name

>(column name)

>VALUES(the values);
{% endhighlight %}

mysql使用xml格式数据，在进入mysql数据库时，输入
{% highlight sql %}
mysql -u lrngsql -p --xml bank
{% endhighlight %}
输入密码之后即进入的是xml格式的数据库。

#####更新数据
{% highlight sql %}
>UPDATE table_name SET column1 = 'value1' column2 = 'value2' ... WHERE primary_key = somevalue
{% endhighlight %}
#####删除数据
{% highlight sql %}
>DELETE FROM table_name WHERE some_value mached
{% endhighlight %}
省略WHERE的条件，则会删除表中的所有数据。

#####常见错误

1. 主键不唯一
2. 不存在对应的外键
3. 列值不合法
4. 无效的日期转换

####显示数据库有多少表
{% highlight sql %}
>SHOW TABLES;
{% endhighlight %}
#####删除表
{% highlight sql %}
>DROP TABLES table_name:
{% endhighlight %}

##CH3 查询入门

1. select 确定结果集中应该包含哪些列
2. from   指明所要提取数据的表，以及这些表是如何链接的
3. where  过滤不需要的数据
4. group by 用于对具有相同列值的行进行分组
5. having  过滤掉不需要的组
6. order by 按一个或多个列，对最后结果集中的行进行排序

通常查询条件至少包好6个子句中的2～3个。

####SELECT子句
example:
{% highlight sql %}
SELECT * FROM table_name;
SELECT name FROM table_name;
{% endhighlight %}
显示`table_name`表中所有的行和列。
`select`子句用于在所有可能的列中，选择查询结果集要包含哪些列。就是从所有的列中，选出自己感兴趣的列进行打印出来。

在`select`字句中可以添加一些”调料“

1. 字符，比如数字或者字符串；
2. 表达式；
3. 调用内建函数；
4. 用户自定义的函数调用。

#####别的别名
{% highlight sql %}
>select column_name1 AS alias1, column_name2 AS alias2 from table;
{% endhighlight %}
从表中查找`column_name1`，同时将其取名为`alias1`。
用于实现标签的名字转换。
#####去除重复的行
在`select`后面加上关键字`distinct`。
{% highlight sql %}
>SELECT DISTINCT cust_id FROM account;
{% endhighlight %}
注意：对`DISTINCT`的使用，会对数据进行排序，会浪费时间。因此不要随便使用这个词，在确定没有重复数据时，便可以不使用它。

####FROM子句
from子句定义了查询中所使用的表，以及连接这些表的方式。

在对表的宽泛定义下，一共存在三种类型的表：

1. 永久表（使用create table语句创建的表）；
2. 临时表（select 子查询所返回的表）；
3. 虚拟表（使用create view 子句所创建的表）。

#####子查询产生的表
子查询可以出现在`select`语句中的各个部分并且包含在圆括号中。
#####视图
视图是存储在数据字典中的查询，它的行为表现的像一个表，但实际上并不拥有任何数据。
在使用这种查询时，需要首先创建一个视图

{% highlight sql %}
>CREATE VIEW view_name AS SELECT colmn_1, colmn_2 FROM table_name;
{% endhighlight %}

#####表链接
详见第5章，使用ON子句连接

#####定义表别名
有两种在from子句之外引用表的方式：

1.使用完整的表名称；

2.为每个表指定别名，并在查询中需要的地方使用该别名。

同样可以在别名的前面使用AS
example:
{% highlight sql %}
>SELECT alias.column1 FROM table alias;

>SELECT alias.column1 FROM table AS alias;
{% endhighlight %}
上面两个例子均是将table这个另外命名为alias，这个操作可以将表的名称进行简化。

####where子句
where子句的作用在于过滤不需要的行。
如果where中包含多个条件，它们之间的操作符使用and、or或者not分隔。
在混合使用不同的操作符时，应当总是使用圆括号来分隔成组的条件。

####group by和having子句
详见第八章
{% highlight sql %}
>SELECT d.name, count(e.emp_id) num_employees
>FROM department d INNER JOIN employee e
>ON d.dept_id = e.dept_id
>GROUP BY d.name
>HAVING coutn(e.emp_id) > 2
{% endhighlight %}

####order by子句
`order by`子句用于对结果中集中的原始列数据或是根据列数据计算的表达式结果进行排序。

可以使用多个条件在`order by`子句中。在这个子句中各列的出现顺序决定了对对各列排序的次序。

#####升序或降序排序
在排序时，可以通过关键字`asc`和`desc`指定是升序还是降序，默认情况下是升序排列。
#####根据表达式排序
{% highlight sql %}
>right(fed_id, 3)
{% endhighlight %}

使用MySQL的内建函数提取`fed_id`列的最后三个字符。
#####根据数字占位符排序
