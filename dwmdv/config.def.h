/* appearance */
static unsigned int borderpx    = 3;  /* border width */
static const unsigned int gappx = 0;  /* gaps between windows */
static unsigned int snap        = 7;  /* snap pixel */
static int showbar              = 1;  /* 0 means no bar */
static int topbar               = 1;  /* 0 means bottom bar */
static int autoraise_floating   = 1;  /* Autoraise on focus */
static const char *fonts[]      = { "monospace:size=10" };
static const char dmenufont[]   = "monospace:size=10";

/*
 * 0 means no systray
 *  
 * 0: sloppy systray follows selected monitor, 
 * >0: pin systray to monitor X 
 *
 * 0: systray in the right corner, 
 * >0: systray on left of status text 
 * 
 * systray spacing 
 *
 * 1: if fail display systray on the first monitor 
 * 0: display systray on the last monitor
*/

static const int showsystray             = 1;
static const unsigned int systraypinning = 0;   
static const unsigned int systrayonleft  = 0;    
static const unsigned int systrayspacing = 2;   
static const int systraypinningfailfirst = 1;   

/* 
 * This build works with Xresources and therefore pywal 
 * so if you load a wal colorscheme with the custom template 
 * the colors will apply if you press the keybind (MODKEY+r)
 * the colors defined below are fallback colors.
 * In order to apply Xresources when starting x you need to
 * add 'xrdb -merge ~/.Xresources' to .xinitrc
*/

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#002433";
static char normfgcolor[]           = "#aaaaaa";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    
	{ "><>",      NULL },   
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = 
{ "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL }; // Change terminal as per use case
static const char *browser[] = { "zen", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

/* 
 * Brightess and volume keys use brightnessctl and pamixer respectively
 * THis is for laptop so you your keyboard dosent have volume keys 
 * you can use modkey up arrow, down arrow and left to controll volume
*/

#include <X11/XF86keysym.h>
static Key keys[] = {
    { 0,XF86XK_MonBrightnessUp,     spawn,          SHCMD("brightnessctl set 10%+ && pkill -RTMIN+2 slstatus") },
 	{ 0,XF86XK_MonBrightnessDown,   spawn,          SHCMD("brightnessctl set 10%- && pkill -RTMIN+2 slstatus") },
    { 0,XF86XK_AudioLowerVolume,    spawn,          SHCMD("pamixer --decrease 5 && pkill -RTMIN+1 slstatus") },
    { 0,XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pamixer --increase 5 && pkill -RTMIN+1 slstatus") },
	{ 0,XF86XK_AudioMute,           spawn,          SHCMD("pamixer --toggle-mute && pkill -RTMIN+1 slstatus") },
	{ MODKEY,            XK_8,      spawn,          SHCMD("pamixer --decrease 5 && pkill -RTMIN+1 slstatus") },
	{ MODKEY,            XK_9,      spawn,          SHCMD("pamixer --increase 5 && pkill -RTMIN+1 slstatus") },
    { MODKEY,            XK_0,      spawn,          SHCMD("playerctl play-pause")  },
	{ MODKEY,            XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,            XK_w,      spawn,          {.v = browser } },
	{ MODKEY,            XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,            XK_b,      togglebar,      {0} },
	{ MODKEY,            XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,            XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,            XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,            XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,            XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,            XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,  XK_Return, zoom,           {0} },
	{ MODKEY,            XK_Tab,    view,           {0} },
	{ MODKEY,            XK_q,      killclient,     {0} },
	{ MODKEY,            XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,            XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,            XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,            XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,  XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,  XK_f,      togglefullscr,  {0} },
	{ MODKEY,            XK_6,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,  XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,            XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,            XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,  XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,  XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            XK_minus,  setgaps,        {.i = -3 } },
	{ MODKEY,            XK_plus,   setgaps,        {.i = +3 } },
	{ MODKEY|ShiftMask,  XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(             XK_1,                      0)
	TAGKEYS(             XK_2,                      1)
	TAGKEYS(             XK_3,                      2)
	TAGKEYS(             XK_4,                      3)
	{ MODKEY|ShiftMask,  XK_q,      quit,           {0} },

	// Keybinds to move windows in floating mode
	{ MODKEY,                       XK_Down,  moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,    moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right, moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,  moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,  moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,    moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right, moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,  moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,    moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,  moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,  moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right, moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,    moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,  moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,  moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right, moveresizeedge, {.v = "R"} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

