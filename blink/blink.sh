echo 78 > /sys/class/gpio/export
sleep 0.5
sudo echo "out" > /sys/class/gpio/gpio78/direction
sudo echo 0 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 1 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 0 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 1 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 0 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 1 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 0 > /sys/class/gpio/gpio78/value
sleep 1
sudo echo 1 > /sys/class/gpio/gpio78/value
echo 78 > /sys/class/gpio/unexport
