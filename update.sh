#!/bin/bash

# Function for copying files and handling errors
copy_file() {
    cp -f "$1" "$2"
    if [ $? -ne 0 ]; then
        echo "Failed to copy or overwrite the file."
        exit 1
    fi
}

# Initialize variables for the directories
CMAKE_CURRENT_LIST_DIR="."
TARGET_DIR_ZEPHYR="$CMAKE_CURRENT_LIST_DIR/../../zephyr"

# Copy files for i2c drivers
TARGET_DIR="$TARGET_DIR_ZEPHYR/drivers/i2c/target"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/driver/i2c/target/Kconfig" "$TARGET_DIR"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/driver/i2c/target/Kconfig.it8xxx2" "$TARGET_DIR"

# And so on for other directories and files...
TARGET_DIR="$TARGET_DIR_ZEPHYR/drivers/i2c"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/driver/i2c/i2c_ite_enhance.c" "$TARGET_DIR"

TARGET_DIR="$TARGET_DIR_ZEPHYR/dts/bindings/i2c"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/dts/bindings/i2c/ite, target-i2c.yaml" "$TARGET_DIR"

TARGET_DIR="$TARGET_DIR_ZEPHYR/dts/bindings/pwm"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/dts/bindings/pwm/ite, it82202-pwm.yaml" "$TARGET_DIR"

TARGET_DIR="$TARGET_DIR_ZEPHYR/soc/riscv/riscv-ite/common"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/soc/riscv/riscv-ite/common/vector.S" "$TARGET_DIR"

TARGET_DIR="$TARGET_DIR_ZEPHYR/soc/riscv/riscv-ite/it8xxx2"
copy_file "$CMAKE_CURRENT_LIST_DIR/src/update/soc/riscv/riscv-ite/it8xxx2/Kconfig.soc" "$TARGET_DIR"

# ... 依此類推，對於其他文件和目錄也做相同的操作

# Exit successfully
echo "Files copied successfully."
exit 0
