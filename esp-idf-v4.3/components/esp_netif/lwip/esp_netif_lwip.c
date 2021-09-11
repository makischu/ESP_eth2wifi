//ESP_eth2wifi
//Copyright (C) 2021 makischu
/* This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

//for proof of concept the following lines need to be added to the orginal file from esp-idf, e.g. right below esp_netif_receive

esp_err_t esp_netif_receive_reg_rxcb(esp_netif_t *esp_netif, void (*fn)(void *input_netif_handle, void *buffer, size_t len, void *eb))
{
    if(!esp_netif || !fn) 
    {
        return ESP_ERR_ESP_NETIF_INVALID_PARAMS;
    }
    esp_netif->lwip_input_fn = fn;
    return ESP_OK;
}
