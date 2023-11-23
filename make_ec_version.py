import re
import datetime

# def generate_version_string_from_file(filename):
#     with open(filename, 'r', encoding='utf-8') as file:
#         file_content = file.read()

#     build_fv = re.search(r'#define _BUILD_FV "(.*?)"', file_content).group(1)
#     build_lsfv = re.search(r'#define _BUILD_LSFV "(.*?)"', file_content).group(1)
#     build_mufg = re.search(r'#define _BUILD_MUFG "(.*?)"', file_content).group(1)
#     build_model = re.search(r'#define _BUILD_MODEL "(.*?)"', file_content).group(1)
#     build_guest = re.search(r'#define _BUILD_GUEST "(.*?)"', file_content).group(1)
#     build_board = re.search(r'#define _BUILD_BOARD "(.*?)"', file_content).group(1)
#     build_main_fw_addr = re.search(r'#define _BUILD_MAIN_FW_ADDR "(.*?)"', file_content).group(1)

#     current_time = datetime.datetime.now()
#     version_string = f"{build_fv} {build_lsfv} {build_mufg} {build_model} {build_guest} {build_board} "
#     version_string += f"BUILD DATE: {current_time.strftime('%Y/%m/%d')}$ TIME: {current_time.strftime('%H:%M:%S')}$ "
#     version_string += f"MAIN_FW_ADDR:{build_main_fw_addr}"

#     return version_string
def generate_version_string_from_file(file_path, current_time):
    with open(file_path, 'r', encoding='utf-8') as file:
        file_content = file.read()

    # Use '\s*' to match zero or more whitespace characters (including spaces and tabs)
    build_fv = re.search(r'#define _BUILD_FV\s+"(.*?)"', file_content).group(1)
    build_lsfv = re.search(r'#define _BUILD_LSFV\s+"(.*?)"', file_content).group(1)
    build_mufg = re.search(r'#define _BUILD_MUFG\s+"(.*?)"', file_content).group(1)
    build_model = re.search(r'#define _BUILD_MODEL\s+"(.*?)"', file_content).group(1)
    build_guest = re.search(r'#define _BUILD_GUEST\s+"(.*?)"', file_content).group(1)
    build_board = re.search(r'#define _BUILD_BOARD\s+"(.*?)"', file_content).group(1)
    build_main_fw_addr = re.search(r'#define _BUILD_MAIN_FW_ADDR\s+"(.*?)"', file_content).group(1)

    # Generate the final string
    date_str = current_time.strftime("%Y/%m/%d")
    time_str = current_time.strftime("%H:%M:%S")
    
    final_str = f'{build_fv} {build_lsfv} {build_mufg} {build_model} {build_guest} {build_board} BUILD DATE: {date_str}$ TIME: {time_str}$ MAIN_FW_ADDR:{build_main_fw_addr}'
    return final_str

def replace_version_in_file(filename, content):
    with open(filename, 'r', encoding='utf-8') as file:
        file_content = file.read()

    # 使用正則表達式找到原始的版本字串並替換
    updated_content = re.sub(r'#define EC_VER ".*?"', '#define EC_VER "' + content + '"', file_content)

    # 將更新後的內容寫回文件
    with open(filename, 'w', encoding='utf-8') as file:
        file.write(updated_content)

def update_build_date_and_time(version_file_path, current_time):
    date_str = current_time.strftime("%Y/%m/%d")
    time_str = current_time.strftime("%H:%M:%S")

    # Read the content of the specified file
    with open(version_file_path, "r") as file:
        version_content = file.read()

    # Update _BUILD_DATE and _BUILD_TIME in the content
    version_content = re.sub(r'#define _BUILD_DATE\s+".*?"', f'#define _BUILD_DATE         "{date_str}$"', version_content)
    version_content = re.sub(r'#define _BUILD_TIME\s+".*?"', f'#define _BUILD_TIME         "{time_str}$"', version_content)

    # Write the updated content back to the file
    with open(version_file_path, "w") as file:
        file.write(version_content)


# 使用
version_file_path = "./src/app/version.h"
current_time = datetime.datetime.now()

update_build_date_and_time(version_file_path, current_time)

content = generate_version_string_from_file(version_file_path, current_time)
replace_version_in_file(version_file_path , content)
