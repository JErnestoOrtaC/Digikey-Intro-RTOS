
//This is for selecting the unicore of our esp32
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu =0;
#else
  static const BaseType_t app_cpu =1;
#endif


//handlers
//no handlers needed in this exmaple

//tasks
/*This Task creates a big array of 100 elements (100 *4 = 400)bytes + 768 required for Tasks on freertos
    so on the exercise is required to expand the stack memory of the task in the taskcreation to 400+768+extra bytes*/
void Task1(void *parameter){  
  while(1){
    int a = 1;
    int b[100];
    for(int i =0; i<100; i++){
      b[i] = a;
    }
    Serial.println(b[0]);
  

    Serial.print("Stack High Water Mark: ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL) );

    Serial.print("HEAP mem before malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
/* Hrere we create a dinmaic array on the heap of the task of 1024 elements to prevent a stackoverflow because every loop u create this array and makes memory leaks
    of can make a safety cheack to se if the prt of the Darray is NULL -> no memory and escape, but also is intendede to delete or FREE this memory after use it */
    int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));

    if(ptr == NULL){
      Serial.println("ERROR no enough heap memory");
    }
    else{

      for(int i =0;i<1024;i++){
        ptr[i] = 2;
      }

      Serial.print("EAP mem after malloc (bytes): ");
      Serial.println(xPortGetFreeHeapSize());

      vPortFree(ptr);

      vTaskDelay(200/ portTICK_PERIOD_MS);
    }
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
              Task1, //taskname
              "Task 1",   //task name for humans
              1500,       //memory size
              NULL,       
              1,           //priority level 
              NULL,      //handler as reference
              app_cpu       //cpu
  );

}

void loop(){
  
}
