# Ubuntu
## 先安装依赖 flatpak
```bash
sudo apt install flatpak

sudo apt install gnome-software-plugin-flatpak -y

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
```
## 安装 cloudcompare
```
flatpak install flathub org.cloudcompare.CloudCompare
```

## run cloudcompare
```
flatpak run org.cloudcompare.CloudCompare
```