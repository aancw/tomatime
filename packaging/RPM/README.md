# tomatime Packaging: RPM

This specfile can be used to build tomatime RPM package for Red Hat based distributions. Tested on Fedora 24.

## Local build

### Install build tools
```sh
$ su -c 'dnf -y install rpmdevtools'
```

### Setup packaging directory and enter to SPEC file directory
```sh
$ rpmdev-setuptree
$ cd ~/rpmbuild/SPECS
```

### Install dependencies
```sh
$ su -c 'dnf builddep tomatime.spec'
```

### Download source files
```sh
$ spectool -g -R tomatime.spec
```

### Build RPM
```sh
$ rpmbuild -bb tomatime.spec
```

### Try RPM
```sh
$ cd ~/rpmbuild/RPMS/$(uname -m)/
$ su -c 'dnf install ./tomatime-*.rpm'
```
