enum GameFamily { GF_UNKNOWN, GF_IE3, GF_GO1, GF_CHRONO, GF_GALAXY };
#define EXAMPLE_ADDR_DIRECT 0u
static enum GameFamily g_family=GF_UNKNOWN; static u32 g_lowTitleId=0;
static void DetectGameFromPluginPath(void){char path[256]={0};if(R_FAILED(PLGLDR__GetPluginPath(path)))return;for(char*p=path;*p;p++)if(!strncmp(p,"00040000",8)){char t[17];memcpy(t,p,16);t[16]=0;g_lowTitleId=(u32)strtoull(t+8,NULL,16);break;}switch(g_lowTitleId){case 0xF7B00:case 0xF7C00:case 0xF7D00:case 0xF7E00:case 0xF7F00:case 0xF8000:g_family=GF_IE3;break;case 0x112F00:case 0x113000:g_family=GF_GO1;break;case 0x136C00:case 0x136D00:g_family=GF_CHRONO;break;case 0x10BA00:case 0x10BB00:g_family=GF_GALAXY;break;default:break;}}
static int IsOgre(void){return g_lowTitleId==0xF7F00||g_lowTitleId==0xF8000;}static void Fill8(u32 a,u32 s,u32 n,u8 v){for(u32 i=0;i<n;i++)W8(a+i*s,v);}
static u32 EnterNum(const char *title,u32 initial,int *cancel);
static u32 g_playerSlot=1;static char g_editorMsg[48];
static u32 PlayerExpAddr(void){return(IsOgre()?0x152BFF80:0x152BEE80)+(g_playerSlot-1)*0x6C;}
static u32 PlayerStatsAddr(void){return(IsOgre()?0x152BC3EC:0x152BB2EC)+(g_playerSlot-1)*0x98;}
static void MaxOnePlayer(void){u32 p=PlayerStatsAddr();W32(p,0x03E703E7);W32(p+4,0x03E703E7);W32(p+8,~0u);W32(p+12,~0u);W32(p+16,~0u);W16(p+20,0xFFFF);}
static int RunCheatWrite(int id){g_oneShotMsg="OK";if(id==CH_STATUS){g_oneShotMsg=g_family==GF_IE3?"IE3 READY":g_family==GF_GO1?"GO READY":g_family==GF_CHRONO?"CHRONO READY":g_family==GF_GALAXY?"GALAXY READY":"UNSUPPORTED";return 1;}if(g_family==GF_UNKNOWN){g_oneShotMsg="BLOCKED";return 1;}switch(id){
case CH_CURRENCY:if(g_family==GF_IE3){W32(0x087E8F30,999999);W32(0x087E8F34,999999);}else if(g_family==GF_GO1){u32 p=R32(0x08066B58);if(p>=0x08000000&&p<0x20000000){W32(p+4,9999999);W32(p+8,9999999);}else{W32(0x14C27E1C,9999999);W32(0x14C27E20,9999999);}}else if(g_family==GF_CHRONO){W32(0x1471D1F8,9999999);W32(0x1471D1FC,9999999);}else W32(0x14EBDF30,9999999);return 1;
case CH_COINS:if(g_family!=GF_GALAXY){g_oneShotMsg="GALAXY ONLY";return 1;}for(u32 a=0x14EBE328;a<=0x14EBE330;a+=2)W16(a,999);return 1;
case CH_ITEMS:if(g_family==GF_IE3)Fill8(0x087E8B19,1,0x3F5,99);else if(g_family==GF_GO1)Fill8(0x14C28218,0x10,0xFD,99);else if(g_family==GF_CHRONO)Fill8(0x1471E010,0x10,0x13D,99);else Fill8(0x14EBEEA0,0x10,0x259,99);return 1;
case CH_EQUIPMENT:if(g_family==GF_IE3)Fill8(0x087E8B19,1,0x3F5,99);else if(g_family==GF_GO1)Fill8(0x14C2C9F0,0x14,0xDD,99);else if(g_family==GF_CHRONO)Fill8(0x14720090,0x14,0x14D,99);else Fill8(0x14EC154C,0x14,0x1B9,99);return 1;
case CH_LEVEL99:{u32 s,st,n;if(g_family==GF_IE3){s=IsOgre()?0x152BFF80:0x152BEE80;st=0x6C;n=100;}else if(g_family==GF_GO1){s=0x14D9E708;st=0xFC;n=111;}else if(g_family==GF_CHRONO){s=0x14700350;st=0x134;n=300;}else{s=0x14EA0490;st=0x13C;n=125;}for(u32 i=0;i<n;i++)W32(s+i*st,9999999);return 1;}
case CH_LEVEL255:if(g_family==GF_CHRONO)Fill8(0x1470035A,0x134,300,255);else if(g_family==GF_GALAXY)Fill8(0x14EA04A2,0x13C,125,255);else g_oneShotMsg="CS/GALAXY ONLY";return 1;
case CH_SECRET:if(g_family==GF_IE3)W8(0x087DF079,2);else g_oneShotMsg="IE3 ONLY";return 1;
case CH_MAPS:if(g_family==GF_IE3)Fill8(0x087E8B2F,1,5,1);else g_oneShotMsg="IE3 ONLY";return 1;
case CH_TICKETS:if(g_family==GF_IE3){Fill8(0x087E8B34,1,10,1);Fill8(0x087E8B3F,1,5,1);}else g_oneShotMsg="IE3 ONLY";return 1;
case CH_TOKENS:if(g_family==GF_IE3)Fill8(0x087E8B71,1,3,99);else g_oneShotMsg="IE3 ONLY";return 1;
case CH_BADGE:if(g_family==GF_IE3)W8(0x087E8B70,99);else g_oneShotMsg="IE3 ONLY";return 1;
case CH_PLAYER_SLOT:{if(g_family!=GF_IE3){g_oneShotMsg="IE3 ONLY";return 1;}int c=0;u32 v=EnterNum("Roster slot (1-100)",g_playerSlot,&c);if(!c&&v>=1&&v<=100)g_playerSlot=v;siprintf(g_editorMsg,"SLOT %lu",(unsigned long)g_playerSlot);g_oneShotMsg=g_editorMsg;return 1;}
case CH_PLAYER_EXP:{if(g_family!=GF_IE3){g_oneShotMsg="IE3 ONLY";return 1;}int c=0;u32 a=PlayerExpAddr(),v=EnterNum("Experience (0-9999999)",R32(a),&c);if(!c&&v<=9999999)W32(a,v);siprintf(g_editorMsg,"S%lu EXP %lu",(unsigned long)g_playerSlot,(unsigned long)R32(a));g_oneShotMsg=g_editorMsg;return 1;}
case CH_PLAYER_MAX:if(g_family==GF_IE3){MaxOnePlayer();siprintf(g_editorMsg,"SLOT %lu MAX",(unsigned long)g_playerSlot);g_oneShotMsg=g_editorMsg;}else g_oneShotMsg="IE3 ONLY";return 1;
case CH_STATS:if(g_family==GF_IE3){u32 s=IsOgre()?0x152BC3EC:0x152BB2EC;for(u32 i=0;i<100;i++){u32 p=s+i*0x98;W32(p,0x03E703E7);W32(p+4,0x03E703E7);W32(p+8,~0u);W32(p+12,~0u);W32(p+16,~0u);W16(p+20,0xFFFF);}}else if(g_family==GF_GO1){for(u32 i=0;i<111;i++){u32 p=0x14D9E70C+i*0xFC;W32(p,0x03E703E7);for(u32 o=0xC0;o<=0xD0;o+=4)W32(p+o,0x03E703E7);}}else if(g_family==GF_CHRONO){for(u32 i=0;i<300;i++){u32 p=0x14700354+i*0x134;W32(p,0x03E703E7);W32(p+4,0xFDE8FDE8);for(u32 o=0xF8;o<=0x108;o+=4)W32(p+o,0xFDE8FDE8);}}else for(u32 i=0;i<125;i++){u32 p=0x14EA058C+i*0x13C;W32(p,0x03E703E7);for(u32 o=4;o<=16;o+=4)W32(p+o,0xFDE8FDE8);}return 1;}return 0;}

static int IsActionCheat(int id){return id==CH_STATUS||id==CH_PLAYER_SLOT||id==CH_PLAYER_EXP||id==CH_PLAYER_MAX;}
static int IsToggleCheat(int id){return id>=CH_CURRENCY&&id<=CH_BADGE&&!IsActionCheat(id);}
static int OneShot(int id){
    if(IsActionCheat(id))return RunCheatWrite(id);
    // Toggle rows still need their write once when being enabled. Returning zero lets the
    // menu retain the checked state instead of replacing it with the short confirmation flash.
    if(IsToggleCheat(id)&&!cheatState[id])RunCheatWrite(id);
    return 0;
}
static void ApplyCheats(void){
    // Values that the game routinely recalculates are held while their toggle is enabled.
    // Large inventory/roster writes are deliberately not repeated every frame.
    if(cheatState[CH_CURRENCY])RunCheatWrite(CH_CURRENCY);
    if(cheatState[CH_COINS])RunCheatWrite(CH_COINS);
    if(cheatState[CH_TIMER]&&g_family==GF_IE3){u32 p=R32(0x08805F90);if(p>=0x08000000&&p<0x20000000)W16(p+0x584,0xFFD4);}
}
