#pragma once
#include "dependencies/std_include.hpp"

#define DOT_PRODUCT(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define ANGLE2SHORT(a) ((int)((a)*(65536/360.0f))&65535)
#define SHORT2ANGLE(a) ((float)((a)*(360.0f/65536)))
#define M_PI 3.14159265358979323846
#define M_PI_DOUBLE ((float)M_PI*2.0f)
#define DEG2RAD(a) ((a)*((float)M_PI/180.0f))
#define RAD2DEG(a) ((a)*(180.0f/(float)M_PI))
#define GET_SIGN(a) ((a) ? ((*(int*)&(a) >> 31) | 1) : 0)
#define VECTOR_COPY(a,b) ((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])

class Vec2 {
public:
	float x, y;

	Vec2() :x(0), y(0) {}
	Vec2(const float x, const float y) : x(x), y(y) {}
	Vec2(const Vec2& v) : x(v.x), y(v.y) {}
	Vec2(const float fl[2]) : x(fl[0]), y(fl[1]) {}

	operator float*() { return &x; }
	operator const float*() const { return &x; }

	bool operator==(const Vec2& v) const { return x == v.x && y == v.y; };
	bool operator!=(const Vec2& v) const { return !(*this == v); };

	Vec2 operator-() const { return Vec2(-x, -y); }
	Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
	Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
	Vec2 operator*(const float fl) const { return Vec2(x * fl, y * fl); }
	Vec2 operator/(const float fl) const { return Vec2(x / fl, y / fl); }

	void operator+=(const Vec2& v) { x += v.x; y += v.y; }
	void operator-=(const Vec2& v) { x -= v.x; y -= v.y; }
	void operator*=(const Vec2& v) { x *= v.x; y *= v.y; }
	void operator*=(const float fl) { x *= fl; y *= fl; }
	void operator/=(const Vec2& v) { x /= v.x; x /= v.y; }

	void set(const float x, const float y) {
		this->x = x;
		this->y = y;
	}

	void rotate(const double deg) {
		const double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}

	void clear() {
		this->x = 0.0f; this->y = 0.0f;
	}

	bool empty() const {
		return this->x == 0.0f && this->y == 0.0f;
	}

	Vec2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0f / length());
		return *this;
	}

	float distance(const Vec2& v) const {
		Vec2 d(x - v.x, y - v.y);
		return d.length();
	}

	float length() const {
		return std::sqrtf(x * x + y * y);
	}
};

class Vec3
{
public:
	float x, y, z;

	Vec3() :x(0), y(0) {}
	Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
	Vec3(const float fl[3]) : x(fl[0]), y(fl[1]), z(fl[3]) {}

	operator float* () { return &x; }
	operator const float* () const { return &x; }

	bool operator==(const Vec3& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const Vec3& v) const { return !(*this == v); }

	Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 operator-() const { return Vec3(-x, -y, -z); }
	Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 operator*(const float fl) const { return Vec3(x * fl, y * fl, z * fl); }
	Vec3 operator/(const float fl) const { return Vec3(x / fl, y / fl, z / fl); }

	void operator += (const Vec3& add) { x += add.x; y += add.y; z += add.z; }
	void operator -= (const Vec3& sub) { x -= sub.x; y -= sub.y; z -= sub.z; }
	void operator *= (const float mul) { x *= mul; y *= mul; z *= mul; }
	void operator /= (const float mul) { x /= mul; y /= mul; z /= mul; }

	void set(const float value) {
		x = value; y = value; z = value;
	}

	Vec3 clear() {
		return {};
	}

	float length() const {
		return std::sqrtf(x * x + y * y + z * z);
	}

	bool empty() const {
		return x == 0.0f && y == 0.0f;
	}

	float dot() const {
		return (x * x + y * y + z * z);
	}

	Vec3 cross_product(const Vec3& other) const {
		return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}

	Vec3& normalized() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float distance(Vec3 v) const {
		Vec3 d(x - v.x, y - v.y, z - v.z);
		return d.length();
	}
};

using LocalClientNum_t = std::uint32_t;
using scr_string_t = std::uint16_t;
using Weapon = std::uint32_t;
using ControllerIndex_t = std::uint32_t;
using ClientNum_t = std::uint32_t;

