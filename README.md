## N32G452_template说明
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [N32G452_template说明](#n32g452_template说明)
  - [简介](#简介)
  - [历史版本](#历史版本)

<!-- /code_chunk_output -->
### 简介
这是一个N32G452的工程模板，内容包含了N32G452的keil-mdk基本配置，同时加入了freertos的炒作系统
### 历史版本
```bash
+---Application//用于存放应用层代码
|   +---Inc
|   \---Src
+---BSP//板级支持包，包括驱动，外设
|   +---Device//外设
|   |   +---Inc
|   |   \---Src
|   \---Driver//驱动
|       +---Inc
|       \---Src
+---firmware//官方提供的固件库部分代码，这个部分是从官方的SDK移植过来的
|   +---CMSIS
|   |   +---core
|   |   \---device
|   |       \---startup
|   +---n32g45x_algo_lib
|   |   +---inc
|   |   \---lib
|   +---n32g45x_std_periph_driver
|   |   +---inc
|   |   \---src
|   \---n32g45x_usbfs_driver
|       +---inc
|       \---src
+---FreeRTOS//freertos操作系统
|   +---include
|   \---portable
|       +---Keil
|       +---MemMang
|       \---RVDS
|           \---ARM_CM4F
+---Middleware//中间层，这部分我的理解是一些算法和对驱动进一步封装的一些模块
|   +---Inc
|   \---Src
\---Project//存放keil project
