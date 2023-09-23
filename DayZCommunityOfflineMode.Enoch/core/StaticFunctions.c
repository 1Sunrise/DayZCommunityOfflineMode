static string COM_FormatFloat( float value, int decimals ) 
{
    if ( !value.ToString().Contains(".") ) return value.ToString();
	
    string result = "";
    array<string> output = new array<string>;

    value.ToString().Split(".", output);

    if ( output.Count() == 0 ) return value.ToString();

    if ( decimals == 0 ) return output.Get(0);

    string right = output.Get(1).Substring(0, decimals);
    result = output.Get(0) + "." + right;
    return result;
}

static string COM_VectorToString( vector vec )
{
    string result = vec.ToString();
    result.Replace( "<", "" );
    result.Replace( ">", "" );
    result.Replace( ",", "" );

    return result;
}

static string COM_VectorToString( vector vec, int decimals ) 
{
    string result = "";
    result = COM_FormatFloat(vec[0], decimals) + "|" + COM_FormatFloat(vec[1], decimals) + "|" + COM_FormatFloat(vec[2], decimals);

    return result;
}

static TStringArray COM_GetChildrenFromBaseClass( string strConfigName, string strBaseClass )
{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    TStringArray class_names = new TStringArray;

    for (int p = 0; p < count; p++)
    {
        GetGame().ConfigGetChildName ( strConfigName, p, child_name );

        if ( GetGame().IsKindOf(child_name, strBaseClass ) && ( child_name != strBaseClass ) )
        {
            class_names.Insert(child_name);
        }
    }

    return class_names;
}

static TVectorArray COM_GetSpawnPoints()
{
    return { "1509.023926 182.689377 7440.780762" };
}

static set< Object > COM_GetObjectsAt( vector from, vector to, Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector contact_pos;
    vector contact_dir;
    int contact_component;

    set< Object > geom = new set< Object >;
    set< Object > view = new set< Object >;

    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius );
    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, view, with, ignore, false, false, ObjIntersectView, radius );

    if ( geom.Count() > 0 ) 
    {
        return geom;
    }
    if ( view.Count() > 0 ) 
    {
        return view;
    }
    return NULL;
}

static Object COM_GetPointerObject( Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector dir = GetGame().GetPointerDirection();

    vector from = GetGame().GetCurrentCameraPosition();

    vector to = from + ( dir * 10000 );

    auto objs = COM_GetObjectsAt( from, to, ignore, radius, with );

    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
    }

    return NULL;
}

static Object COM_GetCursorObject()
{
    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;

    auto objs = COM_GetObjectsAt( rayStart, rayEnd );

    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
    }

    return NULL;
}

static vector COM_GetPointerPos()
{
    if ( !COM_GetPB() )
    {
        return "0 0 0";
    }

    vector dir = GetGame().GetPointerDirection();

    vector from = GetGame().GetCurrentCameraPosition();

    vector to = from + ( dir * 10000 );

    vector rayStart = from;
    vector rayEnd = to;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, COM_GetPB());

    return hitPos;
}

static vector COM_GetCursorPos()
{
    if ( !COM_GetPB() )
    {
        return "0 0 0";
    }

    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, COM_GetPB());

    return hitPos;
}

static void COM_Message( string txt ) 
{
    COM_GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", txt, ""));
}

static Weapon COM_GetWeaponInHands()
{
    Weapon weapon_in_hands;
    if( COM_GetPB() && COM_GetPB().GetItemInHands() ) Class.CastTo(weapon_in_hands,  COM_GetPB().GetItemInHands());

    return weapon_in_hands;
}

static MissionBase COM_GetMission()
{
    return MissionBase.Cast( GetGame().GetMission() );
}

static CommunityOfflineClient COM_GetClientMission()
{
    return CommunityOfflineClient.Cast( GetGame().GetMission() );
}

static CommunityOfflineServer COM_GetServerMission()
{
    return CommunityOfflineServer.Cast( GetGame().GetMission() );
}

static PlayerBase COM_GetPB()
{
    return PlayerBase.Cast( GetGame().GetPlayer() );
}

static bool COM_SHIFT()
{
    return( ( KeyState( KeyCode.KC_LSHIFT ) > 0 ) || ( KeyState( KeyCode.KC_RSHIFT ) > 0 ) );
}

