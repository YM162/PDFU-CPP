timearray=()
for i in {1..20}
do
    exec 3>&1 4>&2
    time=$(LC_NUMERIC=C;TIMEFORMAT="%R"; { time pdfu multiplepdf/alexromeral_Bloque_2.pdf 1>&3 2>&4; } 2>&1)
    exec 3>&- 4>&-
    timearray+=($time)
    sleep 1
done


sum=0
for value in "${timearray[@]}"
do
     sum=$(echo $sum + $value | bc -l)
done

media=$(echo $sum / 20 | bc -l)
echo "Tiempo medio: $media"