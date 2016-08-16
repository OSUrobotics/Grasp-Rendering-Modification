#! /bin/bash

# Install the collada support debians
sudo dpkg -i collada-dom2.4-dp_2.4.3.0-ubuntu1~trusty1_amd64.deb collada-dom2.4-dp-base_2.4.3.0-ubuntu1~trusty1_amd64.deb collada-dom2.4-dp-dev_2.4.3.0-ubuntu1~trusty1_amd64.deb collada-dom-dev_2.4.3.0-ubuntu1~trusty1_amd64.debs

# Using software center to install dependencies as well as the openrave debian. Couldn'tfigure out how to use apt-get or dpkg to build dependencies and install.
software-center openrave_0.9-1_amd64.deb