namespace game
{
	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCOLLMAP = 0x1,
		ASSET_TYPE_XANIMPARTS = 0x2,
		ASSET_TYPE_XMODEL_SURFS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_MATERIAL = 0x5,
		ASSET_TYPE_PIXELSHADER = 0x6,
		ASSET_TYPE_VERTEXSHADER = 0x7,
		ASSET_TYPE_VERTEXDECL = 0x8,
		ASSET_TYPE_TECHNIQUE_SET = 0x9,
		ASSET_TYPE_IMAGE = 0xA,
		ASSET_TYPE_SOUND = 0xB,
		ASSET_TYPE_SOUND_CURVE = 0xC,
		ASSET_TYPE_LOADED_SOUND = 0xD,
		ASSET_TYPE_CLIPMAP_SP = 0xE,
		ASSET_TYPE_CLIPMAP_MP = 0xF,
		ASSET_TYPE_COMWORLD = 0x10,
		ASSET_TYPE_GAMEWORLD_SP = 0x11,
		ASSET_TYPE_GAMEWORLD_MP = 0x12,
		ASSET_TYPE_MAP_ENTS = 0x13,
		ASSET_TYPE_FXWORLD = 0x14,
		ASSET_TYPE_GFXWORLD = 0x15,
		ASSET_TYPE_LIGHT_DEF = 0x16,
		ASSET_TYPE_UI_MAP = 0x17,
		ASSET_TYPE_FONT = 0x18,
		ASSET_TYPE_MENULIST = 0x19,
		ASSET_TYPE_MENU = 0x1A,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x1B,
		ASSET_TYPE_WEAPON = 0x1C,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1D,
		ASSET_TYPE_FX = 0x1E,
		ASSET_TYPE_IMPACT_FX = 0x1F,
		ASSET_TYPE_AITYPE = 0x20,
		ASSET_TYPE_MPTYPE = 0x21,
		ASSET_TYPE_CHARACTER = 0x22,
		ASSET_TYPE_XMODELALIAS = 0x23,
		ASSET_TYPE_RAWFILE = 0x24,
		ASSET_TYPE_STRINGTABLE = 0x25,
		ASSET_TYPE_LEADERBOARD = 0x26,
		ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
		ASSET_TYPE_TRACER = 0x28,
		ASSET_TYPE_VEHICLE = 0x29,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x2A,
		ASSET_TYPE_COUNT = 0x2B,
		ASSET_TYPE_STRING = 0x2B,
		ASSET_TYPE_ASSETLIST = 0x2C,
		ASSET_TYPE_INVALID = -1,
	}; 

	
	enum PlayerDiveState
	{
		DIVE_NONE = 0x0,
		DIVE_FORWARD = 0x1,
		DIVE_FORWARDLEFT = 0x2,
		DIVE_LEFT = 0x3,
		DIVE_BACKLEFT = 0x4,
		DIVE_BACK = 0x5,
		DIVE_BACKRIGHT = 0x6,
		DIVE_RIGHT = 0x7,
		DIVE_FORWARDRIGHT = 0x8,
	};
	
	enum errorParm_t
	{
		ERR_FATAL = 0x0,
		ERR_DROP = 0x1,
		ERR_FROM_STARTUP = 0x2,
		ERR_SERVERDISCONNECT = 0x3,
		ERR_DISCONNECT = 0x4,
		ERR_SCRIPT = 0x5,
		ERR_SCRIPT_DROP = 0x6,
		ERR_LOCALIZATION = 0x7,
	};

	enum svscmd_type
	{
		SV_CMD_CAN_IGNORE = 0x0,
		SV_CMD_RELIABLE = 0x1,
	};

	enum netsrc_t
	{
		NS_CLIENT1 = 0x0,
		NS_SERVER = 0x1,
		NS_MAXCLIENTS = 0x1,
		NS_PACKET = 0x2,
	};

	enum entityType_t
	{
		ET_GENERAL = 0x0,
		ET_PLAYER = 0x1,
		ET_PLAYER_CORPSE = 0x2,
		ET_ITEM = 0x3,
		ET_MISSILE = 0x4,
		ET_INVISIBLE = 0x5,
		ET_SCRIPTMOVER = 0x6,
		ET_SOUND_BLEND = 0x7,
		ET_FX = 0x8,
		ET_LOOP_FX = 0x9,
		ET_PRIMARY_LIGHT = 0xA,
		ET_TURRET = 0xB,
		ET_HELICOPTER = 0xC,
		ET_PLANE = 0xD,
		ET_VEHICLE = 0xE,
		ET_VEHICLE_COLLMAP = 0xF,
		ET_VEHICLE_CORPSE = 0x10,
		ET_VEHICLE_SPAWNER = 0x11
	};

	enum netadrtype_t
	{
		NA_BOT = 0x0,
		NA_BAD = 0x1,
		NA_LOOPBACK = 0x2,
		NA_BROADCAST = 0x3,
		NA_IP = 0x4,
		NA_IPX = 0x5,
		NA_BROADCAST_IPX = 0x6,
	};

	struct GfxDrawSurfFields
	{
		unsigned __int64 objectId : 16;
		unsigned __int64 reflectionProbeIndex : 8;
		unsigned __int64 hasGfxEntIndex : 1;
		unsigned __int64 customIndex : 5;
		unsigned __int64 materialSortedIndex : 12;
		unsigned __int64 prepass : 2;
		unsigned __int64 useHeroLighting : 1;
		unsigned __int64 sceneLightIndex : 8;
		unsigned __int64 surfType : 4;
		unsigned __int64 primarySortKey : 6;
		unsigned __int64 unused : 1;
	};

	struct shellshock_parms_t
	{
		int blurBlendFadeTime;
		int blurBlendTime;
		int whiteFadeTime;
		int shotFadeTime;
		int screenType;
		int unknown_int3000;
		float viewKickPeriod;
		float viewKickRadius;
		bool shockSound;
		char sfString[31];
	};

	struct shellshock_t
	{
		shellshock_parms_t params[4];
		char unknown0[36];
		int soundFadeInTime;
		int soundFadeOutTime;
		float soundDryLevel;
		float soundWetLevel;
		char soundRoomType[16];
		char unknown1[256];
		int soundModEndDelay;
		int soundLoopFadeTime;
		int soundLoopEndDelay;
		bool lookControl;
		int lookControlFadeTime;
		float lcMouseSensitivityScale;
		float lcMaxPitchSpeed;
		float lcMaxYawSpeed;
		bool shockMovement;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		unsigned __int64 packed;
	}; 
	
	struct MaterialInfo
	{
		const char *name;
		char gameFlags;
		char sortKey;
		char textureAtlasRowCount;
		char textureAtlasColumnCount;
		GfxDrawSurf drawSurf;
		unsigned int surfaceTypeBits;
		unsigned __int16 hashIndex;
	};

	struct MaterialStreamRouting
	{
		char source;
		char dest;
	};

	struct MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[13];
		IDirect3DVertexDeclaration9 *decl[16];
	};

	struct MaterialVertexDeclaration
	{
		const char *name;
		char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
	};

	struct GfxVertexShaderLoadDef
	{
		unsigned int *program;
		unsigned __int16 programSize;
		unsigned __int16 loadForRenderer;
	};

	struct MaterialVertexShaderProgram
	{
		IDirect3DVertexShader9 *vs;
		GfxVertexShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char *name;
		MaterialVertexShaderProgram prog;
	};

	struct GfxPixelShaderLoadDef
	{
		unsigned int *program;
		unsigned __int16 programSize;
		unsigned __int16 loadForRenderer;
	};

	struct MaterialPixelShaderProgram
	{
		IDirect3DPixelShader9 *ps;
		GfxPixelShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char *name;
		MaterialPixelShaderProgram prog;
	};

	struct MaterialArgumentCodeConst
	{
		unsigned __int16 index;
		char firstRow;
		char rowCount;
	};

	union MaterialArgumentDef
	{
		const float *literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	struct MaterialShaderArgument
	{
		unsigned __int16 type;
		unsigned __int16 dest;
		MaterialArgumentDef u;
	};

	struct MaterialPass
	{
		MaterialVertexDeclaration *vertexDecl;
		MaterialVertexShader *vertexShader;
		MaterialPixelShader *pixelShader;
		char perPrimArgCount;
		char perObjArgCount;
		char stableArgCount;
		char customSamplerFlags;
		MaterialShaderArgument *args;
	};

	struct MaterialTechnique
	{
		const char *name;
		unsigned __int16 flags;
		unsigned __int16 passCount;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char *name;
		char worldVertFormat;
		bool hasBeenUploaded;
		char unused[1];
		MaterialTechniqueSet *remappedTechniqueSet;
		MaterialTechnique *techniques[48];
	};

	struct GfxImageLoadDefIW3
	{
		char levelCount;
		char flags;
		__int16 dimensions[3];
		int format;
		int resourceSize;
		char data[1];
	};

	struct __declspec(align(4)) GfxImageLoadDef
	{
		char levelCount;
		char pad[3];
		int flags;
		int format;
		int resourceSize;
		char data[1];
	};

	union GfxTexture
	{
		IDirect3DBaseTexture9 *basemap;
		IDirect3DTexture9 *map;
		IDirect3DVolumeTexture9 *volmap;
		IDirect3DCubeTexture9 *cubemap;
		GfxImageLoadDef *loadDef;
	};

	struct Picmip
	{
		char platform[2];
	};

	struct CardMemory
	{
		int platform[2];
	};

	struct GfxImage
	{
		GfxTexture texture;
		char mapType;
		char semantic;
		char category;
		bool useSrgbReads;
		Picmip picmip;
		bool noPicmip;
		char track;
		CardMemory cardMemory;
		unsigned __int16 width;
		unsigned __int16 height;
		unsigned __int16 depth;
		bool delayLoadPixels;
		const char *name;
	};

	struct WaterWritable
	{
		float floatTime;
	};

	struct complex_s
	{
		float real;
		float imag;
	};

	struct water_t
	{
		WaterWritable writable;
		complex_s *H0;
		float *wTerm;
		int M;
		int N;
		float Lx;
		float Lz;
		float gravity;
		float windvel;
		float winddir[2];
		float amplitude;
		float codeConstant[4];
		GfxImage *image;
	};

	union MaterialTextureDefInfo
	{
		GfxImage *image;
		water_t *water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		char samplerState;
		char semantic;
		MaterialTextureDefInfo u;
	};

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	};

	struct GfxStateBits
	{
		unsigned int loadBits[2];
	};

	struct Material
	{
		MaterialInfo info;
		char stateBitsEntry[48];
		char textureCount;
		char constantCount;
		char stateBitsCount;
		char stateFlags;
		char cameraRegion;
		MaterialTechniqueSet *techniqueSet;
		MaterialTextureDef *textureTable;
		MaterialConstantDef *constantTable;
		GfxStateBits *stateBitsTable;
	};

	union XAssetHeader
	{
		void *data;
		void *physPreset;
		void *physCollmap;
		void *parts;
		void *modelSurfs;
		void *model;
		Material *material;
		MaterialPixelShader *pixelShader;
		MaterialVertexShader *vertexShader;
		MaterialVertexDeclaration *vertexDecl;
		MaterialTechniqueSet *techniqueSet;
		GfxImage *image;
	};

	enum MaterialTechniqueType
	{
		TECHNIQUE_DEPTH_PREPASS = 0x0,
		TECHNIQUE_BUILD_FLOAT_Z = 0x1,
		TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 0x2,
		TECHNIQUE_BUILD_SHADOWMAP_COLOR = 0x3,
		TECHNIQUE_UNLIT = 0x4,
		TECHNIQUE_EMISSIVE = 0x5,
		TECHNIQUE_EMISSIVE_DFOG = 0x6,
		TECHNIQUE_EMISSIVE_SHADOW = 0x7,
		TECHNIQUE_EMISSIVE_SHADOW_DFOG = 0x8,
		TECHNIQUE_LIT_BEGIN = 0x9,
		TECHNIQUE_LIT = 0x9,
		TECHNIQUE_LIT_DFOG = 0xA,
		TECHNIQUE_LIT_SUN = 0xB,
		TECHNIQUE_LIT_SUN_DFOG = 0xC,
		TECHNIQUE_LIT_SUN_SHADOW = 0xD,
		TECHNIQUE_LIT_SUN_SHADOW_DFOG = 0xE,
		TECHNIQUE_LIT_SPOT = 0xF,
		TECHNIQUE_LIT_SPOT_DFOG = 0x10,
		TECHNIQUE_LIT_SPOT_SHADOW = 0x11,
		TECHNIQUE_LIT_SPOT_SHADOW_DFOG = 0x12,
		TECHNIQUE_LIT_OMNI = 0x13,
		TECHNIQUE_LIT_OMNI_DFOG = 0x14,
		TECHNIQUE_LIT_OMNI_SHADOW = 0x15,
		TECHNIQUE_LIT_OMNI_SHADOW_DFOG = 0x16,
		TECHNIQUE_LIT_INSTANCED = 0x17,
		TECHNIQUE_LIT_INSTANCED_DFOG = 0x18,
		TECHNIQUE_LIT_INSTANCED_SUN = 0x19,
		TECHNIQUE_LIT_INSTANCED_SUN_DFOG = 0x1A,
		TECHNIQUE_LIT_INSTANCED_SUN_SHADOW = 0x1B,
		TECHNIQUE_LIT_INSTANCED_SUN_SHADOW_DFOG = 0x1C,
		TECHNIQUE_LIT_INSTANCED_SPOT = 0x1D,
		TECHNIQUE_LIT_INSTANCED_SPOT_DFOG = 0x1E,
		TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW = 0x1F,
		TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW_DFOG = 0x20,
		TECHNIQUE_LIT_INSTANCED_OMNI = 0x21,
		TECHNIQUE_LIT_INSTANCED_OMNI_DFOG = 0x22,
		TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW = 0x23,
		TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW_DFOG = 0x24,
		TECHNIQUE_LIT_END = 0x25,
		TECHNIQUE_LIGHT_SPOT = 0x25,
		TECHNIQUE_LIGHT_OMNI = 0x26,
		TECHNIQUE_LIGHT_SPOT_SHADOW = 0x27,
		TECHNIQUE_FAKELIGHT_NORMAL = 0x28,
		TECHNIQUE_FAKELIGHT_VIEW = 0x29,
		TECHNIQUE_SUNLIGHT_PREVIEW = 0x2A,
		TECHNIQUE_CASE_TEXTURE = 0x2B,
		TECHNIQUE_WIREFRAME_SOLID = 0x2C,
		TECHNIQUE_WIREFRAME_SHADED = 0x2D,
		TECHNIQUE_DEBUG_BUMPMAP = 0x2E,
		TECHNIQUE_DEBUG_BUMPMAP_INSTANCED = 0x2F,
		TECHNIQUE_COUNT = 0x30,
		TECHNIQUE_TOTAL_COUNT = 0x31,
		TECHNIQUE_NONE = 0x32,
	}; 
	
	enum MaterialVertexDeclType
	{
		VERTDECL_GENERIC = 0x0,
		VERTDECL_PACKED = 0x1,
		VERTDECL_WORLD = 0x2,
		VERTDECL_WORLD_T1N0 = 0x3,
		VERTDECL_WORLD_T1N1 = 0x4,
		VERTDECL_WORLD_T2N0 = 0x5,
		VERTDECL_WORLD_T2N1 = 0x6,
		VERTDECL_WORLD_T2N2 = 0x7,
		VERTDECL_WORLD_T3N0 = 0x8,
		VERTDECL_WORLD_T3N1 = 0x9,
		VERTDECL_WORLD_T3N2 = 0xA,
		VERTDECL_WORLD_T4N0 = 0xB,
		VERTDECL_WORLD_T4N1 = 0xC,
		VERTDECL_WORLD_T4N2 = 0xD,
		VERTDECL_POS_TEX = 0xE,
		VERTDECL_STATICMODELCACHE = 0xF,
		VERTDECL_COUNT = 0x10,
	};

	struct $A6DFE8F2BEFD3E7315B44D22E582538B
	{
		unsigned int stride;
		IDirect3DVertexBuffer9 *vb;
		unsigned int offset;
	}; 
	
	struct GfxCmdBufPrimState
	{
		IDirect3DDevice9 *device;
		IDirect3DIndexBuffer9 *indexBuffer;
		MaterialVertexDeclType vertDeclType;
		$A6DFE8F2BEFD3E7315B44D22E582538B streams[2];
		IDirect3DVertexDeclaration9 *vertexDecl;
	}; 

	enum GfxDepthRangeType
	{
		GFX_DEPTH_RANGE_SCENE = 0x0,
		GFX_DEPTH_RANGE_VIEWMODEL = 0x2,
		GFX_DEPTH_RANGE_FULL = 0xFFFFFFFF,
	};
	
	struct GfxViewport
	{
		int x;
		int y;
		int width;
		int height;
	}; 
	
	enum GfxRenderTargetId
	{
		R_RENDERTARGET_SAVED_SCREEN = 0x0,
		R_RENDERTARGET_FRAME_BUFFER = 0x1,
		R_RENDERTARGET_SCENE = 0x2,
		R_RENDERTARGET_RESOLVED_POST_SUN = 0x3,
		R_RENDERTARGET_RESOLVED_SCENE = 0x4,
		R_RENDERTARGET_FLOAT_Z = 0x5,
		R_RENDERTARGET_PINGPONG_0 = 0x6,
		R_RENDERTARGET_PINGPONG_1 = 0x7,
		R_RENDERTARGET_POST_EFFECT_0 = 0x8,
		R_RENDERTARGET_POST_EFFECT_1 = 0x9,
		R_RENDERTARGET_SHADOWMAP_LARGE = 0xA,
		R_RENDERTARGET_SHADOWMAP_SMALL = 0xB,
		R_RENDERTARGET_COUNT = 0xC,
		R_RENDERTARGET_NONE = 0xD,
	}; 
	
	struct /*__declspec(align(16))*/ GfxCmdBufState
	{
		char refSamplerState[16];
		unsigned int samplerState[16];
		GfxTexture *samplerTexture[16];
		GfxCmdBufPrimState prim;
		Material *material;
		MaterialTechniqueType techType;
		MaterialTechnique *technique;
		MaterialPass *pass;
		unsigned int passIndex;
		GfxDepthRangeType depthRangeType;
		float depthRangeNear;
		float depthRangeFar;
		unsigned __int64 vertexShaderConstState[64];
		unsigned __int64 pixelShaderConstState[256];
		char alphaRef;
		unsigned int refStateBits[2];
		unsigned int activeStateBits[2];
		MaterialPixelShader *pixelShader;
		MaterialVertexShader *vertexShader;
		unsigned int scissorX;
		unsigned int scissorY;
		unsigned int scissorW;
		unsigned int scissorH;
		unsigned int pixPrimarySortKey;
		unsigned int pixSceneLightIndex;
		Material *pixMaterial;
		MaterialTechnique *pixTechnique;
		int pixCombine;
		GfxViewport viewport;
		GfxRenderTargetId renderTargetId;
		Material *origMaterial;
		MaterialTechniqueType origTechType;
	};

	struct GfxCmdBufContext
	{
		/*GfxCmdBufSourceState*/ void *source;
		GfxCmdBufState *state;
	};
	
	struct in_addr_t
	{
		union
		{
			std::uint8_t ip[4];
			std::uint32_t inaddr;
		};

		std::uint16_t port;
	}; 
	
	struct XNADDR
	{
		char pad[0x4];
		in_addr_t addr;
		char pad2[0x16];

		const std::string to_string(bool include_port = false) const
		{
			const auto addr = this->addr;
			return include_port ? utils::string::va("%u.%u.%u.%u:%u", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3], addr.port) : utils::string::va("%u.%u.%u.%u", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3]);
		}
	};

	struct netadr_t
	{
		netadrtype_t type;
		in_addr_t addr;
		char pad[0x6];

		const std::string to_string(bool include_port = false) const
		{
			const auto addr = this->addr;
			return include_port ? utils::string::va("%u.%u.%u.%u:%u", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3], htons(addr.port)) : utils::string::va("%u.%u.%u.%u", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3]);
		}
	};

