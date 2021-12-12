/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "main.h"			//Header necesarios
#include <stdio.h>
#include <stdlib.h>
#include "TEXT.h"
//#include <stm32f429i_discovery_gyroscope.h>
/* Include Gyroscope component driver */
//#include "../Components/l3gd20/l3gd20.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x00)
#define ID_TEXT_0    (GUI_ID_USER + 0x06)
#define ID_TEXT_1    (GUI_ID_USER + 0x07)


// USER START (Optionally insert additional defines)
WM_HWIN      hItem;		// Handler


/**** BEGIN ****************/

// Function to swap two numbers
void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

// Function to reverse `buffer[iï¿½j]`
char* reverse(char *buffer, int i, int j)
{
	while (i < j) {
		swap(&buffer[i++], &buffer[j--]);
	}

	return buffer;
}

// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
	int n;
	int i = 0;
	// invalid input
	if (base < 2 || base > 32) {
		return buffer;
	}

	// consider the absolute value of the number
	if (value >= 0) {
		n = value;
	} else {
		n = value *  -1;
	}

	while (n)
	{
		int r = n % base;

		if (r >= 10) {
			buffer[i++] = 65 + (r - 10);
		}
		else {
			buffer[i++] = 48 + r;
		}

		n = n / base;
	}

	// if the number is 0
	if (i == 0) {
		buffer[i++] = '0';
	}

	// If the base is 10 and the value is negative, the resulting string
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < 0 && base == 10) {
		buffer[i++] = '-';
	}

	buffer[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buffer, 0, i - 1);
}

/**** END ****************/

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "FrameWinMoran", ID_FRAMEWIN_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "GUI_Eje_X", ID_TEXT_0, 16, 36, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Output_EjeX", ID_TEXT_1, 146, 35, 80, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
	GUI_TOUCH_StoreState(-1, 1);			//Permite la selección de widgets
	char my_buffer[20];
	int my_idx = 0;
	float pfData_XYZ[3] = {1.0, 2.0, 3.0};																//Resaltando su enfoque
	
//	BSP_GYRO_Init();

//	BSP_GYRO_GetXYZ(pfData_XYZ);

//	sprintf(my_buffer, "%.2f", pfData_XYZ[1]);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
	for (my_idx = 1; my_idx <= 100; ++my_idx) {

		(void)itoa(my_idx, my_buffer, 10);

		TEXT_SetText(hItem, my_buffer);
		GUI_Delay(100);
	}
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'GUI_Eje_X'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "Eje X:");
    //
    // Initialization of 'Output_EjeX'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "___");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  // USER START (Optionally insert additional message handling)
	
		/* Este case WM_INIT_DIALOG: se añade para preparar el entorno 
		y configurar las condiciones iniciales de los widgets		l*/		
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFrameWinMoran
*/
WM_HWIN CreateFrameWinMoran(void);
WM_HWIN CreateFrameWinMoran(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/