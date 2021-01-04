
# Window 安装方式
## .msi 安装成window系统的一个服务，可以自动启动
https://www.jenkins.io/download/thank-you-downloading-windows-installer-stable/
 这种方式后台服务形式运行，调查问题不方便。

## 使用Tomcat
- 下载jenkins.war
- 下载Tomcat
- 将jenkins.war放在tomcat的webapps目录，会自动解压生成一个jenkins目录。

# 配置
- 正常添加系统变量JENKINS_HOME 就可以了，如果不好使的话，按照如下修改xml。
- 需要配置环境变量 JENKINS_HOME。如果是Tomcat,需要在Tomcat 9.0\conf\context.xml，添加JENKINS_HOME环境变量。
```XML
<Context>
<Environment name="JENKINS_HOME" value="D:/jenkins/" type="java.lang.String"/>
</Context>
```
- 初试密码放在：jenkins\secrets\initialAdminPassword
- jenkins.xml 可以修改端口号等信息
- 用户配置信息等 都放在 JENKINS_HOME directory。