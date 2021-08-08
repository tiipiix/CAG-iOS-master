/*

 Chief And Gun HUD module
 TPX
 
*/

//#define	SBAR_HEIGHT		24

//extern	int			sb_lines;			// scan lines to draw

//TPX: CAG sbar HUD declaration
extern      int     ch_color; //Crosshair color (0=Blue 1=Red 2=Green)
void HUD_DrawHealth (void);
void HUD_Crosshairs (void);
void HUD_Weapons(void);
