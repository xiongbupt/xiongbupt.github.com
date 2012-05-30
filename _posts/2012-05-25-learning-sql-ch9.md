---
layout: post
title: "Learning SQL CH9"
category: 
tags: []
---
{% include JB/setup %}
#子查询
可以用于4种SQL语句中。
##什么是子查询
子查询是包含在另一个SQL语句内部的查询。子查询总是由括号括起来，并且通常在包含语句之前执行。
子查询可以返回的结果集为：

* 单列单行
* 单列多行
* 多列多行

当子查询的结果为单列单行时，它可以被用作等式的一个条件中的一个表达式，如果返回结果多于一行，它可以被比较，不能被用于等式判断）。
##子查询类型
根据子查询是否独立可以分为非关联子查询（查询完全独立）和关联子查询（引用包含语句中的列）。
##非关联子查询
可以独立执行。  
非关联的返回单行单列的子查询是<font color ="red">标量子查询。</font>
子查询中可以使用各种查询语句（6个）。
单一事务不能等于多个事务的集合。
###多行单列子查询
####in和not in运算符
{% highlight sql %}
mysql> SELECT branch_id, name, city
    -> FROM branch
    -> WHERE name IN ('Headquarters', 'Quincy Branch');
+-----------+---------------+---------+
| branch_id | name          | city    |
+-----------+---------------+---------+
|         1 | Headquarters  | Waltham |
|         3 | Quincy Branch | Quincy  |
+-----------+---------------+---------+
2 rows in set (0.00 sec)
mysql> SELECT branch_id, name, city
    -> FROM branch
    -> WHERE name NOT IN ('Headquarters', 'Quincy Branch');
+-----------+---------------+--------+
| branch_id | name          | city   |
+-----------+---------------+--------+
|         2 | Woburn Branch | Woburn |
|         4 | So. NH Branch | Salem  |
+-----------+---------------+--------+
2 rows in set (0.00 sec)
mysql> SELECT emp_id, fname, lname, title
    -> FROM employee
    -> WHERE emp_id IN (SELECT DISTINCT
    -> superior_emp_id
    -> FROM employee
    -> );
+--------+---------+-----------+--------------------+
| emp_id | fname   | lname     | title              |
+--------+---------+-----------+--------------------+
|      1 | Michael | Smith     | President          |
|      3 | Robert  | Tyler     | Treasurer          |
|      4 | Susan   | Hawthorne | Operations Manager |
|      6 | Helen   | Fleming   | Head Teller        |
|     10 | Paula   | Roberts   | Head Teller        |
|     13 | John    | Blake     | Head Teller        |
|     16 | Theresa | Markham   | Head Teller        |
+--------+---------+-----------+--------------------+
7 rows in set (0.00 sec)

mysql> SELECT emp_id, fname, lname, title FROM employee WHERE emp_id NOT IN (SELECT DISTINCT superior_emp_id FROM employee WHERE superior_emp_id IS NOT NULL);
+--------+----------+----------+----------------+
| emp_id | fname    | lname    | title          |
+--------+----------+----------+----------------+
|      2 | Susan    | Barker   | Vice President |
|      5 | John     | Gooding  | Loan Manager   |
|      7 | Chris    | Tucker   | Teller         |
|      8 | Sarah    | Parker   | Teller         |
|      9 | Jane     | Grossman | Teller         |
|     11 | Thomas   | Ziegler  | Teller         |
|     12 | Samantha | Jameson  | Teller         |
|     14 | Cindy    | Mason    | Teller         |
|     15 | Frank    | Portman  | Teller         |
|     17 | Beth     | Fowler   | Teller         |
|     18 | Rick     | Tulman   | Teller         |
+--------+----------+----------+----------------+
11 rows in set (0.00 sec)
{% endhighlight %}
<font color ="red">注意上面在使用`NOT IN`的时候该子句中的`WHERE superior_emp_id IS NOT NULL`</font>
####all运算符
####any运算符
###多列子查询
##关联子查询
关联子查询为每一个候选行，即可能成为结果的行执行一遍。
###exists运算符
exists运算符是构造包含关联子查询条件的最常用运算符。
在使用select语句时，经常使用的是`select 1`或者`select \*`
###关联子查询操作数据
<font color ="red">**切记，在MySQL中delete语句使用关联子查询时，无论如何都不能使用表别名。**</font>
##何时使用子查询
###子查询作为数据源
####数据加工
####面向任务的子查询
####过滤条件 中的子查询
####子查询作为表达式生成器
##子查询总结

* 返回结果可以是单行单列，单列多行以及多列多行
* 可以独立于包含语句（非关联子查询）
* 可以引用包含语句中的一行或多行（关联子查询）
* 可以用于条件中，这些条件使用比较运算符以及其他特殊目的的运算符（in，not in，exists和not exists）；
* 它可以出现在select、update、delete和insert语句；
* 它产生的结果集可以与其他表或子查询连接；
* 它可以生成值来填充表或者查询结果集中的一些列；
* 它可以用于查询中的select，from，where，having和order by子句。
