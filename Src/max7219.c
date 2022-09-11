//
// Created by DELL on 2022/9/10.
//

#include "max7219.h"

__IO uint8_t Reg_Current[] = {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
};

void Max7219_Init(void)
{
  max7219_write(REG_DECODE, 0x00); //No decode for digits 7–0
  //max7219_write(0x0a, 0x0F); //亮度设置
  max7219_write(REG_LIMIT, 0x07); //Display digits 0 1 2 3 4 5 6 7
  max7219_write(REG_SHUTDOWN, 0x01); //Normal Operation
  max7219_write(REG_TEST, 0x00); //Normal Operation
  Max7219_Clear();
}

void max7219_write_byte(uint8_t data)
{
  for (uint8_t i = 8; i >= 1; i--)
  {
    CLK_Off;
    if (data & 0x80)
      DIN_On;
    else
      DIN_Off;
    data <<= 1;
    CLK_On;
  }
}

void max7219_write(uint8_t addr, uint8_t data)
{
  CS_Off;
  max7219_write_byte(addr);
  max7219_write_byte(data);
  CS_On;
}

void Max7219_Clear(void)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    max7219_write(0x01 + i, 0x00);
    Reg_Current[i] = 0x00;
  }
}

void Max7219_SetBrightness(uint8_t brightness)
{
  max7219_write(REG_INTENSITY, brightness);
}

void Max7219_SetDot(uint8_t x, uint8_t y, uint8_t state)
{
  uint8_t col_addr = 0x01 + x;
  uint8_t row_addr = 0x01 << y;

  if (state)
  {
    if (!((Reg_Current[x] >> (y)) & 1))
      Reg_Current[x] |= row_addr;
  }
  else
  {
    if (((Reg_Current[x] >> (y)) & 1))
      Reg_Current[x] ^= row_addr;
  }

  max7219_write(col_addr, Reg_Current[x]);
}

void Max7219_Fill(void)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    max7219_write(0x01 + i, 0xFF);
    Reg_Current[i] = 0xFF;
  }
}

void Max7219_DrawBitMap(uint8_t map[], uint8_t length, uint8_t height, int start_X, int start_Y)
{
  if (start_X >= 0 && start_Y >= 0)
  {
    for (uint8_t i = 0; i < height; i++)
    {
      if (i + start_X > length - 1)
        break;
      uint8_t col_addr = 0x01 + i + start_X;
      uint8_t row_addr = map[i] << start_Y;

      Reg_Current[i + start_X] |= row_addr;

      max7219_write(col_addr, Reg_Current[i + start_X]);
    }
  }
  else if (start_X < 0 && start_Y >= 0)
  {
    for (uint8_t i = 0; i < height; i++)
    {
      if (i - start_X > length - 1)
        break;
      uint8_t col_addr = 0x01 + i;
      uint8_t row_addr = map[i - start_X] << start_Y;

      Reg_Current[i] |= row_addr;

      max7219_write(col_addr, Reg_Current[i]);
    }
  }
  else if (start_X >= 0 && start_Y < 0)
  {
    for (uint8_t i = 0; i < height; i++)
    {
      if (i + start_X > length - 1)
        break;
      uint8_t col_addr = 0x01+ i + start_X;
      uint8_t row_addr = map[i] >> -start_Y;

      Reg_Current[i + start_X] |= row_addr;

      max7219_write(col_addr, Reg_Current[i + start_X]);
    }
  }
  else
  {
    for (uint8_t i = 0; i < height; i++)
    {
      if (i - start_X > length - 1)
        break;
      uint8_t col_addr = 0x01 + i;
      uint8_t row_addr = map[i - start_X] >> -start_Y;

      Reg_Current[i] |= row_addr;

      max7219_write(col_addr, Reg_Current[i]);
    }
  }
}

void Max7219_InvertScreen()
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Reg_Current[i] =~ Reg_Current[i];
    max7219_write(0x01 + i, Reg_Current[i]);
  }
}

void Max7219_Power(uint8_t shutdown)
{
  max7219_write(REG_SHUTDOWN, shutdown);
}
