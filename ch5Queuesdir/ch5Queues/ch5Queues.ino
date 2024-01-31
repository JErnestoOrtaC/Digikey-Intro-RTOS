//
//This is for selecting the unicore of our esp32
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu =0;
#else
  static const BaseType_t app_cpu =1;
#endif

//handlers
//TaskHandle_t task1Handler = NULL;

//Queue
static const u_int8_t msg_queue_len = 5;
static QueueHandle_t msg_queue;

//tasks

void Task1(void *parameter){  
  //can initialize Task1 variables here as a locale setup for the Task
  int item=0;
  while(1){
    //Task1 loop
    if( xQueueReceive(msg_queue, (void *)&item, 0) == pdTRUE){
      Serial.println(item);
    }
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}



void setup(){
  Serial.begin(115200);
  vTaskDelay(1000/ portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("************FreeRTos demo*************");

  Serial.print("Task on core: ");
  Serial.println(xPortGetCoreID());
  Serial.print("priority level: ");
  Serial.println(uxTaskPriorityGet(NULL));

//create queue
  msg_queue = xQueueCreate(msg_queue_len, sizeof(int));

  //task definement
  xTaskCreatePinnedToCore(
              Task1,      //taskname
              "Task 1",   //task name for humans
              1024,       //memory size
              NULL,       //pointer to parameter or variable
              1,          //priority level 
              NULL,       //handler as reference
              app_cpu     //cpu
  );

}

void loop(){
  static int num =0;

  if(xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE){
    Serial.print("Queue full");
  }
  num++;
  vTaskDelay(500/ portTICK_PERIOD_MS);
}
