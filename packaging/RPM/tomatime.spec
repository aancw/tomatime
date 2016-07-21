%global _hardened_build 1
%global debug_package %{nil}
%define build_timestamp %(date +"%Y%m%d").git

Summary: tomatime: A Pomodoro App for Linux Platform
Name: tomatime
Version: %{build_timestamp}
Release: 1%{?dist}
License: GPLv2
Group: Applications/Productivity
URL: https://github.com/aancw/tomatime
Source0: https://github.com/aancw/tomatime/archive/master.zip
BuildRequires: qt5-qtbase-devel
Requires: qt5-qtbase

%description
tomatime is a Pomodoro App for Linux Platform

%prep
%autosetup -n %{name}-master/%{name}
cp ../{README.md,AUTHOR,INSTALL,LICENSE,CONTRIBUTORS} .

%build
qmake-qt5
make %{?_smp_mflags}

%install
install -d %{buildroot}%{_bindir}
install -d %{buildroot}%{_datadir}/applications
install -m 751 tomatime %{buildroot}%{_bindir}
install -m 644 tomatime.desktop \
        %{buildroot}%{_datadir}/applications/tomatime.desktop

for i in 1024 512 256 128 64 48 32 24 16; do
    install -D -m 0644 img/icons/${i}/tomatime.png \
            %{buildroot}%{_datadir}/icons/hicolor/${i}x${i}/apps/%{name}.png
done

%post
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null ||:
/usr/bin/update-desktop-database &>/dev/null ||:

%postun
if [ $1 -eq 0 ]; then
    /bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null ||:
    /usr/bin/gtk-update-icon-cache -f -t -q %{_datadir}/icons/hicolor ||:
fi
/usr/bin/update-desktop-database &>/dev/null ||:

%posttrans
/usr/bin/gtk-update-icon-cache -f -t -q %{_datadir}/icons/hicolor ||:

%clean
rm -rf %{buildroot} %{_builddir}/%{name}-master

%files
%defattr(-,root,root,-)
%doc README.md AUTHOR INSTALL LICENSE CONTRIBUTORS
%license LICENSE
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png

%changelog
* Wed Jul 20 2016 La Ode Muh. Fadlun Akbar <fadlun.net@gmail.com> - 20160720.git
- Build tomatime from upstream
- Create RPM SPEC for tomatime
- Convert icon-tomatime.png (512x512 px is actual size) to several size
- Create tomatime.desktop
- Other changelog at https://github.com/aancw/tomatime/commits/master
