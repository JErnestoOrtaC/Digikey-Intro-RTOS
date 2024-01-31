//CHALLENGE PASS A MESSAGE TUTOpart4

// This is for selecting the unicore of our esp32
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

char *msg = NULL;

// Handlers
// TaskHandle_t task1Handler = NULL;
static bool flag = false;

// Tasks
void Task1(void *parameter) {
  int sz = 0;
  char buffer[50];
  while (1) {
    if (flag == false) {
      // Free memory if already allocated
      // Read serial data
      while (Serial.available() > 0) {
        char c = Serial.read();
        if (c != '\n') {
          buffer[sz] = c;
          sz++;
        } else {
          if(msg == NULL){
            msg = (char *)pvPortMalloc(sz * sizeof(char));
          }
          else{
            vPortFree(msg);
            msg = NULL;
            msg = (char *)pvPortMalloc(sz * sizeof(char));
          }
          for (int i = 0; i < sz; i++) {
            msg[i] = buffer[i];
          }
          msg[sz] = '\0';
          sz = 0;
          flag = true;
        }
      }
    } else {
      // Do something if needed
    }
  }
}

void Task2(void *parameter) {
  while (1) {
    if (flag == true) {
      for (int i = 0; msg[i] != '\0'; i++) {
        Serial.print(msg[i]);
      }
      Serial.println();
      flag = false;
      // Free the allocated memory
    }
    //vTaskDelay(100 / portTICK_PERIOD_MS); // Adjust the delay if needed
  }
}

void setup() {
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("************FreeRTos demo*************");

  Serial.print("Task on core: ");
  Serial.println(xPortGetCoreID());
  Serial.print("priority level: ");
  Serial.println(uxTaskPriorityGet(NULL));

  // Task definition
  xTaskCreatePinnedToCore(
      Task1,      // Task name
      "Task 1",   // Task name for humans
      1024,       // Memory size
      NULL,       // Pointer to parameter or variable
      1,          // Priority level
      NULL,       // Handler as reference
      app_cpu     // CPU
  );

  xTaskCreatePinnedToCore(
      Task2,      // Task name
      "Task 2",   // Task name for humans
      1024,       // Memory size
      NULL,       // Pointer to parameter or variable
      1,          // Priority level
      NULL,       // Handler as reference
      app_cpu     // CPU
  );
}

void loop() {
  // Nothing in the loop
}
