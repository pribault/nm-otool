#!/bin/sh

./ft_otool $@ > ft_otool_log
otool -t $@ > otool_log
diff ft_otool_log otool_log > otool_diff
cat otool_diff
