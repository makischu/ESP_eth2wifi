# ESP_eth2wifi
Proposal of a temporary replacement for missing eth2wifi example in espressif/esp-iot-solution

Former releases of espressif/esp-iot-solution, up to v1.1, included a eth2wifi example. 

The current (2021/09) master branch lacks this example. It seems to be "temporarily out of maintenance" and removed in 2020/12. This is an honest move, because in fact the example does not work any more. At least not with a current ESP-IDF Version (4.3 at the time of writing). When diving deeper you can find out that there are major differences in the network architecture between ESP-IDF versions. These changes will be the cause for the old code not working - though compiling (with warnings) and running (without reported errors).

My goal was to get it running on an Olimex ESP32-GATEWAY, in a way that an ethernet-device can connect to an existing wifi network. Therefore the ESP wifi uses STAtion mode and all frames should be transparently forwarded in both directions, nothing more. After some time I got this configured and seemed running. Ethernet was up and wifi was connected, but communication was not possible. After some investigation I noticed that the direction eth2wifi worked, but the direction wifi2eth was dead. 

The reason: esp_wifi_internal_reg_rxcb does not work any more. 

The (temporary) solution: Include a similar functionality into the tcpip_adapter compatibility layer. 

This is what I propose here. It is just a proof of concept. It still relies on the (old) tcpip_adapter-functions, which are to be replaced by (new) netif-equivalents. Hopefully there will be a functional example in the original espressif/esp-iot-solution repository soon. As long as this is not the case, I think it is a valid option to go for this temporary solution.

Unfortunately this proposal requires manual changes in the ESP-IDF. The lines of esp_netif_lwip.c and tcpip_adapter_compat.c need to be added to the original files. Maybe someone other is able to build a more general solution which is good enough to be added to the ESP-IDF one day.

Please note that this repository does not contain the whole solution. But it contains everything that is necessary to make the eth2wifi example (from https://github.com/espressif/esp-iot-solution/tree/release/v1.1 ) work on IDF 4.3 for the purpose explained above. I suggest to first get the original example running (to proof that everything is configured correctly) and then apply the proposed changes to fix the issue of non-forwarded traffic.
