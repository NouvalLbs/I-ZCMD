/*******************************************************************************************************************************
 Improved-ZCMD v0.3 Beta

 New Algorithim for processing commands

 Version:v0.3 Beta

 Credits:
 Yashas
 Zeex for the original ZCMD include
*******************************************************************************************************************************/
#if defined _I_ZCMD_INCLUDED_V031_001_B
	#endinput
#endif
#define _I_ZCMD_INCLUDED_V031_001_B
/******************************************************************************************************************************/
#define MAX_FUNC_NAME (32)

#define COMMAND:%1(%2)          \
			forward cmd_%1(%2); \
			public cmd_%1(%2)

#define CMD:%1(%2) \
			COMMAND:%1(%2)

#define command(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#define cmd(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#define CMD_SUCCESS 1
#define CMD_FAILURE 0
/******************************************************************************************************************************/
#if defined OnPlayerCommandReceived
	forward OnPlayerCommandReceived(playerid,cmdtext[]);
#endif
#if defined OnPlayerCommandPerformed
	forward OnPlayerCommandPerformed(playerid,cmdtext[], success);
#endif
/******************************************************************************************************************************/
static izcmd_pointer_OPCP = 0;
static izcmd_idx;
/******************************************************************************************************************************/
#if defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
	   	if((izcmd_idx = funcidx("OnPlayerCommandPerformed")) != -1)
	   	{
	   	    #emit LCTRL       1
			#emit NEG
			#emit ADD.C       32
			#emit STOR.pri  izcmd_pointer_OPCP
			#emit LREF.alt  izcmd_pointer_OPCP

			#emit LCTRL 1
			#emit NEG
			#emit ADD
			#emit LOAD.alt  izcmd_idx
			#emit SHL.C.alt   3
			#emit ADD
			#emit STOR.pri  izcmd_pointer_OPCP
			#emit LREF.pri  izcmd_pointer_OPCP
			#emit STOR.pri  izcmd_pointer_OPCP
	   	}
	    #if defined izcmd_OnFilterScriptInit
			return izcmd_OnFilterScriptInit();
		#else
			return 1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
	    #undef OnFilterScriptInit
	#else
	    #define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit izcmd_OnFilterScriptInit

	#if defined OnFilterScriptInit
		forward OnFilterScriptInit();
	#endif
