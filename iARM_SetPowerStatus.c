/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include <stdio.h>
#include <string.h>
#include "uidev.h"

const char *pPowerON = "ON";
const char *pPowerOFF = "OFF";
const char *pPowerStandby = "STANDBY";


void usage ()
{
    printf ("\nUsage: 'iARM_SetPowerStatus [ON | STANDBY | OFF]'\n");
    printf ("\t\t ON       -> Set to Active Mode\n");
    printf ("\t\t STANDBY  -> Set to Standby Mode\n");
    printf ("\t\t OFF      -> Set to OFF\n");
}

void setPowerMode();
/**
 * Test application to check whether the box is in standby or not.
 * This has been developed to resolve, XONE-4598
 */
int main(int argc, char *argv[])
{
    UIDev_PowerState_t ePowerstate = UIDEV_POWERSTATE_UNKNOWN;
    IARM_Result_t retVal = IARM_RESULT_INVALID_STATE;
    if (argc < 2)
    {
        usage();
    }
    else if (strncasecmp(pPowerON, argv[1], strlen (pPowerON)) == 0)
    {
            printf ("ON Request...\n");
            ePowerstate = UIDEV_POWERSTATE_ON;
    }
    else if (strncasecmp(pPowerStandby, argv[1], strlen (pPowerStandby)) == 0)
    {
            ePowerstate = UIDEV_POWERSTATE_STANDBY;
            printf ("STANDBY Request...\n");
    }
    else if (strncasecmp(pPowerOFF, argv[1], strlen (pPowerOFF)) == 0)
    {
            printf ("OFF Request...\t Not processed\n");
    }
    else
    {
        usage();
    }
    

    if ((ePowerstate == UIDEV_POWERSTATE_ON) || (ePowerstate == UIDEV_POWERSTATE_STANDBY))
    {
        UIDev_Init("iARMSetPower_tool");

        /** Query current Power state  */
        if (IARM_RESULT_SUCCESS == UIDev_SetPowerState(ePowerstate))
        {
            printf ("SetPowerState :: Success");
        }
        else
        {
            printf ("SetPowerState :: Failed");
        }
    }
    return 0;
}
