require 'formula'

# Documentation: https://github.com/mxcl/homebrew/wiki/Formula-Cookbook
# PLEASE REMOVE ALL GENERATED COMMENTS BEFORE SUBMITTING YOUR PULL REQUEST!

class VmodGeoip < Formula
  homepage ''
  url 'https://github.com/navneetkumar/geoip-vmod/archive/master.zip'
  version '1'
  #sha1 '35826c43232220c41161aeb8f4f4f0f9b207a4ff'

  depends_on 'autoconf' => :build
  depends_on 'automake' => :build
  depends_on 'libtool' => :build
  depends_on 'pkg-config' => :build
  #depends_on 'wget' => :build


  def install
    #system "sh autogen.sh"
    varnish_url = "http://repo.varnish-cache.org/source/varnish-3.0.3.tar.gz"
    system "/usr/local/bin/wget #{varnish_url}"
    system "/usr/bin/tar -xvf varnish-3.0.3.tar.gz"
    #system "cd varnish-3.0.3"
    system "sh #{prefix}/varnish-3.0.3/configure"
    system 'lxs'
    #system "./configure", "--disable-debug", "--disable-dependency-tracking",
    #"--prefix=#{prefix}","VARNISHSRC=/Users/navneetk/Desktop/Dev-Drive/geo_ip/varnish-3.0.3"
    #system "make install" # if this fails, try separate make/make install steps
  end

  def test
    # This test will fail and we won't accept that! It's enough to just replace
    # "false" with the main program this formula installs, but it'd be nice if you
    # were more thorough. Run the test with `brew test vmod-geoip`.
    system "false"
  end
end
