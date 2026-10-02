#include "3ds.h"
#include "csvc.h"
#include "CTRPluginFramework.hpp"
#include <string>

namespace CTRPluginFramework {
enum class Family { Unknown, IE3, GO1, Chrono, Galaxy };
struct Profile { u64 id; const char *name; Family family; };
static const Profile profiles[] = {
 {0x00040000000F7B00ULL,"IE3: Bomb Blast (EUR)",Family::IE3},
 {0x00040000000F7C00ULL,"IE3: Bomb Blast (EUR Multi-3)",Family::IE3},
 {0x00040000000F7D00ULL,"IE3: Lightning Bolt (EUR)",Family::IE3},
 {0x00040000000F7E00ULL,"IE3: Lightning Bolt (EUR Multi-3)",Family::IE3},
 {0x00040000000F7F00ULL,"IE3: Team Ogre Attacks! (EUR)",Family::IE3},
 {0x00040000000F8000ULL,"IE3: Team Ogre Attacks! (EUR Multi-3)",Family::IE3},
 {0x0004000000112F00ULL,"Inazuma Eleven GO: Light (EUR)",Family::GO1},
 {0x0004000000113000ULL,"Inazuma Eleven GO: Shadow (EUR)",Family::GO1},
 {0x0004000000136C00ULL,"GO Chrono Stones: Wildfire (EUR)",Family::Chrono},
 {0x0004000000136D00ULL,"GO Chrono Stones: Thunderflash (EUR)",Family::Chrono},
 {0x000400000010BA00ULL,"GO Galaxy: Big Bang (JPN/translation)",Family::Galaxy},
 {0x000400000010BB00ULL,"GO Galaxy: Supernova (JPN/translation)",Family::Galaxy}
};
static const Profile *game = nullptr;

static void Done(const std::string &s) { OSD::Notify(s, Color::Lime); }
static void Repeat8(u32 address,u32 stride,u32 count,u8 value) {
 for(u32 i=0;i<count;i++) Process::Write8(address+i*stride,value);
}
static bool Ogre() { return game->id==0x00040000000F7F00ULL || game->id==0x00040000000F8000ULL; }

static void Currency(MenuEntry*) {
 switch(game->family) {
  case Family::IE3: Process::Write32(0x087E8F30,999999); Process::Write32(0x087E8F34,999999); break;
  case Family::GO1: {
   u32 p=0;
   if(Process::Read32(0x08066B58,p) && p>=0x08000000 && p<0x20000000) {
    Process::Write32(p+4,9999999); Process::Write32(p+8,9999999);
   } else { Process::Write32(0x14C27E1C,9999999); Process::Write32(0x14C27E20,9999999); }
   break;
  }
  case Family::Chrono: Process::Write32(0x1471D1F8,9999999); Process::Write32(0x1471D1FC,9999999); break;
  case Family::Galaxy: Process::Write32(0x14EBDF30,9999999); break;
  default:return;
 }
 Done("Currency maximised");
}
static void Coins(MenuEntry*) {
 for(u32 a=0x14EBE328;a<=0x14EBE330;a+=2) Process::Write16(a,999);
 Done("All Galaxy coins set to 999");
}
static void Items(MenuEntry*) {
 switch(game->family) {
  case Family::IE3: Repeat8(0x087E8B19,1,0x3F5,99); break;
  case Family::GO1: Repeat8(0x14C28218,0x10,0xFD,99); break;
  case Family::Chrono: Repeat8(0x1471E010,0x10,0x13D,99); break;
  case Family::Galaxy: Repeat8(0x14EBEEA0,0x10,0x259,99); break;
  default:return;
 }
 Done("Owned items and techniques set to 99");
}
static void Equipment(MenuEntry*) {
 switch(game->family) {
  case Family::IE3: Repeat8(0x087E8B19,1,0x3F5,99); break;
  case Family::GO1: Repeat8(0x14C2C9F0,0x14,0xDD,99); break;
  case Family::Chrono: Repeat8(0x14720090,0x14,0x14D,99); break;
  case Family::Galaxy: Repeat8(0x14EC154C,0x14,0x1B9,99); break;
  default:return;
 }
 Done("Owned equipment set to 99");
}
static void Level99(MenuEntry*) {
 u32 start=0,stride=0,count=0;
 switch(game->family) {
  case Family::IE3:start=Ogre()?0x152BFF80:0x152BEE80;stride=0x6C;count=100;break;
  case Family::GO1:start=0x14D9E708;stride=0xFC;count=111;break;
  case Family::Chrono:start=0x14700350;stride=0x134;count=300;break;
  case Family::Galaxy:start=0x14EA0490;stride=0x13C;count=125;break;
  default:return;
 }
 for(u32 i=0;i<count;i++) Process::Write32(start+i*stride,9999999);
 Done("Published Level 99 roster code applied");
}
static void Level255(MenuEntry*) {
 if(game->family==Family::Chrono) Repeat8(0x1470035A,0x134,300,255);
 else if(game->family==Family::Galaxy) Repeat8(0x14EA04A2,0x13C,125,255);
 else return;
 Done("Experimental Level 255 code applied");
}
static void Stats(MenuEntry*) {
 if(game->family==Family::IE3) {
  u32 s=Ogre()?0x152BC3EC:0x152BB2EC;
  for(u32 i=0;i<100;i++){u32 p=s+i*0x98;Process::Write32(p,0x03E703E7);Process::Write32(p+4,0x03E703E7);Process::Write32(p+8,0xFFFFFFFF);Process::Write32(p+12,0xFFFFFFFF);Process::Write32(p+16,0xFFFFFFFF);Process::Write16(p+20,0xFFFF);}
 } else if(game->family==Family::GO1) {
  for(u32 i=0;i<111;i++){u32 p=0x14D9E70C+i*0xFC;Process::Write32(p,0x03E703E7);for(u32 o=0xC0;o<=0xD0;o+=4)Process::Write32(p+o,0x03E703E7);}
 } else if(game->family==Family::Chrono) {
  for(u32 i=0;i<300;i++){u32 p=0x14700354+i*0x134;Process::Write32(p,0x03E703E7);Process::Write32(p+4,0xFDE8FDE8);for(u32 o=0xF8;o<=0x108;o+=4)Process::Write32(p+o,0xFDE8FDE8);}
 } else if(game->family==Family::Galaxy) {
  for(u32 i=0;i<125;i++){u32 p=0x14EA058C+i*0x13C;Process::Write32(p,0x03E703E7);for(u32 o=4;o<=16;o+=4)Process::Write32(p+o,0xFDE8FDE8);}
 } else return;
 Done("Published max-stat roster code applied");
}
static void Status(MenuEntry*) {
 std::string s="Detected: "; s+=game?game->name:"unsupported title";
 s+="\n\nBack up your save before inventory or roster edits. Current entries are imported from public CTRPF/Gateshark codes.";
 MessageBox("Compatibility status",s)();
}
static void InitMenu(PluginMenu &menu) {
 u64 id=Process::GetTitleID(); for(const Profile &p:profiles) if(p.id==id){game=&p;break;}
 if(!game){menu+=new MenuEntry("Unsupported title",Status,"Memory writes are disabled for unknown title IDs.");return;}
 menu+=new MenuEntry("Game / compatibility status",Status);
 MenuFolder *c=new MenuFolder("Currency");
 *c+=new MenuEntry("Max money + friendship/passion",nullptr,Currency);
 if(game->family==Family::Galaxy)*c+=new MenuEntry("All coins x999",nullptr,Coins);
 menu+=c;
 MenuFolder *i=new MenuFolder("Inventory");
 *i+=new MenuEntry("Owned items/techniques x99",nullptr,Items);
 *i+=new MenuEntry("Owned equipment x99",nullptr,Equipment);
 menu+=i;
 MenuFolder *r=new MenuFolder("Players / roster");
 *r+=new MenuEntry("Roster Level 99 after match",nullptr,Level99);
 *r+=new MenuEntry("Roster max stats",nullptr,Stats);
 if(game->family==Family::Chrono||game->family==Family::Galaxy)*r+=new MenuEntry("[Experimental] Roster Level 255",nullptr,Level255);
 menu+=r;
}
void PatchProcess(FwkSettings&) {}
void OnProcessExit(void) {}
int main(void) {
 PluginMenu *menu=new PluginMenu("Inazuma Eleven CTRPF",0,1,0,"Multi-title plugin. Back up saves before one-shot editors.");
 menu->SynchronizeWithFrame(true); InitMenu(*menu); menu->Run(); delete menu; return 0;
}
}
