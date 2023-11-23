cd ~/zephyrproject/zephyr/
git for-each-ref --sort=taggerdate --format='%(refname)' refs/tags \ | grep "zephyr-v"
git log --abbrev-commit