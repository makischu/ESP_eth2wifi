# ESP_eth2wifi
Replacement for missing eth2wifi example in espressif/esp-iot-solution

Former releases of espressif/esp-iot-solution, up to v1.1, included a eth2wifi example. 

The current (2021/09) master branch lacks this example. It seems to be "temporarily out of maintenance" and removed in 2020/12. This is an honest move, because in fact the example does not work any more. At least not with a current ESP-IDF Version (4.3 at the time of writing). When diving deeper you can find out that there are major differences in the network architecture between ESP-IDF versions. These changes will be the cause for the old code not working - though compiling (with warnings).

t.b.c.


