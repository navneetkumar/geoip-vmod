# %define VARNISHVER 3.0.3
Summary: GeoIP vmod
Name: geoip-vmod-%{VARNISHVER}
Version: 0.1
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: ./libvmod-digest.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0
BuildRequires: make, autoconf, automake, libtool, python-docutils

%description
GeoIP vmod

%prep
%setup -n %{name}

%build

%install
cp vmod/libvmod_geoip.so %{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
/usr/lib64/varnish/vmods/

%changelog
* rpm spec for 1.0