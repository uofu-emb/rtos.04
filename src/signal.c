#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    printf("+ Waiting for request\n");
    xSemaphoreTake(request, portMAX_DELAY);
    printf("+ Handling calculation\n");
    data->output = data->input + 5;
    vTaskDelay(10);
    printf("+ Done with calculation\n");
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data)
{
    printf("- Handoff to worker\n");
    xSemaphoreGive(request);
    printf("- Waiting for results\n");
    BaseType_t res = xSemaphoreTake(response, 100);
    printf("- Result ready\n");
    return res;
}
