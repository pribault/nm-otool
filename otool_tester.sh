#!/bin/sh

./ft_otool $@ > ft_otool_log
otool $@ > otool_log
diff ft_otool_log otool_log > otool_diff
cat otool_diff