#pragma pack(push, 1)
	struct bdSecurityID
	{
		std::uint64_t id;
	};
#pragma pack(pop)

	struct bdSecurityKey
	{
		char ab[16];
	};

	struct XSESSION_INFO
	{
		bdSecurityID sessionID;
		XNADDR hostAddress;
		bdSecurityKey keyExhangeKey;
	};

	struct msg_t 
	{
		int overflowed;
		int readOnly;
		char* data;
		char* splitData;
		int maxsize;
		int cursize;
		int splitSize;
		int readcount;
		int bit;
		int lastEntityRef;
		int scrambleBuf;
		int length;
	};

#pragma pack(push, 1)
	struct PartyHostDetails
	{
		char pad[0x4];
		game::netadr_t adr;
		XSESSION_INFO sessionInfo;
		int lastPacketTime;
		int lastPacketSentTime;
		int numPrivateSlots;
		int numPublicSlots;
		int hostNum;
		bool accepted;
		int challenge;
		char pad4[0x3];
	};
#pragma pack(pop)

	struct PartyMember
	{
		std::uint8_t status;
		bool headsetPresent;
		char gamertag[32];
		char clanAbbrev[5];
		char pad2[0x16];
		XNADDR xnaddr;
		char pad3[0x48];
		std::uint64_t player;
		char pad4[0x28];
	};

#pragma pack(push, 4)
	struct ClientInfo
	{
		std::uint64_t xuid;
		char pad[0x4];
		netadr_t addr;
		int voiceConnectivityBits;
		char pad2[0x12];
	};
