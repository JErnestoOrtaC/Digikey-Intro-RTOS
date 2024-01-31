//CHALLENGE PASS A MESSAGE TUTOpart4


//This is for selecting the unicore of our esp32
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu =0;
#else
  static const BaseType_t app_cpu =1;
#endif

static const int buffersize = 60*sizeof(char);

//handlers
//TaskHandle_t task1Handler = NULL;

//tasks

void Task1(void *parameter){  
  //can initialize Task1 variables here as a locale setup for the Task
  while(1){
    //Task1 loop
    
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
  
}
