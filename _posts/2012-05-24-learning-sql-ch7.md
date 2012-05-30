---
layout: post
title: "Learning SQL ch7"
category: 
tags: [MySQL]
---
{% include JB/setup %}
##CH7 数据生成、转换和操作
###使用字符串数据
字符类型有CHAR，VARCHAR，TEXT类型，各种的范围不同，第二章中有详细的说明。
创建一个仅仅包含字符的表如下所示：
{% highlight sql %}
mysql> CREATE TABLE string_tbl
    -> (char_fld CHAR(30),
    -> vchar_fld VARCHAR(30),
    -> text_fld TEXT
    -> );
{% endhighlight %}
####生成字符串
生成字符串最简单的方式是用一对单引号将需要使用的字符串括起来。在向表中插入字符串数据时，保证长度不会超过设定的最大值。
{% highlight sql %}
mysql> INSERT INTO string_tbl (char_fld, vchar_fld, text_fld)
    -> VALUES ('This is char data',
    -> 'This is varchar data',
    -> 'This is text data');
{% endhighlight %}

#####包含单引号
通过在单引号前面添加一个单引号来转义该单引号。*在MySQL中可以使用反斜杠\\来作为转义符。*
#####包含特殊字符
通过使用MySQL中自带的`char`函数，可以将数字转成对应的字符。对于ASCII字符集，使用`CHAR(number)`可以返回ASCII的值为number的数所对应的字符。  
可以使用`concat()`函数来连接若干字符串，一些可以输入，另外一些可以通过`char()`函数生成。  
如果需要通过字符查询该字符的ASCII的值，可以通过调用`ascii`函数，该函数将会返回对应字符的ASCII值。  
####操作字符串
一共有两类操作字符串的函数，分别是返回<font color="red">数字</font>的和返回<font color="red">字符串</font>的。
#####返回数字的字符串函数
`length()`函数，返回字符串的长度。
{% highlight sql %}
mysql> SELECT LENGTH(char_fld) char_length,
    -> LENGTH(vchar_fld) varchar_length,
    -> LENGTH(text_fld) text_length
    -> FROM string_tbl;
{% endhighlight %}
`position()`函数，返回子字符串在字符串的位置。
{% highlight sql %}
mysql> SELECT POSITION('charcters' IN vchar_fld)
    -> FROM string_tbl;
{% endhighlight %}
上面这个`POSITION`函数的返回值，当没有匹配的时候，返回0，当匹配了的时候，返回匹配的位置。注意这个第一位置为1，不是0。

如果希望指定搜索开始的位置，而不是默认的0那个位置，可以使用`locate`函数。与`position`类似，但是可以接受可选的第三个参数，指定开始的位置。
{% highlight sql %}
mysql> SELECT LOCATE('is', vchar_fld, 5)
    -> FROM string_tbl;
{% endhighlight %}

`strcmp()`函数，有三种返回值，

* -1，第一个字符串的排序位于第二个字符串之前；
*  0，两个字符串相同；
*  1，第一个字符串的排序位于第二个字符串之后。

<font color ="red">在**MySQL中，`strcmp`对小写不区分，也因为这，会导致在比较的两个字符是对应的大小写时，会出现相应的结果
**</font>

除了`strcmp`函数之外，对于比较还可以使用`like`或者`regex`操作符来比较字符串。这些比较的结果为1（true）或0（false）。

ex1：
{% highlight sql %}
mysql> SELECT name, name LIKE "%ns" ends_in_ns
    -> FROM department;
+----------------+------------+
| name           | ends_in_ns |
+----------------+------------+
| Operations     |          1 |
| Loans          |          1 |
| Administration |          0 |
+----------------+------------+
3 rows in set (0.00 sec)
{% endhighlight %}

ex2:
{% highlight sql %}
mysql> SELECT cust_id, cust_type_cd, fed_id,
    -> fed_id REGEXP '.{3}-.{2}-.{4}' is_ss_no_format
    -> FROM customer;
+---------+--------------+-------------+-----------------+
| cust_id | cust_type_cd | fed_id      | is_ss_no_format |
+---------+--------------+-------------+-----------------+
|       1 | I            | 111-11-1111 |               1 |
|       2 | I            | 222-22-2222 |               1 |
|       3 | I            | 333-33-3333 |               1 |
|       4 | I            | 444-44-4444 |               1 |
|       5 | I            | 555-55-5555 |               1 |
|       6 | I            | 666-66-6666 |               1 |
|       7 | I            | 777-77-7777 |               1 |
|       8 | I            | 888-88-8888 |               1 |
|       9 | I            | 999-99-9999 |               1 |
|      10 | B            | 04-1111111  |               0 |
|      11 | B            | 04-2222222  |               0 |
|      12 | B            | 04-3333333  |               0 |
|      13 | B            | 04-4444444  |               0 |
+---------+--------------+-------------+-----------------+
{% endhighlight %}

