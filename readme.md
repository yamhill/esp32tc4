## ESP32 with OLED and MAX6675 to read thermocouples and function as TC4 for recording bean and environmental temperatures for Roastlogger and Artisan coffee roasting software ##

### Boards used ###
ESP32:<br/>
http://www.lilygo.cn/prod_view.aspx?TypeId=50032&Id=1152&FId=t3:50032:3<br/>
ordered via: https://www.aliexpress.com/item/32824839148.html<br/>

MAX6675:<br/>
ordered via: https://www.aliexpress.com/item/1902975176.html<br/>

Thermocouples: <br/>(I've tried a few -- in addition to the ones that come with the MAX6675)<br/>
ordered via: https://www.aliexpress.com/item/32848451468.html<br/>
ordered via: https://www.aliexpress.com/item/32795229358.html<br/>

Pin map for above the ESP32 board:<br/>
https://0.rc.xiniu.com/g1/M00/29/CB/CgAGTF1agBWASwmZAAF9zU1LNpY299.jpg<br/>
![picture alt](https://0.rc.xiniu.com/g1/M00/29/CB/CgAGTF1agBWASwmZAAF9zU1LNpY299.jpg "Pin map")

It's just a little code to use ttgo esp32 board with two max6675 and oled -- to work like a TC4 to artisan roasting software