static bool COM_CTRL()
{
    return( ( KeyState( KeyCode.KC_LCONTROL ) > 0 ) || ( KeyState( KeyCode.KC_RCONTROL ) > 0 ) );
}

static bool COM_ALT()
{
    return( ( KeyState( KeyCode.KC_LMENU ) > 0 ) || ( KeyState( KeyCode.KC_RMENU ) > 0 ) );
}

static bool COM_WINKEY()
{
    return( ( KeyState( KeyCode.KC_LWIN ) > 0 ) || ( KeyState( KeyCode.KC_RWIN ) > 0 ) );
}

/* 
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
static Weapon_Base COM_CreateWeapon( PlayerBase oPlayer )
{
    Weapon_Base oWpn1 = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( "M4A1_Black" ));
    oWpn1.GetInventory().CreateAttachment( "M4_Suppressor" );
    oWpn1.GetInventory().CreateAttachment( "M4_RISHndgrd_Black" );
    oWpn1.GetInventory().CreateAttachment( "M4_MPBttstck_Black" );
    EntityAI optic = oWpn1.GetInventory().CreateAttachment( "ACOGOptic" )

    return oWpn1;
}
 */

/* 
static Weapon_Base COM_CreateWeapon( PlayerBase oPlayer )
{
    Weapon_Base oWpn1 = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( "M4A1_Black" ));
    oWpn1.GetInventory().CreateAttachment( "M4_Suppressor" );
	oWpn1.GetInventory().CreateAttachment( "M4_RISHndgrd_Black" );
    oWpn1.GetInventory().CreateAttachment( "M4_CQBBttstck_Black" );
    EntityAI optic = oWpn1.GetInventory().CreateAttachment( "ACOGOptic" );
//    optic.GetInventory().CreateAttachment("Battery9V");
	oWpn1.GetInventory().CreateAttachment( "Mag_STANAGCoupled_30Rnd" );

    return oWpn1;
}
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
 */

// ОТВЕЧАЕТ ЗА СБОРКУ ОРУЖИЯ В **@PlayerBase** ЗА ПАРАМЕТР **@Weapon_Base oWpn** (СОЗДАНИЕ ОРУЖИЯ)

static Weapon_Base COM_CreateAkm( PlayerBase oPlayer, string sWeapon )
{
    Weapon_Base Akm = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( sWeapon ));
	Akm.GetInventory().CreateAttachment( "AK_Suppressor" );
    Akm.GetInventory().CreateAttachment( "AK_WoodHndgrd" );
    Akm.GetInventory().CreateAttachment( "AK_WoodBttstck" );
    EntityAI optic = Akm.GetInventory().CreateAttachment( "PSO1Optic" );
	//optic.GetInventory().CreateAttachment( "Battery9V" );
	Akm.GetInventory().CreateAttachment( "Mag_AKM_Drum75Rnd" );
    return Akm;
}

static Weapon_Base COM_CreateFal( PlayerBase oPlayer, string sWeapon )
{
    Weapon_Base Fal = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( sWeapon ));
    Fal.GetInventory().CreateAttachment( "Fal_OeBttstck" );
    Fal.GetInventory().CreateAttachment( "Mag_FAL_20Rnd" );
    EntityAI optic = Fal.GetInventory().CreateAttachment( "ACOGOptic" );
	//optic.GetInventory().CreateAttachment( "Battery9V" );
	Fal.GetInventory().CreateAttachment( "ImprovisedSuppressor" );
    return Fal;
}

static Weapon_Base COM_CreateWinchester( PlayerBase oPlayer, string sWeapon )
{
    Weapon_Base Winchester = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( sWeapon ));
    Winchester.GetInventory().CreateAttachment( "HuntingOptic" );
	Winchester.GetInventory().CreateAttachment( "ImprovisedSuppressor" );
    return Winchester;
}

static Weapon_Base COM_CreateM4( PlayerBase oPlayer, string sWeapon )
{
    Weapon_Base M4 = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( sWeapon ));
    M4.GetInventory().CreateAttachment( "M4_Suppressor" );
    M4.GetInventory().CreateAttachment( "M4_RISHndgrd_Black" );
    M4.GetInventory().CreateAttachment( "M4_CQBBttstck" );
    EntityAI optic = M4.GetInventory().CreateAttachment( "ACOGOptic" )
	M4.GetInventory().CreateAttachment( "Mag_STANAGCoupled_30Rnd" );
    return M4;
}

