deps_config := \
	/home/trizzone52/esp/esp-idf/components/app_trace/Kconfig \
	/home/trizzone52/esp/esp-idf/components/aws_iot/Kconfig \
	/home/trizzone52/esp/esp-idf/components/bt/Kconfig \
	/home/trizzone52/esp/esp-idf/components/driver/Kconfig \
	/home/trizzone52/esp/esp-idf/components/esp32/Kconfig \
	/home/trizzone52/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/trizzone52/esp/esp-idf/components/esp_event/Kconfig \
	/home/trizzone52/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/trizzone52/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/trizzone52/esp/esp-idf/components/ethernet/Kconfig \
	/home/trizzone52/esp/esp-idf/components/fatfs/Kconfig \
	/home/trizzone52/esp/esp-idf/components/freemodbus/Kconfig \
	/home/trizzone52/esp/esp-idf/components/freertos/Kconfig \
	/home/trizzone52/esp/esp-idf/components/heap/Kconfig \
	/home/trizzone52/esp/esp-idf/components/libsodium/Kconfig \
	/home/trizzone52/esp/esp-idf/components/log/Kconfig \
	/home/trizzone52/esp/esp-idf/components/lwip/Kconfig \
	/home/trizzone52/esp/esp-idf/components/mbedtls/Kconfig \
	/home/trizzone52/esp/esp-idf/components/mdns/Kconfig \
	/home/trizzone52/esp/esp-idf/components/mqtt/Kconfig \
	/home/trizzone52/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/trizzone52/esp/esp-idf/components/openssl/Kconfig \
	/home/trizzone52/esp/esp-idf/components/pthread/Kconfig \
	/home/trizzone52/esp/esp-idf/components/spi_flash/Kconfig \
	/home/trizzone52/esp/esp-idf/components/spiffs/Kconfig \
	/home/trizzone52/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/trizzone52/esp/esp-idf/components/vfs/Kconfig \
	/home/trizzone52/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/trizzone52/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/trizzone52/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/trizzone52/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/trizzone52/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
