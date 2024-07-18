#include "board_bridge.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "common/circular_byte_array.hpp"

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

void Error_Handler(void);

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);

uint8_t aRxBuffer[10];
uint8_t aTxBuffer[10];

#ifdef __cplusplus
}
#endif

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  __HAL_RCC_GPIOC_CLK_ENABLE();

  // LED GPIO INIT
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}

BoardBridge::BoardBridge() {}

BoardBridge::~BoardBridge() {}

uint8_t BoardBridge::initialize() {
  HAL_Init();
  
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  HAL_UART_Receive_DMA(&huart1, (uint8_t *)&aRxBuffer, 10);

  return 0;
}

uint8_t BoardBridge::configure_sensors() {
  configure_imu();

  return 0;
}

uint8_t BoardBridge::task_led_on() {
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
  return 0;
}

uint8_t BoardBridge::task_led_off() {
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  return 0;
}

#define MPU6050_ADDRESS (0x68 << 1)
#define MPU6050_ACC_X_HIGH_REG		0x3B
#define MPU6050_GYRO_X_HIGH_REG		0x43
#define MPU6050_TEMPRATURE_HIGH_REG		0x41
#define IMU_READING_MULTIPLIER (1.0 / 4096.0 * 9.81);
#define	GYRO_READING_MULTIPLIER (1.0 / 65.5);
uint8_t BoardBridge::configure_imu() {
  uint8_t check;
  uint8_t data;

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, 0x75, 1, &check, 1, HAL_MAX_DELAY);

  if (check == 0x68) {
    // Acc config
    data = 0x10;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, 0x1C, 1, &data, 1, HAL_MAX_DELAY);
    
    // Gyro config
    data = 0x08;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, 0x1B, 1, &data, 1, HAL_MAX_DELAY);

    // Power Up
    data = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, 0x6B, 1, &data, 1, HAL_MAX_DELAY);
  }

  return 0;
}
  
uint8_t BoardBridge::read_imu_data(float* data, float &temp) {
  uint8_t iicData[14];

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, MPU6050_ACC_X_HIGH_REG, 1, iicData, 14, HAL_MAX_DELAY);

  // Acc
  data[0] = (int16_t)(iicData[0] << 8 | iicData[1]) * IMU_READING_MULTIPLIER;  // X
  data[1] = (int16_t)(iicData[2] << 8 | iicData[3]) * IMU_READING_MULTIPLIER;  // Y
  data[2] = (int16_t)(iicData[4] << 8 | iicData[5]) * IMU_READING_MULTIPLIER;  // Z

  // Temp
  temp = (int16_t)(iicData[6] << 8 | iicData[7]) * 1/340.0 + 36.53;

  // Gyro
  data[3] = (int16_t)(iicData[8] << 8 | iicData[9]) * GYRO_READING_MULTIPLIER;  // X
  data[4] = (int16_t)(iicData[10] << 8 | iicData[11]) * GYRO_READING_MULTIPLIER; // Y
  data[5] = (int16_t)(iicData[12] << 8 | iicData[13]) * GYRO_READING_MULTIPLIER; // Z

  return 0;
}

uint8_t BoardBridge::uart_send_message(uint8_t* data, uint16_t size) {
  return HAL_UART_Transmit(&huart1, data, size, 100);
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

  if(huart->Instance == USART1) {
    memcpy(aTxBuffer, aRxBuffer, 10);
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&aTxBuffer, 10);
  }
  
}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}