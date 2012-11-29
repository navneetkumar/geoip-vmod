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
  def setup
    Dir.chdir(PROJECT_ROOT)
    FileUtils.mkdir_p 'tmp'
    FileUtils.mkdir_p 'vmod'
  end

  def compile_varnish
    Dir.chdir("#{PROJECT_ROOT}/tmp/")
    %x[wget #{VARNISH_URL}] unless File.exists?(VARNISH_FILE_NAME)
    %x[tar -xzf #{VARNISH_FILE_NAME}]
    Dir.chdir("#{PROJECT_ROOT}/tmp/#{VARNISH_FOLDER}")
    system("./configure")
    system("make")
  end

  def compile_geoip_vmod
    Dir.chdir(PROJECT_ROOT)
    system("sh autogen.sh")
    system("./configure VARNISHSRC=tmp/#{VARNISH_FOLDER} VMODDIR=#{PROJECT_ROOT}/vmod")
    system('make install')
  end

  desc "Compiles and builds geoip-vmod for varnish version #{VARNISH_VERSION}"
  task :compile do
    setup
    puts "compiling varnish from source at #{VARNISH_URL}"
    compile_varnish
    puts "compiling geoip-vmod from source"
    compile_geoip_vmod
  end

  desc "cleans varnish artifacts"
  task :clean do
    %x[rm -rf tmp]
    %x[rm -rf vmod]
    %x[rm -rf rpmbuild]
  end

  namespace :vmod do

    desc 'create geoip-vmod rpm from source'
    task :rpm => [:rpm_build_area] do
      puts "building geoip-vmod rpm for varnish version #{VARNISH_FOLDER}"
      Dir.chdir(PROJECT_ROOT)
      %x[rpmbuild --define 'version #{VERSION}' --define 'release #{RELEASE}' --define 'source #{SOURCE_URL}' --define 'varnish_url #{VARNISH_URL}' --define '_topdir #{RPM_ROOT}'  --bb geoip-vmod.spec]
    end

    desc 'publish geoip-vmod rpm RPMS to yum repos'
    task :publish do
      (yum_repos = ENV['YUM_REPOS'].split(",")) rescue raise 'Please set YUM_REPOS'
      scp_opts = ENV['SCP_OPTS']
      raise 'Please set SCP_OPTS' unless scp_opts
      rpm = File.join RPM_ROOT, 'RPMS/x86_64', "geoip-vmod-#{VARNISH_VERSION}-#{VERSION}-#{RELEASE}.x86_64.rpm"
      yum_repos.each { |server| sh "scp #{scp_opts} #{rpm} #{server}" }
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