#####返回字符串的字符串函数
可以使用`concat()`来替换字符列所存储的数据。
{% highlight sql %}
mysql> DELETE FROM string_tbl;
Query OK, 1 row affected (0.09 sec)

mysql> INSERT INTO string_tbl (text_fld)
    -> VALUES ('This string was 29 characters');
Query OK, 1 row affected (0.11 sec)

mysql> UPDATE string_tbl
    -> SET text_fld = CONCAT(text_fld, ', but now it is longer');
Query OK, 1 row affected (0.10 sec)
Rows matched: 1  Changed: 1  Warnings: 0
mysql> SELECT text_fld FROM string_tbl;
+-----------------------------------------------------+
| text_fld                                            |
+-----------------------------------------------------+
| This string was 29 characters, but now it is longer |
+-----------------------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
`insert()`函数接受四个参数：原始字符串、字符串操作开始的位置、需要替换的字符数以及替换字符串。  
ex1：
{% highlight sql %}
mysql> SELECT INSERT('goodbye world', 9, 0, 'cruel ') string;
+---------------------+
| string              |
+---------------------+
| goodbye cruel world |
+---------------------+
1 row in set (0.00 sec)
{% endhighlight %}
如上所示，若第三个参数为0，则不会发生替换，第二个位置开始的字符将会向右移动，相当于插入操作了。  
如果第三个操作数不为0，则从第二个操作数指定的位置开始，延续第三个操作数那么长的字符均将会被抹去，替换成为第四个字符串指定的内容。如下所示：  
{% highlight sql %}
mysql> SELECT INSERT('goodbye world', 1, 7, 'hello ') string;
+--------------+
| string       |
+--------------+
| hello  world |
+--------------+
1 row in set (0.00 sec)
mysql> SELECT INSERT('goodbye world', 1, 2, 'hello ') string;
+-------------------+
| string            |
+-------------------+
| hello odbye world |
+-------------------+
1 row in set (0.00 sec)

mysql> SELECT INSERT('goodbye world', 1, 1, 'hello ') string;
+--------------------+
| string             |
+--------------------+
| hello oodbye world |
+--------------------+
1 row in set (0.00 sec)
{% endhighlight %}
`replace()`函数完成替换功能，但是它是全部替换。如下所示：
{% highlight sql %}
mysql> SELECT REPLACE('goodbye world', 'goodbye', 'hello')
    -> FROM dual;
+----------------------------------------------+
| REPLACE('goodbye world', 'goodbye', 'hello') |
+----------------------------------------------+
| hello world                                  |
+----------------------------------------------+
1 row in set (0.00 sec)
mysql> SELECT REPLACE('goodbye goodbye hello world', 'goodbye', 'hello') string; 
+-------------------------+
| string                  |
+-------------------------+
| hello hello hello world |
+-------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
###使用数值数据
####执行算术函数
|函数名|描述|
|:---:|:----:|
|Acos(x)|反余弦
|Asin(x)|反正弦
|Atan(x)|反正切
|Cos(x)|余弦
|Cot(x)|余切
|Exp(x)|e的x次方
|Ln(x)|x的自然对数
|Sin(x)|正弦
|Sqrt(x)|x的平方根
|Tan(x)|正切

`mod(x,y)`用于取余操作，如下所示：
{% highlight sql %}
mysql> SELECT MOD(10, 4);
+------------+
| MOD(10, 4) |
+------------+
|          2 |
+------------+
1 row in set (0.00 sec)
{% endhighlight %}

`POW(x,y)`用于求幂操作，如下所示：
{% highlight sql %}
mysql> SELECT POWER(2, 10);
+--------------+
| POWER(2, 10) |
+--------------+
|         1024 |
+--------------+
1 row in set (0.00 sec)
{% endhighlight %}
####控制数字的精度

* `ceil()`向上取整。
* `floor()`向下取整。
* `round()`四舍五入。
* `truncate()`小数点后长度截短，不进行进位。

