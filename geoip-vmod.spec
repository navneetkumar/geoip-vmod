# %define VARNISHVER 3.0.3
Summary: GeoIP vmod
Name: geoip-vmod-%{VARNISHVER}
Version: %{version}
Release: %{release}%{?dist}
License: BSD
Group: System Environment/Daemons
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0, geoip
BuildRequires: make, autoconf, pcre-devel,automake,libtool,geoip,geoip-devel


%description
GeoIP vmod

%prep
rm -rf varnish-3.0.3
rm -rf geoip-vmod
wget %{varnish_url}
tar -xzvf varnish-3.0.3.tar.gz
git clone %{source} geoip-vmod

%build
pushd varnish-3.0.3
  ./configure
   make
popd

%define vmod_dir %{buildroot}/usr/lib64/varnish/vmods/
rm -rf %{buildroot}
mkdir -p %{vmod_dir}

pushd geoip-vmod
  ./autogen.sh
  ./configure VARNISHSRC=../varnish-3.0.3 VMODDIR=%{vmod_dir} --prefix=/usr/
  make
popd

%install
pushd geoip-vmod
    make install
popd

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
/usr/lib64/varnish/vmods/