# Mikrodenetleyici Driver Gelistirme

Mikrodenetleyici Driver Geliştirme kursunu, 23.07.2024 tarihinde [linkte](https://www.udemy.com/course/mikrodenetleyici-driver-gelistirme-gpio-spi-usart-i2c/) sunulan video serisi izlenerek tamamlanmıştır. <br>
Oluşturulan [kütüphaneye](/Software/Firmware/Drivers), [örnek kodlara](/Docs/code-example.md) ve alınan [notlara](/Docs/reference-manual.pdf) link üzerinden ulaşabilirsiniz.

- İşlemci olarak STM32F407VGT6 kullanılmıştır.
- AHB1, APB1 ve APB2 Clock hatlarının aktivasyonu ve çevresel birimlerle entegrasyonu yapılmıştır.
- GPIO, SPI, USART ve I2C çevresel birimleri ele alınmıştır.
- Çevresel birimlerin Init, Veri Gönderme, Veri Alma, Kesme ile Gönderme, Kesme ile Alma gibi API'ler geliştirilmiştir.

```
Software/Firmware/
│
├── Core/              
│   ├── Src/
│   │   ├── main.c
│   │   ├── syscalls.c
│   │   ├── sysmem.c
│   └── Startup/
│       ├── startup_stm32f407vgtx.s
│
├── Drivers/              
│   ├── Inc
│   │   ├── rcc.h
│   │   ├── gpio.h
│   │   ├── exti.h
│   │   ├── usart.h
│   │   ├── i2c.h
│   │   ├── spi.h
│   │   ├── stm32f407xx.h 
│   └── Src
│       ├── rcc.c
│       ├── gpio.c
│       ├── exti.c
│       ├── usart.c
│       ├── i2c.c
│       ├── spi.c 
```