#else
	public OnGameModeInit()
	{
	   	if((izcmd_idx = funcidx("OnPlayerCommandPerformed")) != -1)
	   	{
	   	    #emit LCTRL       1
			#emit NEG
			#emit ADD.C       32
			#emit STOR.pri  izcmd_pointer_OPCP
			#emit LREF.alt  izcmd_pointer_OPCP

			#emit LCTRL 1
			#emit NEG
			#emit ADD
			#emit LOAD.alt  izcmd_idx
			#emit SHL.C.alt   3
			#emit ADD
			#emit STOR.pri  izcmd_pointer_OPCP
			#emit LREF.pri  izcmd_pointer_OPCP
			#emit STOR.pri  izcmd_pointer_OPCP
	   	}
	    #if defined izcmd_OnGameModeInit
			return izcmd_OnGameModeInit();
		#else
			return 1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
	    #undef OnGameModeInit
	#else
	    #define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit izcmd_OnGameModeInit

	#if defined izcmd_OnGameModeInit
	forward izcmd_OnGameModeInit();
	#endif
#endif
/******************************************************************************************************************************/
public OnPlayerCommandText(playerid, cmdtext[])
{
   	#if defined OnPlayerCommandReceived
	    if(!OnPlayerCommandReceived(playerid,cmdtext)) return 1;
	#endif

	static pos,pointer;
	static funcname[MAX_FUNC_NAME] = "cmd_",nullstr[] = "";

	if((pos = strfind(cmdtext," ",false,1)) == -1)
	{
		if((pointer = getproperty(0,cmdtext,cellmin,nullstr)))
		{
		    #emit PUSH.C nullstr
		    #emit PUSH.S playerid
		    #emit PUSH.C 8

		    #emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri

			#emit LOAD.pri pointer
			#emit SCTRL      6

			#emit PUSH.pri

			#if !defined OnPlayerCommandPerformed

		    switch(false)
			{
			    case true:
			    {
            #endif
			  		#emit PUSH.S cmdtext
					#emit PUSH.S playerid
					#emit PUSH.C 12

					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri

					#emit LOAD.pri izcmd_pointer_OPCP
					#emit SCTRL      6

					#emit RETN

    		#if !defined OnPlayerCommandPerformed
			    }
			}
			#endif

			#emit POP.pri
			#emit RETN
		}
		else
		{
            memcpy(funcname,cmdtext[1],16,strlen(cmdtext)<<2,MAX_FUNC_NAME-4);
		    if((izcmd_idx = funcidx(funcname)) == -1)
		    {
		       	#if !defined OnPlayerCommandPerformed
		       	    return 0;
	  		   	#endif

				#emit PUSH.C 0
				#emit PUSH.S cmdtext
				#emit PUSH.S playerid
				#emit PUSH.C 12

		        #emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri

				#emit LOAD.pri izcmd_pointer_OPCP
				#emit SCTRL      6

				#emit RETN
		    }
		    else
		    {
		        #emit LCTRL       1
				#emit NEG
				#emit ADD.C       32
				#emit STOR.pri  pointer
				#emit LREF.alt  pointer

				#emit LCTRL 1
				#emit NEG
				#emit ADD
				#emit LOAD.alt  izcmd_idx
				#emit SHL.C.alt   3
				#emit ADD
				#emit STOR.pri  pointer
				#emit LREF.pri  pointer
				#emit STOR.pri  pointer

				setproperty(.name= cmdtext,.value = pointer);

				#emit PUSH.C nullstr
			    #emit PUSH.S playerid
			    #emit PUSH.C 8

			    #emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri

				#emit LOAD.pri pointer
				#emit SCTRL      6

                #emit PUSH.pri

				#if !defined OnPlayerCommandPerformed
			    switch(false)
				{
				    case true:
				    {
	            #endif
				  		#emit PUSH.S cmdtext
						#emit PUSH.S playerid
						#emit PUSH.C 12

						#emit LCTRL      6
						#emit ADD.C      28
						#emit PUSH.pri

						#emit LOAD.pri izcmd_pointer_OPCP
						#emit SCTRL      6

						#emit RETN

	    		#if !defined OnPlayerCommandPerformed
				    }
				}
				#endif

				#emit POP.pri
				#emit RETN
    		}
		}
	}
	else
	{
	    cmdtext[pos] = 0;
		if((pointer = getproperty(0,cmdtext,cellmin,nullstr)))
		{
		    cmdtext[pos] =  ' ';
		    while (cmdtext[++pos] == ' ') {}

			#emit LOAD.S.alt cmdtext
			#emit LOAD.pri pos
			#emit IDXADDR

			#emit PUSH.pri
		    #emit PUSH.S playerid
		    #emit PUSH.C 8

		    #emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri

			#emit LOAD.pri pointer
			#emit SCTRL      6

            #emit PUSH.pri

			#if !defined OnPlayerCommandPerformed
		    switch(false)
			{
			    case true:
			    {
            #endif

			  		#emit PUSH.S cmdtext
					#emit PUSH.S playerid
					#emit PUSH.C 12

					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri

					#emit LOAD.pri izcmd_pointer_OPCP
					#emit SCTRL      6

					#emit RETN

    		#if !defined OnPlayerCommandPerformed
			    }
			}
			#endif

			#emit POP.pri
			#emit RETN
		}
		else
		{
		    cmdtext[pos] = 0;
		    memcpy(funcname,cmdtext[1],16,pos<<2,28);
		    if((izcmd_idx = funcidx(funcname)) == -1)
		    {
				cmdtext[pos] = ' ';
          		#if !defined OnPlayerCommandPerformed
        			return 0;
	   			#endif

				#emit PUSH.C 0
				#emit PUSH.S cmdtext
				#emit PUSH.S playerid
				#emit PUSH.C 12

		        #emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri

				#emit LOAD.pri izcmd_pointer_OPCP
				#emit SCTRL      6

				#emit RETN
		    }
		    else
		    {
		        #emit LCTRL       1
				#emit NEG
				#emit ADD.C       32
				#emit STOR.pri  pointer
				#emit LREF.alt  pointer

				#emit LCTRL 1
				#emit NEG
				#emit ADD
				#emit LOAD.alt  izcmd_idx
				#emit SHL.C.alt   3
				#emit ADD
				#emit STOR.pri  pointer
				#emit LREF.pri  pointer
				#emit STOR.pri  pointer

				setproperty(.name = cmdtext,.value = pointer);
				cmdtext[pos] = ' ';

				while (cmdtext[++pos] == ' ') {}

				#emit LOAD.S.alt cmdtext
				#emit LOAD.pri pos
				#emit IDXADDR

				#emit PUSH.pri
			    #emit PUSH.S playerid
			    #emit PUSH.C 8

			    #emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri

				#emit LOAD.pri pointer
				#emit SCTRL      6

                #emit PUSH.pri
				#if !defined OnPlayerCommandPerformed
			    switch(false)
				{
				    case true:
				    {
	            #endif

				  		#emit PUSH.S cmdtext
						#emit PUSH.S playerid
						#emit PUSH.C 12

						#emit LCTRL      6
						#emit ADD.C      28
						#emit PUSH.pri

						#emit LOAD.pri izcmd_pointer_OPCP
						#emit SCTRL      6

						#emit RETN

	    		#if !defined OnPlayerCommandPerformed
				    }
				}
				#endif

				#emit POP.pri
				#emit RETN
    		}
		}
	}
	return 0;
}
