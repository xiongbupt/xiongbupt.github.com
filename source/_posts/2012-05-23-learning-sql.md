---
layout: post
title: "Learning SQL(ch4-ch6)"
category: Notes
tags: [MySQL, Learning]
---
##CH4 过滤
在所有的SQL数据处理语句中（insert语句除外）都包含了可选的where子句，其中的过滤条件限制了SQL语句所需要的行数。select子句中包含的having子句也可以对分组数据进行条件过滤。  
###条件评估
####使用圆括号
当含有多个条件时，各个条件应该使用圆括号括起来。
<!--more-->
####使用not操作符
一般用的较少，相当于取反的操作。
###构建条件
条件通常是由1个或多个包含1个到多个操作符的表达式构成。
表达式的组成包括：  

* 数字  
* 表或视图中的列
* 字符串
* 内建函数，比如函数concat('Learning', 'SQL')
* 子查询
* 表达式列表
* 比较操作符，比如=, !=, <, >, <>, LIKE, IN 和BEWEEN。
* 算术操作符，比如+, -, *和/

###条件类型
####相等条件
{% codeblock lang:sql %}
mysql>SELECT pt.name product_type, p.name product
->FROM product p INNER JOIN product_type pt
->ON p.product_type_cd = pt.product_type_cd
->WHERE pt.name = 'Customer Accounts';
{% endcodeblock %}

####不等条件
构造不等条件时，可以从`!=`或者`<>`中任选一个
{% codeblock lang:sql %}
mysql>SELECT pt.name product_type, p.name product
->FROM product p INNER JOIN product_type pt
->ON p.product_type_cd = pt.product_type_cd
->WHERE pt.name <> 'Customer Accounts';
{% endcodeblock %}

####范围条件
使用<，>等来构造范围
{% codeblock lang:sql %}
mysql> SELECT emp_id, fname, lname, start_date
    -> FROM employee
    -> WHERE start_date < '2007-01-01';
{% endcodeblock %}

{% codeblock lang:sql %}
mysql> SELECT emp_id, fname, lname, start_date
    -> FROM employee
    -> WHERE start_date < '2007-01-01';
    -> AND start_date > '2005-01-01';
{% endcodeblock %}

#####使用BETWEEN条件符
{% codeblock lang:sql %}
mysql> SELECT emp_id, fname, lname, start_date
    -> FROM employee
    -> WHERE start_date BETWEEN '2005-01-01' AND '2007-01-01';
{% endcodeblock %}
注意BETWEEN后面的数的取值，紧接着的那个数应该小于AND后面的那个数，同时，这是一个闭区间。比如BETWEEN a AND b，则取值范围为[a,b]。

使用BEWTEEN可以查询日期范围、数字范围，同时也可以查询字符串的范围。

{% codeblock lang:sql %}
mysql> SELECT account_id , product_cd, cust_id , avail_balance  
    -> FROM account 
    -> WHERE avail_balance BETWEEN 3000 AND 5000;
{% endcodeblock %}

####成员条件

{% codeblock lang:sql %}
mysql> SELECT account_id, product_cd, cust_id, avail_balance 
    -> FROM account
    -> WHERE product_cd = 'CHK' OR product_cd = 'SAV'
    -> OR product_cd = 'CD' OR product_cd = 'MM';
{% endcodeblock %}
使用in来代替上面的多个输入
{% codeblock lang:sql %}
mysql> SELECT account_id, product_cd, cust_id, avail_balance 
    -> FROM account
    -> WHERE product_cd IN ('CHK', 'SAV', 'CD', 'MM');
{% endcodeblock %}

使用子查询

使用not in

#####匹配条件
使用通配符

|通配符|匹配|
|:---:|:---:|
|_|正好一个字符
|%|任意数字字符（包括0）

使用正则表达式  
REGEXP

###null关键字
null的使用场合包括如下几种

* **没有合适的值**
* **值未确定**
* **值未定义**

当使用null时必须牢记以下两点

+ 表达式可以为null，但是不能等于null;
+ 两个null值彼此不能判断为相等。

##CH5 多表查询
将位于两个表中的数据通过一个相同的关键字整合到一起的机制便是连接（**join**）。本章主要描述的是内连接（**INNER JOIN**）。
###什么是连接
使用两个不同表中的列，这两个列的值是对应的，即这两个表中该列的值是相同的。通过使用这一列，从而实现在同一查询的结果集中包含来自两个表的列，这个操作被称为连接。
####笛卡尔积
在`FROM`子句中包含两个表，并且使用`JOIN`隔开。如下所示：
{% codeblock lang:sql %}
mysql> SELECT e.fname, e.lname, d.name
    -> FROM employee e JOIN department d;
{% endcodeblock %}
上面将会将这两个表中选出的东西做交叉乘积，类似于笛卡尔积的方式将返回结果。
     >笛卡尔积基本概念
     有两个集合A,B，对于任意元素a属于A，元素b属于B。这两个集合的笛卡尔积表示的是C{c=(a,b)|a属于A，b属于B}

