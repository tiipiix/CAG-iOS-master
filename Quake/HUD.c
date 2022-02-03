/*

 Chief And Gun HUD module
 TPX
 
*/

#include "quakedef.h"

int			sb_updates;		// if >= vid.numpages, no update needed
int			sb_lines;		// scan lines to draw

//
// CHIEF AND GUN HUD Functions
//

int     ch_color; //Crosshair color (0=Blue 1=Red 2=Green)
extern  int HUD_IsDeathmatch;

/*
 ===============
 HUD_DrawHealth
 ===============
 */
void HUD_DrawHealth(void)
{
    qpic_t* pic;
    float x, y;
    
    //x = -55;
    //y = -150;
    pic = Draw_CachePic("gfx/hud/health0.lmp");//debug
    x = (vid.width/2) - (pic->width/2);
    y = -20;
    
    scr_copyeverything = 1;
    scr_fullupdate = 0;
    
    if (cl.stats[STAT_HEALTH] >= 100)
    {
        pic = Draw_CachePic("gfx/hud/health10.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 90)
    {
        pic = Draw_CachePic("gfx/hud/health9.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 80)
    {
        pic = Draw_CachePic("gfx/hud/health8.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 70)
    {
        pic = Draw_CachePic("gfx/hud/health7.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 60)
    {
        pic = Draw_CachePic("gfx/hud/health6.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 50)
    {
        pic = Draw_CachePic("gfx/hud/health5.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 40)
    {
        pic = Draw_CachePic("gfx/hud/health4.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 30)
    {
        pic = Draw_CachePic("gfx/hud/health3.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 20)
    {
        pic = Draw_CachePic("gfx/hud/health2.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 10)
    {
        pic = Draw_CachePic("gfx/hud/health1.lmp");
        Draw_Pic(x, y, pic);
    }
    if (cl.stats[STAT_HEALTH] >= 0)
    {
        pic = Draw_CachePic("gfx/hud/health0.lmp");
        Draw_Pic(x, y, pic);
    }
    //TPX: debug test, the vid zone is not equal to the reel screen space o_O
    //WHY ???
    //Draw_Fill(0, 0, vid.width, vid.height, 0xf0);
}

/*
 ===================================
 HUD_Crosshairs
 ==================================
 */
void HUD_Crosshairs(void)
{
    qpic_t* pic;
    
    int    x, y;
    
    x = vid.width/2 -16;
    y = vid.height/2 -16;
    pic = Draw_CachePic("");
    
    switch (cl.stats[STAT_ACTIVEWEAPON])
    {
        case IT_SHOTGUN:        // SHOTGUN
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_sgun.lmp"); // blue ch
            if (ch_color == 1)
                pic = Draw_CachePic("gfx/ch/ch_rsgun.lmp"); // red ch
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_gsgun.lmp");  //green ch
            //Draw_Pic(x, y, pic);
            break;
        case IT_SUPER_SHOTGUN:    //PISTOL
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_pistol.lmp");
            if (ch_color == 1 )
                pic = Draw_CachePic("gfx/ch/ch_rpistol.lmp");
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_gpistol.lmp");
            //Draw_Pic(x, y, pic);
            break;
        case IT_NAILGUN:        //SMG
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_smg.lmp");
            if (ch_color == 1)
                pic = Draw_CachePic("gfx/ch/ch_rsmg.lmp");
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_gsmg.lmp");
            //Draw_Pic(x, y, pic);
            break;
        case IT_SUPER_NAILGUN:    //PLASMA RIFLE
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_plasma.lmp");
            if (ch_color == 1)
                pic = Draw_CachePic("gfx/ch/ch_rplasma.lmp");
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_gplasma.lmp");
            //Draw_Pic(x, y, pic);
            break;
        case IT_GRENADE_LAUNCHER: //PLASMA PISTOL
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_plasma.lmp");
            if (ch_color == 1)
                pic = Draw_CachePic("gfx/ch/ch_rplasma.lmp");
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_gplasma.lmp");
            //Draw_Pic(x, y, pic);
            break;
        case IT_ROCKET_LAUNCHER: //ROCKET_LAUNCHER
            if (ch_color == 0)
                pic = Draw_CachePic("gfx/ch/ch_rocket.lmp");
            if (ch_color == 1)
                pic = Draw_CachePic("gfx/ch/ch_rrocket.lmp");
            if (ch_color == 2)
                pic = Draw_CachePic("gfx/ch/ch_grocket.lmp");
            //Draw_Pic(x, y, pic);
            break;
    }
    Draw_Pic(x, y, pic);
}

/*
 ===================================
 HUD_Weapons
 ==================================
 */
void HUD_Weapons(void)
{
    qpic_t* pic2;
    float x, y;
    
    x = vid.width;
    y = 0;
    pic2 = Draw_CachePic("");
    
    switch (cl.stats[STAT_ACTIVEWEAPON])
    {
            case IT_SUPER_SHOTGUN:    //PISTOL
            pic2 = Draw_CachePic("gfx/wep/pistol.lmp");
            break;
            
            case IT_NAILGUN:        //SMG
            pic2 = Draw_CachePic("gfx/wep/smg.lmp");
            break;
            
            case IT_SUPER_NAILGUN:    //PLASMA RIFLE
            pic2 = Draw_CachePic("gfx/wep/prifle.lmp");
            break;
    }
    Draw_Pic(x, y, pic2);
}

/*
 ===================================
 HUD_Deathmatch
 ==================================
 */
void HUD_Deathmatch(void)
{
    qpic_t* pic3;
    float x, y;
    int bscore;
    int rscore;
    #define MAX_DIGITS 3
    
    if (Cvar_VariableValue ("deathmatch"))
    {
        //draw deathmatch score backgroud
        pic3 = Draw_CachePic("gfx/deathmatch.lmp");
        x = (vid.width/2) - (pic3->width/2);
        y = 0;
        Draw_AlphaPic(x, y, pic3, 0.5);
        
        //draw blue score
        bscore = Cvar_VariableValue("bluescore");
        char bscore_char[MAX_DIGITS + sizeof(char)];
        sprintf(bscore_char, "%d", bscore);
        Draw_String(x+10, y+5, bscore_char);
        
        //draw red score
        rscore = Cvar_VariableValue("redscore");
        char rscore_char[MAX_DIGITS + sizeof(char)];
        sprintf(rscore_char, "%d", rscore);
        Draw_String(x+50, y+5, rscore_char);
    }
}