#pragma pack(pop)

	struct SessionDynamicData
	{
		char pad[0x1D4];
		XSESSION_INFO sessionInfo;
		bool sessionStartCalled;
		char pad2[0x8];
		int privateSlots;
		int publicSlots;
		int flags;
		char pad4[0xC];
		ClientInfo users[18];
	};

	struct SessionStaticData
	{
		char* sessionName;
	};

	struct SessionData
	{
		SessionStaticData staticData;
		SessionDynamicData dyn;
	};

	struct PartyData_s
	{
		SessionData *session;
		char pad[0xF4];
		PartyMember partyMembers[18];
		char pad2[0x634];
		PartyHostDetails currentHost;
		PartyHostDetails potentialHost;
		char pad3[0x24];
		int areWeHost;
		int joiningAnotherParty;
		char pad4[0x4];
		int inParty;
		int party_systemActive;
		char pad5[0x44];
		int partyID;
		char pad6[0xB9C];

		bool is_running() const
		{
			return party_systemActive == 1;
		}

		bool in_party() const
		{
			return is_running() && inParty;
		}

		bool are_we_host() const
		{
			return areWeHost && inParty;
		}

		bool is_user_registered(const int index) const
		{
			if (index >= 0 && index < 18)
			{
				return partyMembers[index].status > 2
					&& reinterpret_cast<bool(*)(void*, size_t)>(0x00621340)(this->session, index);
			}

			return false;
		}
	};

	struct netchan_t
	{
		int outgoingSequence;
		netsrc_t sock;
		int dropped;
		int incomingSequence;
		netadr_t remoteAddress;
		int qport;
		int fragmentSequence;
		int fragmentLength;
		char *fragmentBuffer;
		int fragmentBufferSize;
		int unsentFragments;
		int unsetFragmentStart;
		int unsentLength;
		char* unsentBuffer;
		int unsentBufferSize;
		char pad2[0x05E0];
	};

	enum ViewLockTypes
	{
		PLAYERVIEWLOCK_NONE = 0x0,
		PLAYERVIEWLOCK_FULL = 0x1,
		PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
		PLAYERVIEWLOCKCOUNT = 0x3,
	}; 
	
	struct SprintState
	{
		int sprintButtonUpRequired;
		int sprintDelay;
		int lastSprintStart;
		int lastSprintEnd;
		int sprintStartMaxLength;
	}; 
	
	struct MantleState
	{
		float yaw;
		int timer;
		int transIndex;
		int flags;
	}; 
	
	struct PlayerActiveWeaponState
	{
		int weapAnim;
		int weaponTime;
		int weaponDelay;
		int weaponRestrictKickTime;
		int weaponState;
		int weapHandFlags;
		unsigned int weaponShotCount;
	};

	struct PlayerEquippedWeaponState
	{
		bool usedBefore;
		bool dualWielding;
		char weaponModel;
		bool needsRechamber[2];
	};

	enum OffhandClass
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_OTHER = 0x5,
		OFFHAND_CLASS_COUNT = 0x6,
	}; 

	enum PlayerHandIndex
	{
		WEAPON_HAND_RIGHT = 0x0,
		WEAPON_HAND_LEFT = 0x1,
		NUM_WEAPON_HANDS = 0x2,
		WEAPON_HAND_DEFAULT = 0x0,
	};

	struct GlobalAmmo
	{
		int ammoType;
		int ammoCount;
	};

	struct ClipAmmo
	{
		int clipIndex;
		int ammoCount[2];
	};
	
	struct PlayerWeaponCommonState
	{
		int offHandIndex;
		OffhandClass offhandPrimary;
		OffhandClass offhandSecondary;
		unsigned int weapon;
		unsigned int primaryWeaponForAltMode;
		int weapFlags;
		float fWeaponPosFrac;
		float aimSpreadScale;
		int adsDelayTime;
		int spreadOverride;
		int spreadOverrideState;
		PlayerHandIndex lastWeaponHand;
		GlobalAmmo ammoNotInClip[15];
		ClipAmmo ammoInClip[15];
		int weapLockFlags;
		int weapLockedEntnum;
		float weapLockedPos[3];
		int weaponIdleTime;
	};
	
	enum ActionSlotType
	{
		ACTIONSLOTTYPE_DONOTHING = 0x0,
		ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
		ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
		ACTIONSLOTTYPE_NIGHTVISION = 0x3,
		ACTIONSLOTTYPECOUNT = 0x4,
	};

	enum
	{
		FL_GODMODE = 0x1,
		FL_DEMI_GODMODE = 0x2,
		FL_NOTARGET = 0x4,
		FL_NO_KNOCKBACK = 0x8,
		FL_DROPPED_ITEM = 0x10,
		FL_NO_BOTS = 0x20,
		FL_NO_HUMANS = 0x40,
		FL_TOGGLE = 0x80,
		FL_SOFTACTIVATE = 0x100,
		FL_PARACHUTE = 0x200,
		FL_NO_HEADCHECK = 0x400,
		FL_SUPPORTS_LINKTO = 0x1000,
		FL_NO_AUTO_ANIM_UPDATE = 0x2000,
		FL_GRENADE_TOUCH_DAMAGE = 0x4000,
		FL_MISSILE_DESTABILIZED = 0x10000,
		FL_STABLE_MISSILES = 0x20000,
		FL_REPEAT_ANIM_UPDATE = 0x40000,
	};

	struct ActionSlotParam_SpecifyWeapon
	{
		unsigned int index;
	};

	struct ActionSlotParam
	{
		ActionSlotParam_SpecifyWeapon specifyWeapon;
	};

	enum objectiveState_t
	{
		OBJST_EMPTY = 0x0,
		OBJST_ACTIVE = 0x1,
		OBJST_INVISIBLE = 0x2,
		OBJST_DONE = 0x3,
		OBJST_CURRENT = 0x4,
		OBJST_FAILED = 0x5,
		OBJST_NUMSTATES = 0x6,
	};
	
	struct objective_t
	{
		objectiveState_t state;
		float origin[3];
		int entNum;
		int teamNum;
		int icon;
	};

	enum he_type_t
	{
		HE_TYPE_FREE = 0x0,
		HE_TYPE_TEXT = 0x1,
		HE_TYPE_VALUE = 0x2,
		HE_TYPE_PLAYERNAME = 0x3,
		HE_TYPE_MAPNAME = 0x4,
		HE_TYPE_GAMETYPE = 0x5,
		HE_TYPE_MATERIAL = 0x6,
		HE_TYPE_TIMER_DOWN = 0x7,
		HE_TYPE_TIMER_UP = 0x8,
		HE_TYPE_TIMER_STATIC = 0x9,
		HE_TYPE_TENTHS_TIMER_DOWN = 0xA,
		HE_TYPE_TENTHS_TIMER_UP = 0xB,
		HE_TYPE_TENTHS_TIMER_STATIC = 0xC,
		HE_TYPE_CLOCK_DOWN = 0xD,
		HE_TYPE_CLOCK_UP = 0xE,
		HE_TYPE_WAYPOINT = 0xF,
		HE_TYPE_COUNT = 0x10,
	};

	struct hud_color
	{
		char r;
		char g;
		char b;
		char a;
	};

	union hudelem_color_t
	{
		hud_color __s0;
		int rgba;
	};

	struct hudelem_s
	{
		he_type_t type;
		float x;
		float y;
		float z;
		int targetEntNum;
		float fontScale;
		float fromFontScale;
		int fontScaleStartTime;
		int fontScaleTime;
		int font;
		int alignOrg;
		int alignScreen;
		hudelem_color_t color;
		hudelem_color_t fromColor;
		int fadeStartTime;
		int fadeTime;
		int label;
		int width;
		int height;
		int materialIndex;
		int fromWidth;
		int fromHeight;
		int scaleStartTime;
		int scaleTime;
		float fromX;
		float fromY;
		int fromAlignOrg;
		int fromAlignScreen;
		int moveStartTime;
		int moveTime;
		int time;
		int duration;
		float value;
		int text;
		float sort;
		hudelem_color_t glowColor;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int soundID;
		int flags;
	};

	struct $3EB5F037EADAEE8E2FA2A1F9FFF31312
	{
		hudelem_s current[31];
		hudelem_s archival[31];
	}; 
	
	struct playerState_s
	{
		int commandTime;
		int pm_type;
		int pm_time;
		int pm_flags;
		int otherFlags;
		int linkFlags;
		int bobCycle;
		Vec3 origin;
		Vec3 velocity;
		int grenadeTimeLeft;
		int throwbackGrenadeOwner;
		int throwbackGrenadeTimeLeft;
		unsigned int throwbackWeaponIndex;
		int remoteEyesEnt;
		int remoteEyesTagname;
		int remoteControlEnt;
		int foliageSoundTime;
		int gravity;
		float leanf;
		int speed;
		float delta_angles[3];
		int groundEntityNum;
		float vLadderVec[3];
		int jumpTime;
		float jumpOriginZ;
		int legsTimer;
		int legsAnim;
		int torsoTimer;
		int torsoAnim;
		int legsAnimDuration;
		int torsoAnimDuration;
		int damageTimer;
		int damageDuration;
		int flinchYawAnim;
		int corpseIndex;
		int movementDir;
		int eFlags;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		int oldEventSequence;
		int unpredictableEventSequence;
		int unpredictableEventSequenceOld;
		int unpredictableEvents[4];
		unsigned int unpredictableEventParms[4];
		int clientNum;
		int viewmodelIndex;
		float viewangles[3];
		int viewHeightTarget;
		float viewHeightCurrent;
		int viewHeightLerpTime;
		int viewHeightLerpTarget;
		int viewHeightLerpDown;
		float viewAngleClampBase[2];
		float viewAngleClampRange[2];
		int damageEvent;
		int damageYaw;
		int damagePitch;
		int damageCount;
		int damageFlags;
		int stats[4];
		float proneDirection;
		float proneDirectionPitch;
		float proneTorsoPitch;
		ViewLockTypes viewlocked;
		int viewlocked_entNum;
		float linkAngles[3];
		float linkWeaponAngles[3];
		int linkWeaponEnt;
		int loopSound;
		int cursorHint;
		int cursorHintString;
		int cursorHintEntIndex;
		int cursorHintDualWield;
		int iCompassPlayerInfo;
		int radarEnabled;
		int radarBlocked;
		int radarMode;
		int locationSelectionInfo;
		SprintState sprintState;
		float holdBreathScale;
		int holdBreathTimer;
		float moveSpeedScaleMultiplier;
		MantleState mantleState;
		PlayerActiveWeaponState weapState[2];
		unsigned int weaponsEquipped[15];
		PlayerEquippedWeaponState weapEquippedData[15];
		PlayerWeaponCommonState weapCommon;
		float meleeChargeYaw;
		int meleeChargeDist;
		int meleeChargeTime;
		unsigned int perks[2];
		unsigned int perkSlots[8];
		ActionSlotType actionSlotType[4];
		ActionSlotParam actionSlotParam[4];
		int weaponHudIconOverrides[6];
		int animScriptedType;
		int shellshockIndex;
		int shellshockTime;
		int shellshockDuration;
		float dofNearStart;
		float dofNearEnd;
		float dofFarStart;
		float dofFarEnd;
		float dofNearBlur;
		float dofFarBlur;
		float dofViewmodelStart;
		float dofViewmodelEnd;
		objective_t objective[32];
		int deltaTime;
		int killCamEntity;
		int killCamLookAtEntity;
		int killCamClientNum;
		$3EB5F037EADAEE8E2FA2A1F9FFF31312 hud;
		unsigned int partBits[6];
		int recoilScale;
		int diveDirection;
		int stunTime;
	};

	enum team_t
	{
		TEAM_FREE,
		TEAM_AXIS,
		TEAM_ALLIES,
		TEAM_SPECTATOR,
		TEAM_NUM_TEAMS
	};
	
	struct IWSteamClient
	{
		char pad0[0xA4];
		XNADDR xnaddr;
	};

	struct snapshot_s
	{
		playerState_s ps;
		int snapFlags;
		int ping;
		int serverTime;
		char pad[0x308C4];
	};

	struct animation_s
	{
		char name[64];
		int initialLerp;
		float moveSpeed;
		int duration;
		int nameHash;
		int flags;
		int64_t movetype;
		int noteType;
	}; 
	
	struct lerpFrame_t
	{
		float yawAngle;
		int yawing;
		float pitchAngle;
		int pitching;
		int animationNumber;
		animation_s* animation;
		int animationTime;
		float oldFramePos[3];
		float animSpeedScale;
		int oldFrameSnapshotTime;
	}; 
	
	struct clientControllers_t
	{
		float angles[4][3];
		float tag_origin_angles[3];
		float tag_origin_offset[3];
	}; 
	
	struct clientInfo_t
	{
		int infoValid;
		int nextValid;
		int clientNum;
		char name[16];
		team_t team;
		team_t oldteam;
		int rank;
		int prestige;
		unsigned int perks[2];
		int score;
		int location;
		int health;
		char model[64];
		char attachModelNames[6][64];
		char attachTagNames[6][64];
		unsigned int partBits[6];
		lerpFrame_t legs;
		lerpFrame_t torso;
		float lerpMoveDir;
		float lerpLean;
		float playerAngles[3];
		int legsAnim;
		int torsoAnim;
		float fTorsoPitch;
		float fWaistPitch;
		int leftHandGun;
		int dobjDirty;
		clientControllers_t control;
		unsigned int clientConditions[18][2];
		void* pXAnimTree;
		int iDObjWeapon;
		char weaponModel;
		int stanceTransitionTime;
		int turnAnimEndTime;
		char turnAnimType;
		bool hideWeapon;
		bool usingKnife;
		int dualWielding;
		PlayerDiveState diveState;
		int riotShieldNext;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
	};
	
	struct refdef_t
	{
		int x;
		int y;
		int	width;
		int	height;
		float tanHalfFovX;
		float tanHalfFovY;
		Vec3 viewOrg;
		Vec3 viewAxis[3];
		char pad0[0x3F18];
	}; 

	struct trajectory_t
	{
		int trType;
		int trTime;
		int trDuration;
		Vec3 trBase;
		Vec3 trDelta;
	}; 
	
	struct LerpEntityState
	{
		trajectory_t pos;
		trajectory_t apos;
		char pad[0x4];
	}; 
	
	struct centity_t
	{
		short currentValid;
		short grenadeValid;
		char pad0[0x014];
		Vec3 origin;
		Vec3 angles;
		char pad1[0x03C];
		int zooming;
		char pad2[0x0C];
		Vec3 origin2;
		char pad3[0x054];
		int number;
		int type;
		int flags;
		char pad4[0x0C];
		Vec3 origin3;
		char pad5[0x06C];
		int pickup;
		int number2;
		char pad6[0x034];
		short weapon;
		char pad7[0x02];
		short weapon2;
		char pad8[0x02E];
		int alive;
		char pad9[0x020];
		int number3;

		auto& prev_state() const {
			return *reinterpret_cast<LerpEntityState*>(reinterpret_cast<uintptr_t>(this) + 0x74);
		}

		auto& next_state() const {
			return *reinterpret_cast<LerpEntityState*>(reinterpret_cast<uintptr_t>(this) + 0xF0);
		}

		bool is_alive() const {
			return alive & 1;
		}
	};
	
	struct cg_t
	{
	private:
		std::uintptr_t get_base() const {
			return std::uintptr_t(this);
		}

		template<typename T> T& get(std::uintptr_t offset) const {
			return *reinterpret_cast<T*>(get_base() + offset);
		}
	public:
		playerState_s predictedPlayerState;
		char pad[0x024C];
		int latestSnapshotNum;
		int latestSnapShotTime;
		snapshot_s* snap;
		snapshot_s* nextSnap;
		snapshot_s activeSnapshots[2];
		float frameInterpolation;
		int frameTime;
		int time;
		int oldTime;
		char pad2[0x08];
		bool renderingThirdPerson;
		char pad3[0x0F];
		refdef_t refdef;
		Vec3 refdefViewAngles;
		char pad4[0x57BC];
		bool zooming;
		char pad5[0x3B];
		Vec3 gunAngles;
		char pad6[0x00082B28];
		clientInfo_t clients[18];
		char pad7[0x0BDC];
		float aimSpreadScale;
		char pad8[0x0428];

		auto in_killcam() const {
			return get<bool>(0x73FF0);
		}

		auto& v_dmg_pitch() const {
			return get<float>(0x73EAC);
		}

		auto& v_dmg_roll() const {
			return get<float>(0x73EB0);
		}
	};