// СОЗДАНИЕ КАСТОМНОГО СПАВНА ПЕРСОНАЖА

static PlayerBase COM_CreateCustomDefaultCharacter()
{
    PlayerBase oPlayer = PlayerBase.Cast( GetGame().CreatePlayer( NULL, GetGame().CreateRandomPlayer(), COM_GetSpawnPoints().GetRandomElement(), 0, "NONE") );

	oPlayer.GetInventory().CreateInInventory( "Mich2001Helmet" );
	oPlayer.GetInventory().CreateInInventory( "BalaclavaMask_Green" );
	oPlayer.GetInventory().CreateInInventory( "TacticalGoggles" );
	oPlayer.GetInventory().CreateInInventory( "BDUJacket" );
	oPlayer.GetInventory().CreateInInventory( "BDUPants" );
	oPlayer.GetInventory().CreateInInventory( "TortillaBag" );
	oPlayer.GetInventory().CreateInInventory( "MilitaryBoots_Black" );
	oPlayer.GetInventory().CreateInInventory( "TacticalGloves_Green" );
	

/*  oPlayer.GetInventory().CreateInInventory( "TacticalGoggles" );
    oPlayer.GetInventory().CreateInInventory( "RM_Mich2001_CRDF" ); 
    oPlayer.GetInventory().CreateInInventory( "RM_Balaclava_CRDF" ); 
    oPlayer.GetInventory().CreateInInventory( "RM_TacticalShirt_CRDF" ); 
    oPlayer.GetInventory().CreateInInventory( "RM_TacticalGloves_CRDF" );
    oPlayer.GetInventory().CreateInInventory( "RM_CargoPants_CRDF" ); 
    oPlayer.GetInventory().CreateInInventory( "MilitaryBoots_Black" ); 
    oPlayer.GetInventory().CreateInInventory( "RM_TortillaBag_CRDF" ); 
	oPlayer.GetInventory().CreateInInventory( "RM_Platecarrier_CRDF" ); 
*/
	
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
	oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );
    oPlayer.GetInventory().CreateInInventory( "Ammo_308WinTracer" );

	oPlayer.GetInventory().CreateInInventory( "WeaponCleaningKit" );
	oPlayer.GetInventory().CreateInInventory( "WeaponCleaningKit" );
	oPlayer.GetInventory().CreateInInventory( "WeaponCleaningKit" );
	oPlayer.GetInventory().CreateInInventory( "WeaponCleaningKit" );
	
	/* 
    oPlayer.GetInventory().CreateInInventory( "Winchester70" );
	oPlayer.GetInventory().CreateInInventory( "HuntingOptic" );
	oPlayer.GetInventory().CreateInInventory( "ImprovisedSuppressor" );
	
	oPlayer.GetInventory().CreateInInventory( "SVD" );
	oPlayer.GetInventory().CreateInInventory( "Mag_SVD_10Rnd" );
	oPlayer.GetInventory().CreateInInventory( "PSO1Optic" );
	oPlayer.GetInventory().CreateInInventory( "AK_Suppressor" );
	
	oPlayer.GetInventory().CreateInInventory( "FAL" );
	oPlayer.GetInventory().CreateInInventory( "Fal_OeBttstck" );
	oPlayer.GetInventory().CreateInInventory( "Mag_FAL_20Rnd" );
	oPlayer.GetInventory().CreateInInventory( "ACOGOptic" );
	oPlayer.GetInventory().CreateInInventory( "ImprovisedSuppressor" ); 
	*/

//-----------------------------------------------------------------------

	// 	СПАВН АКM
	//Weapon_Base Akm = COM_CreateAkm( oPlayer, "AKM" );

//	СПАВН M4
	Weapon_Base M4 = COM_CreateM4( oPlayer, "M4A1_Black" );

// 	СПАВН FAL
	Weapon_Base Fal = COM_CreateFal( oPlayer, "FAL" );
	
// 	СПАВН WINCHESTER70
	Weapon_Base Winchester = COM_CreateWinchester( oPlayer, "Winchester70" );
	
//-----------------------------------------------------------------------

	/* ПАРАМЕТР ОТВЕЧАЕТ БУДЕТ ЛИ ОРУЖИЕ СПАВНИТЬСЯ В РУКАХ СРАЗУ ПОСЛЕ СПАВНА ПЕРСОНАЖА */

