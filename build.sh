#!/bin/bash


folder_name=${PWD##*/}

clear
rm -rf build

echo "Project Name: $folder_name"

# bash update.sh

echo "python3 make_ec_ver.py"
python3 make_ec_version.py

echo "python3 update_headers.py"
python3 update_headers.py

echo "west build -p always -b it82xx2_evb $folder_name"
west build -p always -b it82xx2_evb ../$folder_name

mv build/zephyr/zephyr.bin zephyr_app.bin
cp zephyr_app.bin zephyr_app_backup.bin

dd if=nist_placeholder_32KB.bin of=zephyr_app.bin bs=32K conv=notrunc
mv zephyr_app.bin zephyr_Full.bin
