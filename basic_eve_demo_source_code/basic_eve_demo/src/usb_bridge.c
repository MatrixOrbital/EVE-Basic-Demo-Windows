#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define FT800_PD_N      7
#pragma comment(lib, "libMPSSE.lib")

#include "libMPSSE_spi.h"

static FT_HANDLE handle;

void HAL_Close(void)
{
	if (handle)
		SPI_CloseChannel(handle);
}

void HAL_SPI_Enable(void)
{
	SPI_ToggleCS(handle, 1);
}

void HAL_SPI_Disable(void)
{
	SPI_ToggleCS(handle, 0);
}

uint8_t HAL_SPI_Write(uint8_t data)
{
	uint32_t SizeTransfered = 0;
	SPI_Write(
		handle,
		&data,
		1,
		&SizeTransfered,
		SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES 
	);
	return 0;
}

uint8_t HAL_SPI_WriteByte(uint8_t data)
{
	uint32_t SizeTransfered;
	SPI_Write(handle, &data, 1, &SizeTransfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
	return 0;
}

uint8_t HAL_SPI_ReadByte(uint8_t data)
{
	uint8_t res;
	uint32_t SizeTransfered;
	SPI_Read(handle, &res, 1, &SizeTransfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
	return res;
}

void HAL_SPI_WriteBuffer(uint8_t *Buffer, uint32_t Length)
{
	uint32_t SizeTransfered;
	SPI_Write(handle, Buffer, Length, &SizeTransfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
	printf("writb: %d %d\n", SizeTransfered, 0);

}

void HAL_SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length)
{
	HAL_SPI_WriteByte(0);
	uint32_t SizeTransfered;
	FT_STATUS res = SPI_Read(handle, Buffer, Length, &SizeTransfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
}

void HAL_Delay(uint32_t DLY) 
{
	Sleep(DLY);
}

void HAL_Eve_Reset_HW(void)
{
	uint32_t total_channels;
	Init_libMPSSE();
	FT_STATUS result = SPI_GetNumChannels(&total_channels);
	printf("channels found : %d\n", total_channels);
	if (total_channels > 0)
	{
		FT_DEVICE_LIST_INFO_NODE devList;
		SPI_GetChannelInfo(0, &devList);

		ChannelConfig channelConf;            //channel configuration
		FT_STATUS status;
		/* configure the spi settings */
		channelConf.ClockRate = 12000 * 1000;
		channelConf.LatencyTimer = 2;
		channelConf.configOptions = SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3 | SPI_CONFIG_OPTION_CS_ACTIVELOW;
		channelConf.Pin = 0x00000000;

		/* Open the first available channel */
		SPI_OpenChannel(0, (FT_HANDLE *)&handle);
		status = SPI_InitChannel(handle, &channelConf);
		if (status == FT_OK)
		{
			printf("USB->SPI Bridge opened\n");
		}
		else
		{
			printf("Unable to open USB->SPI Bridge\n");
			exit(1);
		}
	}
	else
	{
		printf("USB->SPI Bridge not found.");
		exit(1);
	}
	FT_WriteGPIO(handle, (1 << FT800_PD_N) | 0x3B, (0 << FT800_PD_N) | 0x08);//PDN set to 0 ,connect BLUE wire of MPSSE to PDN# of FT800 board
	Sleep(20);
	
	FT_WriteGPIO(handle, (1 << FT800_PD_N) | 0x3B, (1 << FT800_PD_N) | 0x08);//PDN set to 0 ,connect BLUE wire of MPSSE to PDN# of FT800 board
	Sleep(20);


}
