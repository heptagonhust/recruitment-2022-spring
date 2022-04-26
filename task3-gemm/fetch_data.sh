#!/bin/sh
if [ ! -f data.tar.gz ]; then
    curl https://honeta.site/files/data.tar.gz --output data.tar.gz
fi

if [ ! -d data ]; then
    tar -xzvf data.tar.gz
fi