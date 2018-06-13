#!/bin/bash

# Update apt
sudo apt-get update && sudo apt-get -y upgrade

# Install base software
sudo apt-get install -y python-software-properties git zsh htop

# Add Zorba official repo
sudo add-apt-repository ppa:fcavalieri/zorba
sudo apt-get update

# Install Zorba
sudo apt-get install -y zorba zorba-*-module

# Install build-essential, C++ and make
sudo apt-get install -y build-essential g++ make

# Install Java 8
sudo apt-get install -y openjdk-8-jdk-headless openjdk-8-jre-headless default-jre-headless

# Install JZorba build dependencies
sudo apt-get install -y maven ant libmaven-antrun-extended-plugin-java cmake openjdk-8-source

# Install and configure zsh
rm -rf /home/vagrant/.oh-my-zsh
git clone git://github.com/robbyrussell/oh-my-zsh.git /home/vagrant/.oh-my-zsh
cp /home/vagrant/.oh-my-zsh/templates/zshrc.zsh-template /home/vagrant/.zshrc
chsh -s /bin/zsh vagrant
