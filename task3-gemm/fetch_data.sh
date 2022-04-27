#!/bin/sh

if [ ! -f data.tar.gz ]; then
    echo '> Fetching https://honeta.site/files/data.tar.gz ...'
    curl https://honeta.site/files/data.tar.gz --output data.tar.gz
fi

if [ ! -d data ]; then
    echo '> Unpacking data.tar.gz ...'
    tar -xzvf data.tar.gz
fi