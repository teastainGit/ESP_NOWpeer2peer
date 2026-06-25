This demonstrates esp_now communication between two esp32, incl S3
This is peer to peer mode where both esp can send and receive in duplex mode
This is one sketch to be copied into two esp32...and the MAC address of one 
is copied over to the others 'broadcastAddress[] '
For testing: type a number from 0 to 9 in the serial monitor input field
You should see the ASCII number equiv showing up in the other boards serial monitor
i.e. type '0' into the serial window the other board will display ASCII 48 decimal 
in its serial stream...and vice versa
contact teastain@me.com for assistance
