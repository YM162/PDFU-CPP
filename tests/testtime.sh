timearray=()
for i in {1..100}
do
    exec 3>&1 4>&2
    time=$(LC_NUMERIC=C;TIMEFORMAT="%R"; { time ../build/PDFU-CPP multiplepdf/BMPITemario.pdf 1>&3 2>&4; } 2>&1)
    exec 3>&- 4>&-
    timearray+=($time)
    #sleep 1
done


sum=0
for value in "${timearray[@]}"
do
     sum=$(echo $sum + $value | bc -l)
done

media=$(echo $sum / 100 | bc -l)
echo "Tiempo medio: $media"