# Mikrodenetleyici Driver Gelistirme

Mikrodenetleyici Driver Geliştirme kursunu, 23.07.2024 tarihinde [linkte](https://www.udemy.com/course/mikrodenetleyici-driver-gelistirme-gpio-spi-usart-i2c/) sunulan video serisi izlenerek tamamlanmıştır. <br>
Oluşturulan [kütüphaneye](/Software/Firmware/STM32F407VGTX/Drivers/), [örnek kodlara](/Docs/code-example.md) ve alınan [notlara](/Docs/reference-manual.pdf) link üzerinden ulaşabilirsiniz.

- İşlemci olarak STM32F407VGT6 kullanılmıştır.
- AHB1, APB1 ve APB2 Clock hatlarının aktivasyonu ve çevresel birimlerle entegrasyonu yapılmıştır.
- GPIO, SPI, USART ve I2C çevresel birimleri ele alınmıştır.
- Çevresel birimlerin Init, Veri Gönderme, Veri Alma, Kesme ile Gönderme, Kesme ile Alma gibi API'ler geliştirilmiştir.

```
Software/Firmware/STM32F407VGTX
│
├── Application/ 
│   ├── User/
│   │   ├── Inc/    
│   │   │   └── stm32f4xx_conf.h
│   │   └── Src/
│   │       ├── main.c
│   │       ├── syscalls.c
│   │       └── sysmem.c
│   │   
│   └── Startup/
│       └── startup_stm32f407vgtx.s
│
├── Drivers/ 
│   ├── BSP/
│   │   └── STM32F407G-DISC1
│   │       ├── stm32f407g_disc1.h
│   │       └── stm32f407g_disc1.h
│   │
│   ├── CMSIS
│   │   └── Device/ST/STM32F4xx/
│   │       └── Include/
│   │           ├── stm32f4xx.h
│   │           └── stm32f407xx.h
│   │   
│   └── STM32F4xx_Driver/            
│       ├── Inc/
│       │   ├── stm32f4xx_rcc.h
│       │   ├── stm32f4xx_gpio.h
│       │   ├── stm32f4xx_exti.h
│       │   ├── stm32f4xx_usart.h
│       │   ├── stm32f4xx_i2c.h
│       │   ├── stm32f4xx_spi.h
│       │   └── stm32f407xx.h 
│       └── Src/
│           ├── stm32f4xx_rcc.c
│           ├── stm32f4xx_gpio.c
│           ├── stm32f4xx_exti.c
│           ├── stm32f4xx_usart.c
│           ├── stm32f4xx_i2c.c
│           └── stm32f4xx_spi.c 
└──
```