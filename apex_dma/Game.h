#include "Math.h"
#include "glowmode.h"
#include "memory.hpp"
#include "offsets.h"
#include "vector.h"
#include <cstdint>

#define NUM_ENT_ENTRIES (1 << 12)
#define ENT_ENTRY_MASK (NUM_ENT_ENTRIES - 1)

typedef struct Bone {
  uint8_t pad1[0xCC];
  float x;
  uint8_t pad2[0xC];
  float y;
  uint8_t pad3[0xC];
  float z;
} Bone;

struct GColor {
  float r, g, b;
};

struct Fade {
  int a, b;
  float c, d, e, f;
};

class Entity {
public:
  uint64_t ptr;
  uint8_t buffer[0x3FF0];
  Vector getPosition();
  bool isDummy();
  bool isPlayer();
  bool isKnocked();
  bool isAlive();
  float lastVisTime();
  int getTeamId();
  int getHealth();
  int getShield();
  int getArmortype();
  int getMaxshield();
  bool isGlowing();
  bool isZooming();
  Vector getViewOffset();
  Vector getAbsVelocity();
  QAngle GetSwayAngles();
  QAngle GetViewAngles();
  Vector GetCamPos();
  QAngle GetRecoil();
  Vector GetViewAnglesV();
  float GetYaw();
  void enableGlow(int setting_index, uint8_t inside_value, uint8_t outline_size,
                  std::array<float, 3> highlight_parameter, float glow_dist);
  float lastCrossHairTime();
  void SetViewAngles(SVector angles);
  void SetViewAngles(QAngle &angles);
  Vector getBonePositionByHitbox(int id);
  bool Observing(uint64_t entitylist);
  void get_name(uint64_t g_Base, uint64_t index, char *name);
  void glow_weapon_model(uint64_t g_Base, bool enable_glow,
                         std::array<float, 3> highlight_colors);
  bool check_love_player(uint64_t entity_index);
};

class Item {
public:
  uint64_t ptr;
  uint8_t buffer[0x3FF0];
  Vector getPosition();
  bool isItem();
  bool isBox();
  bool isTrap();
  //bool isGlowing();
  void enableGlow(int setting_index, uint8_t outline_size, std::array<float, 3> highlight_parameter);
  //void disableGlow();
  //void BlueGlow();
};

class WeaponXEntity {
public:
  void update(uint64_t LocalPlayer);
  float get_projectile_speed();
  float get_projectile_gravity();
  float get_zoom_fov();
  int get_ammo();
  const char *get_name_str();
  int get_mod_bitfield();
  uint32_t get_weap_id();

private:
  float projectile_scale;
  float projectile_speed;
  float zoom_fov;
  int ammo;
  char name_str[200];
  int mod_bitfield;
  uint32_t weap_id;
};

struct ClientClass {
  uint64_t pCreateFn;
  uint64_t pCreateEventFn;
  uint64_t pNetworkName;
  uint64_t pRecvTable;
  uint64_t pNext;
  uint32_t ClassID;
  uint32_t ClassSize;
};

// DONE WITH THE EDITING
// Player Definitions, dont edit unless you know what you are doing.
typedef struct player {
  float dist = 0;
  int entity_team = 0;
  float boxMiddle = 0;
  float h_y = 0;
  float width = 0;
  float height = 0;
  float b_x = 0;
  float b_y = 0;
  bool knocked = false;
  bool visible = false;
  int health = 0;
  int shield = 0;
  // seer
  int maxshield = 0;
  int armortype = 0;
  Vector EntityPosition;
  Vector LocalPlayerPosition;
  QAngle localviewangle;
  float targetyaw = 0;
  bool is_alive = true;
  bool is_love = false;
  bool is_spectator = false;
  char name[33] = {0};
} player;

struct Matrix {
  float matrix[16];
};

Entity getEntity(uintptr_t ptr);
Item getItem(uintptr_t ptr);

bool WorldToScreen(Vector from, float *m_vMatrix, int targetWidth,
                   int targetHeight, Vector &to);
float CalculateFov(Entity &from, Entity &target);
QAngle CalculateBestBoneAim(Entity &from, Entity &target, float max_fov, float smooth);
void get_class_name(uint64_t entity_ptr, char *out_str);

enum weapon_id : int32_t {
  idweapon_r301 = 0,
  idweapon_sentinel = 1,
  idweapon_bow = 2,
  idsheila_stationary = 14,
  idsheila = 58,
  idweapon_rampage = 6,
  idmelee = 116,
  idsnipers_mark = 78,
  idweapon_alternator = 81,
  idweapon_re45 = 82,
  idweapon_charge_rifle = 84,
  idweapon_devotion = 95,
  idweapon_longbow = 86,
  idweapon_havoc = 87,
  idweapon_eva8 = 89,
  idweapon_flatline = 90,
  idweapon_g7_scout = 91,
  idweapon_hemlock = 92,
  idweapon_kraber = 94,
  idweapon_lstar = 95,
  idweapon_mastiff = 97,
  idweapon_mozambique = 98,
  idweapon_prowler = 103,
  idweapon_peacekeeper = 105,
  idweapon_r99 = 106,
  idweapon_p2020 = 107,
  idweapon_spitfire = 108,
  idweapon_triple_take = 109,
  idweapon_wingman = 111,
  idweapon_volt = 112,
  idweapon_3030_repeater = 113,
  idweapon_car_smg = 114,
  idweapon_nemesis = 115,
  idthrowing_knife = 169,
  idgrenade_thermite = 170,
  idgrenade_frag = 171,
  idgrenade_arc_star = 172,
  idmax
};

typedef struct {
  uint64_t item_id;
  Vector position;
  float distance;
} TreasureClue;