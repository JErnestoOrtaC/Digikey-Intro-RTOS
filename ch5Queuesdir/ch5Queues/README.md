# FreeRTOS ESP32 Demo

This is a simple FreeRTOS (Real-Time Operating System) demo for the ESP32 platform. The code demonstrates how to create a task, a queue, and interact with them on the ESP32 platform.

## Table of Contents

- [Overview](#overview)
- [Configuration](#configuration)
- [Tasks](#tasks)
- [Queue](#queue)
- [Setup](#setup)
- [Loop](#loop)

## Overview

The main purpose of this demo is to showcase the implementation of a task (`Task1`) and a queue (`msg_queue`) on the ESP32 using FreeRTOS. The code checks if a queue is not full and sends an incrementing integer to the task, which prints the received value.

## Configuration

The core of the ESP32 is selected based on the `CONFIG_FREERTOS_UNICORE` configuration. If it's set to true, the task will run on core 0; otherwise, it will run on core 1.

```c
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif


The main task in this demo is Task1, which continuously loops, checks the queue for incoming messages, and prints them to the Serial monitor.

void Task1(void *parameter) {
  int item = 0;
  while (1) {
    if (xQueueReceive(msg_queue, (void *)&item, 0) == pdTRUE) {
      Serial.println(item);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

Queue

A queue (msg_queue) is created to facilitate communication between the loop function and Task1.

c

static const u_int8_t msg_queue_len = 5;
static QueueHandle_t msg_queue;

Setup

The setup function initializes the Serial communication, prints information about the task's core and priority, and creates the queue and the task.

c

void setup() {
  // ... Serial setup ...

  // Create queue
  msg_queue = xQueueCreate(msg_queue_len, sizeof(int));

  // Task definition
  xTaskCreatePinnedToCore(
    Task1,      // task name
    "Task 1",   // task name for humans
    1024,       // memory size
    NULL,       // pointer to parameter or variable
    1,          // priority level 
    NULL,       // handler as reference
    app_cpu     // cpu
  );
}

Loop

The loop function sends an incrementing integer to the queue and prints a message if the queue is full.

c

void loop() {
  static int num = 0;

  if (xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE) {
    Serial.print("Queue full");
  }
  num++;
  vTaskDelay(500 / portTICK_PERIOD_MS);
}