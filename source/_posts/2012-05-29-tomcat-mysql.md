---
layout: post
title: "Tomcat MySQL"
category: 
tags: [Tomcat]
---
{% highlight java %}
org.apache.jasper.JasperException: javax.servlet.ServletException: com.mysql.jdbc.CommunicationsException: Communications link failure due to underlying exception: 

** BEGIN NESTED EXCEPTION ** 

java.net.SocketException
MESSAGE: java.net.ConnectException: Connection refused

STACKTRACE:

java.net.SocketException: java.net.ConnectException: Connection refused
	at com.mysql.jdbc.StandardSocketFactory.connect(StandardSocketFactory.java:156)
	at com.mysql.jdbc.MysqlIO.<init>(MysqlIO.java:276)
	at com.mysql.jdbc.Connection.createNewIO(Connection.java:2641)
	at com.mysql.jdbc.Connection.<init>(Connection.java:1531)
	at com.mysql.jdbc.NonRegisteringDriver.connect(NonRegisteringDriver.java:266)
	at java.sql.DriverManager.getConnection(DriverManager.java:579)
	at java.sql.DriverManager.getConnection(DriverManager.java:243)
	at org.apache.jsp.testSQL1_jsp._jspService(testSQL1_jsp.java:77)
	at org.apache.jasper.runtime.HttpJspBase.service(HttpJspBase.java:70)
	at javax.servlet.http.HttpServlet.service(HttpServlet.java:722)
	at org.apache.jasper.servlet.JspServletWrapper.service(JspServletWrapper.java:432)
	at org.apache.jasper.servlet.JspServlet.serviceJspFile(JspServlet.java:390)
	at org.apache.jasper.servlet.JspServlet.service(JspServlet.java:334)
	at javax.servlet.http.HttpServlet.service(HttpServlet.java:722)
	at org.apache.catalina.core.ApplicationFilterChain.internalDoFilter(ApplicationFilterChain.java:305)
	at org.apache.catalina.core.ApplicationFilterChain.doFilter(ApplicationFilterChain.java:210)
	at org.apache.catalina.core.StandardWrapperValve.invoke(StandardWrapperValve.java:224)
	at org.apache.catalina.core.StandardContextValve.invoke(StandardContextValve.java:169)
	at org.apache.catalina.authenticator.AuthenticatorBase.invoke(AuthenticatorBase.java:472)
	at org.apache.catalina.core.StandardHostValve.invoke(StandardHostValve.java:168)
	at org.apache.catalina.valves.ErrorReportValve.invoke(ErrorReportValve.java:98)
	at org.apache.catalina.valves.AccessLogValve.invoke(AccessLogValve.java:927)
	at org.apache.catalina.core.StandardEngineValve.invoke(StandardEngineValve.java:118)
	at org.apache.catalina.connector.CoyoteAdapter.service(CoyoteAdapter.java:407)
	at org.apache.coyote.http11.AbstractHttp11Processor.process(AbstractHttp11Processor.java:987)
	at org.apache.coyote.AbstractProtocol$AbstractConnectionHandler.process(AbstractProtocol.java:579)
	at org.apache.tomcat.util.net.JIoEndpoint$SocketProcessor.run(JIoEndpoint.java:309)
	at java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1110)
	at java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:603)
	at java.lang.Thread.run(Thread.java:722)


** END NESTED EXCEPTION **
{% endhighlight %}
在使用tomcat与mysql时，出现了上述错误，原因是由于mysql中的配置中禁用了网络的连接。在arch环境下，通过编辑/etc/mysql/my.cnf文件，将`skip-networking`这个选项注释掉即可。
