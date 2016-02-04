#!/bin/bash
set -e
make_folder=/tmp/.LedControlMake
target_folder=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
mkdir -p $make_folder
pushd $make_folder
cmake $target_folder
make
echo "Make succeeded, contents of " $make_folder
ls -lh $make_folder
popd