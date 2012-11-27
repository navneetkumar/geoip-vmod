# %define VARNISHVER 3.0.3
Summary: GeoIP vmod
Name: geoip-vmod-%{VARNISHVER}
Version: 0.1
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: .
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0
BuildRequires: make, autoconf, automake, libtool, python-docutils, pcre-devel

%description
GeoIP vmod

%prep
%setup -n %{name}

%build
cd %{VARNISHSRC}
./configure
 make
cd %{_topdir}

./autogen.sh
./configure VARNISHSRC=%{VARNISHSRC} VMODDIR=/usr/lib64/varnish/vmods/ --prefix=/usr/
make

%install
make install

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
/usr/lib64/varnish/vmods/

%changelog
* rpm spec for 1.0