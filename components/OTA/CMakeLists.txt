idf_component_register(SRCS "my_ota.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_http_client esp_https_ota esp_partition app_update)