因此上述的结果与笛卡尔积的结果类似，不属于同一个表的两个结果返回。上面这种连接被称为交叉连接（`cross join`），在实际中用的较少。
####内连接
为了将表的结果返回一个对应的值，需要使用内连接（`INNER JOIN`）。通过添加`ON`子句并可以达到这个目的。在使用内连接（`INNER JOIN`）时，如果两个表中出现了一个表中有而另一个表中对应的元素是缺失的情况下，将会把该对应的行去除。如果需要显示，需要使用外连接（`OUTER JOIN`），在后面会进行详细描述。
下面是个例子
{% codeblock lang:sql %}
mysql> SELECT e.fname, e.lname, d.name
    -> FROM employee e JOIN department d
    -> ON e.dept_id = d.dept_id;
{% endcodeblock %}
在上面的例子中，没有显示的指明是否为内连接，在默认的情况下是内连接，但是最好增加关键词`INNER`。如下所示：
{% codeblock lang:sql %}
mysql> SELECT e.fname, e.lname, d.name
    -> FROM employee e INNER JOIN department d
    -> ON e.dept_id = d.dept_id;
{% endcodeblock %}
如果连接的两个表的列名是相同的，可以使用`USING`子句来代替`ON`子句，如下所示：

{% codeblock lang:sql %}
mysql> SELECT e.fname, e.lname, d.name
    -> FROM employee e INNER JOIN department d
    -> USING (dept_id);
{% endcodeblock %}
####ANSI连接语法
下面是一个使用旧语法的例子，在这个例子中没有`ON`子句，在`FROM`子句中定义各表的别名，并使用逗号隔开，然后在`WHERE`子句中包含连接条件。
{% codeblock lang:sql %}
mysql> SELECT e.fname, e.lname, d.name
    -> FROM employee e, department d
    -> WHERE e.dept_id = d.dept_id;
{% endcodeblock %}
但是ANSI连接语法的优势如下：

* 连接条件和过滤条件被分隔到两个子句（`ON`子句和`WHERE`子句），使查询语句更易理解；
* 每两个表之间的连接条件都在它们自己的`ON`子句中列出，这样不容易错误地忽略了某些连接条件；
* 使用SQL92连接语法的查询语句具有通用性。

例子如下所示：
{% codeblock lang:sql %}
mysql> SELECT a.account_id, a.cust_id, a.open_date, a.product_cd
    -> FROM account a INNER JOIN employee e
    -> ON a.open_emp_id = e.emp_id
    -> INNER JOIN branch b
    -> ON e.assigned_branch_id = b.branch_id
    -> WHERE e.start_date < '2007-01-01'
    -> AND (e.title = 'Teller' OR e.title = 'Head Teller')
    -> AND b.name = 'Woburn Branch';
{% endcodeblock %}
###连接3个或更多的表
两个表的连接中，`FROM`子句中包含了两个表名和一种连接类型，`ON`子句中指定两表是怎么连接的。
对于三个表的连接中，`FROM`子句中包含了三个表名和两种连接类型，以及两个`ON`子句。
两个表的例子：
{% codeblock lang:sql %}
mysql> select a.account_id, c.fed_id
    -> FROM account a INNER JOIN customer c
    -> ON a.cust_id = c.cust_id
    -> WHERE c.cust_type_cd = 'B';
{% endcodeblock %}
三个表的例子
{% codeblock lang:sql %}
mysql> SELECT a.account_id, c.fed_id, e.fname, e.lname
    -> FROM account a INNER JOIN customer c
    -> ON a.cust_id = c.cust_id
    -> INNER JOIN employee e
    -> ON a.open_emp_id = e.emp_id
    -> WHERE c.cust_type_cd = 'B';
{% endcodeblock %}
SQL是一种非过程化的语言，因此表的顺序不重要。如果需要对表的顺序进行强制规定，对于MySQL可以使用`STRAIGHT_JOIN`进行强制的规定。如下所示：
{% codeblock lang:sql %}
mysql> SELECT STRAIGHT_JOIN a.account_id, c.fed_id, e.fname, e.lname
    -> FROM account a INNER JOIN customer c
    -> ON a.cust_id = c.cust_id
    -> INNER JOIN employee e
    -> ON a.open_emp_id = e.emp_id
    -> WHERE c.cust_type_cd = 'B';
{% endcodeblock %}
####将子查询结果作为查询表
在使用这种方式的时候，将子`SELECT`语句返回的结果使用一个括号括起来，然后在后面添加一个别名，在前面使用`INNER JOIN`与该表连接，在后面使用`ON`子句进行连接。
####连续两次使用同一表
在这种情况下，对同一个表使用两个不同的别名即可解决问题，其他的处理方式与两个不同的表的处理方式一样。
###自连接
同样是表的别名，其他与多张不同的表一样。
###相等连接和不等连接
除了可以使用等于号（=）之外还可以使用范围描述符。
###连接条件和过滤条件

