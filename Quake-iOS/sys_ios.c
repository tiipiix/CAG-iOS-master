//
//  sys_ios.c
//  Quake-iOS
//
//  Created by Heriberto Delgado on 5/2/16.
//
//

#include "quakedef.h"
#include "errno.h"
#include <sys/stat.h>

extern double CACurrentMediaTime(void);

extern qboolean com_skipbasedir;

qboolean isDedicated;

static quakeparms_t parms;

float frame_lapse = 1.0 / 60.0;

char gl_shaderdirectory[MAX_OSPATH];

size_t sys_resourcesdirlength;

char sys_resourcesdir[MAX_OSPATH];

size_t sys_documentsdirlength;

char sys_documentsdir[MAX_OSPATH];

extern int sb_updates;

char sys_commandline[MAX_MSGLEN];

int sys_argc = 0;

char* sys_argv[MAX_NUM_ARGVS];

char** sys_messages = NULL;

int sys_messagescount = 0;

int sys_messagessize = 0;

int sys_messagesbegin = 0;

int sys_logmaxlines = 0;

qboolean sys_ended = false;

qboolean sys_inerror = false;

size_t selected_game_dirlength;

char selected_game_dir[MAX_OSPATH];

/*
 ===============================================================================
 
 FILE IO
 
 ===============================================================================
 */

#define MAX_HANDLES             10
FILE    *sys_handles[MAX_HANDLES];

int             findhandle (void)
{
    int             i;
    
    for (i=1 ; i<MAX_HANDLES ; i++)
        if (!sys_handles[i])
            return i;
    Sys_Error ("out of handles");
    return -1;
}

/*
 ================
 filelength
 ================
 */
int filelength (FILE *f)
{
    int             pos;
    int             end;
    
    pos = (int)ftell (f);
    fseek (f, 0, SEEK_END);
    end = (int)ftell (f);
    fseek (f, pos, SEEK_SET);
    
    return end;
}

int Sys_FileOpenRead (char *path, int *hndl)
{
    FILE    *f;
    int             i;
    
    i = findhandle ();
    
    f = fopen(path, "rb");
    if (!f)
    {
        *hndl = -1;
        return -1;
    }
    sys_handles[i] = f;
    *hndl = i;
    
    return filelength(f);
}

int Sys_FileOpenWrite (char *path)
{
    FILE    *f;
    int             i;
    
    i = findhandle ();
    
    f = fopen(path, "wb");
    if (!f)
        Sys_Error ("Error opening %s: %s", path,strerror(errno));
    sys_handles[i] = f;
    
    return i;
}

void Sys_FileClose (int handle)
{
    fclose (sys_handles[handle]);
    sys_handles[handle] = NULL;
}

void Sys_FileSeek (int handle, int position)
{
    fseek (sys_handles[handle], position, SEEK_SET);
}

int Sys_FileRead (int handle, void *dest, int count)
{
    return (int)fread (dest, 1, count, sys_handles[handle]);
}

int Sys_FileWrite (int handle, void *data, int count)
{
    return (int)fwrite (data, 1, count, sys_handles[handle]);
}

int     Sys_FileTime (char *path)
{
    FILE    *f;
    
    f = fopen(path, "rb");
    if (f)
    {
        fclose(f);
        return 1;
    }
    
    return -1;
}

void Sys_mkdir (char *path)
{
    mkdir (path, 0777);
}


/*
 ===============================================================================
 
 SYSTEM IO
 
 ===============================================================================
 */

void Sys_MakeCodeWriteable (unsigned long startaddr, unsigned long length)
{
}

void Sys_AddMessage(char* message)
{
    qboolean append = (sys_messagescount > 0);
    
    if (append)
    {
        size_t lastmessagelen = strlen(sys_messages[sys_messagescount - 1]);
        
        if (lastmessagelen > 0)
        {
            append = (sys_messages[sys_messagescount - 1][lastmessagelen - 1] != '\n');
        }
    }
    
    if (append)
    {
        strcat(sys_messages[sys_messagescount - 1], message);
    }
    else
    {
        if (sys_messagescount >= sys_messagessize)
        {
            if (sys_messagesbegin > 0)
            {
                memcpy(sys_messages, sys_messages + sys_messagesbegin, (sys_messagescount - sys_messagesbegin) * sizeof(char*));
                
                sys_messagescount -= sys_messagesbegin;
                sys_messagesbegin = 0;
            }
            else
            {
                int newsize = sys_messagescount + 64;
                char** newmessages = malloc(newsize * sizeof(char*));
                
                if (sys_messages != NULL)
                {
                    memcpy(newmessages, sys_messages, sys_messagescount * sizeof(char*));
                    
                    free(sys_messages);
                }
                
                sys_messages = newmessages;
                sys_messagessize = newsize;
            }
        }
        
        char* ocurrence = strstr(message, sys_resourcesdir);
        if (ocurrence != NULL)
        {
            strcpy(ocurrence, ocurrence + sys_resourcesdirlength);
        }

        ocurrence = strstr(message, sys_documentsdir);
        if (ocurrence != NULL)
        {
            strcpy(ocurrence, ocurrence + sys_documentsdirlength);
        }
        
        sys_messages[sys_messagescount] = message;
        sys_messagescount++;

        if (sys_logmaxlines > 0 && sys_messagescount - sys_messagesbegin > sys_logmaxlines)
        {
            char* todelete = sys_messages[sys_messagesbegin];
            
            if (todelete != NULL)
            {
                free(todelete);
            }
            
            sys_messagesbegin++;
        }
    }
}

