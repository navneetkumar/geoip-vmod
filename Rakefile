VARNISH_FOLDER = "varnish-3.0.3"
VARNISH_FILE_NAME = "#{VARNISH_FOLDER}.tar.gz"
VARNISH_URL = "http://repo.varnish-cache.org/source/varnish-3.0.3.tar.gz"
PROJECT_ROOT = File.expand_path(File.dirname(__FILE__))

require 'fileutils'

namespace :varnish do
  desc "compile varnish"
  task :clean do
    %x[rm -rf tmp]
    %x[rm -rf vmod]
  end
  task :compile do
    puts "Compiling varnish from #{VARNISH_URL}"
    FileUtils.mkdir_p 'tmp'
    Dir.chdir('tmp')
    %x[wget #{VARNISH_URL}] unless File.exists?(VARNISH_FILE_NAME)
    %x[tar -xzf #{VARNISH_FILE_NAME}]
    Dir.chdir(VARNISH_FOLDER)
    system("./configure")
    system("make")
  end

  task :vmod => :compile do
    puts "building geoip-vmod for varnish version #{VARNISH_FOLDER}"
    Dir.chdir(PROJECT_ROOT)
    FileUtils.mkdir_p 'vmod'
    system("sh autogen.sh")
    system("./configure VARNISHSRC=tmp/#{VARNISH_FOLDER} VMODDIR=#{PROJECT_ROOT}/vmod")
    system('make install')
  end
end

task :default => ['varnish:vmod']