//    oPlayer.PredictiveTakeEntityToHands( Akm );
	oPlayer.PredictiveTakeEntityToHands( M4 );

//-----------------------------------------------------------------------

	/* ПАРАМЕТР ОТВЕЧАЕТ ЗА ПРЕДМЕТЫ В ХОТБАР ПАНЕЛИ */

	/* oPlayer.SetQuickBarEntityShortcut( Akm, 0, true ); */
	oPlayer.SetQuickBarEntityShortcut( M4, 0, true );
//	oPlayer.SetQuickBarEntityShortcut( Fal, 1, true );
	oPlayer.SetQuickBarEntityShortcut( Winchester, 2, true );
//    oPlayer.SetQuickBarEntityShortcut( oMag, 1, true );

//-----------------------------------------------------------------------
    return oPlayer;
}

static string COM_FileAttributeToString( FileAttr attr )
{
    string fileType = "";
    if ( attr & FileAttr.DIRECTORY )
    {
        fileType = fileType + "DIRECTORY";
    }
    if ( attr & FileAttr.HIDDEN )
    {
        fileType = fileType + "HIDDEN";
    }
    if ( attr & FileAttr.READONLY )
    {
        fileType = fileType + "READONLY";
    }
    if ( attr & FileAttr.INVALID )
    {
        fileType = fileType + "INVALID";
    }
    return fileType;
}

static vector COM_SnapToGround(vector pos)
{
    float pos_x = pos[0];
    float pos_z = pos[2];
    float pos_y = GetGame().SurfaceY( pos_x, pos_z );
    vector tmp_pos = Vector( pos_x, pos_y, pos_z );
    tmp_pos[1] = tmp_pos[1] + pos[1];

    return tmp_pos;
}

static bool m_COM_GodMode; // move these to player saves? Edit: Jacob says "yes"
static bool m_COM_OldAiming;
static bool COM_bc_Visible;

static void COM_SnapToGroundNew( Object object ) 
{
    vector pos = object.GetPosition();
    pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
    
    vector clippingInfo[2];
    vector objectBBOX[2];
    
    object.GetCollisionBox( objectBBOX );
    object.ClippingInfo( clippingInfo );

    //float clipY = objectBBOX[1][1] / 2.0//- clippingInfo[0][1];
    //pos[1] = pos[1] + objectBBOX[1][1] - clipY;
    pos[1] = pos[1] + clippingInfo[1][1] / 2.0;//objectBBOX[0][1] - clipY

    object.SetPosition(pos);

    COM_ForceTargetCollisionUpdate( object );
}

static void COM_ForceTargetCollisionUpdate( Object oObj )
{
    if ( !oObj ) return;

    vector roll = oObj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    oObj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    oObj.SetOrientation( roll );
}

static void COM_ToggleCursor()
{
    if ( GetGame().GetInput().HasGameFocus( INPUT_DEVICE_MOUSE ) )
    {
        GetGame().GetInput().ChangeGameFocus( 1 );
        GetGame().GetUIManager().ShowUICursor( true );
    }
    else
    {
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetInput().ResetGameFocus();
    }
}

/*
    Token types:
     0 - error, no token
     1 - defined token (special characters etc. . / * )
     2 - quoted string. Quotes are removed -> TODO
     3 - alphabetic string
     4 - number
     5 - end of line -> TODO
*/
static bool COM_CheckStringType( string str, int type ) 
{
    for(int i = 0; i<str.Length(); i++ ) 
    {
        string character = str.Get(i);
        string token;
        int result = character.ParseStringEx(token);
        if ( result == type ) return true;
    }
    return false;
}

string COM_GetRandomChildFromBaseClass( string strConfigName, string strBaseClass, int minScope = -1 )
{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    array< string > class_names = new array<string>;

    for ( int p = 0; p < count; p++ )
    {
        GetGame().ConfigGetChildName( strConfigName, p, child_name );

        if( ( minScope != -1 ) && ( GetGame().ConfigGetInt( strConfigName + " " + child_name + " scope" ) < minScope ) ) continue;

        if ( GetGame().IsKindOf( child_name, strBaseClass ) && ( child_name != strBaseClass ) )
        {
            class_names.Insert( child_name );
        }
    }

    return class_names.GetRandomElement();
}