void Sys_Error (char *error, ...)
{
    va_list         argptr;
    
    char*		msg = malloc(MAXPRINTMSG);
    
    sprintf (msg,"Sys_Error: ");
    va_start (argptr,error);
    vsprintf (msg+strlen(msg),error,argptr);
    va_end (argptr);
    sprintf (msg+strlen(msg),"\n");

    printf("%s", msg);
    
    Sys_AddMessage (msg);
    
    Host_Shutdown();
    
    sys_ended = true;
    sys_inerror = true;
    
    longjmp (host_abortserver, 1);
}

void Sys_Printf (char *fmt, ...)
{
    va_list         argptr;
    
    char*		msg = malloc(MAXPRINTMSG);
    
    va_start (argptr,fmt);
    vsprintf (msg,fmt,argptr);
    va_end (argptr);

    printf("%s", msg);
    
    Sys_AddMessage (msg);
}

void Sys_Quit (void)
{
    Host_Shutdown();

    sys_ended = true;
    
    //longjmp (host_abortserver, 1);
}

double Sys_FloatTime (void)
{
    return CACurrentMediaTime();
}

char *Sys_ConsoleInput (void)
{
    return NULL;
}

void Sys_Sleep (void)
{
}

void Sys_SendKeyEvents (void)
{
}

void Sys_HighFPPrecision (void)
{
}

void Sys_LowFPPrecision (void)
{
}

void Sys_Cbuf_AddText(const char* text)
{
    Cbuf_AddText((char *)text);
}

void Sys_Con_Printf(const char* text)
{
    Con_Printf((char *)text);
}

void Sys_Key_Event(int key, qboolean down)
{
    if (setjmp (host_abortserver) )
        return;			// something bad happened, or the server disconnected

    Key_Event(key, down);
}

char* Sys_LoadTextFromFile(const char* directory, const char* filename)
{
    char* fullpath = malloc(strlen(directory) + strlen(filename) + 2);
    
    strcpy(fullpath, directory);
    strcat(fullpath, "/");
    strcat(fullpath, filename);
    
    int handle = -1;
    
    int length = Sys_FileOpenRead(fullpath, &handle);
    
    char* result = NULL;
    
    if (handle >= 0 && length > 0)
    {
        result = malloc(length + 1);
        
        Sys_FileRead(handle, result, length);

        result[length] = 0;
    }
    
    Sys_FileClose(handle);
    
    free(fullpath);
    
    return result;
}

void Sys_ExpandCommandLine(const char* commandLine)
{
    sys_argc = 0;
    
    size_t length = strlen(commandLine);
    memset(sys_commandline, 0, MAX_OSPATH);
    memcpy(sys_commandline, "Quake-iOS ", 10);
    memcpy(sys_commandline + 10, commandLine, length);
    
    qboolean atwhitespace = false;
    char* argstart = sys_commandline;

    memset(sys_argv, 0, MAX_NUM_ARGVS * sizeof(char*));
    
    size_t i = 0;

    while(sys_commandline[i] != 0)
    {
        if (sys_commandline[i] <= 32)
        {
            if (!atwhitespace)
            {
                sys_argv[sys_argc] = argstart;
                sys_argc++;
                sys_commandline[i] = 0;
                atwhitespace = true;
            }
        }
        else if (atwhitespace)
        {
            argstart = sys_commandline + i;
            atwhitespace = false;
        }
        
        i++;
    }

    sys_argv[sys_argc] = argstart;
    sys_argc++;
}

void Sys_Init(const char* resourcesDir, const char* documentsDir, const char* commandLine, const char* selectedGame)
{
    com_skipbasedir = true;
    
    sys_resourcesdirlength = strlen(resourcesDir);
    memset(sys_resourcesdir, 0, MAX_OSPATH);
    memcpy(sys_resourcesdir, resourcesDir, sys_resourcesdirlength);
    
    sys_documentsdirlength = strlen(documentsDir);
    memset(sys_documentsdir, 0, MAX_OSPATH);
    memcpy(sys_documentsdir, documentsDir, sys_documentsdirlength);
    
//    memset(sys_ddir, 0, MAX_OSPATH);
//    memcpy(sys_ddir, documentsDir, sys_documentsdirlength);
    
    
    selected_game_dirlength = strlen(selectedGame);
    memset(selected_game_dir, 0, MAX_OSPATH);
    memcpy(selected_game_dir, selectedGame, selected_game_dirlength);
    
    Sys_ExpandCommandLine(commandLine);
    
    printf("Documents=%s\n", sys_documentsdir);
    
    parms.memsize = 16*1024*1024;
    parms.basedir = sys_resourcesdir;
    
    COM_InitArgv (sys_argc, sys_argv);
    
    parms.membase = malloc (parms.memsize);

    parms.argc = com_argc;
    parms.argv = com_argv;
    
    isDedicated = (COM_CheckParm ("-dedicated") != 0);

    strcpy(gl_shaderdirectory, resourcesDir);
    
    if (setjmp (host_abortserver) )
        return;			// something bad happened, or the server disconnected

    printf ("Host_Init\n");
    Host_Init (&parms);
}

void Sys_Frame()
{
    Host_Frame(frame_lapse);
}

int Sys_MessagesCount()
{
    return sys_messagescount - sys_messagesbegin;
}

char* Sys_GetMessage(int index)
{
    return sys_messages[index + sys_messagesbegin];
}