#pragma pack(push, 4)
	struct usercmd_s
	{
		int serverTime;
		int buttons;
		int angles[3];
		unsigned short weapon;
		unsigned short primaryWeaponForAltMode;
		unsigned short offHandIndex;
		char forwardmove;
		char rightmove;
		float meleeChargeYaw;
		char meleeChargeDist;
		char selectedLoc[2];
		char selectedLocAngle;
		char remoteControlAngles[2];
	};
#pragma pack(pop)

	struct clientLinkInfo_t
	{
		__int16 parentId;
		char tagName;
		char flags;
	}; 
	
	struct entityState_s
	{
		int number;
		int eType;
		char lerp[0x70];
		int time2;
		int otherEntityNum;
		int attackerEntityNum;
		int groundEntityNum;
		int loopSound;
		int surfType;

		union
		{
			int brushModel;
			int triggerModel;
			int item;
			int xmodel;
			int primaryLight;
		} index;

		int clientNum;
		int iHeadIcon;
		int iHeadIconTeam;
		int solid;
		unsigned int eventParm;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		unsigned __int16 weapon;
		int legsAnim;
		int torsoAnim;
		int un1;
		int un2;
		clientLinkInfo_t clientLinkInfo;
		unsigned int partBits[6];
		int clientMask[1];
	}; 
	
	struct clSnapshot_t
	{
		playerState_s ps;
		int valid;
		int snapFlags;
		int serverTime;
		int messageNum;
		int deltaNum;
		int ping;
		int cmdNum;
		int numEntities;
		int numClients;
		int parseEntitiesIndex;
		int parseClientsIndex;
		int serverCommandNum;
	}; 

	enum StanceState
	{
		CL_STANCE_STAND = 0x0,
		CL_STANCE_CROUCH = 0x1,
		CL_STANCE_PRONE = 0x2,
	};

	struct ClientArchiveData
	{
		int serverTime;
		float origin[3];
		float velocity[3];
		int bobCycle;
		int movementDir;
		float viewangles[3];
		int locationSelectionInfo;
		float selectedLocation[2];
		float selectedLocationAngle;
	};

	struct outPacket_t
	{
		int p_cmdNumber;
		int p_serverTime;
		int p_realtime;
	};

	struct clientState_s
	{
		int clientIndex;
		team_t team;
		int modelindex;
		int dualWielding;
		int riotShieldNext;
		int attachModelIndex[6];
		int attachTagIndex[6];
		char name[16];
		float maxSprintTimeMultiplier;
		int rank;
		int prestige;
		unsigned int perks[2];
		int diveState;
		int voiceConnectivityBits;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
	};
	
	struct clientActive_t
	{
		bool usingAds;
		int timeoutcount;
		clSnapshot_t snap;
		bool alwaysFalse;
		int serverTime;
		int oldServerTime;
		int oldFrameServerTime;
		int serverTimeDelta;
		int oldSnapServerTime;
		int extrapolatedSnapshot;
		int newSnapshots;
		int serverId;
		char mapname[64];
		int parseEntitiesIndex;
		int parseClientsIndex;
		int mouseDx[2];
		int mouseDy[2];
		int mouseIndex;
		bool stanceHeld;
		StanceState stance;
		StanceState stancePosition;
		int stanceTime;
		int cgameUserCmdWeapon;
		int cgameUserCmdOffHandIndex;
		float cgameFOVSensitivityScale;
		float cgameMaxPitchSpeed;
		float cgameMaxYawSpeed;
		Vec3 cgameKickAngles;
		Vec3 cgameOrigin;
		Vec3 cgameVelocity;
		Vec3 cgameViewangles;
		int cgameBobCycle;
		int cgameMovementDir;
		int cgameExtraButtons;
		int cgamePredictedDataServerTime;
		Vec3 clViewangles;
		usercmd_s cmds[128];
		int cmdNumber;
		ClientArchiveData clientArchive[256];
		int clientArchiveIndex;
		int packetBackupCount;
		int packetBackupMask;
		int parseEntitiesCount;
		int parseClientsCount;
		outPacket_t outPackets[32];
		clSnapshot_t snapshots[32];
		entityState_s parseEntities[19200];
		clientState_s parseClients[576];
		int corruptedTranslationFile;
		char translationVersion[256];

		usercmd_s* get_user_cmd(const size_t i)
		{
			return &cmds[i & 0x7F];
		}
	}; 

	enum sessionState_t : int
	{
		SESS_STATE_PLAYING = 0x0,
		SESS_STATE_DEAD = 0x1,
		SESS_STATE_SPECTATOR = 0x2,
		SESS_STATE_INTERMISSION = 0x3,
	}; 
	
	enum clientConnected_t
	{
		CON_DISCONNECTED = 0x0,
		CON_CONNECTING = 0x1,
		CON_CONNECTED = 0x2,
	};

	struct playerTeamState_t
	{
		int location;
	};
	
	struct clientSession_t
	{
		sessionState_t sessionState;
		int uknown6;
		int score;
		int deaths;
		int kills;
		int assists;
		unsigned short scriptPersID;
		unsigned short undefined;
		clientConnected_t connected;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int localClient;
		int predictItemPickup;
		char newnetname[32];
		int maxHealth;
		int enterTime;
		playerTeamState_t teamState;
		int voteCount;
		int teamVoteCount;
		float moveSpeedScaleMultiplier;
		int viewmodelIndex;
		int noSpectate;
		int teamInfo;
		clientState_s cs;
		char pad[0x10];
		int psOffsetTime;
		int hasRadar;
		int isRadarBlocked;
		char pad2[0x124];
	};

	struct gclient_s
	{
		playerState_s ps;
		clientSession_t sess;
		int mFlags;
		int spectatorClient;
		int lastCmdTime;
		int buttons;
		int oldbuttons;
		int latched_buttons;
		int buttonsSinceLastFrame;
		char pad3[0x2BC];
	};

	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	}; 
	
	struct EntHandle
	{
		unsigned __int16 number;
		unsigned __int16 infoIndex;
	}; 
	
	struct entityShared_t
	{
		char isLinked;
		char modelType;
		char svFlags;
		char isInUse;
		Bounds box;
		int contents;
		Bounds absBox;
		float currentOrigin[3];
		float currentAngles[3];
		EntHandle ownerNum;
		int eventTime;
	}; 

	struct gentity_s
	{
		entityState_s s;
		entityShared_t r;
		gclient_s* client;
		void /*Turret*/* turret;
		void /*Vehicle*/* vehicle;
		int physObjId;
		unsigned __int16 model;
		char physicsObject;
		char takedamage;
		char active;
		char handler;
		char team;
		bool freeAfterEvent;
		__int16 padding_short;
		short classname;
		unsigned __int16 script_classname;
		unsigned __int16 script_linkName;
		unsigned __int16 target;
		unsigned __int16 targetname;
		unsigned int attachIgnoreCollision;
		int spawnflags;
		int flags;
		int eventTime;
		int clipmask;
		int processedFrame;
		EntHandle parent;
		int nextthink;
		int health;
		int maxHealth;
		int damage;
		int count;
		EntHandle missileTargetEnt;
		EntHandle remoteControlledOwner;
		gentity_s* tagChildren;
		unsigned __int16 attachModelNames[19];
		unsigned __int16 attachTagNames[19];
		int useCount;
		gentity_s* nextFree;
		int birthTime;
		char pad[0x64];
	};

	union DvarValue 
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		char* string;
		float value;
		float vector[4];
		float color[4];
	};

	struct dvar_t
	{
		const char* name; 
		char pad[0x8];
		DvarValue current;
	};

	struct cmd_function_s
	{
		cmd_function_s *next;
		const char *name;
		const char *autoCompleteDir;
		const char *autoCompleteExt;
		void(__cdecl *function)();
		int flags;
	};

	struct BulletFireParams
	{
		int weaponEntIndex;
		int ignoreEntIndex;
		float damageMultiplier;
		int methodOfDeath;
		Vec3 origStart;
		Vec3 start;
		Vec3 end;
		Vec3 dir;
	};

	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0x0,
		TRACE_HITTYPE_ENTITY = 0x1,
		TRACE_HITTYPE_DYNENT_MODEL = 0x2,
		TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
		TRACE_HITTYPE_GLASS = 0x4,
	}; 
	
	struct trace_t
	{
		float fraction;
		Vec3 normal;
		int surfaceFlags;
		int contents;
		const char *material;
		TraceHitType hitType;
		unsigned short hitId;
		unsigned short modelIndex;
		unsigned short partName;
		unsigned short partGroup;
		bool allsolid;
		bool startsolid;
		bool walkable;
	};

	struct BulletTraceResults
	{
		trace_t trace;
		char pad0[0x04];
		Vec3 hitPos;
		char pad1[0x04];
		int depthSurfaceType;
		char pad2[0x04];
	};

	enum weapClass_t
	{
		WEAPCLASS_RIFLE = 0x0,
		WEAPCLASS_SNIPER = 0x1,
		WEAPCLASS_MG = 0x2,
		WEAPCLASS_SMG = 0x3,
		WEAPCLASS_SPREAD = 0x4,
		WEAPCLASS_PISTOL = 0x5,
		WEAPCLASS_GRENADE = 0x6,
		WEAPCLASS_ROCKETLAUNCHER = 0x7,
		WEAPCLASS_TURRET = 0x8,
		WEAPCLASS_THROWINGKNIFE = 0x9,
		WEAPCLASS_NON_PLAYER = 0xA,
		WEAPCLASS_ITEM = 0xB,
		WEAPCLASS_NUM = 0xC,
	}; 
	
	enum PenetrateType
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_COUNT = 0x4,
	}; 
	
	enum weapInventoryType_t
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORYCOUNT = 0x6,
	}; 
	
	enum weapFireType_t
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_SINGLESHOT = 0x1,
		WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
		WEAPON_FIRETYPECOUNT = 0x6,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
	}; 
	
	enum weapStance_t
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,
		WEAPSTANCE_NUM = 0x3,
	}; 
	
	union $C8D87EB0090687D323381DFB7A82089C
	{
		float slavePercentage;
		float masterPercentage;
	}; 
	
	struct SndCurve
	{
		const char *filename;
		unsigned __int16 knotCount;
		float knots[16][2];
	}; 
	
	struct MSSSpeakerLevels
	{
		int speaker;
		int numLevels;
		float levels[2];
	};

	struct MSSChannelMap
	{
		unsigned int speakerCount;
		MSSSpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char *name;
		MSSChannelMap channelMaps[2][2];
	}; 
	
	const struct snd_alias_t
	{
		const char *aliasName;
		const char *subtitle;
		const char *secondaryAliasName;
		const char *chainAliasName;
		const char *mixerGroup;
		void *soundFile;
		int sequence;
		float volMin;
		float volMax;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		$C8D87EB0090687D323381DFB7A82089C ___u15;
		float probability;
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		SndCurve *volumeFalloffCurve;
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		SpeakerMap *speakerMap;
	}; 
	
	struct snd_alias_list_t
	{
		const char *aliasName;
		snd_alias_t *head;
		unsigned int count;
	}; 
	
	enum activeReticleType_t
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	}; 
	
	enum ammoCounterClipType_t
	{
		AMMO_COUNTER_CLIP_NONE = 0x0,
		AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
		AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
		AMMO_COUNTER_CLIP_ROCKET = 0x4,
		AMMO_COUNTER_CLIP_BELTFED = 0x5,
		AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
		AMMO_COUNTER_CLIP_COUNT = 0x7,
	}; 
	
	enum weapOverlayReticle_t
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	enum WeapOverlayInteface_t
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
		WEAPOVERLAYINTERFACECOUNT = 0x3,
	}; 
	
	enum guidedMissileType_t
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_COUNT = 0x4,
	}; 
	
	enum weapProjExposion_t
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_NUM = 0x7,
	};

	enum WeapStickinessType
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_KNIFE = 0x5,
		WEAPSTICKINESS_COUNT = 0x6,
	}; 

	enum weapType_t
	{
		WEAPTYPE_BULLET = 0x0,
		WEAPTYPE_GRENADE = 0x1,
		WEAPTYPE_PROJECTILE = 0x2,
		WEAPTYPE_RIOTSHIELD = 0x3,
		WEAPTYPE_NUM = 0x4,
	};
	
	enum weaponIconRatioType_t
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,
		WEAPON_ICON_RATIO_COUNT = 0x3,
	}; 
	
	struct __declspec(align(4)) WeaponDef
	{
		const char *szOverlayName;
		void **gunXModel;
		void *handXModel;
		const char **szXAnimsRightHanded;
		const char **szXAnimsLeftHanded;
		const char *szModeName;
		unsigned __int16 *notetrackSoundMapKeys;
		unsigned __int16 *notetrackSoundMapValues;
		unsigned __int16 *notetrackRumbleMapKeys;
		unsigned __int16 *notetrackRumbleMapValues;
		int playerAnimType;
		weapType_t weapType;
		weapClass_t weapClass;
		PenetrateType penetrateType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		OffhandClass offhandClass;
		weapStance_t stance;
		void *viewFlashEffect;
		void *worldFlashEffect;
		snd_alias_list_t *pickupSound;
		snd_alias_list_t *pickupSoundPlayer;
		snd_alias_list_t *ammoPickupSound;
		snd_alias_list_t *ammoPickupSoundPlayer;
		snd_alias_list_t *projectileSound;
		snd_alias_list_t *pullbackSound;
		snd_alias_list_t *pullbackSoundPlayer;
		snd_alias_list_t *fireSound;
		snd_alias_list_t *fireSoundPlayer;
		snd_alias_list_t *fireSoundPlayerAkimbo;
		snd_alias_list_t *fireLoopSound;
		snd_alias_list_t *fireLoopSoundPlayer;
		snd_alias_list_t *fireStopSound;
		snd_alias_list_t *fireStopSoundPlayer;
		snd_alias_list_t *fireLastSound;
		snd_alias_list_t *fireLastSoundPlayer;
		snd_alias_list_t *emptyFireSound;
		snd_alias_list_t *emptyFireSoundPlayer;
		snd_alias_list_t *meleeSwipeSound;
		snd_alias_list_t *meleeSwipeSoundPlayer;
		snd_alias_list_t *meleeHitSound;
		snd_alias_list_t *meleeMissSound;
		snd_alias_list_t *rechamberSound;
		snd_alias_list_t *rechamberSoundPlayer;
		snd_alias_list_t *reloadSound;
		snd_alias_list_t *reloadSoundPlayer;
		snd_alias_list_t *reloadEmptySound;
		snd_alias_list_t *reloadEmptySoundPlayer;
		snd_alias_list_t *reloadStartSound;
		snd_alias_list_t *reloadStartSoundPlayer;
		snd_alias_list_t *reloadEndSound;
		snd_alias_list_t *reloadEndSoundPlayer;
		snd_alias_list_t *detonateSound;
		snd_alias_list_t *detonateSoundPlayer;
		snd_alias_list_t *nightVisionWearSound;
		snd_alias_list_t *nightVisionWearSoundPlayer;
		snd_alias_list_t *nightVisionRemoveSound;
		snd_alias_list_t *nightVisionRemoveSoundPlayer;
		snd_alias_list_t *altSwitchSound;
		snd_alias_list_t *altSwitchSoundPlayer;
		snd_alias_list_t *raiseSound;
		snd_alias_list_t *raiseSoundPlayer;
		snd_alias_list_t *firstRaiseSound;
		snd_alias_list_t *firstRaiseSoundPlayer;
		snd_alias_list_t *putawaySound;
		snd_alias_list_t *putawaySoundPlayer;
		snd_alias_list_t *scanSound;
		snd_alias_list_t **bounceSound;
		void *viewShellEjectEffect;
		void *worldShellEjectEffect;
		void *viewLastShotEjectEffect;
		void *worldLastShotEjectEffect;
		Material *reticleCenter;
		Material *reticleSide;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		activeReticleType_t activeReticleType;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		void **worldModel;
		void *worldClipModel;
		void *rocketModel;
		void *knifeModel;
		void *worldKnifeModel;
		Material *hudIcon;
		weaponIconRatioType_t hudIconRatio;
		Material *pickupIcon;
		weaponIconRatioType_t pickupIconRatio;
		Material *ammoCounterIcon;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		const char *szAmmoName;
		int iAmmoIndex;
		const char *szClipName;
		int iClipIndex;
		int iMaxAmmo;
		int shotCount;
		const char *szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int damage;
		int playerDamage;
		int iMeleeDamage;
		int iDamageType;
		int iFireDelay;
		int iMeleeDelay;
		int meleeChargeDelay;
		int iDetonateDelay;
		int iRechamberTime;
		int rechamberTimeOneHanded;
		int iRechamberBoltTime;
		int iHoldFireTime;
		int iDetonateTime;
		int iMeleeTime;
		int meleeChargeTime;
		int iReloadTime;
		int reloadShowRocketTime;
		int iReloadEmptyTime;
		int iReloadAddTime;
		int iReloadStartTime;
		int iReloadStartAddTime;
		int iReloadEndTime;
		int iDropTime;
		int iRaiseTime;
		int iAltDropTime;
		int quickDropTime;
		int quickRaiseTime;
		int iBreachRaiseTime;
		int iEmptyRaiseTime;
		int iEmptyDropTime;
		int sprintInTime;
		int sprintLoopTime;
		int sprintOutTime;
		int stunnedTimeBegin;
		int stunnedTimeLoop;
		int stunnedTimeEnd;
		int nightVisionWearTime;
		int nightVisionWearTimeFadeOutEnd;
		int nightVisionWearTimePowerUp;
		int nightVisionRemoveTime;
		int nightVisionRemoveTimePowerDown;
		int nightVisionRemoveTimeFadeInStart;
		int fuseTime;
		int aiFuseTime;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		Material *overlayMaterial;
		Material *overlayMaterialLowRes;
		Material *overlayMaterialEMP;
		Material *overlayMaterialEMPLowRes;
		weapOverlayReticle_t overlayReticle;
		WeapOverlayInteface_t overlayInterface;
		float overlayWidth;
		float overlayHeight;
		float overlayWidthSplitscreen;
		float overlayHeightSplitscreen;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsViewErrorMin;
		float adsViewErrorMax;
		void *physCollmap;
		float dualWieldViewModelOffset;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		float projLifetime;
		float timeToAccelerate;
		float projectileCurvature;
		void *projectileModel;
		weapProjExposion_t projExplosion;
		void *projExplosionEffect;
		void *projDudEffect;
		snd_alias_list_t *projExplosionSound;
		snd_alias_list_t *projDudSound;
		WeapStickinessType stickiness;
		float lowAmmoWarningThreshold;
		float ricochetChance;
		float *parallelBounce;
		float *perpendicularBounce;
		void *projTrailEffect;
		void *projBeaconEffect;
		float vProjectileColor[3];
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		void *projIgnitionEffect;
		snd_alias_list_t *projIgnitionSound;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float fightDist;
		float maxDist;
		const char *accuracyGraphName[2];
		float(*originalAccuracyGraphKnots[2])[2];
		unsigned __int16 originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		float accuracy;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char *szUseHintString;
		const char *dropHintString;
		int iUseHintStringIndex;
		int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char *szScript;
		float fOOPosAnimLength[2];
		int minDamage;
		int minPlayerDamage;
		float fMaxDamageRange;
		float fMinDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float *locationDamageMultipliers;
		const char *fireRumble;
		const char *meleeImpactRumble;
		void *tracerType;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		snd_alias_list_t *turretOverheatSound;
		void *turretOverheatEffect;
		const char *turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		snd_alias_list_t *turretBarrelSpinMaxSnd;
		snd_alias_list_t *turretBarrelSpinUpSnd[4];
		snd_alias_list_t *turretBarrelSpinDownSnd[4];
		snd_alias_list_t *missileConeSoundAlias;
		snd_alias_list_t *missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool inheritsPerks;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool armorPiercing;
		bool bBoltAction;
		bool aimDownSight;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool bClipOnly;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoReserveDisplay;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		bool noDualWield;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool bSegmentedReload;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool projExplosionEffectForceNormalUp;
		bool bProjImpactExplode;
		bool stickToPlayers;
		bool hasDetonator;
		bool disableFiring;
		bool timedDetonation;
		bool rotate;
		bool holdButtonToThrow;
		bool freezeMovementWhenFiring;
		bool thermalScope;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
	};

	enum ImpactType
	{
		IMPACT_TYPE_NONE = 0x0,
		IMPACT_TYPE_BULLET_SMALL = 0x1,
		IMPACT_TYPE_BULLET_LARGE = 0x2,
		IMPACT_TYPE_BULLET_AP = 0x3,
		IMPACT_TYPE_BULLET_EXPLODE = 0x4,
		IMPACT_TYPE_SHOTGUN = 0x5,
		IMPACT_TYPE_SHOTGUN_EXPLODE = 0x6,
		IMPACT_TYPE_GRENADE_BOUNCE = 0x7,
		IMPACT_TYPE_GRENADE_EXPLODE = 0x8,
		IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
		IMPACT_TYPE_PROJECTILE_DUD = 0xA,
		IMPACT_TYPE_COUNT = 0xB,
	}; 
	
	struct WeaponCompleteDef
	{
		const char *szInternalName;
		WeaponDef *weapDef;
		const char *szDisplayName;
		unsigned __int16 *hideTags;
		const char **szXAnims;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType impactType;
		int iFireTime;
		weaponIconRatioType_t dpadIconRatio;
		float bulletPenetrationMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char *szAltWeaponName;
		unsigned int altWeaponIndex;
		int iAltRaiseTime;
		Material *killIcon;
		Material *dpadIcon;
		int fireAnimLength;
		int iFirstRaiseTime;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned __int16 accuracyGraphKnotCount[2];
		float(*accuracyGraphKnots[2])[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
	};

	enum connstate_t
	{
		CA_DISCONNECTED = 0x0,
		CA_CINEMATIC = 0x1,
		CA_LOGO = 0x2,
		CA_CONNECTING = 0x3,
		CA_CHALLENGING = 0x4,
		CA_CONNECTED = 0x5,
		CA_SENDINGSTATS = 0x6,
		CA_LOADING = 0x7,
		CA_PRIMED = 0x8,
		CA_ACTIVE = 0x9,
	};

	enum clientMigState_t
	{
		CMSTATE_INACTIVE = 0x0,
		CMSTATE_OLDHOSTLEAVING = 0x1,
		CMSTATE_LIMBO = 0x2,
		CMSTATE_NEWHOSTCONNECT = 0x3,
		CMSTATE_COUNT = 0x4,
	};

	struct ScreenPlacement
	{
		char pad[0x20];
		Vec2 realViewportSize;
	};

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

#pragma pack(push, 4)
	struct kbutton_t
	{
		int down[2];
		unsigned int downtime;
		unsigned int msec;
		bool active;
		bool wasPressed;
	};
#pragma pack(pop)

	enum clientState_t
	{
		CS_FREE = 0,
		CS_ZOMBIE = 1,
		CS_UNKNOWN = 2,
		CS_CONNECTED = 3,
		CS_PRIMED = 4,
		CS_ACTIVE = 5
	};

	struct clientHeader_t
	{
		clientState_t state;
		int sendAsActive;
		int deltaMessage;
		int rateDelayed;
		int hasAckedBaselineData;
		int hugeSnapshotSent;
		netchan_t netchan;
		char pad[0x14];
	};

	struct svscmd_info_t
	{
		char cmd[1024];
		int time;
		int type;
	};

	struct client_t
	{
		clientHeader_t header;
		const char *dropReason;
		char userinfo[1024];
		svscmd_info_t reliableCommandInfo[128];
		int reliableSequence;
		int reliableAcknowledge;
		int reliableSent;
		int messageAcknowledge;
		int gamestateMessageNum;
		int challenge;
		usercmd_s lastUsercmd;
		int lastClientCommand;
		char lastClientCommandString[1024];
		gentity_s *gentity;
		char name[16];
		char pad[0x2083C];
		int bIsTestClient;
		int serverId;
		char pad2[0x2404];
		std::uint64_t steamId;
		bool sendMatchData;
		char pad3[0x62880];
	};

	struct sv_clients_t
	{
		int maxClients;
		char pad[0x4];
		client_t clients[18];
	};

	struct ReliableCommands
	{
		int sequence;
		int acknowledge;
		char commands[128][1024];
	};

	struct clientConnection_t
	{
		int qport;
		ClientNum_t clientNum;
		int lastPacketSentTime;
		int lastPacketTime;
		netadr_t serverAddress; 
		int connectTime;
		int connectPacketCount;
		char serverMessage[256];
		int challenge;
		int checksumFeed;
		ReliableCommands reliableCommands;
		int serverMessageSequence;
		int serverCommandSequence;
		int lastExecutedServerCommand;
		char serverCommands[128][1024];
		bool isServerRestarting;
		char pad[0x70];
		netchan_t netchan;
	};

	enum NATType
	{
		NAT_UNKNOWN = 0,
		NAT_OPEN = 1,
		NAT_MODERATE = 2,
		NAT_STRICT = 3
	};

	struct stats_t
	{
		std::uint32_t experience;
		char pad0[0x4];
		std::uint32_t prestige;
		char pad1[0x627];
		char weaponChallenges[284];
		char perkChallenges[16];
		char miscChallenges[187];
	};

	struct ucmd_t
	{
		char *name;
		void(*func)(client_t*);
		int allowFromOldServer;
	};

	struct DvarClientInfo
	{
		char* dvar;
		char* value;
	};

	struct MapnameRichPresenceInfo
	{
		char mapname[32];
		int context;
		int mapPack;
	};

	enum PartyStatus
	{
		PARTYSTATUS_EMPTY = 0x0,
		PARTYSTATUS_ZOMBIE = 0x1,
		PARTYSTATUS_ANONYMOUS = 0x2,
		PARTYSTATUS_PRESENT = 0x3,
		PARTYSTATUS_TESTCLIENT = 0x4,
		PARTYSTATUS_COUNT = 0x5,
	};

	struct DeferredMsg
	{
		game::netadr_t addr;
		char data[1400];
		int datalen;
	};

	struct DeferredQueue
	{
		DeferredMsg msgs[16];
		volatile int get;
		volatile int send;
	};

	enum RagdollBodyState
	{
		BS_DEAD = 0x0,
		BS_DOBJ_WAIT = 0x1,
		BS_VELOCITY_CAPTURE = 0x2,
		BS_TUNNEL_TEST = 0x3,
		BS_RUNNING = 0x4,
		BS_IDLE = 0x5,
		RAGDOLL_NUM_STATES = 0x6,
	};

	struct RagdollBody
	{
		int references;
		int ragdollDef;
		int dobj;
		void *obj;
		void *pose;
		Vec3 poseOffset;
		LocalClientNum_t localClientNum;
		RagdollBodyState state;
		int stateMsec;
		int stateFrames;
		char pad[0xA10];
	};

	struct StateEnt
	{
		bool(__cdecl *enterFunc)(RagdollBody *, RagdollBodyState, RagdollBodyState);
		bool(__cdecl *exitFunc)(RagdollBody *, RagdollBodyState, RagdollBodyState);
		void(__cdecl *updateFunc)(RagdollBody *, int);
	};
}