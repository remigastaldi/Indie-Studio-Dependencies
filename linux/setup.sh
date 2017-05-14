#!/bin/bash

START=$PWD
CORE=$(grep -c ^processor /proc/cpuinfo)

if [ $CORE == 0 ]
then
    exit
fi

/bin/echo "************************************"
/bin/echo "*Start install script using $CORE cores*"
/bin/echo "************************************"

mkdir lib && mkdir include

#OIS
cd OIS/ && ./bootstrap && ./configure --prefix=$START && make && make install && cd -

#BOOST
tar -xvf boost_1_63_0.tar.bz2
cd boost_1_63_0 && ./bootstrap.sh --prefix=$START && ./b2 install && cd -

#CG TOOLKIT
tar -xvf cg_tool.tar.gz

#OGRE
cd ogre/ && mkdir build && cd build/ && cmake .. && make $CORE && make install

