#include "dfplayer.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/task.h"

#define DF_TX_PIN 43
#define DF_RX_PIN 44
#define DFPLAYER_UART_NUM UART_NUM_1
#define TAG "DFPlayer"

static void df_send_command(uint8_t cmd, uint8_t param1, uint8_t param2) {
    uint8_t packet[10] = {
        0x7E, 0xFF, 0x06, cmd, 0x01,
        param1, param2,
        0x00, 0x00, 0xEF
    };
    uart_write_bytes(DFPLAYER_UART_NUM, (const char *)packet, 10);
    vTaskDelay(pdMS_TO_TICKS(100)); // Prevent overwhelming DFPlayer
}

void dfplayer_init(void) {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_driver_install(DFPLAYER_UART_NUM, 256, 0, 0, NULL, 0);
    uart_param_config(DFPLAYER_UART_NUM, &uart_config);
    uart_set_pin(DFPLAYER_UART_NUM, DF_TX_PIN, DF_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    vTaskDelay(pdMS_TO_TICKS(500)); // Allow DFPlayer time to boot

    df_send_command(0x06, 0x00, 20); // Set volume to 20
    ESP_LOGI(TAG, "DFPlayer initialized with volume 20");
}

void dfplayer_play_beep(void) {
    df_send_command(0x03, 0x00, 0x01); // Play track 1
}

void dfplayer_start_music(void) {
    df_send_command(0x03, 0x00, 0x02); // Play track 2
}

void dfplayer_stop_music(void) {
    df_send_command(0x16, 0x00, 0x00); // Stop playback
}

void dfplayer_resume_music(void) {
    df_send_command(0x0D, 0x00, 0x00); // Resume playback
}
