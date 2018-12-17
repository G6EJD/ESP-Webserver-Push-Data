# ESP-Webserver-Push-Data

An ESP Webserver that pushes data to a client using AJAX

There are three files:

ESP_RANDOM_DATA_PUSH creates random data in place of a sensor and so can be used for demonstration/trial purposes. It pushes sensor data to a client.

ESP_RANDOM_DATA_NO_PUSH creates random data in place of a sensor and so can be used for demonstration/trial purposes. No sensor data is sent to the client, the page has be refreshed as normal to get new readings.

ESP_BME280_DATA_PUSh is configured for an BME280 sensor on the I2C bus and then pushes the sensor values to client's webpage, no page refresh is required.
