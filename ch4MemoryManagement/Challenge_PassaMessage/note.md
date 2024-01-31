//CHALLENGE PASS A MESSAGE TUTOpart4


//This is for selecting the unicore of our esp32
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu =0;
#else
  static const BaseType_t app_cpu =1;
#endif

char *msg =NULL;

//handlers
//TaskHandle_t task1Handler = NULL;
bool flag = false;
//tasks

void Task1(void *parameter){  
  //can initialize Task1 variables here as a locale setup for the Task
  int sz=0;
  char buffer[50];
  while(1){
    if(flag == false){
      //leer datos de seria
      while(Serial.available()>0){
        char c = Serial.read();
        if(c != '\n'){
          buffer[sz] = c;
          sz++;
        }
        else{
          msg = (char*)pvPortMalloc(sz * sizeof(char));
          for(int i = 0; i<sz; i++){
          msg[i] = buffer[i];
          }
          msg[sz] = '\0';
          sz=0;
          flag = true;
        }
      }
    }
    else{
      vTaskDelay(500/ portTICK_PERIOD_MS);
    }
  }
}

void Task2(void *parameter){
  while(1){
    if(flag == true){
      Serial.println("Deberia escribir");
      flag = false;
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
              Task1,      //taskname
              "Task 1",   //task name for humans
              1024,       //memory size
              NULL,       //pointer to parameter or variable
              1,          //priority level 
              NULL,       //handler as reference
              app_cpu     //cpu
  );
  xTaskCreatePinnedToCore(
              Task2,      //taskname
              "Task 2",   //task name for humans
              1024,       //memory size
              NULL,       //pointer to parameter or variable
              1,          //priority level 
              NULL,       //handler as reference
              app_cpu     //cpu
  );
}

void loop(){
  
}
