# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"


Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial64"

  config.vm.provider "virtualbox" do |vbox|
    vbox.memory = 2048
  end

  config.vm.synced_folder "./JZorba/", "/opt/jzorba/"
  
  config.vm.provision "shell", path: "vm.sh"

end
