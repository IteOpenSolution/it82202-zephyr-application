import os
import re

def update_headers(directory):
    for foldername, subfolders, filenames in os.walk(directory):
        for filename in filenames:
            if filename.endswith(('.c', '.h')):
                filepath = os.path.join(foldername, filename)
                with open(filepath, 'r') as file:
                    content = file.read()

                # 檢查文件的前幾行是否包含指定的內容
                header_lines = [
                    "/*\n",
                    " * Copyright (c) 2023 ITE Corporation. All Rights Reserved.\n",
                    " *\n",
                    " * SPDX-License-Identifier: Apache-2.0\n",
                    " */\n"
                ]

                if not all(line in content for line in header_lines):
                    # 如果缺少指定的內容，則在文件的最前面加入
                    with open(filepath, 'w') as file:
                        file.write(''.join(header_lines) + content)
                    
# 指定目標資料夾的路徑
target_directory = './src'

# 呼叫函式更新文件頭
update_headers(target_directory)
