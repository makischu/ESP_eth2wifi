//ESP_eth2wifi
//Copyright (C) 2021 makischu
/* This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

//for proof of concept the following lines need to be added to the orginal file from esp-idf, e.g. right below tcpip_adapter_sta_input

//while the compatibility layer cares about the implementation of tcpip_adapter_sta_input, see its implementation,
//it does not care about the fact that this function seems not be used any more by the framework,
//which makes the registration of an alternative callback function via esp_wifi_internal_reg_rxcb useless. 
esp_err_t esp_netif_receive_reg_rxcb(esp_netif_t *esp_netif, void (*lwip_input_fn_n)(void *input_netif_handle, void *buffer, size_t len, void *eb)); // defined in esp_netif_lwip.c
static wifi_rxcb_t compat_rxcb_sta=0; //as new callback has more parameters we keep a reference on the original callback and use the following wrapper function to call it.
void lwip_input_fn_compat_sta(void *input_netif_handle, void *buffer, size_t len, void *eb)
{
    if(compat_rxcb_sta) 
    {
        compat_rxcb_sta(buffer,len,eb);
    }
}
esp_err_t esp_wifi_internal_reg_rxcb_compat(wifi_interface_t ifx, wifi_rxcb_t fn)
{
    if (ifx != WIFI_IF_STA) //ESP_IF_WIFI_STA
    {
        return ESP_ERR_NOT_SUPPORTED; // not a general problem but not implemented in this proof of concept
    }
    esp_netif_t *esp_netif = netif_from_if(TCPIP_ADAPTER_IF_STA);
    compat_rxcb_sta = fn;
    esp_netif_receive_reg_rxcb(esp_netif, lwip_input_fn_compat_sta);
    return ESP_OK;
}