例子如下所示：
{% highlight sql %}
mysql> SELECT CEIL(72.445), FLOOR(72.445);
+--------------+---------------+
| CEIL(72.445) | FLOOR(72.445) |
+--------------+---------------+
|           73 |            72 |
+--------------+---------------+
1 row in set (0.00 sec)
mysql> SELECT ROUND(72.449), ROUND(72.5001),  ROUND(72.500);
+---------------+----------------+---------------+
| ROUND(72.449) | ROUND(72.5001) | ROUND(72.500) |
+---------------+----------------+---------------+
|            72 |             73 |            73 |
+---------------+----------------+---------------+
1 row in set (0.00 sec)
mysql> SELECT ROUND(72.909, 1), ROUND(72.909, 2),  ROUND(72.909, 3);
+------------------+------------------+------------------+
| ROUND(72.909, 1) | ROUND(72.909, 2) | ROUND(72.909, 3) |
+------------------+------------------+------------------+
|             72.9 |            72.91 |           72.909 |
+------------------+------------------+------------------+
1 row in set (0.00 sec)
mysql> SELECT TRUNCATE(72.909, 1), TRUNCATE(72.909, 2),  TRUNCATE(72.909, 3);
+---------------------+---------------------+---------------------+
| TRUNCATE(72.909, 1) | TRUNCATE(72.909, 2) | TRUNCATE(72.909, 3) |
+---------------------+---------------------+---------------------+
|                72.9 |               72.90 |              72.909 |
+---------------------+---------------------+---------------------+
1 row in set (0.00 sec)
{% endhighlight %}
####处理有符号数
`SIGN()`函数根据正负数返回值。正数返回1，负数返回-1，零返回0。如下所示：
{% highlight sql %}
mysql> SELECT SIGN(-10), SIGN(10.1), SIGN(0);
+-----------+------------+---------+
| SIGN(-10) | SIGN(10.1) | SIGN(0) |
+-----------+------------+---------+
|        -1 |          1 |       0 |
+-----------+------------+---------+
1 row in set (0.00 sec)
{% endhighlight %}
`ABS()`函数返回绝对值，如下所示：
{% highlight sql %}
mysql> SELECT ABS(-10), ABS(10.1), ABS(0);
+----------+-----------+--------+
| ABS(-10) | ABS(10.1) | ABS(0) |
+----------+-----------+--------+
|       10 |      10.1 |      0 |
+----------+-----------+--------+
1 row in set (0.00 sec)
{% endhighlight %}
###使用时间数据
####处理时区
查看当前系统时区以及会话所取的时区如下所示：
{% highlight sql %}
mysql> SELECT @@global.time_zone, @@session.time_zone;
+--------------------+---------------------+
| @@global.time_zone | @@session.time_zone |
+--------------------+---------------------+
| SYSTEM             | SYSTEM              |
+--------------------+---------------------+
1 row in set (0.00 sec)
{% endhighlight %}
####生成时间数据
可以使用下面任意一种方法产生时间数据：
* 从已有的date、datetime和time列中复制数据；
* 执行返回date、datetime和time型数据的内建函数；
* 构建可以被服务器识别的代表日期的字符串。
#####从字符串到日期的转换
`cast()`函数
{% highlight sql %}
mysql> SELECT CAST('2012-05-24 18:40:00' AS DATETIME);
+-----------------------------------------+
| CAST('2012-05-24 18:40:00' AS DATETIME) |
+-----------------------------------------+
| 2012-05-24 18:40:00                     |
+-----------------------------------------+
1 row in set (0.00 sec)

mysql> SELECT CAST('2012-05-24 18:40:00' AS TIME);
+-------------------------------------+
| CAST('2012-05-24 18:40:00' AS TIME) |
+-------------------------------------+
| 18:40:00                            |
+-------------------------------------+
1 row in set (0.00 sec)

mysql> SELECT CAST('2012-05-24 18:40:00' AS DATE);
+-------------------------------------+
| CAST('2012-05-24 18:40:00' AS DATE) |
+-------------------------------------+
| 2012-05-24                          |
+-------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
#####产生日期的函数
当提供的字符串不满足`CAST()`函数操作的字符串时，需要将对应的字符串进行转换，可以使用`str_to_date()`函数。该函数的使用之后生成的字符串将可以被`CAST()`函数使用。
`str_to_date()`
{% highlight sql %}
mysql> SELECT STR_TO_DATE('September 17, 2012', '%M %d, %Y');
+------------------------------------------------+
| STR_TO_DATE('September 17, 2012', '%M %d, %Y') |
+------------------------------------------------+
| 2012-09-17                                     |
+------------------------------------------------+
1 row in set (0.00 sec)
mysql> SELECT CAST(STR_TO_DATE('September 17, 2012', '%M %d, %Y') AS DATE);
+--------------------------------------------------------------+
| CAST(STR_TO_DATE('September 17, 2012', '%M %d, %Y') AS DATE) |
+--------------------------------------------------------------+
| 2012-09-17                                                   |
+--------------------------------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}

|日期格式部件|描述|
|:----------:|:-----:|
|%M|月名称（1~12）
|%m|月序号（01-12）
|%d|日序号（01-31）
|%j|日在一年中的序号（01-366）
|%W|星期名称
|%Y|4位数表示年份
|%y|两位数字表示年份
|%H|小时（00～23）
|%h|小时（01～12）
|%i|分钟（00～59）
|%s|秒钟（00～59）
|%f|微妙（000000～999999）
|%p|A.M.或P.M.

`str_to_date`根据字符串内容返回`datetime`、`date`、或者`time`类型值，如果格式字符串只包含%H，%i或%s，将会返回`TIME`值。

