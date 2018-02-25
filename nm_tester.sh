#!/bin/sh

if [[ $# = "1" ]]
then
	./ft_nm $@ > ft_nm_log
	nm $@ > nm_log
	diff ft_nm_log nm_log > nm_diff
	cat nm_diff
else
	echo "./nm_tester <file>"
fi