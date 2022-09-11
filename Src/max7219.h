//
// Created by DELL on 2022/9/10.
//

#ifndef LATTICE_TEST_MAX7219_H
#define LATTICE_TEST_MAX7219_H

#include "stm32f1xx_hal.h"

/*
 DIN A0
 CS A1
 CLK A2
*/
#define CS_On HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
#define CS_Off HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define DIN_On HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)
#define DIN_Off HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
#define CLK_On HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define CLK_Off HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)

#define REG_DECODE        0x09
#define REG_INTENSITY     0x0A
#define REG_LIMIT         0x0B
#define REG_SHUTDOWN      0x0C
#define REG_TEST          0x0F

enum Brightness
{
    L0 = 0x00,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6,
    L7,
    L8,
    L9,
    L10,
    L11,
    L12,
    L13,
    L14,
    L15,
};

enum State
{
    ON = 1,
    OFF = 0
};

void Max7219_Init(void);
void Max7219_Clear(void);
void Max7219_SetDot(uint8_t x, uint8_t y, uint8_t state);
void Max7219_SetBrightness(uint8_t brightness);
void Max7219_Fill(void);
void Max7219_DrawBitMap(uint8_t map[], uint8_t length, uint8_t height, int start_X, int start_Y);
void Max7219_InvertScreen();
void Max7219_Power(uint8_t shutdown);

void max7219_write_byte(uint8_t data);
void max7219_write(uint8_t addr, uint8_t data);

#endif //LATTICE_TEST_MAX7219_H
