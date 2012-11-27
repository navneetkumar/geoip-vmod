# %define VARNISHVER 3.0.3
Summary: GeoIP vmod
Name: geoip-vmod-%{VARNISHVER}
Version: 0.1
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0
BuildRequires: make, autoconf, pcre-devel,automake,libtool,geoip


%description
GeoIP vmod

%prep
rm -rf varnish-3.0.3
rm -rf geoip-vmod
wget %{varnish_src}
tar -xzvf varnish-3.0.3.tar.gz
git clone %{source} geoip-vmod

%build
pushd varnish-3.0.3
  ./configure
   make
popd

pushd geoip-vmod
  ./autogen.sh
  ./configure VARNISHSRC=../varnish-3.0.3 VMODDIR=/usr/lib64/varnish/vmods/ --prefix=/usr/
  make
popd

%install
make install

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
/usr/lib64/varnish/vmods/