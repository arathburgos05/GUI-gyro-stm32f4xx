/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : App.c
Purpose     : Simple demo drawing "Hello world"
----------------------------------------------------------------------
*/

#include "DIALOG.h"
#include "main.h"

#include <stdio.h>
#include <stm32f429i_discovery_gyroscope.h>
/* Include Gyroscope component driver */
//#include "../Components/l3gd20/l3gd20.h"
#include "../Components/i3g4250d/i3g4250d.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_TEXT_1            (GUI_ID_USER + 0x02)
#define ID_TEXT_4 (GUI_ID_USER + 0x05)
#define ID_TEXT_5 (GUI_ID_USER + 0x06)
#define ID_SLIDER_0 (GUI_ID_USER + 0x08)
#define ID_SLIDER_1 (GUI_ID_USER + 0x09)

#define DT_SEG (0.1f)
//#define DT_MS (int)(DT_SEG*1000f)

//#define ANG_EJE_X pfData_XYZ[0]
//#define ANG_EJE_Y pfData_XYZ[1]
//#define ANG_EJE_Z pfData_XYZ[2]

WM_HWIN CreateFrameWinMoran(void);	//Prototipado de la funci�n del Framewin

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
//  GUI_Clear();
//  GUI_SetFont(&GUI_Font20_1);
//  GUI_DispStringAt("Hola Mundo!", (LCD_GetXSize()-100)/2, (LCD_GetYSize()-20)/2);
	uint8_t b_isFirstTime = 0;
	/* Use memory devices on all windows to avoid flicker */
	WM_SetCreateFlags(WM_CF_MEMDEV);
	CreateFrameWinMoran();					//Llamado a la funci�n del Framewin
	float angulo_X = 0.0;
	float angulo_Y = 0.0;
	float angulo_Z = 0.0;

	while (1) {
		/***** Tareas que se ejecutan de forma simult�nea con el GUI ********/
		// Parpadea led verde
		BSP_LED_Toggle(LED3);
		GUI_Delay(100);				//Retardo 500 msegs, usando la API del GUI

		if (1 == b_isInitcbDialog) {
			if (0 == b_isFirstTime) {

//				if ( GYRO_OK == BSP_GYRO_Init() ) {
//					sprintf(my_buffer, "GYRO_OK");
//				} else {
//					sprintf(my_buffer, "GYRO_NOT_OK");
//				}
				b_isFirstTime = 1;
			} else {
				BSP_GYRO_GetXYZ(pfData_XYZ);

				angulo_X = angulo_X + (pfData_XYZ[0]/1000.0f) * DT_SEG;
				angulo_Y = angulo_Y + (pfData_XYZ[1]/1000.0f) * DT_SEG;
				angulo_Z = angulo_Z + (pfData_XYZ[2]/1000.0f) * DT_SEG;

				if (angulo_X > 180.0f) {
					angulo_X = 180.0f;
				} else if (angulo_X < -180.0f) {
					angulo_X = -180.0f;
				}

			    hItem = WM_GetDialogItem(main_windows_hItem, ID_SLIDER_0);
				SLIDER_SetRange(hItem, -180, 180);
				SLIDER_SetValue(hItem, (int)angulo_X);

				sprintf(my_buffer, "%.1f", angulo_X);
				hItem = WM_GetDialogItem(main_windows_hItem, ID_TEXT_1);
				TEXT_SetText(hItem, my_buffer);

				sprintf(my_buffer, "%.1f", angulo_Y);
				hItem = WM_GetDialogItem(main_windows_hItem, ID_TEXT_4);
				TEXT_SetText(hItem, my_buffer);

				sprintf(my_buffer, "%.1f", angulo_Z);
				hItem = WM_GetDialogItem(main_windows_hItem, ID_TEXT_5);
				TEXT_SetText(hItem, my_buffer);

			}
		}
	}
}

/*************************** End of file ****************************/
