VARNISH_VERSION = "3.0.3"
VARNISH_FOLDER = "varnish-#{VARNISH_VERSION}"
VARNISH_FILE_NAME = "#{VARNISH_FOLDER}.tar.gz"
VARNISH_URL = "http://repo.varnish-cache.org/source/varnish-#{VARNISH_VERSION}.tar.gz"
SOURCE_URL = "https://github.com/navneetkumar/geoip-vmod.git"
PROJECT_ROOT = File.expand_path(File.dirname(__FILE__))
RPM_ROOT = "#{PROJECT_ROOT}/rpmbuild"
VERSION = "0.1"
RELEASE = "1"
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
    %x[rm -rf rpmbuild]
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
      %x[rpmbuild --define 'version #{VERSION}' --define 'release #{RELEASE}' --define 'source #{SOURCE_URL}' --define 'varnish_url #{VARNISH_URL}' --define '_topdir #{RPM_ROOT}'  --bb geoip-vmod.spec]
    end

    desc 'publish geoip-vmod rpm RPMS to yum repo'
    task :publish do
      raise 'Please set YUM_REPOSITORY_HOST' unless ENV['YUM_REPOSITORY_HOST']
      raise 'Please set YUM_REPOSITORY_ROOT' unless ENV['YUM_REPOSITORY_ROOT']

      rpm = "geoip-vmod-#{VARNISH_VERSION}-#{VERSION}-#{RELEASE}.x86_64.rpm"
      sh "scp '#{File.join RPM_ROOT, 'RPMS/x86_64', rpm}' '#{ENV['YUM_REPOSITORY_HOST']}:#{ENV['YUM_REPOSITORY_ROOT']}'"
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