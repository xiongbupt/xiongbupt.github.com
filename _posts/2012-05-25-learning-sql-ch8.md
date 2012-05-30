---
layout: post
title: "Learning SQL CH8"
category: 
tags: [MySQL]
---
{% include JB/setup %}
##分组与聚集
使用`GROUP`来完成分组的功能，如下图所示：
{% highlight sql %}
mysql> SELECT open_emp_id
    -> FROM account
    -> GROUP BY open_emp_id;
+-------------+
| open_emp_id |
+-------------+
|           1 |
|          10 |
|          13 |
|          16 |
+-------------+
4 rows in set (0.00 sec)
{% endhighlight %}
`COUNT()`称为聚集函数，可以计算每个分组的行数，如下面的例子所示。本例相对于上例来说仅仅添加了`COUNT()`函数来完成聚集功能。
{% highlight sql %}
mysql> SELECT open_emp_id, COUNT(*) how_many
    -> FROM account
    -> GROUP BY open_emp_id;
+-------------+----------+
| open_emp_id | how_many |
+-------------+----------+
|           1 |        8 |
|          10 |        7 |
|          13 |        3 |
|          16 |        6 |
+-------------+----------+
4 rows in set (0.00 sec)
{% endhighlight %}
上例说明，通过联合使用`group by`子句和`count()`聚集函数，可以在不查看原始数据的情况下，精确满足业务问题对数据的需要。  
<font color ="red">**使用group函数时，不应该在`WHERE`子句中使用聚集函数`COUNT()`。因为在评估`WHERE`子句时分组还没有被创建。因此必须在`HAVING()`子句中使用分组过滤条件。**</font>
{% highlight sql %}
mysql> SELECT open_emp_id, COUNT(*) how_many
    -> FROM account
    -> GROUP BY open_emp_id
    -> HAVING COUNT(*) > 4;
+-------------+----------+
| open_emp_id | how_many |
+-------------+----------+
|           1 |        8 |
|          10 |        7 |
|          16 |        6 |
+-------------+----------+
3 rows in set (0.00 sec)
{% endhighlight %}
###聚集函数
聚集函数对某个分组的所有行执行特定的操作。

* `MAX()`返回集合中的最大值
* `MIN()`返回集合中的最小值
* `AVG()`返回集合中的平均值
* `SUM()`返回集合中的所有值的和
* `COUNT()`返回集合中值的个数

####隐式分组或显示分组
隐式分组就是没有使用`GOURP BY`的查询语句，显示分组即是使用了`GROUP BY`子句的语句。
####对独立值计数
即在`COUNT()`子句中不是使用`COUNT(*)`来进行聚集，而是使用`COUNT(name)`来记数。当需要去除重复的name时，需要在`COUNT()`中添加`DISTINCT`关键字。即`COUNT(DISTINCT NAME)`的方式来完成对应的计数统计。
####使用表达式
在聚集函数中可以使用表达式
####NULL值的处理
对于`MAX()`,`MIN()`,`AVG()`,`SUM()`中，没有什么影响。但是对于`COUNT()`而言，当使用`COUNT(*)`时，会有变化。但是使用`COUNT(NAME)`这种情况没有变化。
###产生分组
####单列分组
`GROUP BY`后面仅仅有一个条目
####多列分组
`GROUP BY`后面有多个条目
####利用表达式分组
`GROUP BY`后面跟着的是一个表达式
####产生合计数
使用`WITH ROLLUP`，示例如下：
{% highlight sql %}
mysql> SELECT product_cd, open_branch_id,
    -> SUM(avail_balance) avail_balance
    -> FROM account
    -> GROUP BY product_cd, open_branch_id WITH ROLLUP;
+------------+----------------+---------------+
| product_cd | open_branch_id | avail_balance |
+------------+----------------+---------------+
| BUS        |              2 |       9345.55 |
| BUS        |              4 |          0.00 |
| BUS        |           NULL |       9345.55 |
| CD         |              1 |      11500.00 |
| CD         |              2 |       8000.00 |
| CD         |           NULL |      19500.00 |
| CHK        |              1 |        782.16 |
| CHK        |              2 |       3315.77 |
| CHK        |              3 |       1057.75 |
| CHK        |              4 |      67852.33 |
| CHK        |           NULL |      73008.01 |
| MM         |              1 |      14832.64 |
| MM         |              3 |       2212.50 |
| MM         |           NULL |      17045.14 |
| SAV        |              1 |        767.77 |
| SAV        |              2 |        700.00 |
| SAV        |              4 |        387.99 |
| SAV        |           NULL |       1855.76 |
| SBL        |              3 |      50000.00 |
| SBL        |           NULL |      50000.00 |
| NULL       |           NULL |     170754.46 |
+------------+----------------+---------------+
21 rows in set (0.00 sec)
{% endhighlight %}
###分组过滤条件
当使用分组数据时，不能使用`WHERE`子句，过滤子句应该使用`HAVING`子句。在分组之后如果需要对数据应用过滤条件，可以在`HAVING`子句中放置这些条件。
可以在`HAVING`子句中包含未在`SELECT`子句中出现的聚集函数。

