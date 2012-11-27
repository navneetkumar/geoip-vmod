VARNISH_FOLDER = "varnish-3.0.3"
VARNISH_FILE_NAME = "#{VARNISH_FOLDER}.tar.gz"
VARNISH_URL = "http://repo.varnish-cache.org/source/varnish-3.0.3.tar.gz"
SOURCE_URL = "https://github.com/navneetkumar/geoip-vmod.git"
PROJECT_ROOT = File.expand_path(File.dirname(__FILE__))
RPM_ROOT = "#{PROJECT_ROOT}/rpmbuild"

require 'fileutils'

namespace :varnish do
  desc "compile varnish"
  task :setup do
    Dir.chdir(PROJECT_ROOT)
    FileUtils.mkdir_p 'tmp'
    FileUtils.mkdir_p 'vmod'
  end

  task :clean do
    %x[rm -rf tmp]
    %x[rm -rf vmod]
  end

  task :get => :setup do
    Dir.chdir("#{PROJECT_ROOT}/tmp/")
    %x[wget #{VARNISH_URL}] unless File.exists?(VARNISH_FILE_NAME)
    %x[tar -xzf #{VARNISH_FILE_NAME}]
  end

  task :compile => :get do
    puts "Compiling varnish from #{VARNISH_URL}"

    Dir.chdir("#{PROJECT_ROOT}/tmp/#{VARNISH_FOLDER}")
    system("./configure")
    system("make")
  end

  namespace :vmod do
    task :rpm => ['varnish:get', :rpm_build_area] do
      puts "building geoip-vmod rpm for varnish version #{VARNISH_FOLDER}"
      Dir.chdir(PROJECT_ROOT)
      %x[rpmbuild --define 'source #{SOURCE_URL}' --define 'VARNISH_URL #{VARNISH_URL}' --define '_topdir #{RPM_ROOT}'  --bb geoip-vmod.spec]
    end

    task :compile => :'varnish:compile' do
      puts "building geoip-vmod for varnish version #{VARNISH_FOLDER}"
      Dir.chdir(PROJECT_ROOT)
      FileUtils.mkdir_p 'vmod'
      system("sh autogen.sh")
      system("./configure VARNISHSRC=tmp/#{VARNISH_FOLDER} VMODDIR=#{PROJECT_ROOT}/vmod")
      system('make install')
    end

    task :rpm_build_area do
      Dir.chdir(PROJECT_ROOT)
      dirs = %w{
        BUILD
        RPMS/noarch
        RPMS/x86_64
        SOURCES
        SPECS
        SRPMS
      }
      dirs.each do |dir|
        full_path = "#{RPM_ROOT}/#{dir}"
        FileUtils.rm_rf full_path
        FileUtils.mkdir_p full_path
      end
    end
  end
end

task :default => ['varnish:vmod:rpm']