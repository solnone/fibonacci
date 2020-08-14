#!/usr/bin/sh
for i in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
do
    echo performance > ${i}
done