如果需要产生当前日期/时间，可以调用内建函数，`CURRENT_DATE()`，`CURRENT_TIME()`，`CURRENT_TIMESTAMP()`
{% highlight sql %}
mysql> SELECT CURRENT_DATE(), CURRENT_TIME(), CURRENT_TIMESTAMP();
+----------------+----------------+---------------------+
| CURRENT_DATE() | CURRENT_TIME() | CURRENT_TIMESTAMP() |
+----------------+----------------+---------------------+
| 2012-05-25     | 02:56:43       | 2012-05-25 02:56:43 |
+----------------+----------------+---------------------+
1 row in set (0.00 sec)
{% endhighlight %}  
####操作时间数据
#####返回日期的函数
`DATE_ADD()`，接收一个日期型的值作为参数，返回另一个日期，如下所示： 
{% highlight sql %}
mysql> SELECT DATE_ADD(CURRENT_DATE(), INTERVAL 5 DAY);
+------------------------------------------+
| DATE_ADD(CURRENT_DATE(), INTERVAL 5 DAY) |
+------------------------------------------+
| 2012-05-30                               |
+------------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
其中第二个参数包含了3个元素：<font color ="red">`INTERVAL`关键字、所需要增加的数量以及时间间隔类型</font>

|间隔名称|描述|
|:---:|:----:|
|Second|秒
|Minute|分钟
|Hour|小时
|Day|天数
|Month|月份
|Year|年份
|Minute_second|分钟数和秒钟数，中间用":"隔开
|Hour_second|小时、分钟和秒钟数，中间用":"隔开
|Year_month|年份和月份，中间用"-"隔开
`last_day()`函数返回当前月份的最后一天。 
{% highlight sql %}
mysql> SELECT LAST_DAY(CURRENT_DATE());
+--------------------------+
| LAST_DAY(CURRENT_DATE()) |
+--------------------------+
| 2012-05-31               |
+--------------------------+
1 row in set (0.00 sec)
mysql> SELECT LAST_DAY(CAST(CURRENT_DATE() AS DATETIME));
+--------------------------------------------+
| LAST_DAY(CAST(CURRENT_DATE() AS DATETIME)) |
+--------------------------------------------+
| 2012-05-31                                 |
+--------------------------------------------+
1 row in set (0.01 sec)

mysql> SELECT LAST_DAY(CAST(CURRENT_DATE() AS DATE));
+----------------------------------------+
| LAST_DAY(CAST(CURRENT_DATE() AS DATE)) |
+----------------------------------------+
| 2012-05-31                             |
+----------------------------------------+
1 row in set (0.00 sec)

mysql> SELECT LAST_DAY(CAST(CURRENT_DATE() AS TIME));
+----------------------------------------+
| LAST_DAY(CAST(CURRENT_DATE() AS TIME)) |
+----------------------------------------+
| NULL                                   |
+----------------------------------------+
1 row in set, 2 warnings (0.00 sec)
{% endhighlight %}

`convert_tz()`函数将一个时区的datetime值转换为另一个时区的datetime值。
#####返回字符串的时间函数
返回字符串的函数大多用于提取日期或时间的一部分。`dayname()`可以确定某一日是星期几：
{% highlight sql %}
mysql> SELECT DAYNAME(CURRENT_DATE());
+-------------------------+
| DAYNAME(CURRENT_DATE()) |
+-------------------------+
| Friday                  |
+-------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
推荐使用`EXTRACT()`函数从时间中获取当前的年月日等。
{% highlight sql %}
mysql> SELECT EXTRACT(YEAR FROM CURRENT_DATE());
+-----------------------------------+
| EXTRACT(YEAR FROM CURRENT_DATE()) |
+-----------------------------------+
|                              2012 |
+-----------------------------------+
1 row in set (0.00 sec)
mysql> SELECT EXTRACT(MINUTE FROM CURRENT_TIMESTAMP());
+------------------------------------------+
| EXTRACT(MINUTE FROM CURRENT_TIMESTAMP()) |
+------------------------------------------+
|                                       36 |
+------------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
#####返回数字的时间函数
`datediff()`计算两个日期的相差天数。
###转换函数
使用'CAST()`函数完成转换功能。
{% highlight sql %}
mysql> SELECT CAST('1456328' AS SIGNED INTEGER);
+-----------------------------------+
| CAST('1456328' AS SIGNED INTEGER) |
+-----------------------------------+
|                           1456328 |
+-----------------------------------+
1 row in set (0.00 sec)

mysql> SELECT CAST('-1456328' AS SIGNED INTEGER);
+------------------------------------+
| CAST('-1456328' AS SIGNED INTEGER) |
+------------------------------------+
|                           -1456328 |
+------------------------------------+
1 row in set (0.00 sec)
{% endhighlight %}
