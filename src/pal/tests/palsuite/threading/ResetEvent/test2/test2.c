//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information. 
//

/*=============================================================================
**
** Source: test2.c
**
** Dependencies: PAL_Initialize
**               PAL_Terminate
**               CreateEvent
**               CloseHandle
**               WaitForSingleObject
**
** Purpose: Test to ensure proper operation of the ResetEvent()
**          API by calling it on an event handle that's already
**          unsignalled.
** 

**
**===========================================================================*/
#include <palsuite.h>



int __cdecl main( int argc, char **argv ) 

{
    /* local variables */
    DWORD                   dwRet = 0;
    HANDLE                  hEvent = NULL;
    LPSECURITY_ATTRIBUTES   lpEventAttributes = NULL;
    BOOL                    bManualReset = TRUE; 
    BOOL                    bInitialState = FALSE;
    LPCTSTR                 lpName = "HolyMoly";


    /* PAL initialization */
    if( (PAL_Initialize(argc, argv)) != 0 )
    {
        return( FAIL );
    }


    /* create an unsignalled event which we can use with ResetEvent */
    hEvent = CreateEvent(   lpEventAttributes, 
                            bManualReset,
                            bInitialState,
                            lpName );

    if( hEvent == INVALID_HANDLE_VALUE )
    {
        /* ERROR */
        Fail( "ERROR:%lu:CreateEvent() call failed\n", GetLastError() );
    }
    
    /* verify that the event isn't signalled yet */
    dwRet = WaitForSingleObject( hEvent, 0 );
    if( dwRet != WAIT_TIMEOUT )
    {
        /* ERROR */
        Trace( "ERROR:WaitForSingleObject() call returned %lu, "
                "expected WAIT_TIMEOUT\n",
                dwRet );
        CloseHandle( hEvent );
        Fail( "Test failed\n" );
    }
    
    /* try to reset the event */
    if( ! ResetEvent( hEvent ) )
    {
        /* ERROR */
        Trace( "FAIL:%lu:ResetEvent() call failed\n", GetLastError() );
        CloseHandle( hEvent );
        Fail( "Test failed\n" );
    }

    /* close the event handle */
    if( ! CloseHandle( hEvent ) )
    {
        Fail( "ERROR:%lu:CloseHandle() call failed\n", GetLastError() );
    }

    
    /* PAL termination */
    PAL_Terminate();
    
    /* return success */
    return PASS;
}
