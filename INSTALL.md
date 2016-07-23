# Some installation methods for every GNU/Linux distribution package management system should be here.

## Fedora 23/24/Rawhide
Fedora users can easily obtain tomatime from alunux/tomatime-git Copr repository.

```sh
$ su -c 'dnf copr enable alunux/tomatime-git'
$ su -c 'dnf install tomatime'
```
## Install from source

Before install tomatime from source, make sure you have **gcc** with c++ support, **Qt5**\*,**qmake**, and **qtchooser**.

```sh
$ git clone https://github.com/aancw/tomatime.git
$ cd tomatime/tomatime
$ make
$ sudo make clean install
```

Uninstall with this,

```sh
$ sudo make uninstall
```
\* Yes, it works in Qt5 only.