##CH6 使用集合
###集合理论
交（intersect)
并（union）
差（except）
###示例
{% codeblock lang:sql %}
mysql> SELECT 1 num, 'abc' str
    -> UNION
    -> SELECT 9 num, 'efg' str;
{% endcodeblock %}
使用`SELECT`语句显示语句，然后使用`UNION`操作符将两个`SELECT`语句的内容进行并操作，在最终的结果中将会显示两行。
###集合操作符
集合操作符包含两种修饰符，一个表示包含重复项，另一个表示去除重复项。
####`UNION`操作符
`UNION ALL`保留重复项，`UNION`去除重复项。
示例
{% codeblock lang:sql %}
mysql> SELECT 'IND' type_cd, cust_id, lname name
    -> FROM individual
    -> UNION ALL
    -> SELECT 'BUS' type_cd, cust_id, name
    -> FROM business;
{% endcodeblock %}
示例2
{% codeblock lang:sql %}
mysql> SELECT 'IND' type_cd, cust_id, lname name
    -> FROM individual
    -> UNION ALL
    -> SELECT 'BUS' type_cd, cust_id, name
    -> FROM business
    -> UNION ALL
    -> SELECT 'BUS' type_cd, cust_id, name
    -> FROM business;
{% endcodeblock %}
示例3
{% codeblock lang:sql %}
mysql> SELECT emp_id
    -> FROM employee
    -> WHERE assigned_branch_id = 2
    -> AND (title = "Teller" OR title = "Header Teller")
    -> UNION ALL
    -> SELECT DISTINCT open_emp_id
    -> FROM account
    -> WHERE open_branch_id = 2;
{% endcodeblock %}

示例4
{% codeblock lang:sql %}
mysql> SELECT emp_id
    -> FROM employee
    -> WHERE assigned_branch_id = 2
    -> AND (title = "Teller" OR title = "Header Teller")
    -> UNION
    -> SELECT DISTINCT open_emp_id
    -> FROM account
    -> WHERE open_branch_id = 2;
{% endcodeblock %}
####intersect操作符
在MySQL中，没有实现intersect的操作。
{% codeblock lang:sql %}
SELECT emp_id, fname, lname
FROM employee
INTERSECT
SELECT cust_id, fname, lname
FROM individual
{% endcodeblock %}
####except操作符
MySQL中没有该操作符。
###集合操作规则
####对复合查询结果排序
通常情况下，复合查询中两个查询对应列的名字是相同的，但是不是强制的，如下所示：
{% codeblock lang:sql %}
mysql> SELECT emp_id, assigned_branch_id
    -> FROM employee
    -> WHERE title = 'Teller'
    -> UNION
    -> SELECT open_emp_id, open_branch_id
    -> FROM account
    -> WHERE product_cd = 'SAV'
    -> ORDER BY emp_id;
{% endcodeblock %}
如果这两个列的名字不同，但是指定的是后面列的名字的话，会出错，如下所示：
{% codeblock lang:sql %}
mysql> SELECT emp_id, assigned_branch_id
    -> FROM employee
    -> WHERE title = 'Teller'
    -> UNION
    -> SELECT open_emp_id, open_branch_id
    -> FROM account
    -> WHERE product_cd = 'SAV'
    -> ORDER BY open_emp_id;
ERROR 1054 (42S22): Unknown column 'open_emp_id' in 'order clause'
{% endcodeblock %}
####集合操作符优先级
用不同的集合操作符构建复合查询时会产生不同的查询结果。当复合查询包含3个或3个以上的查询语句，它们以自顶向下的顺序被解析和执行。注意以下两点

* 根据ANSI SQL标准，在调用集合操作时，intersect操作符比其他操作符具有更高的优先级；
* 可以用圆括号对多个查询进行封装，以明确指定它们的执行顺序。

但是需要注意的是**在MySQL中还没有实现intersect操作符，并且也不允许在复合查询时使用括号。**
