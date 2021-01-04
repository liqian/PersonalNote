Note these considerations and project scope first.

Download the latest build of OpenSSH. To get links to latest downloads this wiki page.

Extract contents of the latest build to C:\Program Files\OpenSSH (Make sure binary location has the Write permissions to just to SYSTEM, Administrator groups. Authenticated users should and only have Read and Execute.)

In an elevated Powershell console, run the following
```
powershell.exe -ExecutionPolicy Bypass -File install-sshd.ps1
```
Open the firewall for sshd.exe to allow inbound SSH connections

New-NetFirewallRule -Name sshd -DisplayName 'OpenSSH Server (sshd)' -Enabled True -Direction Inbound -Protocol TCP -Action Allow -LocalPort 22
Note: New-NetFirewallRule is for Windows 2012 and above servers only. If you're on a client desktop machine (like Windows 10) or Windows 2008 R2 and below, try:

netsh advfirewall firewall add rule name=sshd dir=in action=allow protocol=TCP localport=22
Start sshd (this will automatically generate host keys under %programdata%\ssh if they don't already exist)

net start sshd
Optional

To configure a default shell, see here
To setup sshd service to auto-start
Set-Service sshd -StartupType Automatic
To migrate sshd configuration from older versions (0.0.X.X), see here
Uninstall Win32 OpenSSH
Start Windows Powershell as Administrator
Navigate to the OpenSSH directory
cd 'C:\Program Files\OpenSSH'
Run the uninstall script
```
powershell.exe -ExecutionPolicy Bypass -File uninstall-sshd.ps1
```