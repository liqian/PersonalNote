# Jenkins 邮件配置
- 配置邮件测试时，如果出现：
com.sun.mail.smtp.SMTPSenderFailedException: 550 5.7.1 Client does not have   permissions to send as this sender.  
需要将[系统管理员邮件地址]同发送邮件的地址设置成一样的。
- https://blog.csdn.net/russ44/article/details/52263454

## Jenkins AUTH LOGIN failed
- 2个发送邮件的插件，如果配置和修改密码都需要同时修改。配置要一致。使用的账号需要同系统账号相同。
1. Extended E-mail Notification
2. 邮件通知
## Jenkins 根据 exit 1/0 判断失败还是成功

## Jenkins git
- 配置branch名： */branch_name
- 配置tag名：tag_name   
tag不需要 */
# Publish-Over-SSH 插件

## 邮件自定义变量内容，可用通过配置文件方式实现
- 路径是相对应${WORKSPACE}的相对目录
${PROPFILE,file="env.properties",property="line1"}
echo xxxx=xx > t.properties

使用echo创建文件
echo "aaaa" >> hello.txt
以追加的形式打开或创建文件,将字段写入到hello.txt;
echo "aaaa" > hello.txt
将字段写入hello.txt 覆盖之前的文件内容.

在echo创建文件时写入换行
echo -e "aaaa\nbbbb" >> hello.txt
-e 代表执行转义，-E代表禁止转义

注意：window下有可能非utf-8编码，解析会出现错误，使用如下bat:
@echo off
REM ::use utf-8 coding
chcp 65001
echo "# config file" > t.properties
echo username=ftpuser >> t.properties
echo password=ftpuser123 >> t.properties

## jenkins pipeline 
- 处理负载发布流程的，脚本实现

