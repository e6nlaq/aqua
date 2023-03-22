
#!/bin/bash
# This file is part of aqua.
# Licensed under the MIT License.

now=$(pwd)
mkdir temp
cd temp
tag="1.5.0"
wget https://github.com/e6nlaq/aqua/archive/refs/tags/v$tag.tar.gz
tar -zxvf v$tag.tar.gz
cd ./aqua-$tag/bin/x64/
cp ./aqua ~/.local/bin
cd ~/.local/bin
chmod +x ./aqua

cd $now
rm -rf ./temp/