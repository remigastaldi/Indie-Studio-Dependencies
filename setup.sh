#!/bin/bash

START=$PWD

mkdir lib && mkdir include

#OIS
cd OIS/ && ./bootstrap && ./configure --prefix=$START && make && make install && cd -

#OGRE
cd ogre/ && mkdir build && cd build/ && cmake .. && make
cp lib/* $PWD/lib/

