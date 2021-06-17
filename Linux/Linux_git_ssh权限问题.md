例如： Permissions 0644 for '/home/dbc-server-154/.ssh/id_rsa' are too open. It is required that your private key files are NOT accessible by others. This private key will be ignored. Load key "/home/dbc-server-154/.ssh/id_rsa": bad permissions

原因：
The relevant portion from the manpage (man ssh)：

~/.ssh/id_rsa
        Contains the private key for authentication.  These files contain sensitive 
        data and should be readable by the user but not
        accessible by others (read/write/execute).  ssh will simply ignore a private 
        key file if it is              
        accessible by others.  It is possible to specify a
        passphrase when generating the key which will be used to encrypt the sensitive 
        part of this file using 3DES.

~/.ssh/identity.pub
~/.ssh/id_dsa.pub
~/.ssh/id_ecdsa.pub
~/.ssh/id_rsa.pub
        Contains the public key for authentication.  These files are not sensitive and 
        can (but need not) be readable by anyone.

也就是说为了保护 ssh key的私有性，如果这个文件是可以被别人访问的，那么 ssh会任务有问题，不会使用。

同时这种情况只出现在 sshd服务使用StrictModes 的情况下，也可以修改这个mode，但是不推荐。 修改方式：

 chmod 400 ~/.ssh/id_rsa

或者

 chmod 600 ~/.ssh/id_rsa
