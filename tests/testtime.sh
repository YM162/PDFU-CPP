exec 3>&1 4>&2
time=$(TIMEFORMAT="%R"; { time ../build/PDFU-CPP 1>&3 2>&4; } 2>&1)
exec 3>&- 4>&-

echo "The time is $time"
