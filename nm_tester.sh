#!/bin/sh

./ft_nm $@ > ft_nm_log
nm $@ > nm_log
diff ft_nm_log nm_log > nm_diff
cat nm_diff
